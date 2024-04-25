import cv2
import numpy as np
from keras.api.models import load_model

height = 28 
width = 28

h5_file = "h5/drawing_text_test.h5"
cap_file = "image/capture/"
img_type = ".png"

def draw_num():
  for i in range(0, 10):
    Xt = []
    filename = cap_file + 'draw_font/' + str(i) + img_type
    img = cv2.imread(filename, 0)
    img = cv2.resize(img, (int(width), int(height)), cv2.INTER_CUBIC)

    Xt.append(img)
    Xt = np.array(Xt) / 255

    # 学習済みモデルロード
    model = load_model(h5_file)

    # 判定
    predict = model.predict(Xt)
    result = np.argmax(predict, axis=1)
    print(f'{filename}: {result[0]}')

def draw_free():
  Xt = []
  filename = cap_file + 'sample' + img_type
  img = cv2.imread(filename, 0)
  img = cv2.resize(img, (int(width), int(height)), cv2.INTER_CUBIC)

  Xt.append(img)
  Xt = np.array(Xt) / 255

  # 学習済みモデルロード
  model = load_model(h5_file)

  # 判定
  predict = model.predict(Xt)
  result = np.argmax(predict, axis=1)
  print(f'{filename}: {result[0]}')

draw_num()
# draw_free()