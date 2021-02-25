#ifndef __MAT_ELEM_H__
#define __MAT_ELEM_H__

typedef double (*pf)(double, double);
matrice_profil_sym k_elem(Point S1,Point S2, Point S3, Maillage& M, pf a);
matrice_profil_sym m_elem(Point S1,Point S2,Point S3);

#endif