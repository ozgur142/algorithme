#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <string>
#include "ABR.h"

using namespace std;

//------------------------------------------------------
// Inserer un noeud z dans l'arbre A
//------------------------------------------------------

noeud* ABR::inserer(int k)
{
  if (!racine) { 
    racine = new noeud(k);
    return racine;
  }

  noeud* x = racine;
  noeud* p = NULL;

  while (x)
  {
    p = x;
    if (k < x->val)
      x = x->filsG;
    else
      x = x->filsD;
  }
  noeud* z = new noeud(k);
  z->pere = p;
  if (k < p->val)
    p->filsG = z;
  else
    p->filsD = z;
  return z;
}

//------------------------------------------------------
// Parcours infixe
//------------------------------------------------------

void ABR::parcoursInfixe(noeud* x)
{
  if (!x) return;
  if (x->filsG) parcoursInfixe(x->filsG);
  cout << x->val << " ";
  if (x->filsD) parcoursInfixe(x->filsD);
}

//------------------------------------------------------
// Noeud de valeur minimale dans l'arbre
//------------------------------------------------------

noeud* ABR::minimum(noeud* x)
{
  if (!x) return x;
  while (x->filsG) x = x->filsG;
  return x;
}

//------------------------------------------------------
// Recherche d'un noeud de valeur k
//------------------------------------------------------

noeud* ABR::rechercher(int k)
{
  noeud* z = racine;
  while (z and z->val != k) {
    if (z->val > k) z = z->filsG;
    else z = z->filsD;
  }
  return z;
}

//------------------------------------------------------
// Recherche du successeur du noeud x
//------------------------------------------------------

noeud* ABR::successeur(noeud *x)
{
  if (x->filsD) return minimum(x->filsD);
  noeud* p = x->pere;
  while (p and x == p->filsD)
  {
    x = x->pere;
    p = p->pere;
  }
  return p;
}

//------------------------------------------------------
// Suppression d'un noeud
//------------------------------------------------------

void ABR::supprimer(noeud* z)
{
  if (!z->filsG) {
    remplacer(z, z->filsD);
  }
  else if (!z->filsD) {
    remplacer(z, z->filsG);
  }
  else {
    noeud* y = successeur(z);
    remplacer(y, y->filsD);
    remplacer(z, y);
    y->filsD = z->filsD;
    y->filsG = z->filsG;
    if (y->filsD) y->filsD->pere = y;
    if (y->filsG) y->filsG->pere = y;
  }
  
  delete z;
}


//------------------------------------------------------
// Rotations
//------------------------------------------------------

void ABR::rotationGauche(noeud* z)
{
  noeud* fd = z->filsD;
  if (!fd) return;
  noeud* fdg = fd->filsG;
  noeud* p = z->pere;

  if (p && z == p->filsD) 
    p->filsD = fd;
  else if (p) 
    p->filsG = fd;
  else
    racine = fd;

  z->filsD = fdg;
  if (fdg) fdg->pere = z;

  z->pere = fd;
  fd->pere = p;
  
  fd->filsG = z;


}

void ABR::rotationDroite(noeud* z)
{
  noeud* fg = z->filsG;
  if (!fg) return;
  noeud* fgd = fg->filsD;
  noeud* p = z->pere;

  if (p && z == p->filsG) 
    p->filsG = fg;
  else if (p) 
    p->filsD = fg;
  else
    racine = fg;
  z->filsG = fgd;
  if (fgd) fgd->pere = z;

  z->pere = fg;
  fg->pere = p;
  
  fg->filsD = z;
}
