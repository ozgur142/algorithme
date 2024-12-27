#%%
# 1)
def permSuivante(P):
    n = len(P)
    j = n-2
    while j >= 0 and P[j] > P[j+1]:
        j -= 1
    if j < 0:
        return None
    l = n-1
    while P[j] > P[l]:
        l -= 1
    P[j], P[l] = P[l], P[j]
    j, l = j+1, n-1
    while j<l:
        P[j], P[l] = P[l], P[j]
        j, l = j+1, l-1
    
    return P

permSuivante([0,1,2,3,4,5,6,7,8,9])
#%%
# 2)
def dico(a, b, c):
    i = 1
    d = {}

    for m in [a, b, c]:
        for x in m:
            if x not in d:
                d[x] = i
                i+=1

    return d

a = 'oasis'
b = 'soleil'
c = 'mirage'
dico(a,b,c)
# %%
# 3)
def valeur(m, D, p):
    v = 0
    for x in m:
        v = 10*v + p[D[x]]
    return v

# test
a = 'oasis'
b = 'soleil'
c = 'mirage'
D = dico(a,b,c)
valeur("oasis", D, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
# %%
def cryptarithme(a, b, c):
    d = dico(a, b, c)    # O(m)
    p = list(range(10))
    while p != None:
        if valeur(a, d, p) + valeur(b, d, p) == valeur(c, d, p):
            r = {}
            for x in d:
                r[x] = p[d[x]]
            return r
        if p == None:
            return {}

        p = permSuivante(p)
        
#test
a = 'oasis'
b = 'soleil'
c = 'mirage'
print(cryptarithme(a, b, c))
# %%
#test2
a = 'COCA'
b = 'COLA'
c = 'PEPSI'
print(cryptarithme(a, b, c))