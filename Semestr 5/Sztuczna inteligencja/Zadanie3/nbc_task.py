import numpy as np
import pandas as pd
from sklearn.preprocessing import LabelEncoder
from nbc import NBCDiscrete

def read_student_data(path):
    # zmiana na pandas bo plikiem wejsciowym jest csv
    D = pd.read_csv(path, delimiter=';', encoding='utf-8')

    # ostatnia kolumna jest wynikowa, wiec ja pomijamy
    X = D.iloc[:, :-1].values

    # bierzemy tylko ostatnia wynikowa kolumne
    y = D.iloc[:, -1].values

    return X, y

def train_test_split(X, y, train_ratio=0.75):
    m = X.shape[0]
    indexes = np.random.permutation(m)
    X = X[indexes]
    y = y[indexes]
    i = int(np.round(train_ratio * m))

    X_train = X[:i]
    y_train = y[:i]
    X_test = X[i:]
    y_test = y[i:]

    return X_train, y_train, X_test, y_test

def discretize(X, bins, mins_ref=None, maxes_ref=None):
    if mins_ref is None:
        mins_ref = np.min(X, axis=0)
        maxes_ref = np.max(X, axis=0)
    X_d = np.clip(np.floor((X - mins_ref) / (maxes_ref - mins_ref) * bins), 0, bins - 1).astype(np.int8)
    return X_d, mins_ref, maxes_ref

if __name__ == '__main__':
    bins = 5
    np.random.seed(0)

    X, y = read_student_data('student_data.csv')

    label_encoder = LabelEncoder()
    y = label_encoder.fit_transform(y)

    continuous_columns = [6, 12, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35]
    categorical_columns = [1, 3, 5, 7, 8, 9, 10, 11]

    for col in categorical_columns:
        unique_values = np.unique(X[:, col])
        if not np.all(np.diff(unique_values) == 1):
            X[:, col] = label_encoder.fit_transform(X[:, col])

    X_train, y_train, X_test, y_test = train_test_split(X, y, train_ratio=0.75)

    # dyskretyzujemy tylko ciagle columny
    X_train_continuous = X_train[:, continuous_columns]
    X_train_d, mins_ref, maxes_ref = discretize(X_train_continuous, bins)
    X_train[:, continuous_columns] = X_train_d

    # to samo dla testowych
    X_test_continuous = X_test[:, continuous_columns]
    X_test_d, _, _ = discretize(X_test_continuous, bins, mins_ref, maxes_ref)
    X_test[:, continuous_columns] = X_test_d

    n = X.shape[1]
    domains = np.ones(n, dtype=np.int8) * bins
    for i in range(n):
        if i not in continuous_columns:
            domains[i] = np.unique(X[:, i]).size

    clf = NBCDiscrete(domains, laplace=True)
    clf.fit(X_train_d, y_train)

    acc_train = clf.score(X_train_d, y_train)
    acc_test = clf.score(X_test_d, y_test)
    print(f"ACC -> TRAIN: {acc_train}, TEST: {acc_test}")