import numpy as np
from sklearn.base import BaseEstimator, ClassifierMixin

class SimplePerceptron(BaseEstimator, ClassifierMixin):

    def __init__(self, learning_rate=0.1, k_max = 500):
        self.learning_rate = learning_rate
        self.k_max = k_max

    def fit(self, X, y):
        self.classes_ = np.unique(y) # zakladamy 2 klasy, i ze: self.classes_[0] -> -1, self.classes_[1] -> +1
        m, n = X.shape
        X_ext = np.hstack((np.ones((m, 1)), X))
        yy = np.ones(m, dtype=np.int8)
        yy[y == self.classes_[0]] = -1
        self.w_ = np.zeros(n + 1)
        self.k_ = 0

        while self.k_ < self.k_max:
            E = np.where(self.w_.dot(X_ext.T) * yy <= 0.0)[0]

            if len(E) == 0:
                break

            i = np.random.choice(E)
            self.w_ = self.w_ + self.learning_rate * yy[i] * X_ext[i]

            self.k_ += 1

    def predict(self, X):
        return self.classes_[(self.decision_function(X) > 0.0) * 1]

    def decision_function(self, X):
        m = X.shape[0]
        X_ext = np.hstack((np.ones((m, 1)), X))
        return self.w_.dot(X_ext.T)
