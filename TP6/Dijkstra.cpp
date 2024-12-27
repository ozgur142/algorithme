#include <iostream>
#include <cmath>
#include "Dijkstra.h"

using namespace std;

coord* sommetsAleatoires(int n, int l, int h)
{
	coord* sommets = new coord[n];
	for (int i = 0; i < n; ++i)
	{
		sommets[i].x = 10 + rand() % (l-19);
		sommets[i].y = 10 + rand() % (h-19);
	}
  return sommets; // à modifier
}

float distance(coord* sommets, int i, int j)
{
	int dx = sommets[i].x - sommets[j].x;
	int dy = sommets[i].y -sommets[j].y;
  return sqrt(dx*dx + dy*dy); // à modifier
}

listeAdj* graphe(int n, coord* sommets, float dmax)
{
	listeAdj* G = new listeAdj[n]; //graphe à n sommets
	for (int i = 0; i < n; ++i)
		G[i] = NULL;

	for (int i = 0; i < n-1; ++i)
	{
		for (int j = i+1; j < n; ++j)
		{
			float d = distance(sommets, i, j);
			if (d <= dmax)
			{
				G[i] = new Voisin(j, d, G[i]);
				G[j] = new Voisin(i, d, G[j]);
			}
		}
	}

  return G; // à modifier
}

//int *p = G[u]
//p->sommet : numéro du "premier" voisin de u
//p->poids : poids de l'arête entre u et son "premier" voisin*
//p->suivant : pointeur vers le maillon suivant (le voisin suivant)

void dijkstra(int n, listeAdj* G, int s, float*& D, int*& P)
{
	File* F = new File(n); // File avec les sommets 0 à n-1, de priorités +INF chacun
	D = new float[n];
	P = new int[n];
	
	for (int i = 0; i < n; ++i)
		D[i] = INFINITY;
	for (int i = 0; i < n; ++i)
		P[i] = -1;
	


	F->changer_priorite(s, 0);
	D[s] = 0;

	while (!F->est_vide()){
		int u = F->extraire_min();
		Voisin* v = G[u];

		while (v != NULL){
			float vpoids = v->poids;
			int vsommet = v->sommet;

			if (D[u] + vpoids < D[vsommet])
			{
				D[vsommet] = D[u] + vpoids;
				P[vsommet] = u;
				F->changer_priorite(vsommet, D[vsommet]);
			}
			v = v->suivant;
		}
	}

  //return ; // à modifier
}

listeAdj chemin(int n, listeAdj* G, int* P, int s, int v)
{
	listeAdj C;
	C = new Voisin(v,0,NULL);

	while(v != s){
		v = P[v];
		C = new Voisin(v,0,C);
	}
	
  return C; // à modifier
}

listeAdj* arbre(int n, listeAdj* G, int* P, int s)
{
	listeAdj* T = new listeAdj[n];
	for (int i = 0; i < n; ++i)
		T[i] = NULL;

	int u = n;
	while(u != s){
		T[u] = new Voisin(P[u],0,G[u]);
		T[P[u]] = new Voisin(u,0,G[P[u]]);
		u--;
	}
	
  return T; // à modifier
}

  
void a_etoile(int n, listeAdj* G, coord* sommets, int s, int t, float*& D, int*& P)
{
	File* F = new File(n); // File avec les sommets 0 à n-1, de priorités +INF chacun
	D = new float[n];
	P = new int[n];
	
	for (int i = 0; i < n; ++i)
		D[i] = INFINITY;
	for (int i = 0; i < n; ++i)
		P[i] = -1;
  //return; // à modifier
}
