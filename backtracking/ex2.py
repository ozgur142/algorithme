# %%
# 1)
# 1.i
def lecture_sudoku(nom):
    f = open(nom, 'r')
    n = int(f.readline())
    data = f.readlines()[0:]
    f.close()
    G = []
    
    for l in data:
        le = [int(e) for e in l.split()]
        for e in le:
            G.append(e)

    return G,n

c = 'sudokus/sudoku-3-facile-4.txt'
lecture_sudoku(c)
#%%
# 1.ii
def ecriture_sudoku(G, n, nom):
    with open(nom, 'w') as f:
        f.write(str(n)+'\n')

        for i in range(0, n**4, n**2):
            for j in range(n**2):
                f.write(str(G[i+j])+" ")
            f.write('\n')


c = 'sudokus/sudoku-3-facile-4.txt'
G,n = lecture_sudoku(c)
ecriture_sudoku(G, n, "mon_sudoku")
# %%
# 1.iii
def affiche_sudoku(G, n):
    for i in range(0, n**4, n**2):
        for j in range(n**2):
            if G[i+j] == 0:
                print('_', end=" ")
            else:
                print(G[i+j], end=" ")
        print('')

affiche_sudoku(G, n)
# %%
# 2)
# 2.i
def zone(n, u):
    if u > n**4-1:
        raise ValueError("not in range!!!")
    #finding zone
    k = 0
    for p in range(1,n):
        if u < (n**3)*p:
            k = p-1
            break

    L = []
    start = (n**3)*k
    for i in range(start, n**3+start, n**2):
        for j in range(n):
            L.append(j+i)
    for i in range(n**2):
        if u in L:
            return L
        L=list(map(lambda x:x+3, L))
#testing
zone(4,50)
# %%
# 2.ii
def valide(G, n, u, x):
    i,j = int(u/(n**2)), u % (n**2)
    #controle de ligne et du colone
    for k in range(n**2):
        if k!= i and G[(k*(n**2))+j] == x:
            return False
        if k != j and G[(i*(n**2))+k] == x:
            return False
    #controle de zone
    zi, zj = 3*int(i/3), 3*int(j/3)
    for k in range(n):
        for l in range(n):
            if (zi+k)*(n**2) + (zj+l) != u and G[(zi+k)*(n**2) + (zj+l)] == x:
                return False
    return True
# %%
# 2.iii
def sudoku(G, n, u=0):
    while u < n**4 and G[u] != 0:
        u += 1
    if u == n**4:
        return True
    for x in range(1, (n**2)+1):
        if valide(G,n,u,x):
            G[u] = x
            if sudoku(G, n, u+1):
                return True
    G[u] = 0
    return False
# %%
c = 'sudokus/sudoku-3-difficile-2.txt'
G, n = lecture_sudoku(c)
sudoku(G, n)
# %%
print(G)
# %%
affiche_sudoku(G,3)
# %%
