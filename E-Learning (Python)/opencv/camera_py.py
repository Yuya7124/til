import cv2
import math
import pyocr
from PIL import Image
import pyocr.builders
import numpy as np
from keras.api.datasets import mnist
from keras.api.models import Sequential, load_model
from keras.src.layers.core import Dense, Activation
from keras.src.layers import Conv2D, MaxPooling2D, Dropout, Reshape
from keras.src.utils import np_utils

def mnist():
  height = 28 
  width = 28
  (x_train, y_train), (x_test, y_test) = mnist.load_data()

  x_train = x_train.reshape(60000, height * width) / 255
  x_test = x_test.reshape(10000, height * width) / 255

  y_train = np_utils.to_categorical(y_train)
  y_test = np_utils.to_categorical(y_test)

  model = Sequential()
  model.add(Dense(512, input_dim=(height * width)))
  model.add(Activation("relu"))

  # 出力層
  model.add(Dense(10))
  model.add(Activation("softmax"))

  cv2.namedWindow('src')
  cv2.namedWindow('dst')
  
  model.compile(loss="catrgorical_crossentropy", optimizer="sgd", metrics=["accuracy"])

  hist = model.fit(x_train, y_train, batch_size= 200, verbose=1, epochs=10, validation_split=0.1)

  score = model.evaluate(x_test, y_test, verbose=1)
  print("Acc: ", score[1])

tools = pyocr.get_available_tools()
tool = tools[0]

def camera():
  cap = cv2.VideoCapture(0)
  while True:
    ret, img_src = cap.read()
    height, width, _ = img_src.shape[:3]

    height_center = height // 2
    width_center = width // 2

    img = cv2.resize(img_src, (int(width), int(height)))

    # OCRで読み取りたい領域
    cv2.rectangle(img, (width_center-71, height_center-71)
                     , (width_center+71, height_center+71)
                     , (255, 255, 0)
                     , 5)
    
    ocr(img, width, height)
    # img_dst = cv2.flip(img_src, filpCode = 0)

    cv2.imshow('src', img)  # 入力画像表示
    # cv2.imshow('dst', img_dst)  # 出力画像表示
    ch = cv2.waitKey(1)
    if ch == ord('q'):
      break
    elif ch == ord('s'):
      flash(img, height_center, width_center)
      break
    
  cap.release()
  cv2.destroyAllWindows()

def ocr(img, width, height):
  img_dst = img[100:height-200, 100:width-200]
  PIL_Image = Image.fromarray(img_dst)
  text = tool.image_to_string(PIL_Image, lang='eng', builder=pyocr.builders.TextBuilder())
  if text != "" :
    print(text)

def flash(frame, height, width):
  img = frame[height-70:height+70, width-70:width+70]
  img =cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

  _, th = cv2.threshold(img, 0, 255, cv2.THRESH_OTSU)
  th = cv2.bitwise_not(th)
  th = cv2.GaussianBlur(th,(9,9), 0)
  cv2.imwrite('image/capture/frame_img.png', img)

# camera()
mnist()
