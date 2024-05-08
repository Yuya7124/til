text = "I am learning Python programming language"
split_text = text.split(' ')
print(split_text)

count = 0
for word in split_text:
  if len(word) >= 3:
    count += 1
print(f'単語数: {count}')

data_num = [[10, 20], [30]]
for inner in data_num:
  for number in inner:
    print(number)

data_str = "なまむぎなまごめなまたまご"
count_str = {}
for char in data_str:
  if char not in count_str:
    count_str[char] = 0
  count_str[char] += 1
for char, str_num in count_str.items():
  print(f'{char}: {str_num}')

runner = ['3-A', '2-B', '1-C', '3-D', '1-E', '3-F', '1-G', '2-H', '3-I']
counter_runner = {}
for value in runner:
  grade, name = value.split('-')
  if grade not in counter_runner:
    counter_runner[grade] = []
  counter_runner[grade].append(name)
for grade in sorted(counter_runner):
  print(f'{grade}年')
  for rank, name in enumerate(counter_runner[grade]):
    print(f'{rank + 1}位: {name}')