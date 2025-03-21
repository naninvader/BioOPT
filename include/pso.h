#ifndef PSO_H
#define PSO_H

#include "base_optimizer.h"
#include <vector>
#include <functional>
#include <random>

/**
 * @brief Particle Swarm Optimization (PSO) optimizer.
 */
class PSO : public BaseOptimizer {
public:
    /**
     * @brief Construct a new PSO object.
     *
     * @param num_individuals Number of particles.
     * @param dim Dimensionality of the search space.
     * @param lower_bound Lower bound of the search space.
     * @param upper_bound Upper bound of the search space.
     * @param max_iter Maximum number of iterations.
     * @param c1 Cognitive coefficient.
     * @param c2 Social coefficient.
     * @param w Inertia weight.
     * @param v_max Maximum velocity (0.0 implies no clamping).
     * @param minimize True for minimization problems.
     * @param verbose Enable verbose output.
     * @param seed Random seed.
     * @param velocity_init_random If true, initialize velocities randomly.
     * @param use_ring_topology If true, use ring topology for local best.
     * @param neighbor_size Neighborhood size for ring topology.
     * @param use_w_decrement If true, linearly decrease inertia weight.
     * @param w_start Starting inertia weight (if decrement is used).
     * @param w_end Ending inertia weight (if decrement is used).
     * @param store_history_each_iter If true, store history of positions.
     */
    PSO(int num_individuals, int dim,
        double lower_bound, double upper_bound,
        int max_iter, double c1, double c2,
        double w, double v_max = 0.0,
        bool minimize = true, bool verbose = false,
        int seed = 42,
        bool velocity_init_random = true,
        bool use_ring_topology = false,
        int neighbor_size = 1,
        bool use_w_decrement = false,
        double w_start = 0.9,
        double w_end = 0.4,
        bool store_history_each_iter = false);

    virtual ~PSO() {}

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

private:
    std::function<double(const std::vector<double>&)> objective_function;

    // Core configuration parameters.
    int max_iter;
    double c1, c2, w, v_max;
    bool minimize;
    bool verbose;

    // Optional toggles.
    bool velocity_init_random;
    bool use_ring_topology;
    int neighbor_size;
    bool use_w_decrement;
    double w_start, w_end;
    bool store_history_each_iter;

    std::mt19937 rng;

    // Particle data.
    std::vector<std::vector<double>> positions;
    std::vector<std::vector<double>> velocities;
    std::vector<std::vector<double>> pbest_positions;
    std::vector<double> pbest_fitness;

    // Global best solution.
    std::vector<double> gbest_position;
    double gbest_fitness;

    // Population history.
    std::vector<std::vector<std::vector<double>>> population_history;

    // Helper methods.
    void initialize_particles();
    void update_positions(int iteration);
    int get_local_best_index(int i);
    void update_inertia(int iteration, int total_iters);
    void clamp_velocity(std::vector<double>& velocity);
    void enforce_bounds(std::vector<double>& individual);
};

#endif // PSO_H
