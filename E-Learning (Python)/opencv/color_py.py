import cv2
import math
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors

img_type = '.png'
file_src = 'image/iOS_Photo_01.png'
file_dst = 'image/dst' + img_type

height = 800
width = 240

color_gradients = [
    np.array([255, 255, 255], np.int8),   # 白
    np.array([  0, 255, 255], np.int8),   # 黄
    np.array([255, 255,   0], np.int8),   # 水
    np.array([  0, 255,   0], np.int8),   # 緑
    np.array([255,   0, 255], np.int8),   # 赤紫
    np.array([  0,   0, 255], np.int8),   # 赤
    np.array([255,   0,   0], np.int8),   # 青
    np.array([  0,   0,   0], np.int8),   # 黒
]

color_bar = np.zeros((height, width, 3), np.uint8)

for i in range(height // 100):
  start_row = i * 100
  end_row = (i + 1) * 100
  color_index = i % len(color_gradients)
  color = color_gradients[color_index]
  color_bar[start_row:end_row, :] = color

img_bgr = cv2.split(color_bar)
img_dst = cv2.merge((img_bgr[2], img_bgr[1], img_bgr[0]))
img_dst = cv2.cvtColor(color_bar, cv2.COLOR_BGR2YCrCb)


cv2.imshow('color_bar', color_bar)  # 出力画像表示
cv2.imwrite('image/color_bar.png', color_bar)

# img_src = cv2.imread(file_src, 1)  # 入力画像(カラー)読み込み
# # img_src = cv2.imread(file_src, 0)  # 入力画像(グレースケール)読み込み

# img_bgr = cv2.split(img_src)
# img_dst = cv2.merge((img_bgr[0], img_bgr[0], img_bgr[0]))
# img_dst = cv2.cvtColor(img_src, cv2.COLOR_BGR2HSV)

# cv2.imshow('src', img_src)  # 入力画像表示
cv2.imshow('dst', img_dst)  # 出力画像表示


# cv2.imwrite('image/color_photo_01.png', img_dst)  # 処理結果の保存

cv2.waitKey(0)
cv2.destroyAllWindows()