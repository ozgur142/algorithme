# Une instance de sac a dos simple à 12 objets numérotés de 1 à 12

set I := { 1..12 } ; # un ensemble d'indices

param C := 20 ;  # la capacité du sac
param p[I] := <1> 11, <2> 7, <3> 5, <4> 5, <5> 4, <6> 3, <7> 3
  , <8> 2, <9> 2, <10> 2, <11> 2, <12> 1;
param v[I] := <1> 20, <2> 10, <3> 25, <4> 11, <5> 5, <6> 50, <7> 15
  , <8> 12, <9> 6 , <10> 5, <11> 4, <12> 30;

var x[I] binary;     # un "tableau" de 12 variables booléennes

maximize valeur : sum <i> in I: v[i] * x[i];
subto poids : sum <i> in I: p[i] * x[i] <= C;
