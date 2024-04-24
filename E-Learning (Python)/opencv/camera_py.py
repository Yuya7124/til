import cv2
import math
import pyocr
from PIL import Image
import pyocr.builders
import numpy as np
from keras.api.datasets.mnist import load_data
from keras.api.models import Sequential, load_model
from keras.src.layers import Dense, Activation ,Conv2D, Flatten, MaxPooling2D, Dropout, Reshape
from keras.src.utils.numerical_utils import to_categorical

height = 28 
width = 28
(x_train, y_train), (x_test, y_test) = load_data()

x_train = np.array(x_train) / 255
x_test = np.array(x_test) / 255

y_train = to_categorical(y_train)
y_test = to_categorical(y_test)

tools = pyocr.get_available_tools()
tool = tools[0]

h5_file = "h5/drawing_text_test.h5"
cap_file = "image/capture/sample.png"

# モデル構築
model = Sequential()

def mnist(model):
  layers(model)
  # cv2.namedWindow('src')
  # cv2.namedWindow('dst')
  
  # コンパイル
  model.compile(optimizer="sgd", loss="categorical_crossentropy", metrics=["accuracy"])
  
  learning(model)

  # モデル保存
  model.save(h5_file)
  # モデル削除
  del model

def layers(model):
  # 畳み込み層追加
  model.add(Reshape((height, width, 1)))

  # 畳み込み層1
  model.add(Conv2D(32, (3, 3)))
  model.add(Activation("relu"))

  # 畳み込み層2
  model.add(Conv2D(32, (3, 3)))
  model.add(Activation("relu"))

  # ブーリング層
  model.add(MaxPooling2D(2, 2))
  model.add(Dropout(0.5))

  # 畳み込み層3
  model.add(Conv2D(16, (3, 3)))
  model.add(Activation("relu"))
  
  # ブーリング層2
  model.add(MaxPooling2D(2, 2))
  model.add(Dropout(0.5))

  model.add(Flatten())
  # 全結合層
  model.add(Dense(height * width))
  model.add(Activation("relu"))
  model.add(Dropout(0.5))

  # 出力層
  model.add(Dense(10))
  model.add(Activation("softmax"))

def learning(model):
  # 学習実行
  hist = model.fit(x_train, y_train, batch_size=200, epochs=10, verbose=1, validation_split=0.1)
  
  # 評価
  score = model.evaluate(x_test, y_test, verbose=1)
  print("Acc: ", score[1])

def camera(model):
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
    ch = cv2.waitKey(1) & 0xFF

    prop_val = cv2.getWindowProperty('src', cv2.WND_PROP_ASPECT_RATIO)
    if ch == ord('q') or (prop_val < 0) :
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
  # グレースケール変換
  img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
  
  # 2値化処理
  _, th = cv2.threshold(img, 0, 255, cv2.THRESH_OTSU)
  th = cv2.bitwise_not(th)
  th = cv2.GaussianBlur(th,(9,9), 0)
  cv2.imwrite(cap_file, th)

mnist(model)
camera(model)

Xt = []
img = cv2.imread(cap_file, 0)
img = cv2.resize(img, (int(width), int(height)), cv2.INTER_CUBIC)

Xt.append(img)
Xt = np.array(Xt) / 255

# 学習済みモデルロード
model = load_model(h5_file)

# 判定
predict = model.predict(Xt)
result = np.argmax(predict, axis=1)
print(result[0])