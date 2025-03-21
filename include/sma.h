#ifndef SMA_H
#define SMA_H

#include "base_optimizer.h"
#include <vector>
#include <functional>
#include <random>

/**
 * @brief Slime Mold Algorithm (SMA) optimizer.
 */
class SMA : public BaseOptimizer {
public:
    /**
     * @brief Construct a new SMA object.
     *
     * @param num_individuals Number of agents.
     * @param dim Dimensionality of the search space.
     * @param lower_bound Lower bound of the search space.
     * @param upper_bound Upper bound of the search space.
     * @param max_iter Maximum number of iterations.
     * @param c1 Coefficient for attraction toward the best solution.
     * @param c2 Coefficient for random variation.
     * @param w Inertia weight (scaling factor).
     * @param minimize True for minimization problems.
     * @param verbose Enable verbose output.
     * @param seed Random seed.
     * @param random_init_positions If true, initialize positions randomly; otherwise, all zeros.
     * @param use_w_decrement If true, linearly decrease inertia weight.
     * @param w_start Starting inertia weight (if decrement is used).
     * @param w_end Ending inertia weight (if decrement is used).
     * @param store_history_each_iter If true, store population history each iteration.
     */
    SMA(int num_individuals,
        int dim,
        double lower_bound,
        double upper_bound,
        int max_iter,
        double c1,
        double c2,
        double w,
        bool minimize = true,
        bool verbose = false,
        int seed = 42,
        bool random_init_positions = true,
        bool use_w_decrement = false,
        double w_start = 0.9,
        double w_end = 0.4,
        bool store_history_each_iter = false);

    virtual ~SMA() {}

    // Base class overrides with snake_case names.
    void set_objective(std::function<double(const std::vector<double>&)> obj) override;
    void optimize(int iterations) override;
    std::vector<double> get_best_solution() const override;
    double get_best_fitness() const override;

    /**
     * @brief Retrieve the population history.
     *
     * @return std::vector<std::vector<std::vector<double>>> Population history.
     */
    std::vector<std::vector<std::vector<double>>> get_population_history() const;

    /**
     * @brief Update positions for debugging/stepping purposes.
     *
     * @param iteration Current iteration.
     */
    void update_positions(int iteration);

private:
    std::function<double(const std::vector<double>&)> objective_function;
    int max_iter;
    double c1, c2;
    double w;  // Current inertia scaling factor.
    bool minimize;
    bool verbose;

    // Toggles and parameters.
    bool random_init_positions;
    bool use_w_decrement;
    double w_start;
    double w_end;
    bool store_history_each_iter;

    std::mt19937 rng;

    // Particle positions and fitness values.
    std::vector<std::vector<double>> positions;
    std::vector<double> fitness;

    // Global best position and fitness.
    std::vector<double> best_position;
    double best_fitness;

    // Population history.
    std::vector<std::vector<std::vector<double>>> population_history;

    // Helper methods.
    void initialize_positions();
    void enforce_bounds(std::vector<double>& individual);
    void update_inertia(int iteration, int total_iters);
};

#endif // SMA_H
