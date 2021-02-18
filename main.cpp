#include <iostream>
#include "vecteur.hpp"
#include "matrice_new.hpp"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <random>

int main()
{
	/*vecteur v1(5);
    cout<<"v1="<<v1<<endl;
    vecteur v2(5,4.);
    cout<<"v2="<<v2<<endl;
    vecteur v3=v2;
    cout<<"v3="<<v3<<endl;
    v3=3.;
	cout<<"v3="<<v3<<endl;
	cout<<"v2|v3 ="<<(v2|v3)<<endl;
    cout<<"v3="<<v3<<endl;

    for (int i=1;i<=v3.dim(); i++) v3(i)*=i;
    cout<<"v3="<<v3<<endl;
    cout<<"v3(3,5)="<<v3(3,5)<<endl;
	vecteur w=2*v1+v2/4-v3;
    cout<<"w = 2*v1+v2/4-v3 = "<<w<<endl;

    cout<<"(v2,v3)="<<(v2,v3)<<endl;

    cout<<"v2==v2 : "<<(v2==v2)<<endl;
    cout<<"v1!=v2 : "<<(v1!=v2)<<endl;

    matrice_pleine M(6,6,3);*/
    /*matrice_pleine N(6,6,1);
    matrice_pleine P = N*0.91;
    P = 8.1 * P;
    cout<<P;*/
    /*matrice_pleine R(6,6,0);
    matrice_pleine Z(N);
    cout<<"M(2,3)="<<M(2,3)<<endl;
    R = M - N;
    cout<<" M - N  =\n"<<R;
    cout<<" Z  =\n"<<Z;
    */

   /*
    matrice_pleine N(6,6,0);
    matrice_profil P(N);
    matrice_pleine s(6,6,1);
    matrice_profil S(s);
    int p = P.diml();
    int q = P.dimc();
    for(int i = 1; i<=p; i++){
        for(int j = 1; j<=q; j++){
            P(i,j,i*j);
    }
    }
    matrice_profil DIFFERENCE = P - S;
    cout<<"S = "<<S;
    cout<<"P = "<<P;
    cout<<" DIFFERENCE =\n"<<DIFFERENCE;
    //cout<<DIFFERENCE(0,0);
    //cout<<DIFFERENCE(1,0);
    cout<<DIFFERENCE(6,6)<<"\n";
    cout<<DIFFERENCE(3,4)<<"\n";
    DIFFERENCE(3,4,199);
    cout<<DIFFERENCE(3,4)<<"\n";

    

*/
    float temps;
    clock_t t1, t2;
 
    t1 = clock();
    matrice_profil A(5,5);
    matrice_profil B(A);
    B.Id();

    for(int s=1; s<B.diml()+1; s++){
        for(int p=1; p<B.dimc()+1; p++){
            cout<<B(s,p)<<" ";
        }
        cout<<"\n";
    }


B(3,1,8);

for(int s=1; s<B.diml()+1; s++){
        for(int p=1; p<B.dimc()+1; p++){
            cout<<B(s,p)<<" ";
        }
        cout<<"\n";
    }

for(int x=0; x<B.val_.size(); x++){
        cout<<"val_ "<<B.val_[x]<<" ";
    }
    cout<<"\n";
for(int c=0; c<B.profil.size(); c++){
        cout<<"profil "<<B.profil[c]<<" ";
    }
    cout<<"\n";

    for(int v=0; v<B.nbr_coef.size(); v++){
        cout<<"nbr coef "<<B.nbr_coef[v]<<" ";
    }

//B(4,2,8);
//B(4,3,8);
//B(4,4,8);
//B(4,5,8);

for(int s=1; s<B.diml()+1; s++){
        for(int p=1; p<B.dimc()+1; p++){
            cout<<B(s,p)<<" ";
        }
        cout<<"\n";
    }

for(int x=0; x<B.val_.size(); x++){
        cout<<"val_ "<<B.val_[x]<<" ";
    }
    cout<<"\n";
for(int c=0; c<B.profil.size(); c++){
        cout<<"profil "<<B.profil[c]<<" ";
    }
    cout<<"\n";

    for(int v=0; v<B.nbr_coef.size(); v++){
        cout<<"nbr coef "<<B.nbr_coef[v]<<" ";
    }


 


/*
B(1,2,6);

for(int i=0; i<B.val_.size(); i++){
        cout<<"val_ "<<B.val_[i]<<" ";
    }
    cout<<"\n";
for(int i=0; i<B.profil.size(); i++){
        cout<<"profil "<<B.profil[i]<<" ";
    }
    cout<<"\n";

    for(int i=0; i<B.nbr_coef.size(); i++){
        cout<<"nbr coef "<<B.nbr_coef[i]<<" ";
    }
    cout<<"\n"; 

for(int i=1; i<4; i++){
        for(int j=1; j<4; j++){
            cout<<B(i,j)<<" ";
        }
        cout<<"\n";}
    
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);
*/
    
}


/*for(int i=0; i<B.val_.size(); i++){
        cout<<"val_ "<<B.val_[i]<<" ";
    }
    cout<<"\n";
for(int i=0; i<B.profil.size(); i++){
        cout<<"profil "<<B.profil[i]<<" ";
    }
    cout<<"\n";

    for(int i=0; i<B.nbr_coef.size(); i++){
        cout<<"nbr coef "<<B.nbr_coef[i]<<" ";
    }
    cout<<"\n"; */
