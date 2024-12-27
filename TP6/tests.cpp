#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
#include "Structures.h"
#include "Affichage.h"
#include "Dijkstra.h"

using namespace std;

void TEMPS(clock_t t1, clock_t t2) 
{
  double t = (double)(t2-t1)/CLOCKS_PER_SEC;
  if (t > 1) cout << t << " s" << endl;
  else if (t > 0.001) cout << t*1000 << " ms" << endl;
  else cout << t*1000000 << " µs" << endl;
}

int dim(int n)
{
  int k = 1;
  while (k*k < n) k++;
  return 70*k;
}

void coins(int n, coord* S, int& i, int& j)
{
  i = 0; j = 0;
  int di = S[i].x*S[i].x + S[i].x*S[i].y;
  int dj = di;
  for (int t = 1; t < n; t++)
  {
    int d = S[t].x*S[t].x + S[t].y*S[t].y;
    if (d < di) { i = t; di = d; }
    else if (d > dj) { j = t; dj = d; }
  }
}

void centre(int n, coord* S, int l, int h, int& i, int& j)
{
  coord c = {l/2, h/2};
  i = 0; 
  int di = (S[i].x-c.x)*(S[i].x-c.x) + (S[i].y-c.y)*(S[i].y-c.y);
  for (int t=1; t < n; t++)
  {
    int dt = (S[t].x-c.x)*(S[t].x-c.x) + (S[t].y-c.y)*(S[t].y-c.y);
    if (dt < di) { i = t; di = dt; }
  }
  j = rand() % n;
}

template<typename E>
void afficher(int n, E* T)
{
  int m = (n > 15)?10:n;
  cout << "[";
  for(int i=0;i<m-1;i++) cout << T[i] << ",";
  if (m) cout << T[m-1];
  if (m < n) cout << ",... (+ " << n-m << " éléments)";
  cout << "]" << endl;
}

