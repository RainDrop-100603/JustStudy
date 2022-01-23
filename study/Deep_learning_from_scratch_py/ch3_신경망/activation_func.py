#%%

import numpy as np
import matplotlib.pyplot as plt


def step_function(x):
    if x > 0:
        return 1
    else:
        return 0


def step_function2(x):
    y = x > 0
    return y.astype(int)


def sigmoid_func(x):
    return 1 / (1 + np.exp(-x))


def relu_func(x):
    return np.maximum(0, x)


def print_graph(ranges, values):
    plt.plot(ranges, values)
    plt.show()


x = 3
xRange = np.arange(-5.0, 5.0, 0.1)

print(step_function(x))
print_graph(xRange, step_function2(xRange))
print_graph(xRange, sigmoid_func(xRange))
print_graph(xRange, relu_func(xRange))

# %%
