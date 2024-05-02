import numpy as np
import pyxel
import cv2
from PIL import Image
import text_list
import text_capture

WindowWidth = 28
WindowHeight = 28

WindowSize = 128

filename = "image/capture/screen_shot.png"
pyxel_color = pyxel.COLOR_DARK_BLUE
textList = text_list.char_list()

class Painting:
  window = [[0]*WindowSize for _ in range(WindowSize)]
  predigit = None
  
  def __init__(self):
    pyxel.init(WindowSize, WindowSize)
    pyxel.mouse(visible=True)
    pyxel.run(self.update, self.draw)
    

  def update(self):
    # 「Delete」キーでリセット
    if pyxel.btn(pyxel.KEY_DELETE):
      for y in range(pyxel.height):
        for x in range(pyxel.width):
          self.window[y][x] = 0

    # マウスの右ボタンで描画
    if pyxel.btnp(pyxel.MOUSE_BUTTON_LEFT, hold=1, repeat=1):
      x, y = pyxel.mouse_x, pyxel.mouse_y
      dx = [ 0, 0,-1, 0, 1, 0, 0,
             0,-2,-1, 0, 1, 2, 0,
            -3,-2,-1, 0, 1, 2, 3,
            -3,-2,-1, 0, 1, 2, 3,
            -3,-2,-1, 0, 1, 2, 3,
             0,-2,-1, 0, 1, 2, 0,
             0, 0,-1, 0, 1, 0, 0 ]
      dy = [ 3, 3, 3, 3, 3, 3, 3,
             2, 2, 2, 2, 2, 2, 2,
             1, 1, 1, 1, 1, 1, 1,
             0, 0, 0, 0, 0, 0, 0,
            -1,-1,-1,-1,-1,-1,-1,
            -2,-2,-2,-2,-2,-2,-2,
            -3,-3,-3,-3,-3,-3,-3 ]
      for i in range(len(dx)):
        nx = x + dx[i]
        ny = y + dy[i]
        if (0 <= nx < pyxel.width) and (0 <= ny < pyxel.height):
          self.window[ny][nx] = -1
    
    if pyxel.btn(pyxel.KEY_S):
      # 「S」キーで保存
      self._saveImage()
      text = text_capture.draw_free(filename, WindowWidth, WindowHeight)
      self.predigit = textList[text]
      # self.predigit = digit.load_predict(filename)
    if pyxel.btn(pyxel.KEY_Q):
      # 「Q」キーで終了
      quit()
  
  # 描画機能
  def draw(self):
    pyxel.cls(pyxel.COLOR_WHITE)

    for y in range(pyxel.height):
      for x in range(pyxel.width):
        if self.window[y][x] == -1:
          pyxel.pset(x, y, pyxel.COLOR_BLACK)
    
    self.painting_ui()

  # 画像保存
  def _saveImage(self):
    img = Image.new('RGB', (pyxel.width, pyxel.height))
    for y in range(pyxel.height):
      for x in range(pyxel.width):
        if self.window[y][x] == 0:
          img.putpixel((x, y), (255, 255, 255))
        else :
          img.putpixel((x, y), (0, 0, 0))
    img = img.resize((WindowWidth, WindowHeight), Image.BICUBIC)
    img.save(filename)
    self.binary_data(filename)
    print("Image has saved correctly.")
  
  # 2値化処理
  def binary_data(self, filename):
    src_img = cv2.imread(filename, 0)

    _, th = cv2.threshold(src_img, 0, 255, cv2.THRESH_OTSU)
    th = cv2.bitwise_not(th)
    th = cv2.GaussianBlur(th,(3,3), 1)
    cv2.imwrite(filename, th)
  
  # UI
  def painting_ui(self):
    pyxel.text(21, 108, 's: Save', pyxel_color)
    pyxel.text(1, 115, 'Delete: Clear', pyxel_color)
    pyxel.text(21, (WindowSize - 7), 'q: Quit', pyxel_color)
    pyxel.text(1, 1, 'Predict: {}'.format(self.predigit), pyxel_color)

Painting()