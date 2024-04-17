class Counter:  # self.valueをカウントする機能を持つクラス
  def __init__(self):
    self.value = 0
  def count_up(self):
    self.value += 1

class DisplayValue:  # self.valueをprintするメゾットを持つクラス
  def display(self):
    print(f"value is {self.value}")

class DisplayCounter(Counter, DisplayValue):  # CounterとDisplayValueを多重継承
  pass  # 特にメゾットの追加はしないのでpass