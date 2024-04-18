import cv2
import math
import numpy as np

# ヒストグラム描画
def histogram(img_src):
  img_hst = np.zeros([100, 256]).astype('uint8')
  rows, cols = img_hst.shape[:2]

  # 度数分布
  hdism = [256]
  hranges = [0, 256]
  hist = cv2.calcHist([img_src], [0], None, hdism, hranges)

  # 度数の最大値
  min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(hist)
  for i in range(0, 255):
    v = hist[i]
    pt1 = (i, int(rows))
    pt2 = (i, int(rows - (rows * (v / max_val))))

    cv2.line(img_hst, pt1, pt2, (255, 255, 255))

# 垂直反転
def vertical_flip(img_src):
  return cv2.flip(img_src, flipCode = 0)

# ガンマ補正
def gamma_correction(gamma, img_src) :
  Y = np.ones((256, 1), dtype = 'uint8') * 0
  for i in range(256):
    Y[i][0] = 255 * pow(float(i) / 255, 1.0 / gamma)
  return cv2.LUT(img_src, Y)

# ネガポジ変換 
def Nega_posi_conversion(img_src):
  return 255 - img_src

# 明度調整
def brightness_adjustment(shift):
  table = np.arange(256, dtype = np.uint8)
  for i in range(0, 255):
    j = i + shift
    if j < 0:
      table[i] = 0
    elif j > 255:
      table[i] = 255
    else:
      table[i] = j

  return cv2.LUT(img_src, table)

# コントラスト
def contrast(min, max, img_src):
  table = np.arange(256, dtype = np.uint8)
  # c_reduce(min, max, table)
  c_strengthen(min, max, table)
  return cv2.LUT(img_src, table)

# コントラスト低減
def c_reduce(min, max, table):
  for i in range(0, 255):
    table[i] = min + i * (max - min) / 255
  
# コントラスト強調
def c_strengthen(min, max, table):
  for i in range(0, min):
    table[i] = 0
  for i in range(min, max):
    table[i] = 255 * (i - min) / (max - min)
  for i in range(max, 255):
    table[i] = 255


img_type = '.png'
file_src = 'image/iOS_Photo_01.png'
file_dst = 'image/dst' + img_type

img_src = cv2.imread(file_src, 1)  # 入力画像(カラー)読み込み
# img_src = cv2.imread(file_src, 0)  # 入力画像(グレースケール)読み込み

cv2.namedWindow('src')
cv2.namedWindow('dst')
histogram(img_src)

img_dst = contrast(100, 200, img_src)

cv2.imshow('src', img_src)  # 入力画像表示
cv2.imshow('dst', img_dst)  # 出力画像表示
cv2.imwrite(file_dst, img_dst)  # 処理結果の保存

cv2.waitKey(0)
cv2.destroyAllWindows()
