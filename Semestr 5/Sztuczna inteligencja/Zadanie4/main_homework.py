import numpy as np
import matplotlib.pyplot as plt

from perceptron import SimplePerceptron
import time

def fake_data(m):
    x1 = np.random.uniform(0, 2 * np.pi, m)
    x2 = np.random.uniform(-1, 1, m)

    X = np.column_stack((np.ones(m), x1, x2))

    y = np.where(np.abs(np.sin(x1)) > np.abs(x2), -1, 1)
    return X, y

def calculate_distances(X, C, sigma):
    I = X.shape[0]
    m = C.shape[0]

    distances = np.zeros((I, m))

    for i in range(I):
        for j in range(m):
            x1, x2 = X[i, 1], X[i, 2]
            c1, c2 = C[j, 1], C[j, 2]

            # equation (4)
            # distance = np.sqrt((x1 - c1) ** 2 + (x2 - c2) ** 2)
            # distances[i, j] = distance

            # equation (6)
            d2 = (x1 - c1) ** 2 + (x2 - c2) ** 2
            distances[i, j] = np.exp(-d2 / (2 * sigma ** 2))

    return distances

if __name__ == '__main__':
    np.random.seed(0)
    I = 1000
    m = 100      # [20, 100]
    sigma = 0.2 # [1, 0.1]
    k_max = 5000 # [500, 5000]
    learning_rate = 0.1

    np.random.seed(0)
    X,y = fake_data(I)

    # plot before scaling
    # plt.scatter(X[:, 1], X[:, 2], c=y, cmap='bwr', marker='o', s=10, alpha=0.5)
    # plt.show()

    x1 = X[:,1]
    X[:,1] = 2 * (x1 - np.min(x1)) / (np.max(x1) - np.min(x1)) - 1

    # plot after scaling
    # plt.scatter(X[:, 1], X[:, 2], c=y, cmap='bwr', marker='o', s=10, alpha=0.5)
    # plt.show()

    # C
    c1 = np.random.uniform(-1, 1, m)
    c2 = np.random.uniform(-1, 1, m)
    C = np.column_stack((np.ones(m), c1, c2))

    # plot with centers
    # plt.scatter(X[:, 1], X[:, 2], c=y, cmap='bwr', marker='o', s=10, alpha=0.5)
    # plt.scatter(C[:,1], C[:,2], color='black')
    # plt.show()

    # distance matrix (Z) calculations
    distances = calculate_distances(X, C, sigma)
    Z = np.hstack((np.ones((I, 1)), distances))

    # print("Distance Matrix:")
    # print(Z)

    clf = SimplePerceptron(learning_rate=learning_rate, k_max=k_max)

    t1 = time.time()
    clf.fit(Z,y)
    t2 = time.time()

    print(f"FIT TIME: {t2-t1}")
    # print(f"clf.w_: {clf.w_}")
    print(f"k: {clf.k_}")
    print(f"ACC: {clf.score(Z, y)}")

    meshgrid_points = 100
    meshgrid_points2 = meshgrid_points * meshgrid_points
    x1_check = np.linspace(-1, 1, meshgrid_points)
    x2_check = np.linspace(-1, 1, meshgrid_points)
    X1, X2 = np.meshgrid(x1_check, x2_check)

    X_check = np.c_[np.ones(meshgrid_points2), X1.ravel(), X2.ravel()]

    distances_check = calculate_distances(X_check, C, sigma)
    Z_check = np.hstack((np.ones((meshgrid_points2, 1)), distances_check))

    predictions = clf.predict(Z_check)
    predictions_1 = predictions.reshape(X1.shape)

    plt.contourf(X1, X2, predictions_1, cmap='bwr', alpha=0.5)
    plt.scatter(X[:, 1], X[:, 2], c=y, cmap='bwr', marker='o', s=10, alpha=0.5)
    plt.scatter(C[:, 1], C[:, 2], color='black')
    plt.show()
