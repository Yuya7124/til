import numpy as np
import matplotlib.pyplot as plt
from keras.api.datasets.mnist import load_data
from keras.api.models import Sequential
from keras.src.layers import Dense, Activation ,Conv2D, Flatten, MaxPooling2D, Dropout, Reshape
from keras.src.utils.numerical_utils import to_categorical
from keras.src.optimizers import SGD

height = 28 
width = 28
(x_train, y_train), (x_test, y_test) = load_data()

x_train = np.array(x_train) / 255
x_test = np.array(x_test) / 255

y_train = to_categorical(y_train)
y_test = to_categorical(y_test)

h5_file = "h5/drawing_text_test.h5"

epoches_times = 100   # 学習回数

# モデル構築
model = Sequential()
# 評価関数
metrics = ["loss", "accuracy"]

def deep_learning(model):
  layers(model)  
  # コンパイル
  model.compile(optimizer=SGD(learning_rate=0.1), loss="categorical_crossentropy", metrics=["accuracy"])
  learning(model, epoches_times)
  # モデル保存
  model.save(h5_file)
  # モデル削除
  del model

def layers(model):
  # 畳み込み層追加
  model.add(Reshape((height, width, 1)))

  # 畳み込み層1
  model.add(Conv2D(32, (3, 3)))
  model.add(Activation("relu"))

  # 畳み込み層2
  model.add(Conv2D(32, (3, 3)))
  model.add(Activation("relu"))

  # ブーリング層
  model.add(MaxPooling2D(2, 2))
  model.add(Dropout(0.75))

  # 畳み込み層3
  model.add(Conv2D(16, (3, 3)))
  model.add(Activation("relu"))
  
  # ブーリング層2
  model.add(MaxPooling2D(2, 2))
  model.add(Dropout(0.5))

  model.add(Flatten())
  # 全結合層
  model.add(Dense(height * width))
  model.add(Activation("relu"))
  model.add(Dropout(0.25))

  # 出力層
  model.add(Dense(10))
  model.add(Activation("softmax"))

def learning(model, epoches):
  # 学習実行
  hist = model.fit(x_train, y_train, batch_size=200, epochs=epoches, verbose=1, validation_split=0.2, validation_data=(x_test, y_test))
  # 評価
  score = model.evaluate(x_test, y_test, verbose=1)
  print("Acc: ", score[1])
  # グラフ表示
  graph(hist)

def graph(history):
  plt.figure(figsize=(10, 5))

  for i in range(len(metrics)):
    metric = metrics[i]

    plt.subplot(1, 2, i + 1)
    plt.title(metric.capitalize())

    plt_train = history.history[metric]
    plt_val = history.history["val_" + metric]

    plt.plot(plt_train, label = "Training")
    plt.plot(plt_val, label = "Validation")
    plt.xlabel("Epochs")
    plt.ylabel(metric.capitalize())
    plt.legend()
  plt.show()
  
deep_learning(model)