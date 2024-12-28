# Une épidémie de maladie infectieuse a été observée dans un certain nombre $ n $ de sites. Un ensemble de $m$ équipes de médecins doivent aller enquêter pour identifier la maladie, ce qui leur prend un certain temps $t_{ij}$ qui dépend du site $j$ et de l'équipe $i$. Chaque équipe peut enquêter au maximum sur 2 sites, et doit alors se déplacer du site $j_1$ au site $j_2$, ce qui prend un temps $d_{j_1j_2}$. 


# On veut minimiser le coût total en supposant que le coût des missions est proportionnel à la durée totale de travail (= temps de réalisation des missions + temps de déplacement entre deux sites s'il y a lieu)

set I := { 1..3 } ;
set J ................. ;

param t[I*J] ........... ;

param d[J*J] := |  1 ,  2 ,  3 ,  4 |
            | 1 |  0 ,  6 ,  6 ,  8 |
            | 2 |  6 ,  0 ,  7 ,  8 |
            | 3 |  6 ,  7 ,  0 ,  5 |
            | 4 |  8 ,  8 ,  5 ,  0 | ;

var x[I*J] binary ;
var y......... ;

minimize cout :
  sum <i,j,k> in I*J*J with j<k : d[j,k] * y[i,j,k] + ................... ;

subto site : forall <j> in J : sum <i> in I : x[i,j] >= 1 ;
subto eq   : ............................ ;

subto dep1 : forall <i,j,k> in I*J*J : ..................... ;
subto dep2 : ............................................... ;
subto dep3 : ............................................... ;
