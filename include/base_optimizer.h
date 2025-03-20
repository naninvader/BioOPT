#ifndef BASE_OPTIMIZER_H
#define BASE_OPTIMIZER_H

#include <vector>
#include <functional>

class BaseOptimizer {
public:
    BaseOptimizer(int num_individuals, int dim, double lower_bound, double upper_bound)
        : num_individuals(num_individuals), dim(dim),
          lower_bound(lower_bound), upper_bound(upper_bound) {}

    virtual ~BaseOptimizer() {}  // Ensure proper virtual destructor

    virtual void setObjective(std::function<double(const std::vector<double>&)> obj) = 0;
    virtual void optimize(int iterations) = 0;
    virtual std::vector<double> getBestSolution() const = 0;
    virtual double getBestFitness() const = 0;

protected:
    int num_individuals;
    int dim;
    double lower_bound;
    double upper_bound;
};

#endif
