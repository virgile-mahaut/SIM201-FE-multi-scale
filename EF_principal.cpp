#include "EF_principal.hpp"


double A(double x,double y){
    return 1;
    // assez simple, on peut essayer quelque chose de plus subtil.
}

double F(double x, double y){
    return 2*M_PI*M_PI*sin(M_PI*x)*sin(M_PI*y);
    //return 600*exp(-pow((x-1)/0.8,2) - pow((y-1)/0.8,2));
}

double sol_exact_validation(double x, double y){ //fonction de validation du code, pour le calcul des erreurs
    return sin(3.14159*x)*sin(3.14159*y);
}


