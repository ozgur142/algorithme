#include <iostream>
#include "Tas.h"

using namespace std;


// ====================
//  TAS ET TRI PAR TAS
// ====================

void afficher(int n, int* T)
{
  cout << "[";
  for(int i=0;i<n-1;i++) {
    cout << T[i] << ",";}
  if (n>0) cout << T[n-1];
  cout << "]" << endl;
} 

bool estTasMax(int n, int* T)
{
  for (int i = 0; 2*i+1 < n; i++)
  {
    if (T[2*i+1] > T[i]) return false;
    if (2*i+2 < n and T[2*i+2] > T[i]) return false;
  }
  return true;
}

bool estTasMin(int n, int* T)
{
  for (int i = 0; 2*i+1 < n; i++)
  {
    if (T[2*i+1] < T[i]) return false;
    if (2*i+2 < n and T[2*i+2] < T[i]) return false;
  }
  return true;
}

void tableauManuel(int n, int* T)
{
  for(int i=0; i < n; i++) {
    cout << "Entrer une valeur pour la case " << i << " : ";
    cin >> T[i];
    for (int j=0; j < n; j++) cout << T[j] << ", "; cout << endl;
  }
}

void tableauAleatoire(int n, int* T, int m, int M)
{
    for(int i=0;i<n;i++) {
	T[i] = m + (rand() % (M+1-m));
    }
}

void entasser(int n, int* T, int i)
{
  int m = i;
  int g = 2*i + 1;
  int d = 2*i + 2;
  
  if (g < n and T[g] > T[m]) m = g;
  if (d < n and T[d] > T[m]) m = d;

  if (m != i) {
    int tmp = T[i];
    T[i] = T[m];
    T[m] = tmp;
    return entasser(n, T, m);
  }
}

void tas(int n, int* T)
{
  for(int i=n/2-1; i>=0; i--) {
    entasser(n,T,i);
  }
}

int* trier(int n, int* T)
{
  tas(n,T);
  int* S = new int[n];
  for(int i=n-1; i>=0; i--) {
    S[i]=T[0];
    int tmp=T[0];
    T[0]=T[i];
    T[i]=tmp;
    entasser(i,T,0);
  }
  return S;
}

void trierSurPlace(int n, int* T)
{
  tas(n,T);
  for(int i=n-1;i>=0;i--) 
  {
    int tmp=T[0];
    T[0]=T[i];
    T[i]=tmp;
    entasser(i,T,0);
  }
}

