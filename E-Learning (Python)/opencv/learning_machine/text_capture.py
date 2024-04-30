import cv2
import numpy as np
import pyocr
from keras.api.models import load_model
from PIL import Image

h5_file = "h5/drawing_text_test.h5"
cap_file = "image/capture/"
img_file = "image/"
img_type = ".png"

def draw_num(width, height):
  for i in range(0, 11):
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

def draw_free(filename, width, height):
  Xt = []
  img = cv2.imread(filename, 0)
  img = cv2.resize(img, (int(width), int(height)), cv2.INTER_CUBIC)

  Xt.append(img)
  Xt = np.array(Xt) / 255

  # 学習済みモデルロード
  model = load_model(h5_file)

  # 判定
  predict = model.predict(Xt)
  result = np.argmax(predict, axis=1)

  return result[0]

def ocr_engine(filepass):
  tools = pyocr.get_available_tools()
  tool = tools[0]

  txt = tool.image_to_string(Image.open(filepass), lang="eng")
  print(f'{filepass}:\n{txt}')

# filename = cap_file + 'screen_shot' + img_type
# draw_num(28, 28)
# print(f'{filename}: {draw_free(filename, 28, 28)}')
# ocr_engine(filename)