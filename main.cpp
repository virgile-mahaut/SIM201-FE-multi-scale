#include <iostream>
#include "vecteur.hpp"
#include "matrice.hpp"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <random>

int main()
{
    float temps;
    clock_t t1, t2;
 
    t1 = clock();

    vecteur v(5);
    v(1) = 1;
    for (int i=2; i<= v.dim(); i++){
        v(i) = i-1;
    }

matrice_profil_sym A(5,5,v);

for (int i=1; i<v.dim()+1; i++){
    for (int j=A.profil[i-1]; j<=i; j++){
        if (i == j){
            A(i,j,5);
        }
        else{
            A(i,j,-2);
        }
    
    }
}

cout<<A;
//A.info_mat();


vecteur w(5);
for (int i=1; i<w.dim()+1; i++){
w(i)=i*i;}

cout<<w<<"\n";

vecteur soluce(5);
soluce = resol(A,w);
 
cout<<soluce;
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);  
}


