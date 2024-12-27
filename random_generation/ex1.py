# %%
from random import *
from matplotlib import pyplot as plt
# %%
# 1)
# 1.i.
def entiersAleatoires(n, a, b):
    L = []
    for i in range(n):
        x = randint(a,b)
        L.append(x)
    return L
## TEST
print(entiersAleatoires(10, 1, 50))
# %%
# 1.ii.
def entiersAleatoires2(n, a, b):
    L = []
    for i in range(n):
        x = randrange(a,b)
        L.append(x)
    return L
## TEST
print(entiersAleatoires2(10, 1, 50))
# %%
# 1.iii.
t = 1000
a = 1
b = 100
L1 = entiersAleatoires(t, a, b)
L2 = entiersAleatoires2(t, a, b)

plt.hist(L1, bins=100)
plt.show()

plt.hist(L2, bins=100)
plt.show()
# %%
# 2)
# 2.i
def flottantsAleatoires(n):
    L = []
    for _ in range(n):
        L.append(random())
    return L

print(flottantsAleatoires(10))
# %%
# 2.ii
def flottantsAleatoires2(n, a, b):
    L = []
    for _ in range(n):
        L.append(uniform(a, b))
    return L

print(flottantsAleatoires2(10, 3, 5))
# %%
# 2. iii
t = 1000
a = -3
b = 10

L1 = flottantsAleatoires(t)
L2 = flottantsAleatoires2(t, a, b)

plt.plot(L1)
plt.show()
plt.plot(L2)
plt.show()
# %%
# 3)
# 3.i
def pointsDisque(n):
    points = []
    i = 0
    while i < n:
        x = uniform(-1, 1)
        y = uniform(-1, 1)
        eq = x**2 + y**2 <= 1
        if eq:
            points.append((x,y))
            i += 1
        else:
            continue
    return points

print(pointsDisque(5))
# %%
# 3.ii
def pointsDisque2(n):
    points = []
    for _ in range(n):
        x = uniform(-1, 1)
        y = uniform(-1, 1)
        while not x**2 + y**2 <= 1:
            y = uniform(-1, 1)
        
        points.append((x,y))
    
    return points
print(pointsDisque(5))
# %%
# 3.iii
def affichagePoints(L):
    X = [x for x,y in L] # on récupère les abscisses...
    Y = [y for x,y in L] # ... et les ordonnées
    plt.scatter(X, Y, s=1) # taille des points minimale
    plt.axis('square') # même échelle en abscisse et ordonnée
    plt.show()
# %%
# 3.iv
p1 = pointsDisque(10000)
p2 = pointsDisque2(10000)

affichagePoints(p1)
affichagePoints(p2)
# %%
# 4)
# 4.i
def aleatoireModulo(N):
    x = getrandbits(N.bit_length())
    return x % N

print(aleatoireModulo(5))
# %%
# 4.ii
def aleatoireRejet(N):
    x = getrandbits(N.bit_length())
    while not x < N:
        x = getrandbits(N.bit_length())
    return x

print(aleatoireRejet(20))
# %%
# 4.iii
L1 = []
L2 = []

for _ in range(10000):
    L1.append(aleatoireModulo(100))
    L2.append(aleatoireRejet(100))

plt.hist(L1)
plt.show()

plt.hist(L2)
plt.show()
#%%

