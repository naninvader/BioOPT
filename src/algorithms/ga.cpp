#include "../../include/ga.h"
#include <iostream>
#include <limits>
#include <random>
#include <algorithm>
#include <stdexcept>

GA::GA(int num_individuals,
       int dim,
       double lower_bound,
       double upper_bound,
       int max_iter,
       bool minimize,
       bool verbose,
       int seed,
       double crossover_rate,
       double mutation_rate,
       int tournament_size,
       int elitism_count,
       bool use_uniform_crossover,
       bool use_gaussian_mutation,
       double mutation_std,
       bool store_history_each_iter)
    : BaseOptimizer(num_individuals, dim, lower_bound, upper_bound),
      max_iter(max_iter),
      minimize(minimize),
      verbose(verbose),
      crossover_rate(crossover_rate),
      mutation_rate(mutation_rate),
      tournament_size(tournament_size),
      elitism_count(elitism_count),
      use_uniform_crossover(use_uniform_crossover),
      use_gaussian_mutation(use_gaussian_mutation),
      mutation_std(mutation_std),
      store_history_each_iter(store_history_each_iter),
      rng(seed)
{
    if (this->mutation_std <= 0.0) {
        this->mutation_std = (upper_bound - lower_bound) * 0.1;
    }
    best_solution.resize(dim);
    best_fitness = (minimize ? std::numeric_limits<double>::max() : std::numeric_limits<double>::lowest());
    initialize_population();
}

void GA::set_objective(std::function<double(const std::vector<double>&)> obj) {
    objective_function = obj;
}

void GA::initialize_population() {
    std::uniform_real_distribution<double> dist(lower_bound, upper_bound);
    population.resize(num_individuals, std::vector<double>(dim));
    fitness.resize(num_individuals);
    for (int i = 0; i < num_individuals; ++i) {
        for (int d = 0; d < dim; ++d) {
            population[i][d] = dist(rng);
        }
    }
}

void GA::evaluate_population() {
    for (int i = 0; i < num_individuals; ++i) {
        double f = objective_function(population[i]);
        fitness[i] = f;
        if ((minimize && f < best_fitness) || (!minimize && f > best_fitness)) {
            best_fitness = f;
            best_solution = population[i];
        }
    }
}

std::vector<std::vector<double>> GA::selection() {
    std::uniform_int_distribution<int> dist_idx(0, num_individuals - 1);
    std::vector<std::vector<double>> mating_pool;
    mating_pool.reserve(num_individuals);
    for (int i = 0; i < num_individuals; ++i) {
        int best_idx = dist_idx(rng);
        for (int j = 1; j < tournament_size; ++j) {
            int idx = dist_idx(rng);
            if ((minimize && fitness[idx] < fitness[best_idx]) ||
                (!minimize && fitness[idx] > fitness[best_idx])) {
                best_idx = idx;
            }
        }
        mating_pool.push_back(population[best_idx]);
    }
    return mating_pool;
}

std::vector<double> GA::crossover(const std::vector<double>& parent1, const std::vector<double>& parent2) {
    std::vector<double> offspring(dim);
    std::uniform_real_distribution<double> dist01(0.0, 1.0);
    if (use_uniform_crossover) {
        for (int d = 0; d < dim; ++d) {
            offspring[d] = (dist01(rng) < crossover_rate) ? parent1[d] : parent2[d];
        }
    } else {
        std::uniform_int_distribution<int> dist_point(1, dim - 1);
        int cp = dist_point(rng);
        for (int d = 0; d < dim; ++d) {
            offspring[d] = (d < cp) ? parent1[d] : parent2[d];
        }
    }
    return offspring;
}

void GA::mutate(std::vector<double>& individual) {
    std::uniform_real_distribution<double> dist01(0.0, 1.0);
    std::uniform_real_distribution<double> dist_range(lower_bound, upper_bound);
    for (int d = 0; d < dim; ++d) {
        if (dist01(rng) < mutation_rate) {
            if (use_gaussian_mutation) {
                std::normal_distribution<double> gauss(0.0, mutation_std);
                individual[d] += gauss(rng);
            } else {
                individual[d] = dist_range(rng);
            }
        }
    }
}

void GA::enforce_bounds(std::vector<double>& individual) {
    for (int d = 0; d < dim; ++d) {
        if (individual[d] < lower_bound) individual[d] = lower_bound;
        if (individual[d] > upper_bound) individual[d] = upper_bound;
    }
}

void GA::optimize(int iterations) {
    if (!objective_function) {
        throw std::runtime_error("Objective function not set!");
    }
    int iter_limit = (iterations == -1) ? max_iter : iterations;
    evaluate_population();
    if (store_history_each_iter) {
        population_history.push_back(population);
    }
    for (int iter = 0; iter < iter_limit; ++iter) {
        std::vector<std::vector<double>> mating_pool = selection();
        std::vector<std::vector<double>> new_population;
        std::vector<int> indices(num_individuals);
        for (int i = 0; i < num_individuals; ++i) {
            indices[i] = i;
        }
        std::sort(indices.begin(), indices.end(), [&](int a, int b) {
            return (minimize ? (fitness[a] < fitness[b]) : (fitness[a] > fitness[b]));
        });
        for (int i = 0; i < elitism_count; ++i) {
            new_population.push_back(population[indices[i]]);
        }
        while (new_population.size() < static_cast<size_t>(num_individuals)) {
            int idx1 = std::uniform_int_distribution<int>(0, mating_pool.size() - 1)(rng);
            int idx2 = std::uniform_int_distribution<int>(0, mating_pool.size() - 1)(rng);
            std::vector<double> child = crossover(mating_pool[idx1], mating_pool[idx2]);
            mutate(child);
            enforce_bounds(child);
            new_population.push_back(child);
        }
        population = new_population;
        evaluate_population();
        if (verbose) {
            std::cout << "Iteration " << (iter + 1)
                      << ", Best Fitness: " << best_fitness << std::endl;
        }
        if (store_history_each_iter) {
            population_history.push_back(population);
        }
    }
    if (!store_history_each_iter) {
        population_history.push_back(population);
    }
}

std::vector<double> GA::get_best_solution() const {
    return best_solution;
}

double GA::get_best_fitness() const {
    return best_fitness;
}

std::vector<std::vector<std::vector<double>>> GA::get_population_history() const {
    return population_history;
}
