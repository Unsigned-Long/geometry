# coding:utf-8

import matplotlib.pyplot as plt
import csv
import numpy as np
import math

opname = './nearest1.csv'
spname = './nearest2.csv'

# opname = './radius1.csv'
# spname = './radius2.csv'

def readOPoints(filename):
    x = []
    y = []
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        for point in reader:
            x.append(float(point[0]))
            y.append(float(point[1]))
    return x, y

def readSPoints(filename):
    x = []
    y = []
    d = []
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        for point in reader:
            x.append(float(point[0]))
            y.append(float(point[1]))
            d.append(4.0*float(point[2]))
    return x, y, d


opx, opy = readOPoints(opname)
spx, spy, spd = readSPoints(spname)
tp = [0, 0]

plt.rcParams["font.family"] = "Ubuntu Mono"
plt.rcParams['font.size'] = 13

for i in range(len(spx)):
    plt.plot([tp[0], spx[i]], [tp[1], spy[i]], c='g', linestyle='--')

plt.scatter(opx, opy, label='origin points', c='r', marker='X')
plt.scatter(spx, spy, label='searched points', c='g', s=spd)
# plt.scatter(spx, spy, label='searched points', c='g')
plt.scatter(tp[0], tp[1], label='target point', c='b', marker='^', s=100)


# alpha = np.linspace(0.0, 2.0*math.pi, 100)
# x = 50.0*np.cos(alpha) + 0
# y = 50.0*np.sin(alpha) + 0
# plt.plot(x, y, linestyle='--')

plt.xlabel('X(m)')
plt.ylabel('Y(m)')
plt.grid(ls='--', alpha=0.5)

# plt.title('Radius Search on Kd-Tree [radius = 65.0]')
plt.title('K Nearest Search on Kd-Tree [K = 5]')

plt.legend()

plt.show()
