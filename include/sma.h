#ifndef SMA_H
#define SMA_H

#include "base_optimizer.h"
#include <vector>
#include <functional>
#include <random>

class SMA : public BaseOptimizer {
public:
    // Constructor with adjustable hyperparameters
    SMA(int num_individuals, int dim, double lower_bound, double upper_bound,
        int max_iter, double c1, double c2, double w, 
        bool minimize = true, bool verbose = false, int seed = 42);

    virtual ~SMA() {}

    // Override base class virtual methods
    void setObjective(std::function<double(const std::vector<double>&)> obj) override;
    void optimize(int iterations) override;
    std::vector<double> getBestSolution() const override;
    double getBestFitness() const override;

    // Additional function to retrieve population history
    std::vector<std::vector<std::vector<double>>> getPopulationHistory() const;

    // Make update_positions public so Python can call it
    void update_positions(int iter);

private:
    std::function<double(const std::vector<double>&)> objective_function;
    int max_iter;
    double c1, c2, w;
    bool minimize;
    bool verbose;

    std::mt19937 rng;

    // Positions of all agents and their fitness info
    std::vector<std::vector<double>> positions;
    std::vector<double> fitness;
    std::vector<double> best_position;
    double best_fitness;
    
    // (Optional) Store history snapshots (here we return a single snapshot)
    std::vector<std::vector<std::vector<double>>> population_history;

    void enforce_bounds(std::vector<double>& individual);
};

#endif
