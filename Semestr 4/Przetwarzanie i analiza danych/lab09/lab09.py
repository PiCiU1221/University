from sklearn.metrics import accuracy_score
from scipy.spatial import distance
from sklearn.neighbors import KDTree
import numpy as np

# Zadanie 2.1

class k_nn:
    def __init__(self, n_neighbors = 1, use_KDTree = False, regression = False):
        self.n_neighbors = n_neighbors
        self.use_KDTree = use_KDTree
        self.regression = regression

    def fit(self, X, y):
        self.X = X
        self.y = y

    def predict(self, X):
        if self.use_KDTree:
            tree = KDTree(self.X)
            dist, ind = tree.query(X, k=self.n_neighbors)
        else:
            # Oblicz odległości między punktami testowymi a treningowymi
            dist = distance.cdist(X, self.X, 'euclidean')

            # Sortuj indeksy punktów treningowych według odległości na podstawie ich odległości
            # od każdego punktu testowego
            sorted_indices = np.argsort(dist, axis=1)

            # Wybierz tylko n najbliższych sąsiadów z listy posortowanych indeksów
            ind = sorted_indices[:, :self.n_neighbors]
        
        y_pred = np.zeros(X.shape[0])

        if self.regression:
            # Dla każdego punktu testowego oblicz średnią wartość zmiennej docelowej wśród jego sąsiadów
            for i in range(X.shape[0]):
                # Oblicz średnią wartość zmiennej docelowej wśród najbliższych sąsiadów
                y_pred[i] = np.mean(self.y[ind[i]])
        else:

            # Dla każdego punktu testowego znajdz najczęstszą etykietę wśród jego sąsiadów
            for i in range(X.shape[0]):
                # Oblicz wystąpienia każdej etykiety klasy wśród sąsiadów punktu testowego i
                counts = np.bincount(self.y[ind[i]])

                # Znajdź indeks etykiety klasy, która występuje najczęściej wśród sąsiadów punktu testowego i
                predicted_label_index = np.argmax(counts)

                # Przypisz tę najczęściej występującą etykietę klasy jako przewidywaną etykietę dla punktu testowego i
                y_pred[i] = predicted_label_index

        return y_pred

    def score(self, X, y):
        # Oblicz dokładności modelu na danych testowych za pomocą zewnętrznej funkcji accuracy_score
        return accuracy_score(y, self.predict(X))

# Zadanie 3.1

from sklearn import datasets
import matplotlib.pyplot as plt
import numpy as np
from statistics import mode
from sklearn import datasets
from sklearn.decomposition import PCA
from sklearn.neighbors import KDTree
import time
import pandas as pd

X, y = datasets.make_classification(
        n_samples=100, #liczba próbek
        n_features=2, #liczba wymiarów (cech)
        n_informative=2, #cechy ważne w tym przypadku oba wymiary są ważne
        n_redundant=0, #nadmiarowe funkcje ustawione jako 0. Wszystkie cechy w tym przypadku są unikalne
        n_repeated=0, #0 gwarantuje niepowatarzalność cech
        random_state=3 #ustawienie generatora liczb losowych - 3 oznacza generowanie tych samych danych za każdym razem
                                    )

X_value_samples = 100

# ustalenie zakresu danych
X_min, X_max = np.min(X, axis=0), np.max(X, axis=0)
y_min, y_max = np.min(X, axis=0), np.max(X, axis=0)

# tworzenie zbioru testowego w zakresie wylosowanych danych
X_value1 = np.random.uniform(X_min[0], X_max[0], (X_value_samples, 1))
y_value2 = np.random.uniform(y_min[1], y_max[1], (X_value_samples, 1))

# zlaczenie zbioru
test = np.hstack((X_value1, y_value2))

# wizualizacja zbiorow danych
plt.plot(X[y == 0, 0], X[y == 0, 1], 'go', label='Klasa 0')
plt.plot(X[y == 1, 0], X[y == 1, 1], 'ro', label='Klasa 1')

# wizualizacja punktow testowych
plt.plot(test[:, 0], test[:, 1], 'yo', label='Testowe')

plt.legend()
plt.xlabel('Cecha 1')
plt.ylabel('Cecha 2')
plt.title('Zbior danych')
plt.show

# Zadanie 3.2

model = k_nn(5)
model.fit(X, y)
wynik = model.predict(test)
print(wynik)
dokladnosc = model.score(test, wynik)
print(dokladnosc)

# Zadanie 3.3

x0= np.linspace(X[:,0].min(), X[:,0].max(),20)
x1= np.linspace(X[:,1].min(), X[:,1].max(),20)
XX,YY=np.meshgrid(x0,x1)
 
siatka = np.vstack((XX.ravel(),YY.ravel())).T
wynik = model.predict(siatka)
plt.plot(X[:,0][y==0],X[:,1][y==0],'o')
plt.plot(X[:,0][y==1],X[:,1][y==1],'ro')
plt.plot(siatka[:, 0], siatka[:, 1], 'yo')
wynik=wynik.reshape(XX.shape)
plt.contour(XX,YY,wynik)
plt.show()

# Zadanie 3.4

iris = datasets.load_iris()
X_ir=iris.data
Y_ir=iris.target
 
# klasyfikacja
iris_model = k_nn(7)
iris_model.fit(X_ir, Y_ir)
iris_wynik = iris_model.predict(X_ir)
print(iris_wynik)
print(iris_model.score(X_ir, Y_ir))

# Zadanie 3.5

pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_ir)

for i in range(len(iris.target_names)):
    plt.scatter(X_pca[Y_ir == i, 0], X_pca[Y_ir == i, 1])
    
plt.title('3.5 poczatkowy')
plt.xlabel('Skladowa glowna 1')
plt.ylabel('Skladowa glowna 2')
plt.show()

# Oblicz minimum i maksimum dla każdej ze składowych głównych
x_min, x_max = X_pca[:, 0].min(), X_pca[:, 0].max()
y_min, y_max = X_pca[:, 1].min(), X_pca[:, 1].max()

# Utwórz siatkę punktów w przestrzeni składowych głównych
xx, yy = np.meshgrid(np.linspace(x_min, x_max, 100), np.linspace(y_min, y_max, 100))

# Konwertuj siatkę punktów w przestrzeni składowych głównych na oryginalną przestrzeń cech
grid_points = np.c_[xx.ravel(), yy.ravel()]
grid_points_original = pca.inverse_transform(grid_points)

# Predykcja na siatce punktów
Z = iris_model.predict(grid_points_original)
Z = Z.reshape(xx.shape)

for i in range(len(iris.target_names)):
    plt.scatter(X_pca[Y_ir == i, 0], X_pca[Y_ir == i, 1])

plt.contour(xx, yy, Z)
plt.title('3.5 koncowy')
plt.xlabel('Skladowa glowna 1')
plt.ylabel('Skladowa glowna 2')
plt.show()

# Zadanie 4.1

from sklearn.datasets import fetch_california_housing
import pandas as pd

X, y = fetch_california_housing(return_X_y=True)
ilosc_danych=1000
X=X[:ilosc_danych]
y=y[:ilosc_danych]