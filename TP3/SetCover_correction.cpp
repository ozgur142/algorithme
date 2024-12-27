#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "SetCover.h"

using namespace std;

coord* maisonsAleatoires(int n, int l, int h)
{
  coord* maisons = new coord[n];
  for(int i=0;i<n;i++)
  {
    // rand() % N renvoie un entier dans {0, ..., N-1}
    // => 10 + rand() % (l-19) renvoie un entier dans {10,...,l-19-1+10} = {10,...,l-10}
    maisons[i].x = 10 + rand() % (l-19);
    maisons[i].y = 10 + rand() % (h-19);
  }
  return maisons;
}

bool couvre(int i, int j, coord* maisons, int dcouv)
{
  int dx = maisons[i].x - maisons[j].x;
  int dy = maisons[i].y - maisons[j].y;
  return dx*dx + dy*dy <= dcouv*dcouv;
}

bool** graphe(int n, coord* maisons, int dcouv)
{
  bool** G = new bool*[n];
  for (int i=0; i < n; i++) G[i] = new bool[n];
  
  for (int i=0; i < n; i++)
  {
    G[i][i] = false;
    for (int j=i+1; j < n; j++)
    {
      if (couvre(i, j, maisons, dcouv))
      {
        G[i][j] = true;
        G[j][i] = true;
      }
      else
      {
        G[i][j] = false;
        G[j][i] = false;
      }
    }
  }

  return G;
}

int prochaineMaison(int n, bool** G, bool* couvertes)
{
  int max = 0;
  int iMax = 0;
  for(int i=0; i<n; i++)
  {
    if (not couvertes[i])
    {
      int nbCouvertes = 1;
      for(int j=0; j<n; j++)
        if((not couvertes[j]) and G[i][j])
          nbCouvertes++;
      if(nbCouvertes > max)
      {
        max = nbCouvertes;
        iMax = i;
      }
    }
  }
  return iMax;
}

int placementGlouton(int n, bool** G, bool* emetteurs)
{
  bool* couvertes = new bool[n];
  for (int i=0; i < n; i++) couvertes[i] = false;
  for (int i=0; i < n; i++) emetteurs[i] = false;
  int nbCouvertes = 0;
  int nbEmetteurs = 0;

  while(nbCouvertes < n)
  {
    int nvleMaison = prochaineMaison(n, G, couvertes);
    emetteurs[nvleMaison] = true;
    couvertes[nvleMaison] = true;
    nbEmetteurs++;
    nbCouvertes++;
    for(int j=0;j<n;j++)
      if((not couvertes[j]) and G[nvleMaison][j])
      {
        couvertes[j] = true;
        nbCouvertes++;
      }
  }
  delete[] couvertes;
  return nbEmetteurs;
}

// VERSION STANDARD (PAS RAPIDE)
// (compilation normale, avec le Makefile)
#ifndef RAPIDE

// Fonction pour passer d'un tableau de booléen au "suivant"
// - Tableau vu comme un entier en binaire, avec le chiffre des unités en case 0
// - Ajout de 1 à cet entier : on passe de xxx011..1 à xxx100..0 où x = 0 ou 1 
// - Renvoie true tant qu'on a pas bouclé, et false sinon (quand l'entier est 11..1)
bool suivant(int n, bool* tab)
{
  int i = 0;
  while (i < n and tab[i]) tab[i++] = false;
  if (i == n) return false;
  tab[i] = true;
  return true;
}

// Fonction pour tester si l'ensemble d'emetteurs couvre toute les maisons
bool couvreTout(int n, bool** G, bool* emetteurs)
{
  int ncouvertes = 0;
  for (int i=0; i < n; i++)
  {
    bool couverte = emetteurs[i];
    int j = 0;
    for (int j=0; (not couverte) and j < n; j++)
      if (emetteurs[j] and G[i][j])
        couverte = true;
    if (not couverte) return false;
  }
  return true;
}

// Fonction de calcul d'un placement optimal
// - Parcours de tous les tableaux possibles
//   + tableau initial entièrement à false (entier 0..0)
//   + incrément jusqu'à boucler (suivant renvoie false)
// - À chaque tableau, on vérifie s'il couvre toutes les maisons et on compte son nombre de maisons
// - On conserve la solution la plus petite qui couvre tout
int placementOptimal(int n, bool** G, bool* emetteurs)
{
  bool *tentative = new bool[n];
  for (int i=0; i < n; i++) tentative[i] = false;
  int min = n+1;
  while (suivant(n, tentative))
  {
    int c = 0;
    for (int i=0; i < n; i++) if (tentative[i]) c++;
    if (c < min and couvreTout(n, G, tentative))
    {
      min = c;
      for (int i=0; i < n; i++) emetteurs[i] = tentative[i];
    }
  }
  delete[] tentative;
  return min;
}

// VERSION UN PEU PLUS RAPIDE
// pour la compiler : 
//    g++ -DRAPIDE -Wpedantic tests.cpp SetCover.cpp Affichage.cpp -o tests
//
// Ingrédients :
// 1. Représentation de G par listes d'adjacence plutôt que matrice d'adjacence
// 2. Représentation des solutions par des entiers plutôt que des listes de booléens
// 3. Parcours des solutions possibles par nombre de maisons (celles à 1 maison, celles à 2 maisons, etc.)
// 4. On calcule une solution approchée (avec l'algo glouton). 
//    Si on trouve k maisons, on commence par tester les solutions à k-1 maisons ;
//    s'il n'y en a pas, le glouton a renvoyé l'optimal ;
//    sinon, on teste les solutions à k-2 maisons ; etc.
// 5. Le passage d'une solution à t maisons à une autre solution à t maisons est faite avec un code de Gray :
//    passer d'une solution à une autre nécessite de bouger un seul émetteur d'une maison à une autre.
//    Savoir si toutes les maisons sont toujours couvertes va vite : pas besoin de retester toutes les maisons !
//    De plus, on garde pour chaque maison le nombre d'émetteurs qui la couvrent : elle est couverte si ce
//    nombre est strictement positif.

