import numpy as np
import numpy.linalg as npl
import scipy.io as sio
from matplotlib import pyplot as plt

data1 = sio.loadmat('lab11_data1.mat')["data1"] # zbior testowy
data2 = sio.loadmat('lab11_data2.mat')["data2"] # zbior uczacy

# data -> [xpp, ypp, xp, yp, x, y]

# zad 1 - model liniowy
# xpp - a11 * xp + a12 * yp + a13 * x + a14 * y
# ypp - a21 * xp + a22 * yp + a23 * x + a24 * y

Xtrain = np.hstack((data2[:, 0:1], data2[:, 1:2])).T
Ztrain = np.hstack((data2[:, 2:3], data2[:, 3:4], data2[:, 4:5], data2[:, 5:6])).T

Rs = Xtrain @ Ztrain.T
Ps = Ztrain @ Ztrain.T
A1 = Rs @ npl.inv(Ps)
print(A1)

Xpp = data1[:, 0]
Ypp = data1[:, 1]

d2x = lambda xp, yp, x, y: A1[0, 0] * xp + A1[0, 1] * yp + A1[0, 2] * x + A1[0, 3] * y
d2y = lambda xp, yp, x, y: A1[1, 0] * xp + A1[1, 1] * yp + A1[1, 2] * x + A1[1, 3] * y

msexpp = np.mean((Xpp - d2x(data1[:, 2], data1[:, 3], data1[:, 4], data1[:, 5])) ** 2)
mseypp = np.mean((Ypp - d2y(data1[:, 2], data1[:, 3], data1[:, 4], data1[:, 5])) ** 2)
err = (msexpp + mseypp) / 2
print(err)

# zad 2 - model nieliniowy
# xpp - a11 * xp ** 2 + a12 * yp ** 2 + a13 * x + a14 * y + a15 * xp * yp
# ypp - a21 * xp ** 2 + a22 * yp ** 2 + a23 * x + a24 * y + a15 * xp * yp

Xtrain = np.hstack((data2[:, 0:1], data2[:, 1:2])).T
Ztrain = np.hstack((data2[:, 2:3] ** 2, data2[:, 3:4] ** 2, data2[:, 4:5], data2[:, 5:6], data2[:, 2:3] * data2[:, 3:4])).T

Rs = Xtrain @ Ztrain.T
Ps = Ztrain @ Ztrain.T
A2 = Rs @ npl.inv(Ps)
print(A2)

Xpp = data1[:, 0]
Ypp = data1[:, 1]

d2x = lambda xp, yp, x, y: A2[0, 0] * xp ** 2 + A2[0, 1] * yp ** 2 + A2[0, 2] * x + A2[0, 3] * y + A2[0, 4] * xp * yp
d2y = lambda xp, yp, x, y: A2[1, 0] * xp ** 2 + A2[1, 1] * yp ** 2 + A2[1, 2] * x + A2[1, 3] * y + A2[1, 4] * xp * yp

msexpp = np.mean((Xpp - d2x(data1[:, 2], data1[:, 3], data1[:, 4], data1[:, 5])) ** 2)
mseypp = np.mean((Ypp - d2y(data1[:, 2], data1[:, 3], data1[:, 4], data1[:, 5])) ** 2)
err = (msexpp + mseypp) / 2
print(err)

# zad 3 - symulacja
# rownania ruchu

d2x = lambda xp, yp, x, y: A1[0, 0] * xp + A1[0, 1] * yp + A1[0, 2] * x + A1[0, 3] * y
d2y = lambda xp, yp, x, y: A1[1, 0] * xp + A1[1, 1] * yp + A1[1, 2] * x + A1[1, 3] * y

# warunki poczatkowe
x = [60]
y = [0]
xp = [0]
yp = [0]

xpp = [d2x(xp[-1], yp[-1], x[-1], y[-1])]
ypp = [d2y(xp[-1], yp[-1], x[-1] ,y[-1])]

# ustawienia metody
h = 2 ** (-12)
stop = 500

for t in np.arange(h, stop, h):
    x.append(x[-1] + xp[-1] * h)
    y.append(y[-1] + yp[-1] * h)
    xp.append(xp[-1] + xpp[-1] * h)
    yp.append(yp[-1] + ypp[-1] * h)
    xpp.append(d2x(xp[-1], yp[-1], x[-1], y[-1]))
    ypp.append(d2y(xp[-1], yp[-1], x[-1] ,y[-1]))

plt.figure()
plt.plot(data1[:, 4], data1[:, 5], 'b')
plt.title("dane pliku")
plt.axis([-60, 60, -60, 60])

plt.figure()
plt.plot(x, y, 'r')
plt.title("metoda euhlera")
plt.axis([-60, 60, -60, 60])

plt.show()
