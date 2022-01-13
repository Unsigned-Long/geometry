# coding:utf-8

from ctypes import sizeof
import matplotlib.pyplot as plt
import csv
import numpy


filename = './data.csv'

plt.rcParams["font.family"] = "Ubuntu Mono"
plt.rcParams["font.size"] = 13

x = []
y = []

with open(filename, 'r') as file:
    reader = csv.reader(file)
    for line in reader:
        x.append(float(line[0]))
        y.append(float(line[1]))

color = numpy.random.random(len(x))

plt.scatter(x, y, label='random points', c=color, alpha=0.75, marker='+')

plt.grid(ls='--', alpha=0.5)
plt.legend()

plt.title('random generator')

plt.show()
