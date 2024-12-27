#include <iostream>
#include "Tas.h"

using namespace std;


// ====================
//  TAS ET TRI PAR TAS
// ====================

void afficher(int n, int* T)
{
  cout<<"[";
  for (int i = 0; i < n-1; ++i)
  {
    cout<<T[i]<<",";
  }
  cout<<T[n-1]<<"]\n";
  // À compléter
} 

bool estTasMax(int n, int* T)
{
  for (int i = 1; i < n; ++i)
  {
    if (T[(i-1)/2] < T[i])
      return false;
  }
  return true; // À modifier...
}

bool estTasMin(int n, int* T)
{
  for (int i = 1; i < n; ++i)
  {
    if (T[(i-1)/2] > T[i])
      return false;
  }
  return true; // À modifier...
}

void tableauManuel(int n, int* T)
{
  for (int i = 0; i < n; ++i)
  {
    cin>>T[i];
  }
  // À compléter
}

void tableauAleatoire(int n, int* T, int m, int M)
{
  for (int i = 0; i < n; ++i)
  {
    T[i] = rand() % (M - m +1) + m;
  }
  // À compléter
}

void entasser(int n, int* T, int i)
{
  while ((i*2)+1 < n){
    int m = i;
    int g = i*2 +1;
    int d = i*2 + 2;
    if (T[g] > T[m])
      m = g;
    if ((d < n) && (T[d] > T[m]))
      m = d;
    if (m != i){
      int tmp = T[i];
      T[i] = T[m];
      T[m] = tmp;
      i = m;
    }
    else
      i = n;
  }
  // À compléter
}

void tas(int n, int* T)
{
  while (!estTasMax(n,T)){
    for (int i = 1; i < n; ++i)
    {
      if (T[(i-1)/2] < T[i])
        entasser(n, T, (i-1)/2);
    }
  }
  // À compléter
}

//******************

void echanger(int& a, int& b){
  int tmp = a;
  a = b;
  b = tmp;
}

void remonter(int *T, int i){
  while (i>0 && T[(i-1)/2] < T[i]){
    echanger(T[i], T[(i-1)/2]);
    i = (i-1)/2;
  }
}

int supprimer(int n, int *T, int i){
  int x = T[i];
  T[i] = T[n-1];
  n--;
  remonter(T,i);
  entasser(n, T, i);
  return x;
}

//0(nlogn)
int* trier(int n, int* T)
{
  int* Ttrie = new int[n];
  for (int i = (n/2)-1; i >= 0 ; --i)
  {
    entasser(n, T, i);
  }
  int taille = n;
  for (int i = n-1; i >= 0; --i){
    Ttrie[i] = supprimer(taille,T,0);
    taille--;
  }
  
  return Ttrie; // À modifier...
}



void trierSurPlace(int n, int* T)
{
  for (int i = n/2-1; i >= 0 ; --i)
  {
    entasser(n,T, i);
  }
  for(int i = n-1; i > 0; --i){
    echanger(T[0], T[i]);
    entasser(i,T,0);
  }
  // À compléter
}

