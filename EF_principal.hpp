#ifndef __EF_H__
#define __EF_H__

typedef double (*pf)(double,double);
// pointeur d'une fonction double f(double, double)

vector<double> transforme(Maillage M, pf f);

double affine(double x,double y);

#endif