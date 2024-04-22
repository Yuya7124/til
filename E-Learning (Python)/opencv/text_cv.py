import cv2
import numpy as np

img = np.zeros((400, 400, 3), dtype = np.uint8)

img = cv2.putText(img, "abc ABC 123", (5, 20), cv2.FONT_HERSHEY_PLAIN, 1.5, (0, 255, 255))

cv2.imshow('img', img)

cv2.waitKey(0)
cv2.destroyAllWindows()