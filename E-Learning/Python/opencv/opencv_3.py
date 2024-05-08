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
    pt2 = (i, int(rows - (rows * (v / max_val))[0]))

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

# 平均化オペレータ
def ave_operater(img_src, x, y):
  return cv2.blur(img_src, (x, y))

# Gaussianオペレータ
def gaussian_operater(img_src, x, y, sigma):
  return cv2.GaussianBlur(img_src, (x, y), sigma)

# バイラテラルオペレータ
def bilateral_operater(img_src, x, sigma1, sigma2):
  return cv2.bilateralFilter(img_src, x, sigma1, sigma2)

# 中央値フィルタ処理
def median_filtering(img_src, size):
  return cv2.medianBlur(img_src, size)

# Sobelオペレータ
def sobel_operater(img_src):
  img_tmp = cv2.Sobel(img_src, cv2.CV_32F, 2, 0)
  return cv2.convertScaleAbs(img_tmp)

# Laplacianオペレータ
def laplacian_operator(img_src, size):
  img_tmp = cv2.Laplacian(img_src, cv2.CV_32F, size)
  return cv2.convertScaleAbs(img_tmp)

# 鮮鋭化フィルタ
def sharpening_filtering(img_src ,k):
  op = np.array([[-k, -k, -k],
                 [-k, 1 + 8 * k, -k],
                 [-k, -k, -k]])
  img_tmp =cv2.filter2D(img_src, -1, op)
  return cv2.convertScaleAbs(img_src)

img_type = '.png'
file_src = 'image/iOS_Photo_01.png'
file_dst = 'image/dst' + img_type

img_src = cv2.imread(file_src, 1)  # 入力画像(カラー)読み込み
# img_src = cv2.imread(file_src, 0)  # 入力画像(グレースケール)読み込み

cv2.namedWindow('src')
cv2.namedWindow('dst')
histogram(img_src)

img_dst = sharpening_filtering(img_src, 10.0)

cv2.imshow('src', img_src)  # 入力画像表示
cv2.imshow('dst', img_dst)  # 出力画像表示
cv2.imwrite(file_dst, img_dst)  # 処理結果の保存

cv2.waitKey(0)
cv2.destroyAllWindows()