int main()
{
  srand(time(NULL));
  int q, n, l, h, s, t, nobs;
  listeAdj* G = NULL;
  listeAdj C;
  listeAdj* A;
  coord* O;
  float dmax;
  coord* S;
  float* D;
  int* P;
  string c;
  clock_t t1, t2;
  do
  {
    cout << "Entrer le numéro de question à tester (0 pour quitter) : ";
    cin >> q;

    if (q == 1)
    {
        cout << "Entrer le nombre de sommets : ";
        cin >> n;
        l = dim(n); h = dim(n);
        S = sommetsAleatoires(n, l, h);
        affichageSommets(n, S, "graphe", l, h);
        cout << "Sommets dessinés dans graphe.svg" << endl;
    }
    else if (q == 2)
    {
        int x1, y1, x2, y2;
        cout << "Entrer l'abscisse et l'ordonnée du premier sommet : ";
        cin >> x1 >> y1;
        cout << "Entrer l'abscisse et l'ordonnée du second sommet : ";
        cin >> x2 >> y2;
        coord deux[] = {{x1,y1},{x2,y2}};
        cout << "Les sommets de coordonnées (" << x1 << "," << y1 << ") et (" 
             << x2 << "," << y2 << ") sont à distance " << distance(deux, 0, 1) << endl;
    }
    else if (q == 3)
    {
        cout << "Entrer le nombre de sommets : ";
        cin >> n;
        cout << "Entrer la distance maximale (recommandé : entre 100 et 200) : ";
        cin >> dmax;
        l = dim(n); h = dim(n);
        S = sommetsAleatoires(n, l, h);
        G = graphe(n, S, dmax);
        affichageSommets(n, S, "sommets", l, h);
        affichageGraphe(n, S, G, "graphe", l, h);
        cout << "Graphe dessiné dans graphe.svg" << endl;
    }
    else if (q > 3 and q < 8)
    {
        cout << "Choix du graphe :" << endl;
        if (G)
        cout << "    0. Garder le graphe courant" << endl;
        cout << "    1. Graphe n°1 (5 sommets)" << endl
             << "    2. Graphe n°2 (10 sommets)" << endl
             << "    3. Graphe aléatoire avec obstacles" << endl
             << "    n. Graphe aléatoire à n sommets" << endl
             << "Choix (entier) : ";
        cin >> c;
        if (c == "n")
        {
          cout << "Entrer le nombre de sommets : ";
          cin >> n;
        }
        if (c != "0")
        {
          s = -1; 
          t = -1; 
          nobs = 0;
          G = NULL;
          C = NULL;
          A = NULL;
          O = NULL;
        }
        if (c == "1") 
        {
          lecture("Graphe5.txt", G, S, n, l, h);
          s = 0; t = 4; nobs = 0;
        }
        else if (c == "2")
        {
          lecture("Graphe10.txt", G, S, n, l, h);
          s = 0; t = 9; nobs = 0;
        }
        else if (c == "3")
        {
          cout << "Nombre de sommets : ";
          cin >> n;
          l = dim(n);
          h = dim(n);
          dmax = 200.;
          nobs = 20;
          int lobs = l / 3;
          grapheObstacles(n, l, h, nobs, lobs, dmax, S, G, O);
          coins(n, S, s, t);
        }
        else if (c != "0")
        {
          n = stoi(c);
          l = dim(n); h = dim(n); dmax = 200.; 
          S = sommetsAleatoires(n, l, h);
          G = graphe(n, S, dmax);

          cout << "Choix de sommet de départ :" << endl
               << "  1. Sommet aléatoire" << endl
               << "  2. Sommet au centre" << endl
               << "  3. Sommet dans un coin" << endl
               << "Choix (entier) : ";
          cin >> s;
          if (s == 1) { s = rand() % n; t = rand() % n; }
          else if (s == 2) centre(n, S, l, h, s, t);
          else if (s == 3) coins(n, S, s, t);

        }
        
        if (c != "0")
        {
          affichageSommets(n, S, "sommets", l, h);
          affichageGraphe(n, S, G, "graphe", l, h, NULL, s, t, NULL, nobs, O);
          cout << "Fichier graphe.svg mis à jour" << endl;
        }
        if (c != "0" or q == 4)
        {
          t1 = clock();
          dijkstra(n, G, s, D, P);
          t2 = clock();
        }

        
      switch(q)
      {
        case 4:
          cout << "Tableau des distances : "; 
          afficher<float>(n, D);
          cout << "Tableau des prédecesseurs : "; 
          afficher<int>(n, P);
          cout << "Plus court chemin entre les sommets " << s << " et " << t << " de longueur " << D[t] << endl;
          cout << "Temps de calcul : "; TEMPS(t1,t2);
          break; 

        case 5:
          C = chemin(n, G, P, s, t);
          affichageGraphe(n, S, G, "graphe", l, h, A, s, t, C, nobs, O);
          cout << "Plus court chemin entre les sommets " << s << " et " << t << " de longueur " << D[t] << " : "; 
          if (C)
          {
            listeAdj C2 = C;
            while (C2->suivant)
            {
              cout << C2->sommet << "→";
              C2 = C2->suivant;
            }
            cout << C2->sommet << endl;
          }
          else cout << "vide" << endl;
          cout << "Fichier graphe.svg mis à jour" << endl;
          break;
        
        case 6:
          A = arbre(n, G, P, s);
          affichageGraphe(n, S, G, "graphe", l, h, A, s, t, C, nobs, O);
          cout << "Fichier graphe.svg mis à jour" << endl;
          break;

        case 7:
          t1 = clock();
          a_etoile(n, G, S, s, t, D, P);
          t2 = clock();
          cout << "Plus court chemin entre les sommets " << s << " et " << t << " de longueur " << D[t] << endl;
          cout << "Temps de calcul : "; TEMPS(t1,t2);

          C = chemin(n, G, P, s, t);
          A = arbre(n, G, P, s);
          affichageGraphe(n, S, G, "graphe", l, h, A, s, t, C, nobs, O);
          cout << "Fichier graphe.svg mis à jour" << endl;
      }
    }

    cout << endl;
    if (q < 4) G = NULL;

  } while (q>0);
  return 0;
}
