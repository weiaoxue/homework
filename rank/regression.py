import pandas as pd
import numpy as np
import operator as op
from sklearn.preprocessing import MinMaxScaler
from sklearn.decomposition import PCA
from sklearn.svm import SVR
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import AdaBoostRegressor
from xgboost.sklearn import XGBRegressor
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import GridSearchCV


if __name__ == "__main__":
    # df = pd.read_csv("train_new.csv")
    # X_train, y_train = df.iloc[:, 1:90].values, df.iloc[:, 90].values
    # df = pd.read_csv("test_new.csv")
    # X_test = df.iloc[:, 1:90].values

    df = pd.read_csv("train.csv")
    cor = df.corr()['sem3_rank'].values.tolist()
    print (cor)
    l = []
    for i in range(len(cor)):
        if i != 0 and i != 318 and abs(cor[i]) >= 0.4:
            l.append(i)
    X_train, y_train = df.iloc[:, l].values, df.iloc[:, 318].values
    df = pd.read_csv("test.csv")
    X_test = df.iloc[:, l].values
    print(X_train.shape)
    print(X_test.shape)
    col = df.columns.values.tolist()
    for i in l:
        print col[i]

    scl = MinMaxScaler()
    X_train = scl.fit_transform(X_train)
    X_test = scl.transform(X_test)

    dcp = PCA(n_components=0.95)
    X_train = dcp.fit_transform(X_train)
    X_test = dcp.transform(X_test)
    print(X_train.shape)
    print(X_test.shape)

    grid = GridSearchCV(SVR(), param_grid={"C": [0.001, 0.01, 0.1, 1, 10, 100, 1000, 10000], "gamma": [0.001, 0.01, 0.1, 1, 10]})
    grid.fit(X_train, y_train)
    print("The best parameters are %s with a score of %0.2f" % (grid.best_params_, grid.best_score_))
    # clf = SVR(C=100, gamma=0.1)
    # clf.fit(X_train, y_train)
    y_prd = grid.predict(X_test)
    print (y_prd)

    id = range(1, 92)
    result = np.column_stack((id, y_prd))
    #print(result)
    result = sorted(result, key=op.itemgetter(1))
    #print(result)
    result = np.column_stack((result, id))
    #print(result)
    result = sorted(result, key=op.itemgetter(0))
    #print(result)
    result = np.delete(result, 1, axis=1)
    print(result)

    f = open("submission.csv", "w")
    f.write("id,rank\n")
    for i in range(len(result)):
        f.write("%d,%d\n" % (result[i][0], result[i][1]))
    f.close()
