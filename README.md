BioOpt is a C++ library with Python bindings designed for bio-inspired optimization. The current implementation includes the Slime Mold Algorithm (SMA) for function optimization. This documentation provides an overview of the available classes, methods, and their usage.
File Structure:
bioopt/
├── include/
│   ├── base_optimizer.h        # Abstract base class for all optimizers
│   ├── sma.h                   # SMA algorithm header
├── src/
│   ├── algorithms/
│   │   ├── sma.cpp             # SMA implementation
│   ├── core/
│   │   ├── optimizer.cpp       # (Optional) Common optimizer utilities
│   ├── bindings/
│   │   ├── bindings.cpp        # Pybind11 bindings for Python
│   ├── main.cpp                # C++ test executable
├── CMakeLists.txt              # CMake build configuration
├── setup.py                    # Python package setup file
├── test.py                      # Python test script
└── README.md                   # Documentation and usage guide

    BaseOptimizer (Abstract Base Class)
This class provides a common interface for optimization algorithms.
setObjective(std::function<double(const std::vector<double>&)> obj)	Sets the objective function to optimize.
optimize(int iterations)	Runs the optimization for a given number of iterations.
getBestSolution() const	Returns the best solution found.
getBestFitness() const	Returns the best fitness value found.
    SMA (Slime Mold Algorithm)
Constructor:
SMA(int num_individuals, int dim, double lower_bound, double upper_bound,
    double c1, double c2, double w, int max_iter, bool verbose = false);
Parameter |	Description
num_individuals	| Number of individuals in the population.
dim	| Dimensionality of the problem space.
lower_bound	| Lower bound for variables.
upper_bound	| Upper bound for variables.
c1	| Coefficient controlling slime mold behavior.
c2	| Secondary coefficient for movement.
w	| nertia weight for velocity update.
max_iter	| Maximum number of iterations.
verbose	| Whether to print progress messages.