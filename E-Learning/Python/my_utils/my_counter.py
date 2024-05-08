class Counter:
    def __init__(self):
      self.value = 0
    def count_up(self):
      self.value += 1
    
    @property # デコレータ記法によるproperty定義
    def double_value(self):
       return self.value * 2 # valueの2倍の値を返すプロパティ
    
    @double_value.setter
    def double_value(self, new_value):
       self.value = new_value // 2 # 半分の値を代入するプロパティ