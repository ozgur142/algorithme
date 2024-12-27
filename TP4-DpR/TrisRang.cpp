#include <cstdlib>
#include "TrisRang.h"

using namespace std;

void fusion(int n1, int n2, int* T1, int* T2, int* T)
{
	int i1 = 0;
	int i2 = 0;
	for (int is = 0; is < n1+n2; ++is)
	{
		if (i2 >= n2 || (i1 < n1 && T1[i1] <= T2[i2]))
		{
			T[is] = T1[i1];
			i1++;
		}
		else  // i1 >= n1 ou T1[i1] > T2[i2]
		{
			T[is] = T2[i2];
			i2++;
		}
	}
  // A compléter
}

void trifusion(int n, int* T)
{
	int n1 = n/2;
	int n2 = n - n1;

	int *T1 = new int[n1];
	int *T2 = new int[n2];

	if (n > 1)
	{

		int a = n1;
		for (int i = 0; i < n1; ++i)
			T1[i] = T[i];
		
		for (int i = 0; i < n2; ++i)
		{
			T2[i] = T[a];
			a++;
		}
		

		trifusion(n1, T1);
		trifusion(n2, T2);
		fusion(n1, n2, T1, T2, T);
	}

	delete[] T1;
	delete[] T2;

  // A compléter
}

int pivot(int n, int* T, bool b) 
{
  return (b)?T[rand()%n]:T[0];
}

int rang(int k, int n, int* T, bool b) //pivot aleatoire est miux!!!
{
	if(n == 1)
		return T[0];
	int p = pivot(n, T, b);
	int nInf = 0;
	int nEq = 0;
	for (int i = 0; i < n; ++i)
	{
		if (T[i] < p)
			nInf++;
		else if(T[i] == p)
			nEq++;
	}
	if (k <= nInf){
		int *Tinf = new int[nInf];
		int x = 0;
		for (int i = 0; i < n; ++i)
		{
			if (T[i] < p){
				Tinf[x] = T[i];
				x++; 
			}
		}
		return rang(k, nInf, Tinf, b);
	}
	else if (nInf < k && k <= nInf+nEq)
	{
		return p;
	}
	else
	{
		int *Tsup = new int[n - nInf - nEq];
		int x = 0;
		for (int i = 0; i < n; ++i)
		{
			if (T[i] > p)		
			{
				Tsup[x] = T[i];
				x++;
			}
		}
		return rang(k-nInf-nEq, n - nInf - nEq, Tsup, b);
	}

  //return 0; // A modifier !
}


//********************************************************************


void trirapide(int n, int* T, bool b)
{
	if (n > 1)
	{
		int p = pivot(n, T, b);
		int nInf = 0;
		int nEq = 0;

		for (int i = 0; i < n; ++i)
		{
			if (T[i] < p)
				nInf++;
			else if(T[i] == p)
				nEq++;
		}

		int nSup = n-nInf-nEq;

//**********************************
		int *Tinf = new int[nInf];//initialisation de tableau inferieure
		int x = 0;
		for (int i = 0; i < n; ++i)
		{
			if (T[i] < p){
				Tinf[x] = T[i];
				x++; 
			}
		}

		int *Teq = new int[nEq]; //initialisation de tableau avec la valeur p
		for (int i = 0; i < nEq; ++i)
		{
			Teq[i] = p;
		}

		int *Tsup = new int[nSup];
		x = 0;
		for (int i = 0; i < n; ++i)
		{
			if (T[i] > p)		
			{
				Tsup[x] = T[i];
				x++;
			}
		}


		trirapide(nInf, Tinf, b);
		trirapide(nSup, Tsup, b);


		fusion(nInf, nEq, Tinf, Teq, T);
		fusion(nInf+nEq, nSup, T, Tsup, T);

		delete[] Tinf;
		delete[] Tsup;
		delete[] Teq;

	}

  // A compléter
}

