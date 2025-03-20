import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt
from bioopt_python import SMA

# --- Generate the NNFS Spiral Dataset ---
def generate_spiral_data(samples, classes):
    """Generate a 2D spiral dataset with multiple classes."""
    X = np.zeros((samples * classes, 2))
    y = np.zeros(samples * classes, dtype=int)
    for class_number in range(classes):
        ix = range(samples * class_number, samples * (class_number + 1))
        r = np.linspace(0.0, 1, samples)
        t = np.linspace(class_number * 4, (class_number + 1) * 4, samples) + np.random.randn(samples) * 0.2
        X[ix] = np.c_[r * np.sin(t), r * np.cos(t)]
        y[ix] = class_number
    return X, y

# Create dataset
X, y = generate_spiral_data(samples=100, classes=3)

# --- Define Meta Neural Network for Tuning SMA ---
class MetaNN(nn.Module):
    def __init__(self, input_size, output_size):
        super(MetaNN, self).__init__()
        self.fc1 = nn.Linear(input_size, 32)
        self.fc2 = nn.Linear(32, output_size)
        self.relu = nn.ReLU()
    
    def forward(self, x):
        x = self.relu(self.fc1(x))
        return self.fc2(x)

# --- Define Fitness Function for SMA ---
def fitness_function(anchors):
    """Fitness function: Measures classification accuracy using anchor points."""
    anchors = np.array(anchors, dtype=np.float32).reshape(num_anchors_per_class * 3, 2)  # e.g., 15 points
    predictions = np.zeros(len(X), dtype=int)
    
    for i, point in enumerate(X):
        distances = np.linalg.norm(anchors - point, axis=1)
        min_idx = np.argmin(distances)
        predictions[i] = min_idx // num_anchors_per_class  # Map to class (e.g., 0-4: class 0)
    
    accuracy = (predictions == y).mean()
    return -accuracy  # Minimize negative accuracy

# --- Setup SMA Parameters ---
num_anchors_per_class = 5  # More anchors to capture spiral shape
total_anchors = num_anchors_per_class * 3  # 15 anchors total
dim = total_anchors * 2  # 30 dimensions (x, y for each anchor)

# --- Train MetaNN and SMA ---
meta_nn = MetaNN(input_size=3, output_size=3)  # Inputs: [Loss, Diversity, Iteration]
meta_optimizer = optim.Adam(meta_nn.parameters(), lr=0.001)

best_accuracy = 0
best_anchors_global = None

for episode in range(100):
    # State: Use previous accuracy (or random initially), diversity placeholder, iteration
    state = torch.tensor([1 - best_accuracy if episode > 0 else np.random.rand(), 
                          np.random.rand(), episode / 100.0], dtype=torch.float32)
    
    # Predict SMA hyperparameters
    suggested_params = meta_nn(state)
    num_individuals = int(torch.abs(suggested_params[0]) * 50) + 10  # 10-60 individuals
    c1 = torch.clamp(torch.abs(suggested_params[1]), min=1.5, max=3.0)
    c2 = torch.clamp(torch.abs(suggested_params[2]), min=0.1, max=1.0)

    # Define SMA (random initialization since set_initial_population isn’t available)
    sma = SMA(num_individuals=num_individuals, dim=dim, lower_bound=-1, upper_bound=1, 
              max_iter=100, c1=c1, c2=c2, w=0.5, minimize=True, verbose=False)
    sma.set_objective(fitness_function)
    
    # Run optimization
    sma.optimize(iterations=100)
    best_anchors = np.array(sma.get_best_solution(), dtype=np.float32).reshape(total_anchors, 2)

    # Compute accuracy
    predictions = np.array([np.argmin(np.linalg.norm(best_anchors - point, axis=1)) // num_anchors_per_class 
                            for point in X])
    final_accuracy = (predictions == y).mean()

    # Update best solution
    if final_accuracy > best_accuracy:
        best_accuracy = final_accuracy
        best_anchors_global = best_anchors.copy()

    # Train MetaNN (pseudo-reinforcement)
    meta_optimizer.zero_grad()
    reward = torch.tensor(final_accuracy, dtype=torch.float32)
    loss = -reward * suggested_params.sum()  # Encourage params that improve accuracy
    loss.backward()
    meta_optimizer.step()

    print(f"Episode {episode}: Num_Individuals={num_individuals}, c1={c1:.2f}, c2={c2:.2f}, "
          f"Accuracy={final_accuracy:.4f}, Best Accuracy={best_accuracy:.4f}")

# --- Visualizing Decision Boundary and Anchors ---
def plot_decision_boundary(anchors, X, y):
    xx, yy = np.meshgrid(np.linspace(X[:, 0].min()-0.5, X[:, 0].max()+0.5, 100),
                         np.linspace(X[:, 1].min()-0.5, X[:, 1].max()+0.5, 100))
    grid = np.c_[xx.ravel(), yy.ravel()]
    
    predictions = np.array([np.argmin(np.linalg.norm(anchors - point, axis=1)) // num_anchors_per_class 
                            for point in grid]).reshape(xx.shape)
    
    plt.figure(figsize=(10, 8))
    plt.contourf(xx, yy, predictions, alpha=0.3, cmap="coolwarm")
    plt.scatter(X[:, 0], X[:, 1], c=y, cmap="coolwarm", edgecolor="k", label="Data")
    plt.scatter(anchors[:, 0], anchors[:, 1], c="black", marker="x", s=100, label="Anchors")
    plt.title("SMA-Tuned Anchor Points and Decision Boundary")
    plt.xlabel("Feature 1")
    plt.ylabel("Feature 2")
    plt.legend()
    plt.show()

# Plot the result
plot_decision_boundary(best_anchors_global, X, y)