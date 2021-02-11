#include "maillage.hpp"
#include "EF_principal.hpp"
#include <iostream>
#include "vecteur.hpp"
#include "matrice.hpp"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <random>

int main()
{
   Maillage M;
   M.affiche();
   pf f = affine;
   vector<double> v =transforme(M,f);
   for (int i=0; i<M.sommets.size(); i++){
      cout<<v[i]<<" ";
   }
   cout<<endl;
   M.output();
   return 0;
}
