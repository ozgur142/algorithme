# Ozgur DOGAN - 22202894

param path := "";

# nom du fichier à lire
param fichier := path+"u120_00.bpa";

param nomfichier := read fichier as "1s" use 1;
param C := read fichier as "1n" use 1 skip 1;
param N := read fichier as "2n" use 1 skip 1; 

do print nomfichier, " : ", N, " objets ; capacite = ", C ;

set I := {1 to N by 1};

#lecture fichier => astuce pas d'index
# lecture des tailles = pas facile, car le fichier n'a pas de colonne d'index

set tmp[<i> in I] := {read fichier as "<1n>" skip 1+i use 1};

# creer un tableau d'ensemble:
# chaque ensemble contient le premier (<ln>) élément de la ligne i+2 puisqu'on saute i+1 lignes;
# c'est donc le volume / poids du ième objet (puisque les deux premières lignes contiennent le nom du fichier et la capacité)

param taille[<i> in I] := ord(tmp[i], 1, 1);

# créer un tableau, dont le ième élément est le 1er composant du 1 élément de l'ensemble tmp[i] :
#dans le langage zimpl, un ensemble contient des tuples, et tel qu'on a construit tmp[i] cet ensemble contient
#un seul tuple de taille 1. qui estjustement le poids/volume du ième objet..

# I : objet;    J: boite

set J := I;  # autant de boites potentielles que d'objets

var x[I*J] binary; # x_{ij} = 1 si l’objet i est mis dans la boite j
var y[J] binary; # y_j = 1 si et seulement si la boite j est utilisée.

minimize boites: sum<j> in J: y[j]; 

#chaque objet doit être dans exactement une boite
subto objet_dans1_boite : forall <i> in I: sum<j> in J: x[i,j] == 1;

#une boite est utilisée (yj = 1 > 0) si et seulement si elle contient au moins un objet  
subto boite_util : forall <j> in J: forall <i> in I : y[j] >= x[i,j];

# dans chaque boite, la somme des tailles des objets ne doit pas dépasser la capacité.
subto capa :  forall <j> in J: sum<i> in I: x[i,j] * taille[i] <= C;

# ****        - V1  sans symmétries -    ******  

# nomfichier     |     solution opt   |    durée(s)
#  u20_00	               9	              0.04
#  u40_00	               17               20.50
#  u60_00	               27                -
#  u120_00	              -                -
#  inst60_non-unif_9	    14               0.76



# ****        - V2  avec symmétries -    ******  

# gestion symétries
# mettre les objet o1,o2,o3 dans boite B1 et les objets o4, o5 dans B2 est le même chose que 
# o4,o5 dans B1 et o1,o2,o3 dans B2

# on utilise le boite ssi le boite précedent est utilisé
subto boite_util_en_ordre: forall <j> in {2 to N by 1}: y[j] - y[j-1] <= 0; 

# u[i][j] : Une variable binaire qui vaut 1 si l'élément j (avec un indice supérieur ou égal à i) est placé dans le boite contenant l'élément d'indice le plus bas i. Elle vaut 0 sinon.
var u[I*J] binary;
subto sym: forall <i> in J : sum<j> in J: taille[i] * u[i,j] - C*u[i,i] <= 0; 


# nomfichier     |     solution opt   |    durée(s)
#  u20_00	               9	                  0.07
#  u40_00	               17                   3.39
#  u60_00	               27                    -
#  u120_00	             49                    -
#  inst60_non-unif_9     14                   0.68



# index
# https://jmsallan.netlify.app/blog/breaking-symmetry-in-linear-programming-formulation/#:~:text=An%20integer%20linear%20program%20(ILP,algorithms%20(Margot%2C%202010).
