#%%
from random import choice, randint, shuffle
from matplotlib import pyplot as plt
# %%
# 1)
# 1.i
def eltMajDet(T):
    n = len(T)
    for i in range(n):
        x = T[i]
        occr = T.count(x)
        if occr >= n/2:
            return x
print(eltMajDet([2,2,3,0,-1,2]))
# %%
# 1.ii
def eltMajProba(T):
    n = len(T)
    x = choice(T)
    while not T.count(x) >= n/2:
        x = choice(T)
    
    return x
    
print(eltMajProba([2,2,3,0,-1,2]))
# %%
# 1.iii
def tabAlea(n, a, b, k):
    T = []
    m = randint(a, b)
    if k < n/2:
        print("k doit être >= n/2!!!")
        return None
    for _ in range(k):
        T.append(m)
    for _ in range(n-k):
        x = randint(a,b)
        while x == m:
            x = randint(a,b)
        T.append(x)
    shuffle(T)
    return T

tabAlea(10,1,9,6)
# %%
# 1.iv
def tabDeb(n, a, b, k):
    T = []
    m = randint(a, b)
    if k < n/2:
        print("k doit être >= n/2!!!")
        return None
    for _ in range(k):
        T.append(m)
    for _ in range(n-k):
        x = randint(a,b)
        while x == m:
            x = randint(a,b)
        T.append(x)
    T.pop(0)
    shuffle(T)
    T.insert(0, m)
    return T
print(tabDeb(10,1,100,6))

def tabFin(n, a, b, k):
    T = []
    m = randint(a, b)
    if k < n/2:
        print("k doit être >= n/2!!!")
        return None
    for _ in range(n-k):
        x = randint(a,b)
        while x == m:
            x = randint(a,b)
        T.append(x)
    for _ in range(k):
        T.append(m)
    return T
print(tabFin(10,1,100,6))
# %%
# 1.v
import time

proba = []
det = []
a = 0
b = 1000
for n in range(1000, 10000, 500):
    k = int(n/2) + randint(0, n/2)
    T = tabAlea(n, a, b, k)
    t1 = time.time()
    eltMajDet(T)
    t2 = time.time()
    eltMajProba(T)
    t3 = time.time()

    det.append(t2-t1)
    proba.append(t3-t2)

plt.hist(det)
plt.show()
plt.hist(proba)
plt.show()
#%%
# 2)
# 2.i
def contientEltMaj(T, m):
    for _ in range(m):
        x = choice(T)
        if T.count(x) >= len(T)/2:
            return True
    return False
contientEltMaj([2,3,3,3,5,1,100,5,3,3,3], 2)
# %%
# 2.ii
def testContient(n, a, b, k, m, N):
    T = tabAlea(n, a, b, k)
    reussite = 0
    for _ in range(n):
        if contientEltMaj(T, m):
            reussite += 1
    return reussite/N
# %%
# 2.iii
n = 1000
m = 1
N = 1000
r = []
for k in range(500,1000,50):
    r.append(testContient(n, 0, 1000, k, m, N))
plt.plot(r)
# %%
