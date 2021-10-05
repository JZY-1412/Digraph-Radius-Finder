import networkx as nx
import random

all_digraph_size = [10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40, 50, 60, 70, 80, 90, 100]
for s in all_digraph_size:
    file_name = "graph_size_" + str(s) + ".txt"
    f = open(file_name, "w")
    digraph_size = [s] * 5000
    for size in digraph_size:
        g = nx.DiGraph()
        vertices = []
        for v in range(size):
            g.add_node(v)
            vertices.append(v)
        for v in vertices:
            for u in vertices:
                if v != u:
                    # connect = random.randrange(0, 100)
                    # if connect > 50:
                    g.add_edge(v, u)
        f.write(str(g.number_of_nodes()) + "\n")
        for v in g.nodes:
            line = ""
            for u in g.neighbors(v):
                line += str(u)
                line += " "
            line = line.strip()
            line += "\n"
            f.write(line)
    f.write("0\n")
    f.close()

