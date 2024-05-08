import numpy as np
import pickle
from PIL import Image
from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier

filename = "image/capture/screen_shot.png"

def train():

  digits = datasets.load_digits()
  X = digits.data
  y = digits.target

  X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.5, shuffle=False)

  knc = KNeighborsClassifier()
  knc.fit(X_train, y_train)

  with open('knc_digit.pkl', 'wb') as f:
    pickle.dump(knc, f)

def load_predict(filename):
  with open('knc_digit.pkl', 'rb') as f:
    loaded_model = pickle.load(f)

  img = Image.open(filename)
  img = img.convert('L')
  img = (255 - np.array(img)) // 16 + 1
  img = img.reshape(28, 28)

  pred = loaded_model.predict(img)
  return pred

train()