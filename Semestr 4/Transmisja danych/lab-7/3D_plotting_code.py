import json
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.patches import Patch

# wybor konfiguracji
# filename = 'ber_results_pierwsza.json'
filename = 'ber_results_druga.json'

# Load JSON data from file using the variable
with open(filename, 'r') as f:
    data = json.load(f)

# Extract data for plotting
keying_methods = list(data['results'].keys())
x_values = list(map(float, data['results'][keying_methods[0]].keys()))
y_values = list(map(float, data['results'][keying_methods[0]][str(x_values[0])].keys()))

# Reverse the x_values and corresponding data
x_values = x_values[::-1]

# Create 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Define colors for each keying method
colors = ['blue', 'green', 'red']

# Plot bars for each combination of alfa and beta values
dx = dy = 0.2  # Width and depth of bars
for i, x in enumerate(x_values):
    for j, y in enumerate(y_values):
        z_values = [data['results'][keying_method][str(x)][str(y)] for keying_method in keying_methods]
        x_pos = np.arange(len(keying_methods)) * dx - dx / 2 + i  # Adjust x-position for each bar
        ax.bar3d(x_pos, j, np.zeros(len(z_values)), dx, dy, z_values, color=colors, zsort='average')

# Set labels and title
ax.set_xlabel('alfa')
ax.set_ylabel('beta')
ax.set_zlabel('BER')

name_parts = filename.split('_')
graph_name = name_parts[2].split('.')[0]

ax.set_title(f'{graph_name} konfiguracja')

# Create legend
legend_elements = [Patch(facecolor=color, edgecolor=color, label=keying_method) for color, keying_method in zip(colors, keying_methods)]
ax.legend(handles=legend_elements)

# Set x-ticks and labels for reversed x-axis
x_ticks = np.arange(len(x_values))
x_ticklabels = [str(round(x, 1)) for x in np.linspace(1, 0, len(x_values))]

ax.set_xticks(x_ticks)
ax.set_xticklabels(x_ticklabels)

# Show plot
plt.show()
