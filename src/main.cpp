#include "sma.h"
#include <iostream>
#include <vector>

int main() {
    // Create an SMA optimizer instance.
    SMA optimizer(50, 2, -10.0, 10.0, 100, 1.5, 1.5, 0.5, true, false, 42);

    // Set the objective function (simple sphere function).
    optimizer.set_objective([](const std::vector<double>& x) {
        return x[0] * x[0] + x[1] * x[1];
    });

    optimizer.optimize();

    std::vector<double> best_solution = optimizer.get_best_solution();
    std::cout << "Best solution: (" << best_solution[0] << ", " << best_solution[1] << ")\n";

    return 0;
}
