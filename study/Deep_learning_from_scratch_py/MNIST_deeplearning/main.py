import sys, os
from mnist import load_mnist

# 처음 한 번은 다운로드를 해서 시간이 좀 걸린다.
(x_train, t_train), (x_test, t_test) = load_mnist(flatten=True, normalize=False)

# 각 데이터의 형상 출력
print(x_train.shape)  # (60000,784) , 784 = 28*28, train image
print(t_train.shape)  # (60000,), train label
print(x_test.shape)  # (10000,784), test image
print(t_test.shape)  # (10000,), test label 
