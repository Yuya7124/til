class Counter:
  def __init__(self):
    self.value = 0
  def count_up(self):
    self.value += 1


class DisplayCounter(Counter):  # Counterクラスを継承
  """count_up()で2倍カウントするクラス"""
  def count_up(self):  # オーバーライド
    # count_upを2回呼ぶ
    super.count_up()  # Counterクラスのcount_up()を呼ぶ
    super.count_up()