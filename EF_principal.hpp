#ifndef __EF_H__
#define __EF_H__
#include "vecteur.hpp"
#include "maillage.hpp"

double A(double x, double y);
double F(double x, double y);
double trace_multi_echelle (double x, double y, Point S1, Point S2, Point S3);
double sol_exact_validation(double x, double y);

#endif
