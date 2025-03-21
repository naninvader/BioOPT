#include "../../include/pso.h"
#include "../../include/base_optimizer.h"
#include <iostream>
#include <limits>
#include <random>

PSO::PSO(int num_individuals,
         int dim,
         double lower_bound, double upper_bound,
         int max_iter,
         double c1, double c2,
         double w, double v_max,
         bool minimize,
         bool verbose,
         int seed,
         bool velocity_init_random,
         bool use_ring_topology,
         int neighbor_size,
         bool use_w_decrement,
         double w_start,
         double w_end,
         bool store_history_each_iter)
    : BaseOptimizer(num_individuals, dim, lower_bound, upper_bound),
      max_iter(max_iter),
      c1(c1),
      c2(c2),
      w(w),
      v_max(v_max),
      minimize(minimize),
      verbose(verbose),
      velocity_init_random(velocity_init_random),
      use_ring_topology(use_ring_topology),
      neighbor_size(neighbor_size),
      use_w_decrement(use_w_decrement),
      w_start(w_start),
      w_end(w_end),
      store_history_each_iter(store_history_each_iter),
      rng(seed)
{
    initialize_particles();
}

void PSO::initialize_particles() {
    positions.resize(num_individuals, std::vector<double>(dim));
    velocities.resize(num_individuals, std::vector<double>(dim));
    pbest_positions.resize(num_individuals, std::vector<double>(dim));
    pbest_fitness.resize(num_individuals);

    gbest_position.resize(dim);
    gbest_fitness = (minimize ? std::numeric_limits<double>::max() : std::numeric_limits<double>::lowest());

    std::uniform_real_distribution<double> dist_pos(lower_bound, upper_bound);
    double vel_range = (upper_bound - lower_bound) * 0.1;
    std::uniform_real_distribution<double> dist_vel(-vel_range, vel_range);

    for (int i = 0; i < num_individuals; ++i) {
        for (int d = 0; d < dim; ++d) {
            positions[i][d] = dist_pos(rng);
            velocities[i][d] = velocity_init_random ? dist_vel(rng) : 0.0;
        }
    }
}

void PSO::set_objective(std::function<double(const std::vector<double>&)> obj) {
    objective_function = obj;
}

void PSO::optimize(int iterations) {
    if (!objective_function) {
        throw std::runtime_error("Objective function not set!");
    }
    int iter_limit = (iterations == -1) ? max_iter : iterations;
    for (int i = 0; i < num_individuals; ++i) {
        double fit = objective_function(positions[i]);
        pbest_positions[i] = positions[i];
        pbest_fitness[i] = fit;
        if ((minimize && fit < gbest_fitness) || (!minimize && fit > gbest_fitness)) {
            gbest_fitness = fit;
            gbest_position = positions[i];
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
            if ((minimize && fit < pbest_fitness[i]) || (!minimize && fit > pbest_fitness[i])) {
                pbest_fitness[i] = fit;
                pbest_positions[i] = positions[i];
            }
            if (!use_ring_topology) {
                if ((minimize && fit < gbest_fitness) || (!minimize && fit > gbest_fitness)) {
                    gbest_fitness = fit;
                    gbest_position = positions[i];
                }
            }
        }
        if (use_ring_topology) {
            double ring_best_fit = (minimize ? std::numeric_limits<double>::max() : std::numeric_limits<double>::lowest());
            std::vector<double> ring_best_pos(dim);
            for (int i = 0; i < num_individuals; ++i) {
                if ((minimize && pbest_fitness[i] < ring_best_fit) || (!minimize && pbest_fitness[i] > ring_best_fit)) {
                    ring_best_fit = pbest_fitness[i];
                    ring_best_pos = pbest_positions[i];
                }
            }
            gbest_fitness = ring_best_fit;
            gbest_position = ring_best_pos;
        }
        if (verbose) {
            std::cout << "Iteration " << (iter + 1)
                      << " Best Fitness: " << gbest_fitness << std::endl;
        }
        if (store_history_each_iter) {
            population_history.push_back(positions);
        }
    }
    if (!store_history_each_iter) {
        population_history.push_back(positions);
    }
}

void PSO::update_positions(int /*iteration*/) {
    std::uniform_real_distribution<double> dist01(0.0, 1.0);
    for (int i = 0; i < num_individuals; ++i) {
        int best_index = (use_ring_topology ? get_local_best_index(i) : -1);
        for (int d = 0; d < dim; ++d) {
            double r1 = dist01(rng);
            double r2 = dist01(rng);
            double best_pos_d = use_ring_topology ? pbest_positions[best_index][d] : gbest_position[d];
            velocities[i][d] = w * velocities[i][d]
                             + c1 * r1 * (pbest_positions[i][d] - positions[i][d])
                             + c2 * r2 * (best_pos_d - positions[i][d]);
            if (v_max > 0.0) {
                clamp_velocity(velocities[i]);
            }
        }
        for (int d = 0; d < dim; ++d) {
            positions[i][d] += velocities[i][d];
        }
        enforce_bounds(positions[i]);
    }
}

int PSO::get_local_best_index(int i) {
    double best_fit = (minimize ? std::numeric_limits<double>::max() : std::numeric_limits<double>::lowest());
    int best_idx = i;
    for (int offset = -neighbor_size; offset <= neighbor_size; ++offset) {
        int idx = (i + offset + num_individuals) % num_individuals;
        double fit = pbest_fitness[idx];
        if ((minimize && fit < best_fit) || (!minimize && fit > best_fit)) {
            best_fit = fit;
            best_idx = idx;
        }
    }
    return best_idx;
}

void PSO::update_inertia(int iteration, int total_iters) {
    double ratio = static_cast<double>(iteration) / (total_iters - 1);
    w = w_start + ratio * (w_end - w_start);
}

void PSO::clamp_velocity(std::vector<double>& velocity) {
    for (int d = 0; d < dim; ++d) {
        if (velocity[d] > v_max) velocity[d] = v_max;
        if (velocity[d] < -v_max) velocity[d] = -v_max;
    }
}

void PSO::enforce_bounds(std::vector<double>& individual) {
    for (int d = 0; d < dim; ++d) {
        if (individual[d] < lower_bound) individual[d] = lower_bound;
        if (individual[d] > upper_bound) individual[d] = upper_bound;
    }
}

std::vector<double> PSO::get_best_solution() const {
    return gbest_position;
}

double PSO::get_best_fitness() const {
    return gbest_fitness;
}

std::vector<std::vector<std::vector<double>>> PSO::get_population_history() const {
    return population_history;
}
