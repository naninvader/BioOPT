#ifndef GA_H
#define GA_H

#include "base_optimizer.h"
#include <vector>
#include <functional>
#include <random>

/**
 * @brief Genetic Algorithm (GA) optimizer with extra configurable parameters.
 */
class GA : public BaseOptimizer {
public:
    /**
     * @brief Construct a new GA object.
     *
     * @param num_individuals Population size.
     * @param dim Dimensionality of the solution vector.
     * @param lower_bound Lower bound for each gene.
     * @param upper_bound Upper bound for each gene.
     * @param max_iter Number of generations (iterations).
     * @param minimize True for minimization problems.
     * @param verbose Enable verbose output.
     * @param seed Random seed.
     * @param crossover_rate Probability of gene crossover.
     * @param mutation_rate Mutation probability per gene.
     * @param tournament_size Tournament size for selection (default: 2).
     * @param elitism_count Number of elite individuals to preserve (default: 1).
     * @param use_uniform_crossover If true, use uniform crossover; otherwise, single-point.
     * @param use_gaussian_mutation If true, use Gaussian mutation; otherwise, random-reset.
     * @param mutation_std Standard deviation for Gaussian mutation (if 0, defaults to 10% of range).
     * @param store_history_each_iter If true, store population history each iteration.
     */
    GA(int num_individuals,
       int dim,
       double lower_bound,
       double upper_bound,
       int max_iter,
       bool minimize = true,
       bool verbose = false,
       int seed = 42,
       double crossover_rate = 0.7,
       double mutation_rate = 0.01,
       int tournament_size = 2,
       int elitism_count = 1,
       bool use_uniform_crossover = true,
       bool use_gaussian_mutation = false,
       double mutation_std = 0.0, // if 0, will be set to (upper_bound - lower_bound) * 0.1
       bool store_history_each_iter = false);

    virtual ~GA() {}

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

    // GA configuration parameters.
    int max_iter;
    bool minimize;
    bool verbose;
    double crossover_rate;
    double mutation_rate;
    int tournament_size;
    int elitism_count;
    bool use_uniform_crossover;
    bool use_gaussian_mutation;
    double mutation_std;
    bool store_history_each_iter;

    std::mt19937 rng;

    // Population data.
    std::vector<std::vector<double>> population;
    std::vector<double> fitness;

    // Global best solution and fitness.
    std::vector<double> best_solution;
    double best_fitness;

    // Population history.
    std::vector<std::vector<std::vector<double>>> population_history;

    // Helper methods.
    void initialize_population();
    void evaluate_population();
    std::vector<std::vector<double>> selection();
    std::vector<double> crossover(const std::vector<double>& parent1, const std::vector<double>& parent2);
    void mutate(std::vector<double>& individual);
    void enforce_bounds(std::vector<double>& individual);
};

#endif // GA_H
