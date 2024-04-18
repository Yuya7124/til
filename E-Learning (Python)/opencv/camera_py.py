import cv2
import math
import numpy as np

cv2.namedWindow('src')
cv2.namedWindow('dst')
cap = cv2.VideoCapture(0)

while True:
  ret, img_src = cap.read()

  # 処理内容
  img_dst = cv2.filp(img_src, filpCode = 0)

  cv2.imshow('src', img_src)  # 入力画像表示
  cv2.imshow('dst', img_dst)  # 出力画像表示
  ch = cv2.waitKey(1)
  if ch == ord('q'):
    break

cap.release()
cv2.destroyAllWindows()