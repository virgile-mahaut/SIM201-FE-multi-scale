#include "maillage.hpp"
#include "EF_principal.hpp"

// exemple de fonction f, d'autres peuvent être ajoutées
double affine(double x,double y){
    return x + y;
}

vector<double> transforme(Maillage M, pf f){
    // calcule le vecteur (f(M_k))
    vector<double> v;
    v.resize(M.sommets.size());
    for (int i=0; i<M.sommets.size(); i++){
        v[i]=f(M.sommets[i].x,M.sommets[i].y);
    }
    return v;
}


