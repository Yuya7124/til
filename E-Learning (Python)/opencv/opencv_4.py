import cv2
import math
import numpy as np

# マスク処理
def masking(img_src, img_msk):
  return cv2.bitwise_and(img_src, img_msk)

# 膨張処理(4近傍)
def element4(img_src):
  element4 = np.array([[0, 1, 0],[1, 1, 1], [0, 1, 0]], np.uint8)  # 4近傍
  element8 = np.array([[1, 1, 1],[1, 1, 1], [1, 1, 1]], np.uint8)  # 8近傍
  opening_ending(img_src, element8)
  return cv2.erode(re_size2, element4, iterations = 1)

# 膨張処理(8近傍)
def element4(img_src):
  element4 = np.array([[0, 1, 0],[1, 1, 1], [0, 1, 0]], np.uint8)  # 4近傍
  element8 = np.array([[1, 1, 1],[1, 1, 1], [1, 1, 1]], np.uint8)  # 8近傍
  opening_ending(img_src, element8)
  return cv2.dilate(re_size2, element8, iterations = 1)

# 面積・周囲長・円形度
def area_peri_clrc(img_src):
  contours, _ = cv2.findContours(img_src, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
  area = cv2.contourArea(contours[0])
  perimeter = cv2.arcLength(np.array(contours[0]), True)
  roundness = 4 * np.pi * area / math.pow(perimeter, 2)

# 縦横比
def aspect(img_src):
  x, y, w ,h = cv2.boundingRect(img_src)
  pimento = float(h) / w
  print(pimento)
  cv2.rectangle(img_src, (x, y), (x + w, y + h), 128)

def opening_ending(img_src, element):
  # オープニング
  img_tmp = cv2.morphologyEx(img_src, cv2.MORPH_OPEN, element)
  # エンディング
  return cv2.morphologyEx(img_src, cv2.MORPH_CLOSE, element)

def moment(img_src):
  m = cv2.moments(img_src)
  area = m['m00']
  x_g = m['m10'] / m['m00']
  y_g = m['m01'] / m['m00']
  ang = 0.5 * math.atan2(2.0 * m['mu11'], m['mu20'] - m['mu02'])
 
img_type = '.png'
file_src = 'image/pimento.png'
file_dst = 'image/dst' + img_type
file_msk = 'image/mask_img.png'

# img_src = cv2.imread(file_src, 1)  # 入力画像(カラー)読み込み
img_src = cv2.imread(file_src, 0)  # 入力画像(グレースケール)読み込み
img_msk = cv2.imread(file_msk, 0)  # 入力画像(グレースケール)読み込み

re_size1 = cv2.resize(img_src, dsize = [400, 400])
re_size2 = cv2.resize(img_msk, dsize = [400, 400])

# 2値化処理
thresh = 100
ret, img_bin = cv2.threshold(img_src, thresh, 255, cv2.THRESH_BINARY)

cv2.namedWindow('src')
# cv2.namedWindow('dst')

moment(re_size2)

# img_dst = masking(re_size1, img_bin)

cv2.imshow('src', re_size2)  # 入力画像表示
# cv2.imshow('dst', img_dst)  # 出力画像表示
# cv2.imwrite(file_dst, img_dst)  # 処理結果の保存

cv2.waitKey(0)
cv2.destroyAllWindows()