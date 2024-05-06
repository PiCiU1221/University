# LAB 02
# gr.220A
# pp53828
# Piotr Pietrusewicz

import pandas as pd
import numpy as np
import scipy.stats as scs
import matplotlib.pyplot as plt


# Manipulowanie danymi
# Ćw. 1

df = pd.DataFrame({
    'A': np.random.normal(0,1,size=5),
    'B': np.random.normal(0,1,size=5),
    'C': np.random.normal(0,1,size=5)
})

df.index = pd.date_range(start='2020-03-01', periods=5)
df.index.name = 'data'

# print(df)

# Ćw. 2

df = pd.DataFrame({
    'A': np.random.normal(size=20),
    'B': np.random.normal(size=20),
    'C': np.random.normal(size=20)
})

df.index.name ='id'

# print(df)

# print(df.head(3))

# print(df.tail(3))

# print(df.index.name)

# print(df.columns.to_list())

# print(df.to_string(header=False, index=False))

# print(df.sample(5))

# print(df['A'].values)
# print(df[['A','B']].values)

# print(df.iloc[0:3, [0, 1]])

# print(df.iloc[5])

# print(df.iloc[[0,5,6,7], [1, 2]])

# Ćw. 3

# print(df.describe())

# print(df[df > 0].stack())

# print(df[df['A'] > 0]['A'])

# print(df.mean(axis=1))

# Ćw. 4

arr1 = np.random.randint(0, 101, size=(6,4))
arr2 = np.random.randint(0, 101, size=(2,4))

df1 = pd.DataFrame(arr1)
df2 = pd.DataFrame(arr2)

df = pd.concat([df1, df2])

# print(df)

# print(np.transpose(df))

# Sortowanie

df = pd.DataFrame({"x": [1, 2, 3, 4, 5], "y": ['a', 'b', 'a', 'b', 'b']}, index=np.arange(5))

df.index.name='id'

# print(df)

df_sorted_by_index = df.sort_index(ascending=False)

# print(df_sorted_by_index)

df_sorted_by_y = df.sort_values(by='y')

# print(df_sorted_by_y)

# Grupowanie danych

slownik ={'Day': ['Mon', 'Tue', 'Mon', 'Tue', 'Mon'], 'Fruit':
['Apple', 'Apple', 'Banana', 'Banana', 'Apple'], 'Pound': [10,
15, 50, 40, 5], 'Profit':[20, 30, 25, 20, 10]}
df3 = pd.DataFrame(slownik)
# print(df3)
# print(df3.groupby('Day').sum())
# print(df3.groupby(['Day','Fruit']).sum())


# Wypelnianie danych

df=pd.DataFrame(np.random.randn(20, 3), index=np.arange(20),
columns=['A','B','C'])
df.index.name='id'
# print(df)

# Wszystkim danym w kolumnie 'B' przypisujemy wartosc 1
df['B']=1
# print(df)
# Dla indeksu [1,2] w data frame przypisujemy wartosc 10
df.iloc[1,2]=10
# print(df)
# Dla kazdej ujemnej wartosci w data frame zmieniamy znak
df[df<0]=-df
# print(df)

# Uzupelnianie danych

# Dla danych o wierszu 0 i 3 w kolumnie 'B' ustawiamy wartosc Nan
df.iloc[[0, 3], 1] = np.nan
# print(df)
# Wpisujemy w miejsca pol Nan wartosc 0
df.fillna(0, inplace=True)
# print(df)
df.iloc[[0, 3], 1] = np.nan
# Zamieniamy Nan na wartosc -9999
df=df.replace(to_replace=np.nan,value=-9999)
# print(df)
df.iloc[[0, 3], 1] = np.nan
# Wypisujemy True albo False w zaleznosci czy dana wartosc jest Null
# print(pd.isnull(df))

# Zadania

df = pd.DataFrame({"x": [1, 2, 3, 4, 5], 'y': ['a', 'b', 'a','b', 'b']})
# print(df)

# Zad 1

# print(df.groupby('y')['x'].mean())

# Zad 2

# print(df[['y','x']].value_counts())

# Zad 3

data2 = np.loadtxt('autos.csv', delimiter=',', dtype='object')
data = pd.read_csv('autos.csv')

# print(data)
# print(data2)

# numpy loadtxt umieszcza zawartosc w tablicy, a pandas read_csv w data frame

# Zad 4

# print(data.groupby('make')[['city-mpg','highway-mpg']].mean())

# Zad 5

# print(data.groupby('make')['fuel-type'].value_counts())

# Zad 6

polynomial1 = np.polyfit(data['length'], data['city-mpg'], 1)
polynomial2 = np.polyfit(data['length'], data['city-mpg'], 2)

# print(polynomial1)
# print(polynomial2)

# print(np.polyval(polynomial1, data['length']))
# print(np.polyval(polynomial2, data['length']))

# Zad 7

# print(scs.pearsonr(data['length'], data['city-mpg']))

# Zad 8

length = data['length']
city_mpg = data['city-mpg']

x_values = np.linspace(length.min(), length.max(), 100)

predicted_city_mpg_linear = np.polyval(polynomial1, x_values)
predicted_city_mpg_quadratic = np.polyval(polynomial2, x_values)

# plt.scatter(length, city_mpg)

# plt.plot(x_values, predicted_city_mpg_linear, label='Polynomial 1', color='purple')
# plt.plot(x_values, predicted_city_mpg_quadratic, label='Polynomial 2', color='green')

# plt.xlabel('Length') 
# plt.ylabel('City MPG')

# plt.grid(True)
# plt.show()

# Zad 9

kde = scs.gaussian_kde(length)

density_estimates = kde.evaluate(x_values)

# plt.plot(x_values, density_estimates, label='KDE')

# plt.hist(length, bins=25, density=True, alpha=0.5, label='Samples')

# plt.xlabel('Length')
# plt.ylabel('Density')

# plt.legend()

# plt.grid(True)
# plt.show()

# Zad 10

width = data['width']

# fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

kde_length = scs.gaussian_kde(length)
x_values_length = np.linspace(length.min(), length.max(), 100)
density_estimates_length = kde_length.evaluate(x_values_length)
# ax1.plot(x_values_length, density_estimates_length, label='KDE')
# ax1.hist(length, bins=25, density=True, alpha=0.5, label='Samples')
# ax1.set_xlabel('Length')
# ax1.set_ylabel('Density')
# ax1.legend()
# ax1.grid(True)

kde_width = scs.gaussian_kde(width)
x_values_width = np.linspace(width.min(), width.max(), 100)
density_estimates_width = kde_width.evaluate(x_values_width)
# ax2.plot(x_values_width, density_estimates_width, label='KDE')
# ax2.hist(width, bins=25, density=True, alpha=0.5, label='Samples')
# ax2.set_xlabel('Width')
# ax2.set_ylabel('Density')
# ax2.legend()
#ax2.grid(True)

# plt.tight_layout()
# plt.show()

# Zad 11

kde = scs.gaussian_kde([length, width])

x_values = np.linspace(length.min(), length.max(), 100)
y_values = np.linspace(width.min(), width.max(), 100)
X, Y = np.meshgrid(x_values, y_values)
positions = np.vstack([X.ravel(), Y.ravel()])

density_estimates = np.reshape(kde(positions).T, X.shape)

plt.figure()
plt.scatter(length, width)

plt.contour(X, Y, density_estimates, cmap='viridis')
plt.xlabel('Length')
plt.ylabel('Width')

plt.savefig('kde_plot.png')
plt.savefig('kde_plot.pdf')

plt.show()