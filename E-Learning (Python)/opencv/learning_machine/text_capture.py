import cv2
import numpy as np
import pyocr
from keras.api.models import load_model
from PIL import Image

import text_list

h5_file = "h5/drawing_text_test.h5"
cap_file = "image/capture/"
img_file = "image/"
img_type = ".png"

textList = text_list.char_list()

def draw_num(width, height):
  for i in range(0, 11):
    Xt = []
    filename = cap_file + "draw_font/" + str(i) + img_type
    img = cv2.imread(filename, 0)
    img = cv2.resize(img, (int(width), int(height)), cv2.INTER_CUBIC)

    Xt.append(img)
    Xt = np.array(Xt) / 255

    # 学習済みモデルロード
    model = load_model(h5_file)

    # 判定
    predict = model.predict(Xt)
    result = np.argmax(predict, axis=1)
    print(f"{filename}: {textList[result[0]]}")

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
  print(f"{textList[result[0]]}")
  
  return result[0]

def ocr_engine(filepass):
  tools = pyocr.get_available_tools()
  tool = tools[0]

  txt = tool.image_to_string(Image.open(filepass), lang="eng", builder=pyocr.builders.TextBuilder(tesseract_layout=10))
  print(f"{filepass}:  {txt}")

print(draw_free(cap_file + "screen_shot.png", 28, 28))