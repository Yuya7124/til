def char_list():
  text_char = [str(i) for i in range(0, 10)]
  upper = [chr(i) for i in range(ord('A'),ord('Z')+1)]
  lower = [chr(i) for i in range(ord('a'),ord('z')+1)]
  text_char.extend(upper)
  text_char.extend(lower)
  return text_char

def char_img_for_emnist():
  img_file = "image/CharList/"
  img_type = ".png"

  font_style = "Regular"
  filepassList = []
  textList = char_list()
  
  for i in range(0, 62):
    if i >= 36:
      filepassList.append(img_file + font_style + "/Alphabet_" + font_style + "/Lower_" + font_style + "/" + textList[i] + img_type)
    elif i >= 10 and i < 36:
      filepassList.append(img_file + font_style + "/Alphabet_" + font_style + "/Upper_" + font_style + "/" + textList[i] + img_type)
    else:
      filepassList.append(img_file + font_style + "/Number_" + font_style + "/" + textList[i] + img_type)
  
  return filepassList