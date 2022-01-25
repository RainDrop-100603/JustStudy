#%%
import numpy as np
import matplotlib.pylab as plt
from mpl_toolkits.mplot3d import Axes3D


def study_3d_graph():

    x1 = x2 = np.arange(-5, 5, 0.1)
    x1, x2 = np.meshgrid(x1, x2)
    z = x1 ** 2 + x2 ** 2

    # fig = plt.figure(figsize=(6, 6))
    # ax = fig.add_subplot(projection="3d")
    # ax.scatter(x1, x2, z, marker="o", s=15, cmap="Greens")
    # plt.show()

    fig = plt.figure(figsize=(10, 6))
    # ax = fig.gca(projection="3d")
    ax = fig.add_subplot(projection="3d")
    surf = ax.plot_surface(
        x1,
        x2,
        z,
        rstride=2,
        cstride=2,
        cmap=plt.cm.coolwarm,
        linewidth=0.5,
        antialiased=True,
    )
    fig.colorbar(surf, shrink=0.5, aspect=5)


study_3d_graph()
# %%
