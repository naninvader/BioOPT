#ifndef BASE_OPTIMIZER_H
#define BASE_OPTIMIZER_H

#include <vector>
#include <functional>

/**
 * @brief Abstract base class for optimization algorithms.
 */
class BaseOptimizer {
public:
    /**
     * @brief Construct a new Base Optimizer object.
     *
     * @param num_individuals Number of individuals (agents/particles).
     * @param dim Dimensionality of the search space.
     * @param lower_bound Lower bound for the search space.
     * @param upper_bound Upper bound for the search space.
     */
    BaseOptimizer(int num_individuals, int dim, double lower_bound, double upper_bound)
        : num_individuals(num_individuals), dim(dim),
          lower_bound(lower_bound), upper_bound(upper_bound) {}

    virtual ~BaseOptimizer() {}  // Virtual destructor

    /**
     * @brief Set the objective function.
     *
     * @param obj A callable that accepts a std::vector<double> and returns a double.
     */
    virtual void set_objective(std::function<double(const std::vector<double>&)> obj) = 0;

    /**
     * @brief Run the optimization process.
     *
     * @param iterations Number of iterations to run (-1 for default max iterations).
     */
    virtual void optimize(int iterations) = 0;

    /**
     * @brief Get the best solution found.
     *
     * @return std::vector<double> Best solution vector.
     */
    virtual std::vector<double> get_best_solution() const = 0;

    /**
     * @brief Get the best fitness value.
     *
     * @return double Best fitness value.
     */
    virtual double get_best_fitness() const = 0;

protected:
    int num_individuals;
    int dim;
    double lower_bound;
    double upper_bound;
};

#endif // BASE_OPTIMIZER_H
