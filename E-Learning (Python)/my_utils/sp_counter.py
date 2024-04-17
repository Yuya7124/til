class Counter:
  def __init__(self, initial = 0):  # コンストラクタ(スペシャルメゾット)
    self.value = initial  # initial引数をvalueの初期値として使う

  def count_up(self):
    self.value += 1  # 通常メゾット

  def __str__(self):
    return f"Counter({self.value})"  # 文字列表記を返すスペシャルメゾット
  
  def __add__(self, other):  # +演算子で呼ばれるスペシャルメゾット
    return Counter(self.value + other.value)  # Counterを新たに生成して返す