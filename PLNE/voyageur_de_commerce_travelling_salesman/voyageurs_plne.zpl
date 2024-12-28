# Ozgur DOGAN - 22202894

param path := "";

param fichier := path+"tsp5.txt";
param nomfichier := read fichier as "1s" use 1;

set V := { read fichier as "<1n>" skip 1 , <0>} ;  # numero de ville
param x[V] := read fichier as "<1n> 2n" skip 1, <0> 0 ; # coordonnées x
param y[V] := read fichier as "<1n> 3n" skip 1 , <0> 0 ;   # coordonnées y

set CENTER := {0, 0};

#set parcour := {1 to V by 1}

defnumb dist(a, b) := sqrt((x[a] - x[b])^2 + (y[a] - y[b])^2);

var p[V*V] binary;
minimize cost : sum<i, j> in V*V : dist(i, j) * p[i, j];



subto two_connected : forall <v> in V do
(sum <v, j> in V*V : p[v, j]) + (sum <i, v> in V*V : p[i, v]) == 2 ;


# daha sonra contarint sum < 692 i ekleyerek test et boylece toplami bundan buyuk olan yoollari aramayi direk durdurucak