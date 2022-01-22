#%%

import numpy as np
import matplotlib.pyplot as plt


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

plt.plot(x1, y1)
plt.show()

# %%
