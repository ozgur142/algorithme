# %%
def affichage_reine(Q):
    for q in Q:
        for i in range(len(Q)):
            if q == i:
                print('x ', end='')
                continue
            print('_ ', end='')
        print('')
            
affichage_reine([2,0,3,1])
# %%
def reine_possible(Q, r, j):
    if Q[r] != -1:
        return False
    if j in Q:
        return False
    for i in range(r):
        if j == Q[i]+r-i:
            return False
        if j == Q[i]+i-r:
            return False
    return True

reine_possible([1,3,-1,-1], 2, 2)
# %%
#il faut essayer tous les solutions possible!!
def placement_reines(Q, r=0):
    n = len(Q)
    if r == n:
        return Q
    
    for j in range(n):
        ok = reine_possible(Q, r, j)
        if ok:
            Q[r] = j
            return placement_reines(Q,r+1)
            
    

#test
a = placement_reines([2,-1,-1,-1], 1)
b = placement_reines([0,3,1,-1], 3)
c = placement_reines([2,5,-1,-1,-1,-1,-1,-1], 2)
print(a,"\n", b)
print(c)
# %%
def reines(n):
    q = [-1 for i in range(n)]
    Q = placement_reines(q,0)                        

    return Q

Q = reines(10)
print(Q)
affichage_reine(Q)
# %%
def valide(Q):
    for i in range(n-1):
        for j in range(i+1, n):
            if Q[i] == Q[j]: 
                return False
            if Q[j] == Q[i] + j -i:
                return False
            if Q[]