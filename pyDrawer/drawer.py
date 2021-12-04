# coding:utf-8
import matplotlib.pyplot as plt

plt.xkcd()
plt.rcParams["font.family"] = "Ubuntu Mono"
plt.rcParams["font.size"] = 13


def drawer_point2():
    plt.scatter([0, 1, 4, 2], [0, 3, 2, 2], label='Point2i')
    plt.scatter([1.3, 1.5, 7.5, 3.2], [9.7, 1.3, 4.2, 2.2], label='Point2f')
    plt.legend()
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Point[2d]')
    plt.show()


def drawer_rectangle():
    plt.plot([0, 0, 2, 2, 0], [0, 1, 1, 0, 0],
             label='Rectangle2i', marker='o', markersize=3)
    plt.plot([1.5, 1.5, 2.7, 2.7, 1.5], [0.5, 2.8, 2.8, 0.5, 0.5],
             label='Rectangle2f', marker='o', markersize=3)
    plt.legend()
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Rectangle[2d]')
    plt.show()


def drawer_triangle():
    plt.plot([0, 2, 2, 0], [0, -1, 5, 0],
             label='Triangle2i', marker='o', markersize=3)
    plt.plot([2.5, 0.5, 1.2, 2.5], [0.5, 2.5, 4.5, 0.5],
             label='Triangle2f', marker='o', markersize=3)
    plt.legend()
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Triangle[2d]')
    plt.show()


def drawer_linestring():
    plt.plot([0, 1, 2, 2], [0, -1, 5, 1],
             label='LineString2i', marker='o', markersize=3)
    plt.plot([2.5, -0.5, 1.2, 0.0], [-0.5, 2.5, 4.5, 4.0],
             label='LineString2f', marker='o', markersize=3)
    plt.legend()
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('LineString[2d]')
    plt.show()


def drawer_line():
    plt.plot([0, 1], [-5, 3],
             label='Line2i', marker='o', markersize=3)
    plt.plot([2.5,  1.2], [-0.5, 4.5],
             label='Line2f', marker='o', markersize=3)
    plt.legend()
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Line[2d]')
    plt.show()


def drawer_polygon():
    plt.plot([0, 1, 2, 3, 2, 0], [0, 3, 5, 2, 1, 0],
             label='Polygon2i', marker='o', markersize=3)
    plt.plot([2.5, -0.5, 1.2, 3.0, 3.5, 2.5], [-0.5, 2.5, 4.5, 3.0, 1.0, -0.5],
             label='Polygon2f', marker='o', markersize=3)
    plt.legend()
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Polygon[2d]')
    plt.show()


if __name__ == "__main__":
    # drawer_point2()
    # drawer_rectangle()
    # drawer_triangle()
    # drawer_linestring()
    # drawer_line()
    # drawer_polygon()
    pass
