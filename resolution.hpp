#ifndef __RESOLUTION_H__
#define __RESOLUTION_H__

#include "mat_elem_ME.hpp"


vecteur transforme_f(Maillage& M, pf f);
void assemblage(Maillage& M);
list<Maillage> sous_maillage(Maillage &M);
void assemblage_ME(Maillage& M);
#endif