import sys, os
from deeplearning_data.mnist import load_mnist
import numpy as np
import pickle
from common.functions import sigmoid, softmax


def cross_entropy_error(y, t):
    # one-hot encoding -> 정답은 [0,0,1,0,0] 과 같은 식
    if y.ndim == 1:
        t = t.reshape(1, t.size)
        y = y.reshape(1, y.size)

    batch_size = y.shape[0]
    # y는 [0.3 0.6 0.1], t는 [0,1,0]과 같이 생겨서, t를 곱하면 정답만 계산하게 된다.
    return -np.sum(t * np.log(y + 1e-10)) / batch_size


def cross_entropy_error2(y, t):
    # not one-hot encoding -> 정답은 2와 같이 단답
    if y.ndim == 1:
        t = t.reshape(1, t.size)
        y = y.reshape(1, y.size)

    batch_size = y.shape[0]
    # numpy 배열이기에 가능한 연산, 정확한 해석은 programming_tips/python.txt 를 참고하자
    return -np.sum(np.log(y[np.arange(batch_size), t] + 1e-10)) / batch_size


def get_data():
    (x_train, t_train), (x_test, t_test) = load_mnist(
        normalize=True, flatten=True, one_hot_label=False
    )
    return x_test, t_test


def init_network():
    with open("sample_weight.pkl", "rb") as f:
        network = pickle.load(f)
    return network


def predict(network, x):
    W1, W2, W3 = network["W1"], network["W2"], network["W3"]
    b1, b2, b3 = network["b1"], network["b2"], network["b3"]

    a1 = np.dot(x, W1) + b1
    z1 = sigmoid(a1)
    a2 = np.dot(z1, W2) + b2
    z2 = sigmoid(a2)
    a3 = np.dot(z2, W3) + b3
    y = softmax(a3)

    return y


# prepare
x, t = get_data()
network = init_network()
idx = 10
batch_size = 10

# individual
# yk = predict(network, x[idx])
# tk = t[idx]
# print(cross_entropy_error(yk, tk))


# batch
x_batch = x[idx : idx + batch_size]
y_batch = predict(network, x_batch)
t_batch = t[idx : idx + batch_size]
print(np.sum(cross_entropy_error2(y_batch, t_batch)))

# batch 검증, 작은 오차는 delta및 부동소수점 연산오류로 인해 생길 수 있다.
sums = 0
for i in np.arange(batch_size):
    yk = predict(network, x[idx + i])
    tk = t[idx + i]
    sums += cross_entropy_error2(yk, tk)
print(sums / batch_size)
