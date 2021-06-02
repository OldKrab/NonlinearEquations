import matplotlib.pyplot as plt
from matplotlib.colors import LightSource
import numpy as np
s_file_name = R"D:\GoogleDrive\sync\source\clion\NonlinearEquations\out.txt"

with open(s_file_name) as s_in:
    xs = [float(num) for num in s_in.readline().strip().split()]
    ys = [float(num) for num in s_in.readline().strip().split()]
    zs = [float(num) for num in s_in.readline().strip().split()]
    rx = [float(num) for num in s_in.readline().strip().split()]
    ry =  [float(num) for num in s_in.readline().strip().split()]
    rx, ry = list(zip(*set(zip(rx, ry))))
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    ax.plot_trisurf(xs, ys, zs)
    for i in range(len(rx)):
        ax.plot([rx[i], rx[i]], [ry[i], ry[i]], [0, 10])
    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')
    plt.show()
