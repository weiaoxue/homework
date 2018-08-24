#!/usr/bin/python

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from imblearn.over_sampling import SMOTE
from imblearn.under_sampling import RandomUnderSampler
from imblearn.under_sampling import TomekLinks
from imblearn.over_sampling import RandomOverSampler
from sklearn.svm import SVC
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestClassifier
from sklearn.naive_bayes import GaussianNB
from keras.utils import to_categorical
from keras.models import Sequential
from keras.layers import Dense, Dropout, Flatten, Conv1D, MaxPool1D
from keras.optimizers import RMSprop
from keras.callbacks import ReduceLROnPlateau
from sklearn.grid_search import GridSearchCV
from sklearn.metrics import confusion_matrix


def evaluation(y_test, y_pred):
    confusion_mat = confusion_matrix(y_pred, y_test)
    tn, fp, fn, tp = confusion_mat.ravel()
    print (tn, fp, fn, tp)
    print (confusion_mat)
    accuracy = (tn + tp) * 1.0 / (tn + fp + fn + tp)
    print ('accuracy: ', accuracy)
    recall = tp * 1.0 / (tp + fn)
    print ('recall: ', recall)
    precision = tp * 1.0 / (tp + fp)
    print ('precision: ', precision)
    f1 = 2 * precision * recall / (precision + recall)
    print ('F1: ', f1)


def train_svm(X_train, y_train, X_test, y_test):
    model = SVC()
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)
    print ('SVM')
    evaluation(y_test, y_pred)


def train_lr(X_train, y_train, X_test, y_test):
    model = LogisticRegression()
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)
    print ('LR')
    evaluation(y_test, y_pred)


def train_rf(X_train, y_train, X_test, y_test):
    model = RandomForestClassifier()
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)
    print ('RF')
    evaluation(y_test, y_pred)


def train_gn(X_train, y_train, X_test, y_test):
    model = GaussianNB()
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)
    print ('GN')
    evaluation(y_test, y_pred)


def createModel():
    model = Sequential()
    model.add(Conv1D(filters=32, kernel_size=3, padding='same', activation='relu', input_shape=(29, 1)))
    model.add(Conv1D(filters=32, kernel_size=3, padding='same', activation='relu'))
    model.add(MaxPool1D(pool_size=2))
    model.add(Dropout(0.25))

    model.add(Conv1D(filters=64, kernel_size=3, padding='same', activation='relu'))
    model.add(Conv1D(filters=64, kernel_size=3, padding='same', activation='relu'))
    model.add(MaxPool1D(pool_size=2))
    model.add(Dropout(0.25))

    model.add(Flatten())
    model.add(Dense(units=128, activation='relu'))
    model.add(Dropout(0.25))
    model.add(Dense(units=2, activation='softmax'))
    return model


def train_cnn(X_train, y_train, X_test, y_test):
    y_train = to_categorical(y_train, num_classes=2)
    y_test = to_categorical(y_test, num_classes=2)
    #print ('-----begin create model-----')
    model = createModel()
    #print ('-----end create model, begin compile-----')
    optimizer = RMSprop(lr=0.001)
    model.compile(optimizer=optimizer, loss='binary_crossentropy', metrics=['accuracy'])
    #print ('-----end compile, begin fit-----')
    X_train = np.expand_dims(X_train, axis=2)
    X_test = np.expand_dims(X_test, axis=2)
    #print (len(X_test))
    #print (len(y_test))
    learning_rate_reduction = ReduceLROnPlateau(monitor='val_acc', patience=3, verbose=0, factor=0.5, min_lr=0.00001)
    model.fit(X_train, y_train, batch_size=128, epochs=10, verbose=0, validation_data=(X_test, y_test),
              callbacks=[learning_rate_reduction])
    #print ('-----end fit-----')
    y_pred = model.predict_proba(X_test)
    #print (y_pred)
    print ('CNN')
    confusion_mat = confusion_matrix(np.argmax(y_pred, axis=1), np.argmax(y_test, axis=1))
    tn, fp, fn, tp = confusion_mat.ravel()
    print (tn, fp, fn, tp)
    print (confusion_mat)
    accuracy = (tn + tp) * 1.0 / (tn + fp + fn + tp)
    print ('accuracy: ', accuracy)
    recall = tp * 1.0 / (tp + fn)
    print ('recall: ', recall)
    precision = tp * 1.0 / (tp + fp)
    print ('precision: ', precision)
    f1 = 2 * precision * recall / (precision + recall)
    print ('F1: ', f1)


def smote(X_train, y_train):
    sm = SMOTE(kind='svm', random_state=0)
    X_train, y_train = sm.fit_sample(X_train, y_train)
    return X_train, y_train


def randomunder(X_train, y_train):
    ru = RandomUnderSampler(random_state=0)
    X_train, y_train = ru.fit_sample(X_train, y_train)
    return X_train, y_train


def randomover(X_train, y_train):
    ro = RandomOverSampler(random_state=0)
    X_train, y_train = ro.fit_sample(X_train, y_train)
    return X_train, y_train


def tomeklinks(X_train, y_train):
    tl = TomekLinks(random_state=0)
    X_train, y_train = tl.fit_sample(X_train, y_train)
    return X_train, y_train


if __name__ == "__main__":
    df = pd.read_csv("creditcard.csv", encoding='gbk')

#    count_classes = pd.value_counts(df['Class'], sort=True).sort_index()
#    print (count_classes)
#    count_classes.plot(kind='bar')
#    plt.title("Class Distribution Histogram")
#    plt.xlabel("Class")
#    plt.ylabel("Frequency")
#    plt.savefig("eg.jpg")
#    plt.show()

    df['NewAmount'] = StandardScaler().fit_transform(df['Amount'].values.reshape(-1, 1))
    df = df.drop(['Time', 'Amount'], axis=1)

    X, y = df.loc[:, df.columns != 'Class'].values, df.iloc[:, df.columns == 'Class'].values
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=0)
    print ('sample begin')
    X_train_ru, y_train_ru = randomunder(X_train, y_train)
    print ('1')
    X_train_tl, y_train_tl = tomeklinks(X_train, y_train)
    print ('1')
    X_train_ro, y_train_ro = randomover(X_train, y_train)
    print ('1')
    X_train_sm, y_train_sm = smote(X_train, y_train)
    print ('sample end')
    for j in range(4):
        if j == 0:
            X_train = X_train_ru
            y_train = y_train_ru
            print ('RandomUnderSample')
        elif j == 1:
            X_train = X_train_tl
            y_train = y_train_tl
            print ('TomekLinks')
        elif j == 2:
            X_train = X_train_ro
            y_train = y_train_ro
            print ('RandomOverSample')
        else:
            X_train = X_train_sm
            y_train = y_train_sm
            print ('SMOTE')

        print("Number of fraud transactions: ", np.sum(y_train))
        print("Number of normal transactions: ", len(y_train) - np.sum(y_train))
        print("Total number of transactions in resampled data: ", len(y_train))

        for i in range(5):
            if i == 0:
                train_lr(X_train, y_train, X_test, y_test)
            elif i == 1:
                train_svm(X_train, y_train, X_test, y_test)
            elif i == 2:
                train_rf(X_train, y_train, X_test, y_test)
            elif i == 3:
                train_gn(X_train, y_train, X_test, y_test)
            else:
                train_cnn(X_train, y_train, X_test, y_test)
