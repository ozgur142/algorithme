# %%
# 1)
# 1.i
def clause(s):
    l = [int(e) for e in s.split()]
    return l[:-1]

print(clause("-1 2 3 0\n"))
# %%
# 1.ii
def parseur(nom):
    f = open(nom, 'r')
    data = f.readlines()
    f.close()
    result = []
    for l in data:
        if l[0] == 'c':
            continue
        if l[0] == 'p':
            rl = l.split()
            n = int(rl[-2])
            continue
        result.append(clause(l))
    
    return result, n

c = 'cnf/simple_v3_c2.cnf'
print(parseur(c))
# %%
# 2)
# 2.i
def est_valide(F, A):
    for C in F:
        OK = False
        for l in C:
            x = -1
            if A[abs(l)-1]:
                x = 1
            if l*x > 0:
                OK = True
        if not(OK):
            return False
    return True

c = 'cnf/simple_v3_c2.cnf'
F,n = parseur(c)
print(F)
A1 = [True, True, False]
A2 = [False, False, False]
print(A1, " -> ", est_valide(F, A1))
print(A2, " -> ", est_valide(F, A2))
# %%
# 2.ii
def aff_suivante(A):
    i = 0
    n = len(A)
    while i < n and A[i] == 1:
        A[i] = -1
        i += 1
    if i == n:
        return None
    A[i] = 1
    return A

A = [-1, -1, -1, -1]
print(A)
for i in range(2**4):
    A = aff_suivante(A)
    print(A)
# %%
# 2.iii
def sat_exhau(F, n):
    A = [-1 for i in range(n)]
    while not(est_valide(F, A)):
        A = aff_suivante(A)
        if A == None:
            return "insatisfiable"
    
    return A

c = 'cnf/simple_v3_c2.cnf'
F,n = parseur(c)
print(sat_exhau(F, n))
c = 'cnf/random-5-unsat.cnf'
F,n = parseur(c)
print(sat_exhau(F, n))
# %%
# 3)
# 3.i
def elimination(F, n, b):
    psi = []
    for C in F:
        Cp = []
        SAT = False
        for l in C:
            if abs(l) == n and l*b > 0:
                SAT = True
            elif abs(l) != n:
                Cp.append(l)
        if not(SAT):
            psi.append(Cp)
    return psi

c = 'cnf/simple_v3_c2.cnf'
F,n = parseur(c)
print(F)
print(elimination(F, n, -1))
# %%
# 3.ii
def sat_backtrack(F, n):
    if F == []:
        A = [1 for i in range(n)]
        return A
    if [] in F:
        return "insatisfiable"
    for b in [-1, 1]:
        psi = elimination(F, n, b)
        A = sat_backtrack(psi, n-1)
        if psi != F:
            return A + [b]
    return "insatisfiable"

c = 'cnf/simple_v3_c2.cnf'
F,n = parseur(c)
print(F)
sat_backtrack(F, n)
# %%

