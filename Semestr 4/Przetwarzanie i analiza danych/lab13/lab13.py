import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn import datasets, svm, metrics
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression, Perceptron
from sklearn.multiclass import OneVsOneClassifier, OneVsRestClassifier
from sklearn import preprocessing
import scipy
from time import time

# Zadanie 1.1

X, y = datasets.make_classification(
    n_samples=1000,
    n_features=2,
    n_informative=2,
    n_redundant=0,
    n_clusters_per_class=2,
    random_state=1
)

# Zadanie 1.2

plt.scatter(X[:,0], X[:,1], c = y)
plt.show()

# Zadanie 1.3

import matplotlib.patches as mpatches

X = pd.DataFrame(X, columns=['x', 'y'])
y = pd.Series(y)

classifiers = [
    ('OvOSVC linear', OneVsOneClassifier(svm.SVC(kernel='linear', probability=True))),
    ('OvRSVC linear', OneVsRestClassifier(svm.SVC(kernel='linear', probability=True))),
    ('OvOSVC' , OneVsOneClassifier(svm.SVC(kernel='rbf', probability=True))),
    ('OvRSVC' , OneVsRestClassifier(svm.SVC(kernel='rbf', probability=True))),
    ('OvOLogisticRegression', OneVsOneClassifier(LogisticRegression())),
    ('OvRLogisticRegression', OneVsRestClassifier(LogisticRegression())),
    ('OvOPerceptron', OneVsOneClassifier(Perceptron())),
    ('OvRPerceptron', OneVsRestClassifier(Perceptron())),
]

results = []
iteration_data = []

for name, clf in classifiers:
    for i in range(100):
        # Podział zbioru danych na zbiór treningowy i testowy
        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.5, random_state=None)
        
        # Pomiar czasu trenowania
        start_train = time()
        clf.fit(X_train, y_train)
        train_time = time() - start_train
        
        # Pomiar czasu predykcji
        start_test = time()
        y_pred = clf.predict(X_test)
        test_time = time() - start_test
        
        # Obliczanie miar jakości
        accuracy_score = metrics.accuracy_score(y_test, y_pred)
        recall_score = metrics.recall_score(y_test, y_pred, average='weighted')
        precision_score = metrics.precision_score(y_test, y_pred, average='weighted')
        f1_score = metrics.f1_score(y_test, y_pred, average='weighted')
        roc_auc = metrics.roc_auc_score(y_test, y_pred, multi_class='ovr')
        
        # Zapis wyników
        results.append({
            'classifier': name,
            'accuracy_score': accuracy_score,
            'recall_score': recall_score,
            'precision_score': precision_score,
            'f1_score': f1_score,
            'roc_auc': roc_auc,
            'train_time': train_time,
            'test_time': test_time
        })

        if i == 99:
            if hasattr(clf, "predict_proba"):
                y_pred_proba = clf.predict_proba(X_test)[:, 1]
            else:
                y_pred_proba = clf.decision_function(X_test)
                y_pred_proba = (y_pred_proba - y_pred_proba.min()) / (y_pred_proba.max() - y_pred_proba.min())

            iteration_data.append({
                'classifier': name,
                'X_test': X_test,
                'y_test': y_test,
                'y_pred': y_pred,
                'y_pred_proba': y_pred_proba
            })

# Tworzenie DataFrame z wynikami
results_df = pd.DataFrame(results)

# Grupowanie wyników według rodzaju klasyfikatora
grouped_results = results_df.groupby('classifier').mean().reset_index()

# Wyświetlenie wyników
print(grouped_results)

# skalowanie czasu trenowania i testowania względem innych miar jakości
max_other_metric = grouped_results[['accuracy_score', 'recall_score', 'precision_score', 'f1_score', 'roc_auc']].max(axis=1).max()
max_train_test_time = max(grouped_results['train_time'].max(), grouped_results['test_time'].max())
grouped_results['train_time'] = grouped_results['train_time'] / max_train_test_time * max_other_metric
grouped_results['test_time'] = grouped_results['test_time'] / max_train_test_time * max_other_metric

# Tworzenie listy miar jakości klasyfikacji
metrics = ['accuracy_score', 'recall_score', 'precision_score', 'f1_score', 'roc_auc', 'train_time', 'test_time']

x = np.arange(len(metrics))  # lokalizacje na osi X
width = 0.1  # szerokość słupków

