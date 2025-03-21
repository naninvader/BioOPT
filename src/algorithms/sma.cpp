#include "../../include/sma.h"
#include "../../include/base_optimizer.h"
#include <iostream>
#include <limits>
#include <random>

SMA::SMA(int num_individuals,
         int dim,
         double lower_bound,
         double upper_bound,
         int max_iter,
         double c1, double c2,
         double w,
         bool minimize,
         bool verbose,
         int seed,
         bool random_init_positions,
         bool use_w_decrement,
         double w_start,
         double w_end,
         bool store_history_each_iter)
    : BaseOptimizer(num_individuals, dim, lower_bound, upper_bound),
      max_iter(max_iter),
      c1(c1),
      c2(c2),
      w(w),
      minimize(minimize),
      verbose(verbose),
      random_init_positions(random_init_positions),
      use_w_decrement(use_w_decrement),
      w_start(w_start),
      w_end(w_end),
      store_history_each_iter(store_history_each_iter),
      rng(seed)
{
    positions.resize(num_individuals, std::vector<double>(dim));
    fitness.resize(num_individuals);
    best_position.resize(dim);
    best_fitness = (minimize
        ? std::numeric_limits<double>::max()
        : std::numeric_limits<double>::lowest());
    initialize_positions();
}

void SMA::initialize_positions() {
    if (random_init_positions) {
        std::uniform_real_distribution<double> dist(lower_bound, upper_bound);
        for (int i = 0; i < num_individuals; ++i) {
            for (int d = 0; d < dim; ++d) {
                positions[i][d] = dist(rng);
            }
        }
    } else {
        for (int i = 0; i < num_individuals; ++i) {
            for (int d = 0; d < dim; ++d) {
                positions[i][d] = 0.0;
            }
        }
    }
}

void SMA::set_objective(std::function<double(const std::vector<double>&)> obj) {
    objective_function = obj;
}

void SMA::optimize(int iterations) {
    if (!objective_function) {
        throw std::runtime_error("Objective function not set!");
    }
    int iter_limit = (iterations == -1) ? max_iter : iterations;
    // Evaluate initial population and set best solution.
    for (int i = 0; i < num_individuals; ++i) {
        double fit = objective_function(positions[i]);
        fitness[i] = fit;
        if ((minimize && fit < best_fitness) ||
            (!minimize && fit > best_fitness)) {
            best_fitness = fit;
            best_position = positions[i];
        }
    }
    if (store_history_each_iter) {
        population_history.push_back(positions);
    }
    for (int iter = 0; iter < iter_limit; ++iter) {
        if (use_w_decrement) {
            update_inertia(iter, iter_limit);
        }
        update_positions(iter);
        for (int i = 0; i < num_individuals; ++i) {
            double fit = objective_function(positions[i]);
            fitness[i] = fit;
            if ((minimize && fit < best_fitness) ||
                (!minimize && fit > best_fitness)) {
                best_fitness = fit;
                best_position = positions[i];
            }
        }
        if (verbose) {
            std::cout << "Iteration " << (iter + 1)
                      << " Best Fitness: " << best_fitness << std::endl;
        }
        if (store_history_each_iter) {
            population_history.push_back(positions);
        }
    }
    if (!store_history_each_iter) {
        population_history.push_back(positions);
    }
}

void SMA::update_positions(int iteration) {
    std::uniform_real_distribution<double> dist01(0.0, 1.0);
    for (int i = 0; i < num_individuals; ++i) {
        for (int d = 0; d < dim; ++d) {
            double factor1 = c1 * dist01(rng);
            double factor2 = c2 * ((dist01(rng) * 2.0) - 1.0);
            double delta = factor1 * (best_position[d] - positions[i][d]) + factor2;
            positions[i][d] += w * delta;
            enforce_bounds(positions[i]);
        }
    }
}

void SMA::enforce_bounds(std::vector<double>& individual) {
    for (int d = 0; d < dim; ++d) {
        if (individual[d] < lower_bound)
            individual[d] = lower_bound;
        if (individual[d] > upper_bound)
            individual[d] = upper_bound;
    }
}

void SMA::update_inertia(int iteration, int total_iters) {
    double ratio = static_cast<double>(iteration) / (total_iters - 1);
    w = w_start + ratio * (w_end - w_start);
}

std::vector<double> SMA::get_best_solution() const {
    return best_position;
}

double SMA::get_best_fitness() const {
    return best_fitness;
}

std::vector<std::vector<std::vector<double>>> SMA::get_population_history() const {
    return population_history;
}
