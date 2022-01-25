#%%

import numpy as np
import matplotlib.pyplot as plt


def numerical_diff(x):
    def func(x):
        return x ** 2

    h = 1e-4
    return (func(x + h) - func(x - h)) / (2 * h)


def func1(x):
    return np.sum(x ** 2)


def numerical_gradient(f, x):
    h = 1e-4
    grad = np.zeros_like(x)

    for idx in range(x.size):
        tmp_x = x[idx]
        # f(x+h)
        x[idx] = tmp_val + h

        # 4.4절 구현하다 말았다.


def study_2d_diff():
    x = np.arange(-10, 10, 0.1)
    y = x ** 2
    n = numerical_diff(x)
    d = 2 * x
    plt.plot(x, y, label="func")
    plt.plot(x, n, label="numerical diff", marker="o")
    plt.plot(x, d, label="analytic diff")
    plt.legend()
    plt.show()


# study_2d_diff()

# %%
