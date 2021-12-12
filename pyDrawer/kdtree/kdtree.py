# coding:utf-8

import matplotlib.pyplot as plt
import csv
import numpy as np
import math

opname = './originPoints.csv'
spname = './searchPoints.csv'


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

plt.rcParams["font.family"] = "Ubuntu Mono"
plt.rcParams['font.size'] = 13

plt.scatter(opx, opy, label='origin points', c='r', marker='X')
plt.scatter(spx, spy, label='searched points', c='g', s=spd)
plt.scatter(53, 25, label='target point', c='b', marker='^')

alpha = np.linspace(0.0, 2.0*math.pi, 100)
x = 65.0*np.cos(alpha) + 53
y = 65.0*np.sin(alpha) + 25
plt.plot(x, y, linestyle='--')

plt.xlabel('X(m)')
plt.ylabel('Y(m)')
plt.grid(ls='--', alpha=0.5)
plt.title('Radius Search on Kd-Tree [radius = 65.0]')

plt.legend()

plt.show()
