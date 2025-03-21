========================================
BioOPT - Bio-Inspired Optimization Library (Python API)
========================================

BioOPT is a bio-inspired optimization library that provides Python bindings
to C++ implementations of popular optimization algorithms. It offers a simple,
consistent interface for using multiple algorithms from Python.

Currently, the following optimizers are available as Python classes:

  • SMA  - Slime Mold Algorithm
  • PSO  - Particle Swarm Optimization
  • GA   - Genetic Algorithm

--------------------------------------------------
File Structure
--------------------------------------------------
bioopt/
  ├── include/
  │     ├── base_optimizer.h    // Abstract base class for optimizers
  │     ├── sma.h             // Header for SMA (Slime Mold Algorithm)
  │     ├── pso.h             // Header for PSO (Particle Swarm Optimization)
  │     └── ga.h              // Header for GA (Genetic Algorithm)
  ├── src/
  │     ├── algorithms/
  │     │     ├── sma.cpp     // SMA implementation
  │     │     ├── pso.cpp     // PSO implementation
  │     │     └── ga.cpp      // GA implementation (with extra toggles)
  │     ├── bindings/
  │     │     └── bindings.cpp // Python bindings via pybind11
  │     └── core/
  │           └── optimizer.cpp // Shared optimizer utilities (currently empty)
  ├── CMakeLists.txt          // CMake build file
  └── setup.py                // Python setup file for building the extension

--------------------------------------------------
Build Instructions
--------------------------------------------------

Using CMake:
  1. Create a build directory and configure:
         mkdir build && cd build
         cmake ..
  2. Build the project:
         cmake --build .
  3. The shared library "bioopt.so" will be located in build/lib.

Python Installation:
  From the project root, run:
         python setup.py build_ext --inplace
  This compiles the Python extension, allowing you to:
         import bioopt

--------------------------------------------------
Python API Reference
--------------------------------------------------

All optimizers are available as classes in the "bioopt" module. The 
following Python classes are provided:

---------------------------
BaseOptimizer (Abstract)
---------------------------
(Not meant for direct instantiation)

Common Methods (available on SMA, PSO, GA):
  • set_objective(func)
       - Sets the objective function.
       - Parameter: func, a callable accepting a list (vector) of floats and
         returning a float.
  • optimize(iterations)
       - Runs the optimization.
       - Parameter: iterations (set to -1 to use the default max iterations).
  • get_best_solution()
       - Returns the best solution found as a list of floats.
  • get_best_fitness()
       - Returns the fitness value (a float) corresponding to the best solution.
  • get_population_history()
       - Returns the history of population positions if enabled.

---------------------------
SMA (Slime Mold Algorithm)
---------------------------
Python Constructor:
  bioopt.SMA(
      num_individuals,         # Number of agents
      dim,                     # Dimensionality of the search space
      lower_bound,             # Lower bound of the search space
      upper_bound,             # Upper bound of the search space
      max_iter,                # Maximum number of iterations
      c1,                      # Coefficient for attraction towards the best solution
      c2,                      # Coefficient for random variation
      w,                       # Inertia weight
      minimize=True,           # True for minimization problems
      verbose=False,           # Verbose output during optimization
      seed=42,                 # Random seed
      random_init_positions=True,  # Initialize positions randomly if True
      use_w_decrement=False,   # Linearly decrease inertia weight if True
      w_start=0.9,             # Starting inertia weight (if decrement is used)
      w_end=0.4,               # Ending inertia weight (if decrement is used)
      store_history_each_iter=False  # Store population history for each iteration if True
  )

---------------------------
PSO (Particle Swarm Optimization)
---------------------------
Python Constructor:
  bioopt.PSO(
      num_individuals,         # Number of particles
      dim,                     # Dimensionality of the search space
      lower_bound,             # Lower bound of the search space
      upper_bound,             # Upper bound of the search space
      max_iter,                # Maximum number of iterations
      c1,                      # Cognitive coefficient
      c2,                      # Social coefficient
      w,                       # Inertia weight
      v_max=0.0,               # Maximum velocity (0.0 means no clamp)
      minimize=True,           # True for minimization problems
      verbose=False,           # Verbose output
      seed=42,                 # Random seed
      velocity_init_random=True,   # Initialize velocities randomly if True
      use_ring_topology=False,     # Use ring topology for local best if True
      neighbor_size=1,              # Size of neighborhood for ring topology
      use_w_decrement=False,        # Linearly decrease inertia weight if True
      w_start=0.9,             # Starting inertia weight (if decrement is used)
      w_end=0.4,               # Ending inertia weight (if decrement is used)
      store_history_each_iter=False  # Store history of positions if True
  )

---------------------------
GA (Genetic Algorithm)
---------------------------
Python Constructor:
  bioopt.GA(
      num_individuals,         # Population size
      dim,                     # Dimensionality of the solution vector
      lower_bound,             # Lower bound of each gene
      upper_bound,             # Upper bound of each gene
      max_iter,                # Number of generations (iterations)
      minimize=True,           # True for minimization problems
      verbose=False,           # Verbose output during optimization
      seed=42,                 # Random seed
      crossover_rate=0.7,      # Probability of gene crossover
      mutation_rate=0.01,      # Mutation probability per gene
      tournament_size=2,       # Number of competitors in tournament selection
      elitism_count=1,         # Number of elite individuals preserved per generation
      use_uniform_crossover=True,  # Use uniform crossover if True; else single-point
      use_gaussian_mutation=False, # Use Gaussian mutation if True; else random-reset
      mutation_std=0.0,        # Std deviation for Gaussian mutation (if 0, defaults to 10% of range)
      store_history_each_iter=False  # Store population history if True
  )

Extra GA Parameters:
  - tournament_size: Adjusts selection pressure (default is 2).
  - elitism_count: Number of best individuals carried to next generation.
  - use_uniform_crossover: True uses uniform crossover; False uses single-point.
  - use_gaussian_mutation: True applies Gaussian mutation; otherwise, a random-reset.
  - mutation_std: Standard deviation for Gaussian mutation (if 0, auto-set to 10% of the search range).

--------------------------------------------------
Python Usage Example
--------------------------------------------------
Below is a simple example using the GA optimizer:

    import bioopt
    import numpy as np

    # Define an objective function (e.g., sphere function)
    def sphere(x):
        return sum(xi**2 for xi in x)

    # Instantiate the GA optimizer with custom parameters
    ga_solver = bioopt.GA(
        num_individuals=50,
        dim=2,
        lower_bound=-5.0,
        upper_bound=5.0,
        max_iter=100,
        minimize=True,
        verbose=True,
        seed=123,
        crossover_rate=0.7,
        mutation_rate=0.01,
        tournament_size=2,
        elitism_count=1,
        use_uniform_crossover=True,
        use_gaussian_mutation=False,
        mutation_std=0.0,
        store_history_each_iter=True
    )

    # Set the objective function and run optimization
    ga_solver.set_objective(sphere)
    ga_solver.optimize()
    print("Best solution:", ga_solver.get_best_solution())
    print("Best fitness:", ga_solver.get_best_fitness())
