# %%
import pandas as pd

df = pd.read_csv('zoo.csv')

print(df.head())

# %% [markdown]
# # Zadanie 1

# %%
def freq(x, prob = True):
    xi = x.unique()

    ni = {}

    for value in x:
        if value in ni:
            ni[value] += 1
        else:
            ni[value] = 1

    if prob == True:
        total_number = len(x)

        for value in ni:
            ni[value] = ni[value] / total_number


    return xi, ni

# %%
[xi, ni] = freq(df['eggs'], True)

print(ni)

[xi, ni] = freq(df['eggs'], False)

print(ni)

# %% [markdown]
# # Zadanie 2

# %%
def freq2(x, y, prob = True):
    xi = x.unique()
    yi = y.unique()

    ni = {}

    for value_x in xi:
        ni[value_x] = {}
        for value_y in yi:
            ni[value_x][value_y] = 0

    for value_x, value_y in zip(x, y):
        ni[value_x][value_y] += 1

    if prob:
        for value_x in xi:
            total_number = sum(ni[value_x].values())
            for value_y in yi:
                ni[value_x][value_y] /= total_number

    return xi, yi, ni

# %%
[xi, yi, ni] = freq2(df['type'], df['eggs'], True)

print(ni)

[xi, yi, ni] = freq2(df['type'], df['eggs'], False)

print(ni)

# %% [markdown]
# # Zadanie 3

# %% [markdown]
# # Entropia

# %%
import math

def entropy(x):
    h = 0

    counts = x.value_counts()
    total_count = len(x)

    for count in counts:
        probability = count / total_count
        h -= probability * math.log(probability, 2)

    return h

# %%
h = entropy(df['eggs'])
print("Entropia:", h)

# %% [markdown]
# # Infogain

# %%
def infogain(x, y):
    total_samples = len(y)
    entropy_parent = entropy(y)

    unique_values = x.unique()
    weighted_entropy_children = 0

    for value in unique_values:
        subset_indices = x[x == value].index
        subset_y = y[subset_indices]
        subset_weight = len(subset_y) / total_samples
        weighted_entropy_children += subset_weight * entropy(subset_y)

    information_gain = entropy_parent - weighted_entropy_children
    return information_gain

# %%
i = infogain(df['eggs'], df['type'])

print("Infogain:", i)

# %% [markdown]
# # Zadanie 4

# %%
results = pd.DataFrame(columns=['column', 'entropy', 'infogain'])

results_list = []

for column in df.columns:
    if column != 'type' and column != 'animal':
        ent = entropy(df[column])
        ig = infogain(df[column], df['type'])
        result_df = pd.DataFrame({'column': [column], 'entropy': [ent], 'infogain': [ig]})
        results_list.append(result_df)

results = pd.concat(results_list, ignore_index=True)
results_sorted = results.sort_values(by='infogain', ascending=False)
print(results_sorted)

# %% [markdown]
# # Zadanie 5

# %%
import numpy as np
from scipy.sparse import csr_matrix

sparse_matrix_x = csr_matrix(np.array([[0, 1, 0], [0, 0, 1], [1, 0, 0]]))
sparse_matrix_y = csr_matrix(np.array([[1, 0, 0], [0, 1, 0], [0, 0, 1]]))

# Blad
# [xi, ni] = freq(sparse_matrix_x)
# [xi, yi, ni] = freq2(sparse_matrix_x, sparse_matrix_y)

# print(ni)

# %% [markdown]
# # freq

# %%
def freq(x, prob = True):
    x = x.toarray().flatten()

    xi = np.unique(x)

    ni = {}

    for value in x:
        if value in ni:
            ni[value] += 1
        else:
            ni[value] = 1

    if prob == True:
        total_number = len(x)

        for value in ni:
            ni[value] = ni[value] / total_number


    return xi, ni

# %%
[xi, ni] = freq(sparse_matrix_x)

print(ni)

# %% [markdown]
# # freq2

# %%
def freq2(x, y, prob = True):
    x = x.toarray().flatten()
    y = y.toarray().flatten()

    xi = np.unique(x)
    yi = np.unique(y)

    ni = {}

    for value_x in xi:
        ni[value_x] = {}
        for value_y in yi:
            ni[value_x][value_y] = 0

    for value_x, value_y in zip(x, y):
        ni[value_x][value_y] += 1

    if prob:
        for value_x in xi:
            total_number = sum(ni[value_x].values())
            for value_y in yi:
                ni[value_x][value_y] /= total_number

    return xi, yi, ni

# %%
[xi, yi, ni] = freq2(sparse_matrix_x, sparse_matrix_y)

print(ni)


