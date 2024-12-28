# Ozgur DOGAN - 22202894

param path := "voyageur_de_commerce/";

param fichier := path+"tsp5.txt";
param nomfichier := read fichier as "1s" use 1;

set V := { read fichier as "<1n>" skip 1 , <0>} ;  # numero de ville en ajoutant la ville 0
param x[V] := read fichier as "<1n> 2n" skip 1, <0> 0 ; # coordonnées x
param y[V] := read fichier as "<1n> 3n" skip 1 , <0> 0 ;   # coordonnées y
set P[] := powerset(V);
set K := indexset(P) ;
set E := {<i, j> in V*V with i < j};



# pour afficher les coordonnées des villes
#do forall <i> in V do print i, " ", x[i], ",", y[i];   
#do print E;

# calcul de la distance entre deux villes
defnumb dist(a, b) := sqrt((x[a] - x[b])^2 + (y[a] - y[b])^2);

var p[E] binary;
minimize cost : sum<i, j> in E : dist(i, j) * p[i, j];


subto deux_connect : forall <v> in V do
(sum <v, j> in E : p[v, j]) + (sum <i, v> in E : p[i, v]) == 2 ;




subto pas_subtour : forall <k> in K with card (P[k]) > 2 and card(P[k]) < card(V) - 2 do
        sum <i, j > in E with <i> in P[k] and <j> in P[k] : p[i, j] <= card (P[k]) - 1;



#constarint sum < meilleur(metaheuristique) ?
#param MAX_DISTANCE := 200;
#subto total_distance_limit: sum <i, j> in E : dist(i, j) * p[i, j] <= MAX_DISTANCE;
