import cv2
import matplotlib.pyplot as plt

path = "image/iOS_Photo_02.jpg"
img = cv2.imread(path)
color = ("b", "g", "r")

re_size = cv2.resize(img, dsize = [600, 400])
cv2.imwrite('image/iOS_Photo_01_re-size.png', re_size)

# 画像の高さ
height = re_size.shape[0]
# 画像の幅
width = re_size.shape[1]
# 画像サイズを取得
print(f"height: {height}, width: {width}")

# cv2.imshow('imshow', img)
# cv2.imshow('imshow', tri_img)

img_color = cv2.cvtColor(re_size, cv2.COLOR_BGR2RGB)

for i, col in enumerate(color):
  histr = cv2.calcHist(images=[img_color], channels=[i],
                        mask=None, histSize=[width], ranges=[0, width])
  plt.plot(histr, color = col)
  plt.xlim([0, width])
# cv2.imshow('image', img)
plt.imshow(img_color)
plt.show()

cv2.waitKey(0)
cv2.destroyAllWindows()