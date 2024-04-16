# print関数での結果
print(1 + 2)

def add(a, b):
  """整数型の引数a, bを加算する関数"""
  return a + b

def sub(a, b):
  return a - b

def add_to_sub(a, b, c):
  return add(a, b) - c

if __name__ == "__main__":
  print(add(1, 2))
  print(add_to_sub(10, 2, 4))

# add関数での結果
print(add(1, 2))