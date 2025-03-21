import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import bioopt  # <-- Make sure bioopt is installed and importable

#############################
# 1) Define the Objective
#############################
# We'll use a simple "sphere" function in 2D:
def sphere(x):
    return x[0]**2 + x[1]**2

# For visualization, let's create a grid of (x, y) points and compute f(x,y)
# so we can draw contour lines:
def make_contour_data(bounds=(-5,5), resolution=100):
    xvals = np.linspace(bounds[0], bounds[1], resolution)
    yvals = np.linspace(bounds[0], bounds[1], resolution)
    X, Y = np.meshgrid(xvals, yvals)
    Z = X**2 + Y**2  # sphere
    return X, Y, Z

#############################
# 2) Animate Slime Mold (SMA)
#############################
def run_sma_animation():
    # Create the SMA solver
    sma_solver = bioopt.SMA(
        num_individuals=30,
        dim=2,
        lower_bound=-5,
        upper_bound=5,
        max_iter=50,
        c1=1.5,
        c2=1.5,
        w=0.5,
        minimize=True,
        verbose=False,
        seed=42,
        random_init_positions=True,
        use_w_decrement=False,
        w_start=0.9,
        w_end=0.4,
        store_history_each_iter=True  # <--- Enable storing each iteration
    )
    sma_solver.set_objective(sphere)
    sma_solver.optimize()  # runs, storing population each iteration

    # Extract the population history (a list of positions for each iteration)
    history = sma_solver.get_population_history()
    # history is [iteration_index][particle_index][dim]

    # Prepare the figure (no subplots)
    fig = plt.figure(figsize=(5, 5))
    fig.suptitle("SMA Optimization (Sphere)")

    # Make the contour data
    X, Y, Z = make_contour_data(bounds=(-5,5))

    # Plot the contour
    plt.contourf(X, Y, Z, levels=30, alpha=0.6)
    plt.colorbar()

    # Initialize a scatter plot for the swarm
    scatter = plt.scatter([], [], c='red', marker='o')

    # Update function for animation
    def update(frame):
        positions = history[frame]  # shape: [num_individuals][2]
        xs = [p[0] for p in positions]
        ys = [p[1] for p in positions]
        scatter.set_offsets(np.column_stack((xs, ys)))
        return (scatter,)

    # Create the animation
    anim = FuncAnimation(
        fig, update, frames=len(history), interval=300, blit=False, repeat=True
    )
    return fig, anim

#############################
# 3) Animate Particle Swarm (PSO)
#############################
def run_pso_animation():
    # Create the PSO solver
    pso_solver = bioopt.PSO(
        num_individuals=30,
        dim=2,
        lower_bound=-5,
        upper_bound=5,
        max_iter=50,
        c1=1.5,
        c2=1.5,
        w=0.7,
        v_max=0.0,  # no velocity clamp
        minimize=True,
        verbose=False,
        seed=123,
        velocity_init_random=True,
        use_ring_topology=False,
        neighbor_size=1,
        use_w_decrement=False,
        w_start=0.9,
        w_end=0.4,
        store_history_each_iter=True  # <--- Enable storing each iteration
    )
    pso_solver.set_objective(sphere)
    pso_solver.optimize()

    # Extract population history from PSO
    history = pso_solver.get_population_history()
    # history is [iteration_index][particle_index][dim]

    # Create a figure
    fig = plt.figure(figsize=(5, 5))
    fig.suptitle("PSO Optimization (Sphere)")

    X, Y, Z = make_contour_data(bounds=(-5,5))
    plt.contourf(X, Y, Z, levels=30, alpha=0.6)
    plt.colorbar()

    scatter = plt.scatter([], [], c='blue', marker='o')

    def update(frame):
        positions = history[frame]
        xs = [p[0] for p in positions]
        ys = [p[1] for p in positions]
        scatter.set_offsets(np.column_stack((xs, ys)))
        return (scatter,)

    anim = FuncAnimation(
        fig, update, frames=len(history), interval=300, blit=False, repeat=True
    )
    return fig, anim

#############################
# 4) Main: Run & Show
#############################
if __name__ == "__main__":
    # Create each animation in its own figure
    sma_fig, sma_anim = run_sma_animation()
    pso_fig, pso_anim = run_pso_animation()

    # Show them
    plt.show()
