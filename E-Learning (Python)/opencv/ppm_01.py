import cv2
import math
import numpy as np

width = 9
height = 9

image = np.zeros((height, width), np.uint8)
filename = "output.ppm"

for y in range(height):
  for x in range(width):
    color_num = 0
    if(color_num < 255):
      image[y][x] = color_num + 32
    else:
      image[y][x] = color_num - 32
      
bgr_img = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
cv2.imwrite(filename, bgr_img)
cv2.waitKey(0)