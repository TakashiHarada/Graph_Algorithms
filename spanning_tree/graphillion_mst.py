# use Python3.7 instead of Python3.9
# input form is the following
# |V| |E|
# e_1
# e_2
# ...
# e_|E|
# u_1 u_2 ... u_k (terminal set)

import sys
from graphillion import GraphSet

lines = sys.stdin.readlines()
lines = [line.rstrip() for line in lines]

edges = []
for line in lines[1:(len(lines)-1)]:
    e = line.split(' ')
    edges.append((e[0], e[1], int(e[2])))

terminals = lines[len(lines)-1].split(' ')
print("U = " + str(terminals))
    
es = []
ws = []
for a in edges:
    es.append((a[0], a[1]))
    ws.append(a[2])

ds = dict(zip(es, ws))
    
G = GraphSet.set_universe(edges)
T = GraphSet.trees(root=terminals[0])

for t in terminals[1:]:
    T = T.including(t)

s = 0
for e in next(T.min_iter()):
    print(str(e) + " " + str(ds[e]))
    s += ds[e]

print("weight = " + str(s))
