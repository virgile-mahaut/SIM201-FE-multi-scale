#include "EF_principal.hpp"
#include <cmath>


double A(double x,double y){
    return 1;
    // assez simple, on peut essayer quelque chose de plus subtil.
}

double F(double x, double y){
    return 2*M_PI*M_PI*sin(M_PI*x)*sin(M_PI*y);
    //return 600*exp(-pow((x-1)/0.8,2) - pow((y-1)/0.8,2));
}

double trace_multi_echelle (double x, double y, Point S1, Point S2, Point S3){
    double x1 = S1.x;
    double y1 = S1.y;
    double x2 = S2.x;
    double y2 = S2.y;
    double x3 = S3.x;
    double y3 = S3.y;

    double val = ( (y2-y3)*(x-x3) - (x2-x3)*(y-y3) )/ ( (x2-x3)*(y3-y1)- (x3-x1)*(y2-y3));
    return val;
}