fig, ax = plt.subplots(figsize=(15, 8))

# Tworzenie słupków dla każdego klasyfikatora
for i, classifier in enumerate(grouped_results['classifier']):
    ax.bar(x + i * width, grouped_results.loc[i, metrics], width, label=classifier)

ax.set_xticks(x + width * (len(grouped_results['classifier']) - 1) / 2)
ax.set_xticklabels(metrics)
ax.legend()
plt.show()

for data in iteration_data:
    name = data['classifier']
    X_test = data['X_test']
    y_test = data['y_test']
    y_pred = data['y_pred']

    plt.figure(figsize=(15, 5))

    # Wykres oczekiwanych wartości
    plt.subplot(1, 3, 1)
    plt.scatter(X_test['x'], X_test['y'], c=y_test, cmap='coolwarm', s=50, alpha=0.5)
    plt.title('oczekiwane')

    # Wykres obliczonych wartości
    plt.subplot(1, 3, 2)
    plt.scatter(X_test['x'], X_test['y'], c=y_pred, cmap='coolwarm', s=50, alpha=0.5)
    plt.title('obliczone')

    # Wykres różnicy między oczekiwanymi a obliczonymi wartościami
    plt.subplot(1, 3, 3)
    plt.scatter(X_test['x'], X_test['y'], c=~(y_test != y_pred), cmap='RdYlGn', s=50, alpha=0.5)
    plt.title('różnice')

    correct_patch = mpatches.Patch(color='green', label='Poprawnie sklasyfikowane')
    incorrect_patch = mpatches.Patch(color='red', label='Błędnie sklasyfikowane')

    plt.legend(handles=[correct_patch, incorrect_patch], loc='lower right')

    plt.suptitle(name)
    plt.show()

    from sklearn.metrics import roc_curve, auc

plt.figure()

for data in iteration_data:
    name = data['classifier']
    X_test = data['X_test']
    y_test = data['y_test']
    y_pred_proba = data['y_pred_proba']

    fpr, tpr, thresholds = roc_curve(y_test, y_pred_proba)
    roc_auc = auc(fpr, tpr)

    plt.plot(fpr, tpr, '-', label=name)

    print(f"AUC for {name}: {roc_auc:.2f}")

plt.title("Krzywa ROC")
plt.xlabel("Odsetek fałszywie pozytywnych")
plt.ylabel("Odsetek prawdziwie pozytywnych")

fpr_tpr_equal = np.linspace(0, 1, 100)
plt.plot(fpr_tpr_equal, fpr_tpr_equal, '--k', label='Losowy wybów')

plt.legend()
plt.show()

x_min, x_max = X['x'].min() - 1, X['x'].max() + 1
y_min, y_max = X['y'].min() - 1, X['y'].max() + 1
xx, yy = np.meshgrid(np.arange(x_min, x_max, 0.01),
                     np.arange(y_min, y_max, 0.01))

for data in iteration_data:
    name = data['classifier']
    X_test = data['X_test']
    y_test = data['y_test']
    y_pred_proba = data['y_pred_proba']
    
    mesh_data = pd.DataFrame(np.c_[xx.ravel(), yy.ravel()], columns=['x', 'y'])
    
    clf = classifiers[[clf[0] for clf in classifiers].index(name)][1]
    if hasattr(clf, "predict_proba"):
        Z = clf.predict_proba(mesh_data)[:, 1]
    else:
        Z = clf.decision_function(mesh_data)
        Z = (Z - Z.min()) / (Z.max() - Z.min())
    
    Z = Z.reshape(xx.shape)

    plt.contourf(xx, yy, Z, cmap=plt.cm.coolwarm)
    
    plt.scatter(X_test['x'], X_test['y'], c=y_test, edgecolor='k', cmap=plt.cm.coolwarm)
    
    plt.title(name)
    plt.xlabel("Atrybut 1")
    plt.ylabel("Atrybut 2")
    plt.show()

# Zadanie 2.1

from sklearn.datasets import make_classification

X, y = make_classification(
    n_samples=200,
    n_features=2,
    n_classes=2,
    n_informative=2,
    n_redundant=0,
    n_repeated=0,
    random_state=42
)

# Zadanie 2.3

k_neighbors_params = {
    'n_neighbors': [1, 3, 5, 7, 9, 11, 13, 15],
    'weights': ['uniform', 'distance'],
    'algorithm': ['auto', 'ball_tree', 'kd_tree', 'brute'],
    'leaf_size': [10, 20, 30, 40],
    'p': [1, 2, 3],
}

