param C := 9;

set I := {0 to 23 by 1};
param taille[I] := <0> 6, <1> 6, <2> 5, <3> 5, <4> 5, <5> 4, <6> 4, <7> 4, <8> 4, 
                <9> 2, <10> 2, <11>2, <12>2, <13> 3, <14> 3, <15> 7, <16> 7, <17> 5, 
                <18> 5, <19> 8, <20> 8, <21> 4, <22> 4, <23> 5;

set J := I;  # autant de boites potentielles que d'objets

var x[I*J] binary; # xij = 1 si l’objet i est mis dans la boite j
var y[J] binary; # yj = 1 si et seulement si la boite j est utilisée.

minimize boites: sum<j> in J: y[j];


subto objet_dans1_boite : forall <i> in I: sum<j> in J: x[i,j] == 1;
subto boite_util : forall <j> in J: forall <i> in I : y[j] >= x[i,j];
subto capa :  forall <j> in J: sum<i> in I: x[i,j] * taille[i] <= C;
