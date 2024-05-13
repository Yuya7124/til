import cv2
import numpy as np
import pyocr
import pyocr.builders
from keras.api.models import load_model
from PIL import Image

import text_list

h5_file = "h5/drawing_text_test.h5"
cap_file = "image/capture/"
img_file = "image/"
img_type = ".png"

textList = text_list.char_list()

text_builder = pyocr.builders.TextBuilder(tesseract_layout=6)
box_builder = pyocr.builders.WordBoxBuilder(tesseract_layout=6)

def draw_num(width, height):
  for i in range(0, 10):
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

def ocr_engine(filepass, builder):
  tools = pyocr.get_available_tools()
  tool = tools[0]
  img = Image.open(filepass)
  txt = tool.image_to_string(img, lang="eng", builder=builder)
  # print(f"{filepass}:  {txt}")

def read_text(filepass):
  out_texts = cv2.imread(filepass)
  txt_count = 0
  filepassList = []

  # 画像サイズ調整
  out_texts = img_size_control(out_texts)

  contours = img_binary(out_texts)

  # 文字検出
  for res in contours:
    x, y , w, h = cv2.boundingRect(res)
    bold = 1 # 線の太さ
    out_text = out_texts[(y + bold): (y + h - bold), (x + bold) : (x + w - bold)]
    filepassList.append(cap_file + "get_text3/get_text_" + str(txt_count) + img_type)
    cv2.imwrite(filepassList[txt_count], out_text)
    binary_data(filepassList[txt_count])
    result = draw_free(filepassList[txt_count], 28, 28)
    cv2.putText(out_texts, textList[result], (x - 3, y - 3), cv2.FONT_ITALIC, 0.5, (255, 175, 0))
    cv2.rectangle(out_texts, (x , y), (x + w , y + h), (255, 255, 0), bold)
    txt_count += 1
  show_window(out_texts)

# 画像表示
def show_window(out):
  cv2.imshow("img", out)
  cv2.waitKey(0)
  cv2.destroyAllWindows()

# 画像サイズ調整
def img_size_control(img):
  height, width, _ = img.shape
  if height > 1000 or width > 1000:
    img = cv2.resize(img, (int(width / 2), int(height / 2)), cv2.INTER_CUBIC)
  if height < 250 or width < 250:
    img = cv2.resize(img, (int(width * 2), int(height * 2)), cv2.INTER_CUBIC)
  return img

# 2値化処理(戻り値あり)
def img_binary(img):
  # グレースケール変換
  img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

  _, th = cv2.threshold(img, 0, 255, cv2.THRESH_OTSU)
  th = cv2.bitwise_not(th)
  th = cv2.GaussianBlur(th,(9,9), 0)
  contours = cv2.findContours(th, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0]
  return contours

# 2値化処理(戻り値なし)
def binary_data(img):
  src_img = cv2.imread(img, 0)

  _, th = cv2.threshold(src_img, 0, 255, cv2.THRESH_OTSU)
  th = cv2.bitwise_not(th)
  th = cv2.GaussianBlur(th,(3,3), 1)
  cv2.imwrite(img, th)

# print(draw_free(cap_file + "screen_shot.png", 28, 28))

read_text(img_file + "handwritten_3" + img_type)