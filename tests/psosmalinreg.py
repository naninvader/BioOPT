import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial.distance import cdist  # Not used here but may be useful for custom losses
import bioopt  # Updated import to match the module name

# --- Generate Synthetic Linear Data ---
# True model: y = 2*x + 3 with Gaussian noise
np.random.seed(42)
num_points = 100
x = np.linspace(-5, 5, num_points)
true_m, true_b = 2, 3
noise = np.random.normal(0, 2, size=num_points)  # Gaussian noise with std=2
y = true_m * x + true_b + noise

# Pack data into a 2D array (for plotting)
data = np.column_stack((x, y))

# --- Define the Loss Function: Mean Squared Error ---
def mse_loss(params):
    """
    Loss function for linear regression.
    params is expected to be a list/array with two elements: [m, b].
    Returns the Mean Squared Error between predictions and true y values.
    """
    m, b = params[0], params[1]
    predictions = m * x + b
    mse = np.mean((y - predictions) ** 2)
    return mse

# --- Run Optimizer to Optimize the Linear Model ---
def run_optimizer(optimizer_class, hyperparams, optimizer_name):
    """
    Run the specified optimizer to minimize the MSE loss for a linear model.
    Returns the best found parameters [m, b] and the associated loss.
    """
    if optimizer_class == bioopt.SMA:
        optimizer = bioopt.SMA(
            num_individuals=hyperparams.get("num_individuals", 50),
            dim=2,  # Two parameters: m and b
            lower_bound=-10.0,
            upper_bound=10.0,
            max_iter=hyperparams.get("max_iter", 200),
            c1=hyperparams.get("c1", 1.0),
            c2=hyperparams.get("c2", 1.0),
            w=hyperparams.get("w", 0.7),
            minimize=True,
            verbose=hyperparams.get("verbose", False),
            seed=hyperparams.get("seed", 42),
            random_init_positions=True,
            use_w_decrement=False,
            w_start=0.9,
            w_end=0.4,
            store_history_each_iter=False
        )
    elif optimizer_class == bioopt.PSO:
        optimizer = bioopt.PSO(
            num_individuals=hyperparams.get("num_individuals", 50),
            dim=2,  # Two parameters: m and b
            lower_bound=-10.0,
            upper_bound=10.0,
            max_iter=hyperparams.get("max_iter", 200),
            c1=hyperparams.get("c1", 1.0),
            c2=hyperparams.get("c2", 1.0),
            w=hyperparams.get("w", 0.7),
            v_max=hyperparams.get("v_max", 0.0),  # No velocity clamping by default
            minimize=True,
            verbose=hyperparams.get("verbose", False),
            seed=hyperparams.get("seed", 42),
            velocity_init_random=True,
            use_ring_topology=False,
            neighbor_size=1,
            use_w_decrement=False,
            w_start=0.9,
            w_end=0.4,
            store_history_each_iter=False
        )
    else:
        raise ValueError(f"Unsupported optimizer: {optimizer_name}")

    optimizer.set_objective(mse_loss)
    optimizer.optimize()
    best_params = np.array(optimizer.get_best_solution())  # Expect a 2-element array: [m, b]
    best_loss = mse_loss(best_params)
    return best_params, best_loss

# --- Main Execution ---
if __name__ == "__main__":
    # Define hyperparameters for optimizers
    default_hyperparams = {
        "num_individuals": 50,
        "max_iter": 200,
        "c1": 1.0,
        "c2": 1.0,
        "w": 0.7,
        "v_max": 0.0,  # For PSO
        "verbose": False,
        "seed": 42
    }

    # Run SMA
    sma_params, sma_loss = run_optimizer(bioopt.SMA, default_hyperparams, "SMA")
    m_sma, b_sma = sma_params[0], sma_params[1]

    # Run PSO
    pso_params, pso_loss = run_optimizer(bioopt.PSO, default_hyperparams, "PSO")
    m_pso, b_pso = pso_params[0], pso_params[1]

    # Print results
    print("Optimized Linear Model Parameters (SMA):")
    print(f"  m (slope) = {m_sma:.4f}")
    print(f"  b (intercept) = {b_sma:.4f}")
    print(f"Best MSE Loss (SMA): {sma_loss:.4f}")

    print("\nOptimized Linear Model Parameters (PSO):")
    print(f"  m (slope) = {m_pso:.4f}")
    print(f"  b (intercept) = {b_pso:.4f}")
    print(f"Best MSE Loss (PSO): {pso_loss:.4f}")

    # --- Visualization ---
    plt.figure(figsize=(10, 6))

    # Plot the noisy data
    plt.scatter(x, y, color='blue', alpha=0.6, label="Noisy Data")

    # Plot the true line
    plt.plot(x, true_m * x + true_b, color='green', linestyle='--', label="True Model")

    # Plot the fitted line from SMA
    plt.plot(x, m_sma * x + b_sma, color='red', label="Fitted Model (SMA)")

    # Plot the fitted line from PSO
    plt.plot(x, m_pso * x + b_pso, color='purple', label="Fitted Model (PSO)")

    plt.title("Linear Regression with SMA and PSO Optimization")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend()
    plt.grid(True)
    plt.show()