#else // RAPIDE

// Les "listes d'adjacence" sont représentées par des tableaux de tableaux. 
// Comme les sommets n'ont pas tous le même nombre de voisins, on stocke ce nombre
// dans la dernière ligne (L[n]).
int** listesAdj(int n, bool** G)
{
  int** L = new int*[n+1];
  L[n] = new int[n];
  for (int i=0; i < n; i++)
  {
    int d = 0;
    for (int j=0; j < n; j++)
      if (G[i][j]) d++;
    L[n][i] = d;
    L[i] = new int[d];
    int k = 0;
    for (int j=0; j < n; j++)
      if (G[i][j])
        L[i][k++] = j;
  }
  return L;
}

// Fonction qui calcule la liste de toutes les solutions possibles à k maisons parmi n maisons.
// Renvoie un tableau de ces solutions (représentées par des entiers), et sa taille est dans bin.
// Algo récursif :
// - R1 ← toutes les solutions à k maisons parmi n-1 maisons ;
// - R2 ← toutes les solutions à k-1 maisons parmi n maisons ;
// - Les solutions à k maisons parmi n maisons sont celles de R1 (pas d'émetteurs sur la n-ème maison)
//   plus celles de R2 auxquelles on ajoute un émetteur sur la n-ème maison.
// - En concaténant R1 (dans le bon sens) et R2 modifié à l'envers, on assure qu'il n'y a qu'un émetteur qui
//   bouge entre deux solutions consécutives (exercice : le démontrer !)
int* r(int n, int k, int& bin)
{
  // Cas de base 1 : 0 maisons parmi n (1 solution)
  if (k == 0) {
    bin = 1;
    int* res = new int[1];
    res[0] = 0;
    return res;
  }
  // Case de base 2 : n maisons parmi n (1 solution)
  if (n == k) {
    bin = 1;
    int* res = new int[1];
    res[0] = (1<<k)-1;
    return res;
  }

  // Appels récursifs
  int* r1 = r(n-1, k, bin);
  int b1 = bin;
  int* r2 = r(n-1, k-1, bin);
  int b2 = bin;
  bin = b1+b2;
  int* res = new int[b1+b2];

  // Concaténation de R1 et R2 modifié à l'envers
  int i = 0;
  for (; i < b1; i++) res[i] = r1[i];
  for (; i < b1+b2; i++) res[i] = r2[b1+b2-i-1] + (1<<(n-1));

  delete[] r1;
  delete[] r2;

  return res;

}

// Algo du placement optimal optimisé
int placementOptimal(int n, bool** G, bool* emetteurs)
{
  // Calcul de la solution gloutonne, qui sert de borne supérieure
  int borneSup = placementGlouton(n, G, emetteurs);

  bool *tentative = new bool[n];
  int *couverture = new int[n];
  int ** L = listesAdj(n, G); 
  for (int i=0; i < n; i++) tentative[i] = false;

  int k = borneSup-1;
  bool ok = true;

  // Recherche de solutions de plus en plus petites
  while (ok) 
  {
    ok = false;
    int bnk;
    int* rnk = r(n,k,bnk); // Solutions à k maisons parmi n

    for (int i=0; i < n; i++) tentative[i] = (rnk[0] & (1<<i)); // première tentative
    
    // Pour chaque maison, on compte le nombre d'émetteurs qui la couvrent
    for (int i=0; i < n; i++) couverture[i] = 0;
    for (int i=0; i < n; i++) 
    {
      if (tentative[i]) 
      {
        couverture[i]++;
        for (int j=0; j < L[n][i]; j++) couverture[L[i][j]]++;
      }
    }
    
    // (*) On teste si toutes les maisons sont couvertes
    // Si c'est le cas, on a une solution à k maisons → on passe à k-1 (break)
    bool couvert = true;
    for (int i=0; couvert and i < n; i++) if (not couverture[i]) couvert = false;

    if (couvert)
    {
      for (int i=0; i < n; i++)
        emetteurs[i] = tentative[i];
      ok = true;
      k--;
      break;
    }

    // Sinon, on parcourt la suite des solutions à k maisons
    for (int j=1; j < bnk; j++)
    {
      int rnkj = rnk[j];
      int diff = rnkj^(rnk[j-1]); // Position des emetteurs changés
      for(int i=0; i < n; i++) tentative[i] = (rnkj & (1<<i));
      // Mise à jour des couvertures
      for(int i=0; i < n; i++)
        if (diff & (1<<i))
        {
          if (tentative[i])
          {
            couverture[i]++;
            for(int v=0; v < L[n][i]; v++) couverture[L[i][v]]++;
          }
          else
          {
            couverture[i]--;
            for(int v=0; v < L[n][i]; v++) couverture[L[i][v]]--;
          }
        } 

      // Teste si la solution couvre toutes les maisons : cf (*)
      couvert = true;
      for (int i=0; couvert and i < n; i++) if (not couverture[i]) couvert = false;
      if (couvert)
      {
        for (int i=0; i < n; i++)
          emetteurs[i] = tentative[i];
        ok = true;
        k--;
        break;
      }

    } 
      
  }

  delete[] tentative;
  for (int i=0; i <= n; i++) delete[] L[i];
  delete[] L;
  delete[] couverture;
  return k+1;
}

#endif // RAPIDE

// VERSION ENCORE PLUS RAPIDE :
// À vous de jouer ;-) Il est possible d'optimiser encore la solution "RAPIDE".
