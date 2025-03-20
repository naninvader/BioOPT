#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include "../../include/sma.h"
#include "../../include/base_optimizer.h"

namespace py = pybind11;

PYBIND11_MODULE(bioopt_python, m) {
    // Bind the abstract base class (for reference only)
    py::class_<BaseOptimizer>(m, "BaseOptimizer")
        .def("set_objective", &BaseOptimizer::setObjective)
        .def("optimize", &BaseOptimizer::optimize)
        .def("get_best_solution", &BaseOptimizer::getBestSolution)
        .def("get_best_fitness", &BaseOptimizer::getBestFitness);

    // Bind SMA as a concrete derived class
    py::class_<SMA, BaseOptimizer>(m, "SMA")
        .def(py::init<int, int, double, double, int, double, double, double, bool, bool, int>(),
             py::arg("num_individuals"), py::arg("dim"), py::arg("lower_bound"),
             py::arg("upper_bound"), py::arg("max_iter"), py::arg("c1"), py::arg("c2"), py::arg("w"),
             py::arg("minimize") = true, py::arg("verbose") = false, py::arg("seed") = 42)
        .def("set_objective", &SMA::setObjective)
        .def("optimize", &SMA::optimize, py::arg("iterations") = -1)
        .def("get_best_solution", &SMA::getBestSolution)
        .def("get_best_fitness", &SMA::getBestFitness)
        .def("get_population_history", &SMA::getPopulationHistory)
        .def("update_positions", &SMA::update_positions);
}
