import networkx as nx
import random
from tqdm import tqdm
import time


def generate_acyclic_graph(num_nodes, num_edges):
    graph = nx.DiGraph()
    nodes = list(range(num_nodes))
    graph.add_nodes_from(nodes)

    edges_added = 0

    with tqdm(total=num_edges) as pbar:
        while nx.number_of_edges(graph) < num_edges:
            node_from = random.choice(nodes)
            node_to = random.choice(nodes)

            if node_from != node_to:

                graph.add_edge(node_from, node_to)
                edges_added += 1
                pbar.update(1)

                if not nx.is_directed_acyclic_graph(graph):
                    graph.remove_edge(node_from, node_to)
                    edges_added -= 1

    return list(graph.edges())


def create_tests():
    n = int(input("Input n:"))
    f = open('{}.in'.format(10), 'w')
    num_edges = .5 * (n * (n - 1) / 2)
    acyclic_graph_edges = generate_acyclic_graph(n, num_edges)

    f.write('{} {}\n'.format(n, int(num_edges)))
    f.write('{}'.format(' \n'.join([str(edge).replace("(", "").replace(")", "").replace(",", "")
                                    for edge in acyclic_graph_edges])))
    f.close()


if __name__ == '__main__':
    create_tests()
