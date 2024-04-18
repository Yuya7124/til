import cv2
import math
import numpy as np

file_src = 'image/iOS_Photo_01.png'
file_dst = 'image/dst.png'

img_src = cv2.imread(file_src, 1)  # 入力画像(カラー)読み込み
# img_src = cv2.imread(file_src, 0)  # 入力画像(グレースケール)読み込み

cv2.namedWindow('src')
cv2.namedWindow('dst')

# 処理内容
gamma = 3.0
Y = np.ones((256, 1), dtype = 'uint8') * 0
for i in range(256):
  Y[i][0] = 255 * pow(float(i) / 255, 1.0 / gamma)

img_dst = cv2.LUT(img_src, Y)

# img_dst = cv2.flip(img_src, flipCode = 0)

cv2.imshow('src', img_src)  # 入力画像表示
cv2.imshow('dst', img_dst)  # 出力画像表示
cv2.imwrite(file_dst, img_dst)  # 処理結果の保存
cv2.waitKey(0)

cv2.destroyAllWindows()