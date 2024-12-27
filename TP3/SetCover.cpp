#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "SetCover.h"

using namespace std;

coord* maisonsAleatoires(int n, int l, int h)
{
  coord* maisons = new coord[n];
  int rectangle[2][2] = {10, l-10, 10, h-10}; //{0,0}{0,1}{1,0}{1,1}

  for (int i = 0; i < n; ++i)
  {
    maisons[i].x = rand() % (rectangle[0][1] - rectangle[0][0] + 1) + rectangle[0][0];
    maisons[i].y = rand() % (rectangle[1][1] - rectangle[1][0] + 1) + rectangle[1][0];
  }
  // À compléter
  return maisons;
}

bool couvre(int i, int j, coord* maisons, int dcouv)
{
  int dist2 = (maisons[i].x - maisons[j].x) * (maisons[i].x - maisons[j].x) + (maisons[i].y - maisons[j].y) * (maisons[i].y - maisons[j].y);
  return dist2 < (dcouv* dcouv); // À modifier !
}

bool** graphe(int n, coord* maisons, int dcouv)
{
  bool** G = new bool*[n];
  for (int i=0; i < n; i++) G[i] = new bool[n];
  for (int i = 0; i < n; ++i)
  {
    for (int j = 1+i; j < n; ++j)
    {
      G[i][j] = G[j][i] = couvre(i,j,maisons,dcouv);
    }
  }
  /*for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      cout<<G[i][j]<<" ";
    }
    cout<<endl;
  }*/
  // À compléter

  return G;
}

int prochaineMaison(int n, bool** G, bool* couvertes)//en çok evi kaplayan indice i buluyo
{
  int compteur[n] = {0};
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      if (G[i][j])
      {
        compteur[i]++;
      }
    }
  }

  int max = -1;
  int k = 0;
  for (int i = 0; i < n; ++i)
  {
    if (max < compteur[i] && !couvertes[i])
    {
      max = compteur[i];
      k = i;
    }
  }
  
  couvertes[k] = true;
  for (int j = 0; j < n; ++j)
  {
    if (G[k][j])
    {
      couvertes[j] = true;
    }
  }

  return k; // À modifier !
}

int placementGlouton(int n, bool** G, bool* emetteurs)
{
  for (int i = 0; i < n; ++i)
  {
    emetteurs[i] = 0;
  }
  int nbrEmetteurs = 0;
  bool couvertes[n] = {0};
  bool toutCouverte = false;
  
  while (!toutCouverte){
    int k = prochaineMaison(n, G, couvertes);
    emetteurs[k] = true;
    nbrEmetteurs++;

    int a = 0;
    for (int i = 0; i < n; ++i)
    {
      a += couvertes[i];
    }
    
    toutCouverte = (n == a);
  }

  return nbrEmetteurs; // À modifier !
}

//*********************************************

bool toutCouverte(int n, bool** G, bool* emetteurs){
  bool couvertes[n] = {0};
  int a = 0;

  for (int i = 0; i < n; ++i)
  {
    if (emetteurs[i])
    {
      couvertes[i] = true;
      for (int j = 0; j < n; ++j)
      {
        if (G[i][j])
        {
          couvertes[j] = true;
        }
      }
    }
  }
  for (int i = 0; i < n; ++i)
  {
    if (couvertes[i])
    {
      a++;
    }
  }
  return a==n;
}

int pow(int a, int b){
  int x = 1;
  for (int i = 0; i < b; ++i)
  {
    x *= a;
  }
  return x;
}

int placementOptimal(int n, bool** G, bool* emetteurs)
{
  

  int nbrEmetteursOpt = n;
  int nbrEmetteurs;
  int possiblite = pow(2, n); //pour trouver le nbr de sous ensemble possible

  bool** sousEnsemble = new bool*[n];
  for (int i=0; i < n; i++) sousEnsemble[i] = new bool[possiblite]; 


  for (int k = 0; k < possiblite; ++k) //creation de table de sousensemble en bianire
  {
    int x = k;
    for (int i = 0; i < n; ++i)
    {
      sousEnsemble[i][k] = x%2;
      x /= 2;
    }
  }

  int possibliteCouvrant[possiblite] = {0}; //pour memoriser les possibilite et le nombre de emmetteurs nessaires pour couvrir tout les maisons
//si le nbr de emmetteurs sont assez on ecrit le nombre d'emetteurs sinon on ecrit n;

  for (int i = 0; i < possiblite; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      emetteurs[j] = 0;
    }
    nbrEmetteurs = 0;
    for (int j = 0; j < n; ++j)
    {
      if (sousEnsemble[j][i])
      {
        emetteurs[j] = true;
        nbrEmetteurs++;
      }
    }
    if (toutCouverte(n, G, emetteurs)) //si le nombre des emetteurs sont assez 
    {
      possibliteCouvrant[i] = nbrEmetteurs;
    }
    else {
      possibliteCouvrant[i] = n; //sinon on ecrit le nbr de max emmetteurs possible
    }
  }

  int indice;
  for (int i = 0; i < possiblite; ++i)
  {
    if (possibliteCouvrant[i] < nbrEmetteursOpt)
    {
      nbrEmetteursOpt = possibliteCouvrant[i];
      indice = i;
    }
  }

  for (int i = 0; i < n; ++i)
  {
    emetteurs[i] = sousEnsemble[i][indice];
  }





  return nbrEmetteursOpt; // À modifier !
}
