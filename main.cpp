#include <iostream>
#include "vecteur.hpp"
#include "matrice.hpp"
#include "maillage.hpp"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <random>

int main()
{
    /*vector<int> profil; profil.resize(4); profil[0]=1; profil[1]=1; profil[2]=1; profil[3]=1;
    matrice_profil_sym A(4,4,profil);
    cout<<A.nbr_coef[0]<<" "<<A.nbr_coef[1]<<" "<<A.nbr_coef[2]<<endl;
    A(1,1)=1; A(2,2)=5; A(3,3)=14; A(4,4)=15;
    A(2,1)=1; A(3,1)=1; A(3,2)=5; A(4,1)=1; A(4,2)=5; A(4,3)=14;                                      
    vecteur y(4); y(1)=1; y(2)=2; y(3)=3; y(4)=4;
    cout<<"matrice A :\n"<<A<<endl;
    cout<<A.val_[0]<<endl;
    cout<<"vecteur y :\n"<<y<<endl;
    vecteur x = resol(A,y);
    cout<<"vecteur x :\n"<<x<<endl;
    cout<<"Ax = "<<A*x<<endl;*/
    Maillage M("geomCarre.msh");
    M.output();
}



/*{
    /*

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
}*/


