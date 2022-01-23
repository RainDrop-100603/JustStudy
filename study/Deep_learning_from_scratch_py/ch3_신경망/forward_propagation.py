import numpy as np


def init_network():
    network = {}
    network["W1"] = np.array([[0.1, 0.2, -0.3], [-2.0, 5.0, 0.5]])
    network["b1"] = np.array([0.5, 2.2, -0.7])
    network["W2"] = np.array([[0.1, 0.4], [-1.0, -2.0], [0.3, 0.6]])
    network["b2"] = np.array([-2.0, 0.5])
    network["W3"] = np.array([[0.2, -0.3], [-2.0, 0.5]])
    network["b3"] = np.array([0.1, 0.2])

    return network


def sigmoid_func(x):
    return 1 / (1 + np.exp(-x))


def identity_func(x):
    return x


def softmax_func(x):
    max_x = np.max(x)
    exp_x = np.exp(x - max_x)
    exp_sum = np.sum(exp_x)
    return exp_x / exp_sum


def forward(network, x):
    W1, W2, W3 = network["W1"], network["W2"], network["W3"]
    b1, b2, b3 = network["b1"], network["b2"], network["b3"]

    z1 = sigmoid_func(b1 + np.dot(x, W1))
    z2 = sigmoid_func(b2 + np.dot(z1, W2))
    z3 = sigmoid_func(b3 + np.dot(z2, W3))

    return z3


network = init_network()
x = np.array([0, 1])
print(softmax_func(forward(network, x)))
