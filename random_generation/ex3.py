# %%
from matplotlib import pyplot as plt
# %%
# 1)
# 1.i
def suivant(xn, a, c, m):
    xnp1 = (a*xn + c) % m
    return xnp1
# %%
# 1.ii
def valeurs(x0, a, c, m, N):
    x = suivant(x0, a, c, m)
    L = [x0, x]
    for _ in range(N-2):
        x = suivant(x, a, c, m)
        L.append(x)
    return L
# %%
# 1.iii
x0, a, c, m = 0, 3, 5, 136
L = valeurs(x0, a, c, m, 20)
print(L)
# %%
# 2)
x0, a, c, m = 0, 75, 74, (2**16)+1
L = valeurs(x0, a, c, m, 2**20)
print(L)
# %%
# 3)
# 3.i
a = 16807
c = 0
m = (2**31)-1
V = valeurs(10, a, c, m, 1000)
plt.plot(V, 'r.')
# %%
# 3.ii
a = 16807
c = 0
m = (2**31)-1
V1 = valeurs(123489, a, c, m, 10000)
V2 = valeurs(25743, a, c, m, 10000)
plt.scatter(V1, V2, s=.2)
# %%
# 3.iii
a = 16807
c = 0
m = (2**31)-1
V1 = valeurs(5, a, c, m, 10000)
V2 = valeurs(6, a, c, m, 10000)
plt.scatter(V1, V2, s=.2)
# %%
class Generateur:
    def __init__(self, a, c, m):
        self.a = a
        self.c = c
        self.m = m
        self.x = None
    
    def graine(g):
        x = g

    def aleatoire():
        x = suivant(x, a, c, m)
# %%
g = Generateur(3,5,17)
g