#include "sma.h"
#include <iostream>

int main() {
    // ✅ Fix: Pass all required arguments
    SMA optimizer(50, 2, -10.0, 10.0, 100, 1.5, 1.5, 0.5, true, false, 42);

    optimizer.setObjective([](const std::vector<double>& x) {
        return x[0] * x[0] + x[1] * x[1];  // Simple sphere function
    });

    optimizer.optimize();

    std::vector<double> best_solution = optimizer.getBestSolution();
    std::cout << "Best solution: (" << best_solution[0] << ", " << best_solution[1] << ")\n";

    return 0;
}
