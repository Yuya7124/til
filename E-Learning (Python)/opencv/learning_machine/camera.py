import cv2
import pyocr
from PIL import Image
import pyocr.builders

height = 28 
width = 28

cap_file = "image/capture/sample.png"

def camera():
  cap = cv2.VideoCapture(0)
  while True:
    ret, img_src = cap.read()
    height, width, _ = img_src.shape[:3]

    height_center = height // 2
    width_center = width // 2

    img = cv2.resize(img_src, (int(width), int(height)))

    # OCRで読み取りたい領域
    cv2.rectangle(img, (width_center-71, height_center-71)
                     , (width_center+71, height_center+71)
                     , (255, 255, 0)
                     , 5)
    
    # ocr(img, width, height)
    # img_dst = cv2.flip(img_src, filpCode = 0)

    cv2.imshow('src', img)  # 入力画像表示
    # cv2.imshow('dst', img_dst)  # 出力画像表示
    ch = cv2.waitKey(1) & 0xFF

    prop_val = cv2.getWindowProperty('src', cv2.WND_PROP_ASPECT_RATIO)
    if ch == ord('q') or (prop_val < 0) :
      break
    elif ch == ord('s'):
      flash(img, height_center, width_center)
      break
    
  cap.release()
  cv2.destroyAllWindows()
  
# 映像の文字認識
def ocr(img, width, height):
  tools = pyocr.get_available_tools()
  tool = tools[0]
  img_dst = img[100:height-200, 100:width-200]
  PIL_Image = Image.fromarray(img_dst)
  text = tool.image_to_string(PIL_Image, lang='jpn', builder=pyocr.builders.TextBuilder(tesseract_layout=6))
  if text != "" :
    print(text)

# 撮影処理
def flash(frame, height, width):
  img = frame[height-70:height+70, width-70:width+70]
  # グレースケール変換
  img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
  
  # 2値化処理
  _, th = cv2.threshold(img, 0, 255, cv2.THRESH_OTSU)
  th = cv2.bitwise_not(th)
  th = cv2.GaussianBlur(th,(9,9), 0)
  cv2.imwrite(cap_file, th)

camera()