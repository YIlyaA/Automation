import networkx as nx
import random


def generate_acyclic_graph(num_nodes, num_edges):
    # Tworzenie pustego grafu skierowanego
    graph = nx.DiGraph()

    # Generowanie listy wierzchołków
    nodes = list(range(num_nodes))

    # Dodanie wierzchołków do grafu
    graph.add_nodes_from(nodes)

    # Dodanie krawędzi, aby zachować acykliczność
    while nx.number_of_edges(graph) < num_edges:
        # Losowo wybieramy wierzchołki
        node_from = random.choice(nodes)
        node_to = random.choice(nodes)

        if node_from != node_to:
            if nx.is_directed_acyclic_graph(graph) or not nx.has_path(graph, node_to, node_from):
                graph.add_edge(node_from, node_to)

    return list(graph.edges())


# Przykład użycia
num_nodes, num_edges = map(int, input().split())
acyclic_graph_edges = generate_acyclic_graph(num_nodes, num_edges)
print("Wygenerowane krawędzie acyklicznego grafu:")
for edge in acyclic_graph_edges:
    print(*edge)
