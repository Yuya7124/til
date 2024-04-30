import numpy as np
import pyxel
from PIL import Image
import text_capture
import digit

WindowWidth = 28
WindowHeight = 28

WindowSize = 64

filename = "image/capture/screen_shot.png"

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
    if pyxel.btnp(pyxel.MOUSE_BUTTON_RIGHT, hold=0, repeat=1):
      x, y = pyxel.mouse_x, pyxel.mouse_y
      dx = [ 0,-1, 0, 1, 0,
            -2,-1, 0, 1, 2,
            -2,-1, 0, 1, 2,
            -2,-1, 0, 1, 2,
             0,-1, 0, 1, 0 ]
      dy = [ 2, 2, 2, 2, 2,
             1, 1, 1, 1, 1,
             0, 0, 0, 0, 0,
            -1,-1,-1,-1,-1,
            -2,-2,-2,-2,-2 ]
      for i in range(len(dx)):
        nx = x + dx[i]
        ny = y + dy[i]
        if (0 <= nx < pyxel.width) and (0 <= ny < pyxel.height):
          self.window[ny][nx] = -1
    
    if pyxel.btn(pyxel.KEY_S):
      # 「S」キーで保存
      self._saveImage()
      self.predigit = text_capture.draw_free(filename, WindowWidth, WindowHeight)
      # self.predigit = digit.load_predict(filename)
    if pyxel.btn(pyxel.KEY_Q):
      # 「Q」キーで終了
      quit()
  
  def draw(self):
    pyxel.cls(pyxel.COLOR_WHITE)

    for y in range(pyxel.height):
      for x in range(pyxel.width):
        if self.window[y][x] == -1:
          pyxel.pset(x, y, pyxel.COLOR_BLACK)

    pyxel.text(0, 0, 'Predict: {}'.format(self.predigit), pyxel.COLOR_DARK_BLUE)

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
    print("Image has saved correctly.")

Painting()