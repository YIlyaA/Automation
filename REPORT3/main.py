import os
import subprocess
import math
from matplotlib import pyplot as plt
import networkx as nx
import random


def mkdir(directory):
    try:
        os.mkdir(directory)
    except FileExistsError:
        pass


def generate_acyclic_graph(num_nodes, num_edges):
    graph = nx.DiGraph()
    nodes = list(range(num_nodes))
    graph.add_nodes_from(nodes)
    while nx.number_of_edges(graph) < num_edges:
        node_from = random.choice(nodes)
        node_to = random.choice(nodes)

        if node_from != node_to:
            if nx.is_directed_acyclic_graph(graph) or not nx.has_path(graph, node_to, node_from):
                graph.add_edge(node_from, node_to)

    return list(graph.edges())


def create_tests(test_dir, test_sizes):
    mkdir(test_dir)
    for ts in test_sizes:
        f = open('{}/{}.in'.format(test_dir, ts), 'w')
        num_edges = ts * (ts - 1) / 2
        acyclic_graph_edges = generate_acyclic_graph(ts, num_edges)

        f.write('{} {}\n'.format(ts, int(num_edges)))
        f.write('{}'.format(' \n'.join([str(edge).replace("(", "").replace(")", "").replace(",", "")
                                        for edge in acyclic_graph_edges])))
        f.close()


def compile_sources(sources, bins, v=False):
    mkdir(bins)
    for code in os.listdir(sources):
        bin_name = code.split('.')[0]
        ext = code.split('.')[1]
        if ext == 'cpp':
            command = ['g++', '{}/{}'.format(sources, code), '-o', '{}/{}'.format(bins, bin_name)]
        else:
            command = ['gcc', '{}/{}'.format(sources, code), '-o', '{}/{}'.format(bins, bin_name), '-lm']
        a = subprocess.run(command, capture_output=True)
        print('Executing: {}'.format(' '.join(command)))
        if v:
            print(a.stdout.decode('utf-8'))
            print(a.stderr.decode('utf-8'))


def run_algo(bins, test_dir, result_dir, ts, algo, v=False):
    mkdir(result_dir)
    f_in_n = '{}/{}.in'.format(test_dir, ts)
    f_out_n = '{}/{}_{}.out'.format(result_dir, algo, ts)
    f_in = open(f_in_n, 'r')
    f_out = open(f_out_n, 'w')
    command = ['{}/{}'.format(bins, algo)]
    subprocess.run(command, stdin=f_in, stdout=f_out)
    if v:
        print(command, f'in={f_in_n}, out={f_out_n}')
    f_in.close()
    f_out.close()


def read_results(times):
    res = {}
    for file in os.listdir(times):
        algo, size, _, string = file.split('_')

        if algo not in res:
            res[algo] = {'x': [], 'y': []}

        res[algo]['x'].append(int(size))

        f = open(times + '/' + file, 'r')
        for line in f:
            if 'user' in line:
                y = line.split()[1]
                # y = float(m)*60 + float(s)

        f.close()
        res[algo]['y'].append(float(y))
    return res


def plot_graf(dictionary, marker, linestyle, undtitle=False):
    # print(dictionary)
    for algo in dictionary:
        if algo == "BST":
            linestyle = '--'
        x = sorted(dictionary[algo]['x'])
        y = sorted(dictionary[algo]['y'])
        plt.plot(x, y, marker=marker, linestyle=linestyle, label=algo)

        # plt.gca().yaxis.set_major_formatter(ticker.FormatStrFormatter('%.2e'))
        plt.xlabel("ilość danych wejściowych")
        plt.ylabel("sekundy (s)")
        plt.yscale('log')
    if undtitle:
        plt.figtext(0.5, -0.02, "*Dla małych liczb czas dla AVL poniżej dolnej granicy pomiaru.*",
                    ha='center',
                    fontsize=10,
                    fontstyle='italic')
    plt.legend(bbox_to_anchor=(1.02, 1), loc='upper left', borderaxespad=0)
    plt.show()
