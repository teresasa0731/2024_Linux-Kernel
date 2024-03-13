import numpy as np
import matplotlib.pyplot as plt

node_t = []
time_t = []

node_m = []
time_m = []

with open('test.txt', 'r') as f:
    for line in f.readlines():
        line = line.strip('\n').split(",")
        node_t.append(int(line[0]))
        time_t.append(int(line[1]))

with open('main.txt', 'r') as f:
    for line in f.readlines():
        line = line.strip('\n').split(",")
        node_m.append(int(line[0]))
        time_m.append(int(line[1]))

plt.figure('compare')

plt.scatter(node_t,time_t,label = 'non-recursive')
plt.scatter(node_m,time_m,label = 'recursive')
plt.xlabel("num of nodes")
plt.ylabel("rebuild time")
plt.legend()
plt.show()