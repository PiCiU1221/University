import re
import matplotlib.pyplot as plt
import networkx as nx

def process_graph_data(data):
    # Extract vertices and edges information
    vertex_pattern = re.compile(r"Vertex (\d+): \(([\d.]+), ([\d.]+)\)")
    edge_pattern = re.compile(r"Edge (\d+): \((\d+), (\d+)\), Weight: ([\d.]+)")

    vertices = {}
    edges = []

    for match in vertex_pattern.finditer(data):
        index, x, y = map(float, match.groups())
        vertices[int(index)] = (x, y)

    for match in edge_pattern.finditer(data):
        index, start, end, weight = map(float, match.groups())
        edges.append((start, end))

    # Create a graph
    G = nx.Graph()

    # Add vertices
    for index, (x, y) in vertices.items():
        G.add_node(index, pos=(x, y))

    # Add edges without using weights
    for start, end in edges:
        G.add_edge(start, end)

    return G

# Get input data from the user
print("Paste the graph data below (press Ctrl-C on a new line to finish input):")
data = ""
try:
    while True:
        line = input()
        data += line + "\n"
except KeyboardInterrupt:
    pass

# Split input into graphs using the "Vertex Count" line as a separator
graph_data_list = re.split(r"Vertex Count: \d+", data)[1:]

# Process each graph and accumulate edges
for i, graph_data in enumerate(graph_data_list, start=1):
    G = process_graph_data(graph_data)

    # Draw the graph
    pos = nx.get_node_attributes(G, 'pos')

    # Draw nodes as small dots
    nx.draw_networkx_nodes(G, pos, node_size=6, node_color='black')

    # Draw labels outside the nodes
    node_labels = nx.get_node_attributes(G, 'pos')
    for node, (x, y) in node_labels.items():
        plt.text(x - 0.02, y + 0.02, str(node), fontsize=5, color='blue', ha='left', va='center')

    # Draw gray edges for the current graph
    nx.draw_networkx_edges(G, pos, edgelist=G.edges(), edge_color=(0.8, 0.8, 0.8, 0.5), width=0.5)

# Draw red edges on top
nx.draw_networkx_edges(G, pos, edgelist=G.edges(), edge_color='red', width=0.5)

plt.show()