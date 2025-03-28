import pickle
import matplotlib.pyplot as plt
import numpy as np

def fake_data(m, domain=np.pi, noise_std=0.1):
    np.random.seed(0)
    X = np.random.rand(m, 2) * domain
    y = np.cos(X[:, 0] * X[:, 1]) * np.cos(2 * X[:, 0]) + np.random.randn(
        m) * noise_std  # target: cos(x_1 * x_2) * cos(2 * x_1) + normal noise
    return X, y

def loss_during_fit(approx, X_train, y_train, X_test, y_test):
    keys = list(approx.history_weights.keys())
    epochs = []
    losses_train = []
    losses_test = []
    weights = approx.weights_
    weights0 = approx.weights0_
    for k in keys:
        epochs.append(k + 1)
        approx.weights_ = approx.history_weights[k]
        approx.weights0_ = approx.history_weights0[k]
        losses_train.append(np.mean((approx.predict(X_train) - y_train) ** 2))
        losses_test.append(np.mean((approx.predict(X_test) - y_test) ** 2))
    approx.weights_ = weights
    approx.weights0_ = weights0
    return epochs, losses_train, losses_test


def plot_comparative_learning_curves(activation_name, structure, learning_rate, X_train, y_train, X_test, y_test):
    algorithms = ["sgd", "momentum", "rmsprop", "adam"]
    plt.figure(figsize=(15, 10))

    for idx, algo_name in enumerate(algorithms):
        model_filename = f"results/{structure}/{activation_name}/{algo_name}/{learning_rate:.1e}/neural_network.pkl"
        with open(model_filename, 'rb') as f:
            approx = pickle.load(f)

        epochs, losses_train, losses_test = loss_during_fit(approx, X_train, y_train, X_test, y_test)

        plt.subplot(2, 2, idx + 1)
        plt.plot(epochs, losses_train, label="Train Loss", color='blue')
        plt.plot(epochs, losses_test, label="Test Loss", color='red')
        plt.title(f"Algorithm: {algo_name}")
        plt.xlabel("Epochs")
        plt.ylabel("Loss (MSE)")
        plt.legend()
        plt.grid(True)

    plt.tight_layout()
    plt.show()

if __name__ == '__main__':
    domain = 1.5 * np.pi
    noise_std = 0.1
    m_train = 1000
    m_test = 10000
    data_settings_str = f"{domain=}, {noise_std=}, {m_train=}, {m_test=}"
    print(f"DATA SETTINGS: {data_settings_str}")
    X_train, y_train = fake_data(m_train, domain, noise_std)
    X_test, y_test = fake_data(m_test, domain, noise_std)

    structure = [128, 128, 64, 64, 32, 32]
    activation_name = "relu"
    learning_rate = 1e-3

    plot_comparative_learning_curves(activation_name, structure, learning_rate, X_train, y_train, X_test, y_test)