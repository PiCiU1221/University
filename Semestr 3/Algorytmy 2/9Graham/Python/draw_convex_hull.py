import matplotlib.pyplot as plt

def parse_input(input_string):
    lines = input_string.strip().split('\n')

    # Extract the starting point
    start_point = tuple(map(float, lines[0].split()))

    # Find the index where the normal points count starts
    normal_count_index = 1
    while not lines[normal_count_index].strip().isdigit():
        normal_count_index += 1

    # Extract the normal points
    normal_point_count = int(lines[normal_count_index])
    normal_lines = [line for line in lines[normal_count_index + 1:normal_count_index + 1 + normal_point_count] if line.strip()]
    normal_points = [tuple(map(float, line.split())) for line in normal_lines]

    # Extract the convex hull points
    convex_hull_point_count = int(lines[normal_count_index + 1 + normal_point_count])
    convex_hull_points = [tuple(map(float, line.split())) for line in lines[normal_count_index + 2 + normal_point_count:]]

    return start_point, normal_points, convex_hull_points


# Get input data from the user
print("Paste the graph data below (press Ctrl-C on a new line to finish input):")
data = ""
try:
    while True:
        line = input()
        data += line + "\n"
except KeyboardInterrupt:
    pass

start_point, normal_points, convex_hull_points = parse_input(data)

# Plotting
plt.scatter(*start_point, color='black', label='Starting Point', marker='o', edgecolors='green', facecolors='none', s=300)
plt.scatter(*start_point, color='black', s=1)

# Extract x and y coordinates from normal points
normal_x, normal_y = zip(*normal_points)
plt.scatter(normal_x, normal_y, color='black', label='Normal Points', s=1)

# Connect the convex hull points with lines
convex_hull_x, convex_hull_y = zip(*convex_hull_points)
convex_hull_x += (convex_hull_x[0],)  # Connect the last point with the first to close the convex hull
convex_hull_y += (convex_hull_y[0],)

plt.plot(convex_hull_x, convex_hull_y, color='red', linestyle='-', linewidth=1, label='Convex Hull')

plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Convex Hull Visualization')
plt.show()
