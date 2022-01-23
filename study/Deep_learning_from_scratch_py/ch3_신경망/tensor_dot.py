#%%

import numpy as np
import matplotlib.pyplot as plt


def step_func(x):
    y = x > 0
    return y.astype(int)


def sigmoid_func(x):
    return 1 / (1 + np.exp(-x))


def relu_func(x):
    return np.maximum(0, x)


def print_graph(ranges, values):
    plt.plot(ranges, values)
    plt.show()


print("--- tensor dot without bias and activation func ---")
x = np.array([0.5, -0.3])
w = np.array([[0.5, 0.7, -1], [-0.1, 0.2, -0.6]])
y = np.dot(x, w)
print(y)

print("--- tensor dot with bias and activation func ---")
b = np.array([-0.3, 0.2, 0.4])
z = relu_func(np.dot(x, w) + b)
print(z)


# %%
