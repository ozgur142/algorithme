#%%
from dessins import *
#%%
#ex1)
#1.1
def distance(A, B):
    return ((A[0]-B[0])**2+(A[1]-B[1])**2)**(1/2)

#tests
A, B, C = (121,77), (48,70), (12,72)
distance(A,B), distance(A,C), distance(B,C)
# %%
#1.2
def aretes(P):
    n = len(P)
    L = []
    for i in range(n-1):
        for j in range(i+1, n):
            L.append((i,j,distance(P[i], P[j])))
    return L

#test
P = [(6,20),(67,18),(96,4),(32,45)]
aretes(P)    
# %%
#1.3.i
from random import random
def pointsAleatoires(n, xmax, ymax):
    L = []
    for _ in range(n):
        L.append((random()*xmax, random()*ymax))
    return L

#test
pointsAleatoires(3, 10, 20)
# %%
#1.3.ii
points = pointsAleatoires(100, 10, 20)
dessinPoints(points)
# %%
#1.4.i
def listesAdjacence(n, A):
    adj = {i:[] for i in range(n)}
    for i,j in A:
        adj[i].append(j)
        adj[j].append(i)
    return adj

#test
A = [(0,1),(0,2),(0,3),(1,2),(1,3),(2,3)]
listesAdjacence(4, A)
#%%
#1.4.ii
points = pointsAleatoires(4, 10, 20)
A = [(0,1),(0,2),(0,3),(1,2),(1,3),(2,3)]
adj = listesAdjacence(4, A)
dessinGraphe(points, adj)
# %%
#ex2)
#2.1.i
def arbreCouvrant2(n, Aretes):
    A = {i:[] for i in range(n)}
    C = [i for i in range(n)]
    m = n
    aretesCroissant = sorted(Aretes, key = lambda x: x[2])
    for aret in aretesCroissant:
        u = aret[0]
        v = aret[1]
        if C[u] != C[v]:
            A[u].append(v)
            A[v].append(u)
            for s in C:
                if s == C[v]:
                    s = C[u]
            m -= 1
            if m == 1:
                break
    return A                    

def arbreCouvrant(n, Aretes):
    C = [i for i in range(n)]
    m = n
    aretesCroissant = sorted(Aretes, key = lambda x: x[2])
    tableau_aretes = []
    for aret in aretesCroissant:
        u = aret[0]
        v = aret[1]
        if C[u] != C[v]:
            tableau_aretes.append((u,v))
            for s in C:
                if s == C[v]:
                    s = C[u]
            m -= 1
            if m == 1:
                break
            
    return listesAdjacence(n, tableau_aretes)


#test
A = aretes([(6,20),(67,18),(96,4),(32,45)])    
arbreCouvrant(4, A)
# %%
#2.1.ii
n = 10
points = pointsAleatoires(n, 10, 20)
A = aretes(points)
arbre = arbreCouvrant(n, A)
print(arbre)
dessinGraphe(points, arbre)
# %%
#2.2.i
def parcoursArbre(n, Adj):
    P = [0]
    C = []
    while P != []:
        s = P.pop()
        C.append(s)
        for voisin in Adj.get(s):
            if voisin not in C:
                P.append(voisin)
    return C
#%%
#2.2.ii
n = 3
points = pointsAleatoires(n, 10, 20)
A = aretes(points)
adj = arbreCouvrant(n, A)
parcour = parcoursArbre(n, adj)
dessinParcours(points, parcour)
# %%
