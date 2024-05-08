import cv2

path = "image/System-RMDF-Pro.png"
img = cv2.imread(path)

img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

ret, threst = cv2.threshold(img_gray, 120, 255, cv2.THRESH_BINARY_INV)
cv2.imwrite("image/change1_SR.png", threst)

contours, hierarchy = cv2.findContours(threst, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
cv2.drawContours(img, contours, -1 ,(255, 120, 0), 2)
cv2.imwrite("image/change2_SR.png", img)
