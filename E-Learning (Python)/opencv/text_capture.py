import cv2
import numpy as np
from keras.api.datasets import mnist
from keras.api.models import Sequential, load_model
from keras.src.layers.core import Dense, Activation, Flatten
from keras.src.layers import Conv2D, MaxPooling2D, Dropout, Reshape
from keras.src.utils import np_utils

Xt = []
img = cv2.imread('image/capture/frame_img.png', 0)
img = cv2.resize(img, (28, 28), cv2.INTER_CUBIC)

Xt.append(img)
Xt = np.array(Xt) / 255