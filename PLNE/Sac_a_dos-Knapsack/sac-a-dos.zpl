# Résolution d'une instance de sac a dos lue dans un fichier
# Suppose que les commentaires commencent par #, que la capacité est sur la première ligne non commentée, et que les autres lignes décrivent les objets : 1 par ligne, d'abord une id puis le poids puis la valeur

param fichier := "sac-a-dos-100.txt" ;

set I := { read fichier as "<1s>" comment "#" skip 1 } ;

param C :=  read fichier as "1n" comment "#" use 1 ;
do print "capacite : " , capacite ;
do print "nb objets : " , card(I) ;
param p[I] := read fichier as "<1s> 2n" comment "#" skip 1 ;
param v[I] := read fichier as "<1s> 3n" comment "#" skip 1 ;
#do forall <i> in I: print "objet " , i, " : poids = ", p[i] , " valeur = " , v[i] ;

var x[I] binary;

maximize valeur : sum <i> in I: v[i] * x[i];
subto poids : sum <i> in I: p[i] * x[i] <= C;
