#%%
# coding: utf-8
import sys, os
import numpy as np
from deeplearning_data.mnist import load_mnist
from PIL import Image


def img_show(img):
    pil_img = Image.fromarray(np.uint8(img))
    pil_img.show()


(x_train, t_train), (x_test, t_test) = load_mnist(flatten=True, normalize=False)

show_idx = 7  # idx 번째 이미지 출력

img = x_train[show_idx]
label = t_train[show_idx]
print(label)  # 5

print(img.shape)  # (784,)
img = img.reshape(28, 28)  # 형상을 원래 이미지의 크기로 변형
print(img.shape)  # (28, 28)

img_show(img)

#%%
# %%
