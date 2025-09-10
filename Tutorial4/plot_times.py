import pandas as pd
import matplotlib.pyplot as plt

# Read the three files
seq = pd.read_csv("sequential_results.txt", sep=r"\s+", names=["n", "time"])
one_d = pd.read_csv("1d_partitioning_results.txt", sep=r"\s+", names=["n", "time"])
two_d = pd.read_csv("2d_partitioning_results.txt", sep=r"\s+", names=["n", "time"])

# Line plot
plt.figure(figsize=(8,6))
plt.plot(seq["n"], seq["time"], marker="o", linestyle="-", linewidth=2, label="Sequential")
plt.plot(one_d["n"], one_d["time"], marker="s", linestyle="-", linewidth=2, label="1D Partitioning")
plt.plot(two_d["n"], two_d["time"], marker="^", linestyle="-", linewidth=2, label="2D Partitioning")

plt.xlabel("Matrix size (n)")
plt.ylabel("Execution time (seconds)")
plt.title("Matrix-Vector Multiplication: Sequential vs 1D vs 2D Partitioning")
plt.legend()
plt.grid(True, linestyle="--", alpha=0.7)
plt.tight_layout()

# Save the figure as JPG
plt.savefig("matrix_multiply_times.jpg", format="jpg", dpi=300)

# Show the figure
plt.show()