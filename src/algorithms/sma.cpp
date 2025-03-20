#include "../../include/sma.h"
#include "../../include/base_optimizer.h"
#include <iostream>
#include <limits>
#include <random>

// Constructor: Initialize population and internal parameters.
SMA::SMA(int num_individuals, int dim, double lower_bound, double upper_bound,
         int max_iter, double c1, double c2, double w, bool minimize, bool verbose, int seed)
    : BaseOptimizer(num_individuals, dim, lower_bound, upper_bound),
      max_iter(max_iter), c1(c1), c2(c2), w(w), minimize(minimize), verbose(verbose), rng(seed) {
    
    positions.resize(num_individuals, std::vector<double>(dim));
    fitness.resize(num_individuals);
    best_position.resize(dim);
    best_fitness = minimize ? std::numeric_limits<double>::max() : std::numeric_limits<double>::lowest();

    std::uniform_real_distribution<double> dist(lower_bound, upper_bound);
    for (int i = 0; i < num_individuals; ++i) {
        for (int d = 0; d < dim; ++d) {
            positions[i][d] = dist(rng);
        }
    }
}

// Set the objective function
void SMA::setObjective(std::function<double(const std::vector<double>&)> obj) {
    objective_function = obj;
}

// Optimize: Run the algorithm for the given number of iterations.
void SMA::optimize(int iterations) {
    if (!objective_function) {
        throw std::runtime_error("Objective function not set!");
    }

    int iter_limit = (iterations == -1) ? max_iter : iterations;

    for (int iter = 0; iter < iter_limit; ++iter) {
        update_positions(iter);

        for (int i = 0; i < num_individuals; ++i) {
            double fitness_value = objective_function(positions[i]);
            if ((minimize && fitness_value < best_fitness) ||
                (!minimize && fitness_value > best_fitness)) {
                best_fitness = fitness_value;
                best_position = positions[i];
            }
        }

        if (verbose) {
            std::cout << "Iteration " << iter + 1 << " Best Fitness: " << best_fitness << std::endl;
        }
    }

    // For simplicity, record one snapshot as history
    population_history.push_back(positions);
}

// Update positions of agents based on hyperparameters and current best solution.
// This is a simplified update inspired by Li et al.'s 2020 paper.
void SMA::update_positions(int iteration) {
    // Compute random factors based on adjustable hyperparameters
    double factor1 = c1 * ((double) rand() / RAND_MAX);
    double factor2 = c2 * ((double) rand() / RAND_MAX);
    for (int i = 0; i < num_individuals; ++i) {
        for (int d = 0; d < dim; ++d) {
            // The update equation: a weighted combination of attraction to the best and random perturbation.
            double delta = factor1 * (best_position[d] - positions[i][d])
                           + factor2 * (((double) rand() / RAND_MAX) * 2 - 1);
            positions[i][d] += w * delta;
            // Enforce boundaries
            if (positions[i][d] < lower_bound) positions[i][d] = lower_bound;
            if (positions[i][d] > upper_bound) positions[i][d] = upper_bound;
        }
    }
}

// Get the best solution found so far.
std::vector<double> SMA::getBestSolution() const {
    return best_position;
}

// Get the best fitness value.
double SMA::getBestFitness() const {
    return best_fitness;
}

// Return population history (here, a single snapshot is provided).
std::vector<std::vector<std::vector<double>>> SMA::getPopulationHistory() const {
    return population_history;
}

// (Optional) Enforce boundaries on an individual vector (not used in this simplified version).
void SMA::enforce_bounds(std::vector<double>& individual) {
    for (int d = 0; d < dim; ++d) {
        if (individual[d] < lower_bound) individual[d] = lower_bound;
        if (individual[d] > upper_bound) individual[d] = upper_bound;
    }
}
