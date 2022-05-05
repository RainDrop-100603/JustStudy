import torch
import torch.optim as optim
import torch.nn as nn

torch.manual_seed(1)

"""
함수들 
    nn.Linear: Apply linaear transformation , Y = Ax+b
        .parameters(): 학습을 위해 
"""


def linear_regression():
    x_train = torch.FloatTensor([[1], [2], [3]])
    y_train = torch.FloatTensor([[5], [6], [7]])

    W = torch.zeros(1, requires_grad=True)
    b = torch.zeros(1, requires_grad=True)

    optimizer = optim.SGD([W, b], lr=0.01)
    epochs = 3000
    for epoch in range(epochs):
        H = x_train * W + b
        cost = torch.mean((H - y_train) ** 2)  # MSE 직접 구현

        optimizer.zero_grad()  # 이전 grad값이 남아 있을 수 있으니 0초기화
        cost.backward()  # grad back propagation
        optimizer.step()  # learning from lr and grad
        if (epoch + 1) % 300 == 0:
            print(
                "Epoch {:4d}/{} W: {:.3f} b: {:.3f} Cost: {:.6f}".format(
                    (epoch + 1), epochs, W.item(), b.item(), cost.item()
                )
            )


def linear_regression2():
    x_train = torch.FloatTensor([[1], [2], [3]])
    y_train = torch.FloatTensor([[5], [6], [7]])

    model = nn.linear(1, 1)  # input, output
    optimizer = optim.SGD(model.parameters(), lr=0.01)
    epochs = 3000
    for epoch in range(epochs):
        model = nn.Linear(input_dim, output_dim)
        cost = torch.mean((H - y_train) ** 2)  # MSE 직접 구현

        optimizer.zero_grad()  # 이전 grad값이 남아 있을 수 있으니 0초기화
        cost.backward()  # grad back propagation
        optimizer.step()  # learning from lr and grad
        if (epoch + 1) % 300 == 0:
            print(
                "Epoch {:4d}/{} W: {:.3f} b: {:.3f} Cost: {:.6f}".format(
                    (epoch + 1), epochs, W.item(), b.item(), cost.item()
                )
            )


linear_regression()
