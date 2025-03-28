import numpy as np
from sklearn.base import BaseEstimator, ClassifierMixin

class NBCDiscrete(BaseEstimator, ClassifierMixin):

    def __init__(self, domains, laplace=False, logs=False):
        self.domains = domains
        self.laplace = laplace
        self.logs = logs

    def fit(self, X, y):
        self.classes_ = np.unique(y)
        K = self.classes_.size # 3
        m, n = X.shape # 134, 13
        q = np.max(self.domains) # 5
        self.PY_ = np.zeros(K) # a priori distribution
        self.P_ = np.zeros((K, n, q)) # conditional probs -> P_[2, 7, 3] = Prob(X_7 = 3 | y = 2)
        yy = np.zeros(m, dtype=np.int8)

        for y_index, label in enumerate(self.classes_):
            indexes = y == label
            yy[indexes] = y_index
            self.PY_[y_index] = np.mean(y == label)

        for i in range(m):
            for j in range(n):
                self.P_[yy[i], j, X[i,j]] += 1

        for y_index, label in enumerate(self.classes_):
            if not self.laplace:
                if not self.logs:
                    self.P_[y_index] /= self.PY_[y_index] * m
                else:
                    self.P_[y_index] = np.log(self.P_[y_index]) - np.log(self.PY_[y_index] * m)
            else:
                for j in range(n):
                    if not self.logs:
                        self.P_[y_index, j] = (self.P_[y_index, j] + 1) / (self.PY_[y_index] * m + self.domains[j])
                    else:
                        self.P_[y_index, j] = np.log(self.P_[y_index, j] + 1) - np.log(self.PY_[y_index] * m + self.domains[j])

    def predict(self, X):
        scores = self.predict_proba(X)
        return self.classes_[np.argmax(scores, axis=1)]

    def predict_proba(self, X):
        m, n = X.shape
        K = self.classes_.size

        if not self.logs:
            scores = np.ones((m, K))
        else:
            scores = np.zeros((m, K))

        for i in range(m):
            for y_index in range(K):
                if not self.logs:
                    for j in range(n):
                        scores[i, y_index] *= self.P_[y_index, j, X[i, j]]
                    scores *= self.PY_[y_index]
                else:
                    log_score = np.log(self.PY_[y_index])
                    for j in range(n):
                        log_score += self.P_[y_index, j, X[i, j]]
                    scores[i, y_index] = log_score

        max_scores = np.max(scores, axis=1, keepdims=True)
        exp_scores = np.exp(scores - max_scores)
        scores = exp_scores / np.sum(exp_scores, axis=1, keepdims=True)

        return scores