class Counter:  # objectを列挙する場合は、(object)は省略可
  """親クラス"""
  def __init__(self):
    self.value = 0
  def count_up(self):
    self.value += 1


class DisplayCounter(Counter):
  """子クラス"""
  def display(self):
    print(f"value = {self.value}")