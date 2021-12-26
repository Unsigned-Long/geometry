# coding:utf-8
import matplotlib.pyplot as plt
import csv

plt.xkcd()
plt.rcParams["font.family"] = "Ubuntu Mono"
plt.rcParams["font.size"] = 13

filename = './output.csv'

x = []
y = []

with open(filename, 'r') as file:
    reader = csv.reader(file)
    for line in reader:
        x.append(float(line[0]))
        y.append(float(line[1]))

plt.plot(x, y, marker='X', mfc='r', ms=9, label='curve')

plt.legend()

plt.title('PolarCoor Curve')

plt.xlabel('X')
plt.ylabel('Y')

plt.show()
