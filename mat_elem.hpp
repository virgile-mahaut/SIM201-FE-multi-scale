#ifndef __MAT_ELEM_H__
#define __MAT_ELEM_H__
#include "maillage.hpp" 

typedef double (*pf)(double, double);
matrice_pleine k_elem(const Point& S1, const Point& S2, const Point& S3, const Maillage& M, pf a);
matrice_pleine m_elem(const Point& S1, const Point& S2, const Point& S3);

#endif