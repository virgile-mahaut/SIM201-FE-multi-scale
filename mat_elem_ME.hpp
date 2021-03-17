#ifndef __MAT_ELEM_ME_H__
#define __MAT_ELEM_ME_H__
#include "mat_elem.hpp"
#include "EF_principal.hpp"

vecteur trace_multi_echelle (double x, double y, Point& S1, Point& S2, Point& S3);
list<vecteur> resolution_local(Maillage& M, Point& S1, Point& S2, Point& S3);
matrice_pleine k_elem_ME(Point& S1,Point& S2, Point& S3, const Maillage& M, pf a);
matrice_pleine m_elem_ME(Point& S1,Point& S2, Point& S3, const Maillage& M, pf a);


#endif