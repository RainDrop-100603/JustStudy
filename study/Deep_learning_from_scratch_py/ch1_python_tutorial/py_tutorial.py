#%%

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.image import imread


# class Hungry:
#     def __init__(self, name):
#         self.name = name
#         print("init!")

#     def hello(self):
#         print(f"hello {self.name}")

#     def goodbye(self):
#         print(f"goodbye {self.name}")


# h = Hungry("Park")
# h.hello()
# h.goodbye()

# x = np.array([1.0, 2.0, 3.0])
# print(x)
# print(type(x))

# y = np.array([-2.0, 3.5, 3.7])
# print(x + y)
# print(x - y)
# print(x * y)
# print(x / y)

# print(x.shape)
# z = np.array([x, y])
# print(z)
# print(z.shape)
# print(z.dtype)

# q = np.array([y, x])
# print(z * q)

print("----------------------matplotlib-----------------")

x1 = np.arange(0, 6, 0.1)
y1 = np.sin(x1)
y2 = np.cos(x1)

plt.plot(x1, y1, label="sin")
plt.plot(x1, y2, label="cos", linestyle="--")
plt.xlabel("x")
plt.ylabel("y")
plt.title("sin & cos")  # 각 선이 무엇을 나타내는지 label해주는 박스 추가
plt.show()

img = imread("img1.jpg")

plt.imshow(img)
plt.show()


# %%