# Zadanie 2.4

from sklearn.model_selection import GridSearchCV
from sklearn.neighbors import KNeighborsClassifier

k_neighbors = KNeighborsClassifier()

grid_search = GridSearchCV(estimator=k_neighbors, param_grid=k_neighbors_params, scoring='roc_auc', cv=5, n_jobs=-1)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.5, random_state=42)

grid_search.fit(X_train, y_train)

best_params = grid_search.best_params_
print(f"Best parameters: {best_params}")

# Zadanie 2.5

param1_values = k_neighbors_params['n_neighbors']
param2_values = k_neighbors_params['p']
accuracy_scores = np.zeros((len(param1_values), len(param2_values)))
for i, param1 in enumerate(param1_values):
    for j, param2 in enumerate(param2_values):
        clf = KNeighborsClassifier(n_neighbors=param1, p=param2)
        clf.fit(X_train, y_train)
        accuracy_scores[i, j] = clf.score(X_test, y_test)

contour = plt.contourf(param1_values, param2_values, accuracy_scores.T, cmap='viridis')
plt.colorbar(contour, label='score')
plt.xlabel('n_neighbors')
plt.ylabel('p')
plt.show()

# Zadanie 2.6

from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, recall_score, precision_score, f1_score, roc_auc_score
import numpy as np
import time
import pandas as pd

optimal_params = {
    'algorithm': 'auto',
    'leaf_size': 10,
    'n_neighbors': 11,
    'p': 1,
    'weights': 'distance'
}

clf = KNeighborsClassifier(**optimal_params)

num_iterations = 100

accuracy_scores = []
recall_scores = []
precision_scores = []
f1_scores = []
roc_auc_scores = []
training_times = []
testing_times = []

iteration_data = []

for i in range(num_iterations):
    # dzielimy dane na część uczącą i testową
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)
    
    # uczenie na zbiorze uczącym
    start_train = time.time()
    clf.fit(X_train, y_train)
    end_train = time.time()
    training_times.append(end_train - start_train)
    
    # wyznaczenie predykcji na zbiorze testowym
    start_test = time.time()
    y_pred = clf.predict(X_test)
    y_pred_prob = clf.predict_proba(X_test)[:, 1]
    end_test = time.time()
    testing_times.append(end_test - start_test)
    
    # liczenie miar klasyfikacji
    accuracy_scores.append(accuracy_score(y_test, y_pred))
    recall_scores.append(recall_score(y_test, y_pred, average='macro'))
    precision_scores.append(precision_score(y_test, y_pred, average='macro'))
    f1_scores.append(f1_score(y_test, y_pred, average='macro'))
    roc_auc_scores.append(roc_auc_score(y_test, y_pred_prob))

    if i == num_iterations - 1:
        y_pred_proba = clf.predict_proba(X_test)[:, 1]

        iteration_data.append({
            'X_test': X_test,
            'y_test': y_test,
            'y_pred_proba': y_pred_proba
        })

results_df = pd.DataFrame({
    'Accuracy': accuracy_scores,
    'Recall': recall_scores,
    'Precision': precision_scores,
    'F1 Score': f1_scores,
    'ROC AUC': roc_auc_scores,
    'Training Time (s)': training_times,
    'Testing Time (s)': testing_times
})

mean_results = results_df.mean()

print("Mean results:")
print(mean_results)

# Zadanie 2.9

from sklearn.metrics import roc_curve, auc
import matplotlib.pyplot as plt

X_test_last = iteration_data[-1]['X_test']
y_test_last = iteration_data[-1]['y_test']
y_pred_proba_last = iteration_data[-1]['y_pred_proba']

# Calculate ROC curve
fpr, tpr, thresholds = roc_curve(y_test_last, y_pred_proba_last)
roc_auc = auc(fpr, tpr)

# Plot ROC curve
plt.figure()
plt.plot(fpr, tpr, color='darkorange', lw=2, label=f'ROC curve (AUC = {roc_auc:.2f})')
plt.plot([0, 1], [0, 1], color='navy', lw=2, linestyle='--')
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.title("Krzywa ROC")
plt.xlabel("Odsetek fałszywie pozytywnych")
plt.ylabel("Odsetek prawdziwie pozytywnych")
plt.legend(loc="lower right")
plt.show()