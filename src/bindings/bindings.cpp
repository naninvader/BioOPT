#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include "../../include/base_optimizer.h"
#include "../../include/sma.h"
#include "../../include/pso.h"
#include "../../include/ga.h"

namespace py = pybind11;

PYBIND11_MODULE(bioopt, m) {
    // BaseOptimizer (abstract)
    py::class_<BaseOptimizer>(m, "BaseOptimizer")
        .def("set_objective", &BaseOptimizer::set_objective)
        .def("optimize", &BaseOptimizer::optimize)
        .def("get_best_solution", &BaseOptimizer::get_best_solution)
        .def("get_best_fitness", &BaseOptimizer::get_best_fitness);

    // SMA
    py::class_<SMA, BaseOptimizer>(m, "SMA")
        .def(py::init<
            int, int, double, double, int, double, double, double,
            bool, bool, int, bool, bool, double, double, bool
        >(),
             py::arg("num_individuals"),
             py::arg("dim"),
             py::arg("lower_bound"),
             py::arg("upper_bound"),
             py::arg("max_iter"),
             py::arg("c1"),
             py::arg("c2"),
             py::arg("w"),
             py::arg("minimize") = true,
             py::arg("verbose") = false,
             py::arg("seed") = 42,
             py::arg("random_init_positions") = true,
             py::arg("use_w_decrement") = false,
             py::arg("w_start") = 0.9,
             py::arg("w_end") = 0.4,
             py::arg("store_history_each_iter") = false
        )
        .def("set_objective", &SMA::set_objective)
        .def("optimize", &SMA::optimize, py::arg("iterations") = -1)
        .def("get_best_solution", &SMA::get_best_solution)
        .def("get_best_fitness", &SMA::get_best_fitness)
        .def("get_population_history", &SMA::get_population_history)
        .def("update_positions", &SMA::update_positions);

    // PSO
    py::class_<PSO, BaseOptimizer>(m, "PSO")
        .def(py::init<
            int, int, double, double, int, double, double, double, double,
            bool, bool, int, bool, bool, int, bool, double, double, bool
        >(),
             py::arg("num_individuals"),
             py::arg("dim"),
             py::arg("lower_bound"),
             py::arg("upper_bound"),
             py::arg("max_iter"),
             py::arg("c1"),
             py::arg("c2"),
             py::arg("w"),
             py::arg("v_max") = 0.0,
             py::arg("minimize") = true,
             py::arg("verbose") = false,
             py::arg("seed") = 42,
             py::arg("velocity_init_random") = true,
             py::arg("use_ring_topology") = false,
             py::arg("neighbor_size") = 1,
             py::arg("use_w_decrement") = false,
             py::arg("w_start") = 0.9,
             py::arg("w_end") = 0.4,
             py::arg("store_history_each_iter") = false
        )
        .def("set_objective", &PSO::set_objective)
        .def("optimize", &PSO::optimize, py::arg("iterations") = -1)
        .def("get_best_solution", &PSO::get_best_solution)
        .def("get_best_fitness", &PSO::get_best_fitness)
        .def("get_population_history", &PSO::get_population_history);

    // GA
    py::class_<GA, BaseOptimizer>(m, "GA")
        .def(py::init<
             int, int, double, double, int,
             bool, bool, int, double, double,
             int, int, bool, bool, double, bool
        >(),
             py::arg("num_individuals"),
             py::arg("dim"),
             py::arg("lower_bound"),
             py::arg("upper_bound"),
             py::arg("max_iter"),
             py::arg("minimize") = true,
             py::arg("verbose") = false,
             py::arg("seed") = 42,
             py::arg("crossover_rate") = 0.7,
             py::arg("mutation_rate") = 0.01,
             py::arg("tournament_size") = 2,
             py::arg("elitism_count") = 1,
             py::arg("use_uniform_crossover") = true,
             py::arg("use_gaussian_mutation") = false,
             py::arg("mutation_std") = 0.0,
             py::arg("store_history_each_iter") = false
        )
        .def("set_objective", &GA::set_objective)
        .def("optimize", &GA::optimize, py::arg("iterations") = -1)
        .def("get_best_solution", &GA::get_best_solution)
        .def("get_best_fitness", &GA::get_best_fitness)
        .def("get_population_history", &GA::get_population_history);
}
