import numpy as np
import matplotlib.pyplot as plt
from perceptron import SimplePerceptron
import time

def fake_data(m):
    X = np.zeros((m,2))
    m_half = m // 2
    X[:, 0] = np.random.rand(m)
    X[:m_half, 1] = np.random.rand(m_half) * 0.49
    X[m_half:, 1] = np.random.rand(m_half) * 0.49 + 0.51
    y = np.ones(m, dtype=np.int8)
    y[m_half:] = -1
    return X, y

if __name__ == '__main__':
    np.random.seed(0)
    X,y = fake_data(m=1000)
    clf = SimplePerceptron(learning_rate=1.0)

    t1 = time.time()
    clf.fit(X,y)
    t2 = time.time()

    print(f"FIT TIME: {t2-t1}")
    print(f"clf.w_: {clf.w_}")
    print(f"k: {clf.k_}")
    print(f"ACC: {clf.score(X, y)}")
    x1 = np.array([0.0, 1.0])
    x2 = -(clf.w_[0] + clf.w_[1] * x1) / clf.w_[2]

    plt.scatter(X[:,0], X[:,1], c=y)
    plt.plot(x1, x2)
    plt.show()