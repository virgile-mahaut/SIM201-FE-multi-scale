#include <iostream>
#include "maillage.hpp"
using namespace std;

Maillage resolution_local(Maillage M, Point S1, Point S2, Point S3){

matrice_profil_sym MM(M.sommets.size(),M.sommets.size(),M.P_), 
                       KK(M.sommets.size(),M.sommets.size(),M.P_);
	pf f = F; pf a = A; pf t_tilde = trace_multi_echelle;
    list<Triangle>::const_iterator itt = M.triangles.begin();
    for (; itt!=M.triangles.end(); itt++){
        // calcul des matrices élémentaires
        matrice_profil_sym Kel = k_elem(M.sommets[(*itt)[0]-1],M.sommets[(*itt)[1]-1],M.sommets[(*itt)[2]-1],M,a);
		matrice_profil_sym Mel = m_elem(M.sommets[(*itt)[0]-1],M.sommets[(*itt)[1]-1],M.sommets[(*itt)[2]-1]);
        int i,j,I,J;
        // assemblage des matrices globales
        for (i=1; i<=3; i++){
            I=(*itt)[i-1];
            for (j=1; j<=i; j++){
                J = (*itt)[j-1];
                MM(I,J)+=Mel(i,j);
                KK(I,J)+=Kel(i,j);
            }
        }
    }
	vecteur FF = transforme_f(M,t_tilde); vecteur LL = - a * KK*FF;
	// élimination au bord du domaine
	for (int I=1; I<=M.sommets.size(); I++){
		if (M.sommets[I-1].reference == 1){
			for (int J=I+1; J<=M.sommets.size(); J++){
				if (I >= M.P_[J-1]) KK(J,I)=0;
			}
			KK(I,I)=1; LL(I)=0;
		}
	}
	vecteur UU = resol(KK,LL);
	for (int i=1; i<=UU.dim();i++){
		M.sommets[i-1].u = UU(i);
	}

     
}