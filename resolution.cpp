#include "resolution.hpp"

vecteur transforme_f(Maillage& M, pf f){
    // calcule le vecteur (f(M_k))
    vecteur v(M.sommets.size());
    for (int i=0; i<M.sommets.size(); i++){
        v(i+1)=f(M.sommets[i].x,M.sommets[i].y);
    }
    return v;
}

void assemblage(Maillage& M){
	matrice_profil_sym MM(M.sommets.size(),M.sommets.size(),M.P_), 
                       KK(M.sommets.size(),M.sommets.size(),M.P_);
	pf f = F; pf a = A;
    list<Triangle>::const_iterator itt = M.triangles.begin();
    for (; itt!=M.triangles.end(); itt++){
        // calcul des matrices élémentaires
        matrice_pleine Kel = k_elem(M.sommets[(*itt)[0]-1],M.sommets[(*itt)[1]-1],M.sommets[(*itt)[2]-1],M,a);
		matrice_pleine Mel = m_elem(M.sommets[(*itt)[0]-1],M.sommets[(*itt)[1]-1],M.sommets[(*itt)[2]-1]);
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
	vecteur FF = transforme_f(M,f); vecteur LL = MM*FF;
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

list<Maillage> sous_maillage(Maillage &M){
    list<Maillage> SM;
    
    list<Triangle>::iterator it; // Iterateur sur une liste de type Triangle
    for (it=M.triangles.begin(); it!=M.triangles.end(); ++it){ // Boucle sur la liste M.triangles
        Maillage M2; M2.sommets.resize(6);

        int A = (*it)[0];    // Numéro du 1er sommet du triangle courant
        int B = (*it)[1];
        int C = (*it)[2];

        // Coordonnees des points A, B, C et ref du triangle courant
        double xA = M.sommets[A-1].x;
        double yA = M.sommets[A-1].y;
        int refA = 1;
        //int refA = M.sommets[A].reference;

        double xB = M.sommets[B-1].x;
        double yB = M.sommets[B-1].y;
        int refB = 1;
        //int refB = M.sommets[B].reference;

        double xC = M.sommets[C-1].x;
        double yC = M.sommets[C-1].y;
        int refC = 1;
        //int refC = M.sommets[C].reference;

        double x;
        double y;
        int ref;
        // Point AB (nouveau point entre A et B)
        x = (xA + xB)/2.; // x_AB = ( x_A + x_B )/2
        y = (yA + yB)/2.;
        ref = 1;
        //if (refA == 1 && refB == 1) ref = 1; // ref(AB) = 1 ssi ref(A) = ref(B) = 1
        Point AB(x,y,0,ref);

        // Point AC
        x = (xA + xC)/2.;
        y = (yA + yC)/2.;
        ref = 1;
        //if (refA == 1 && refC == 1) ref = 1;
        Point AC(x,y,0,ref);

        // Point BC
        x = (xB + xC)/2.;
        y = (yB + yC)/2.;
        ref = 1;
        //if (refB == 1 && refC == 1) ref = 1;
        Point BC(x,y,0,ref);

        // Ajout des points déjà existants
        M2.sommets[0] = M.sommets[A]; M2.sommets[0].reference=1;
        M2.sommets[1] = M.sommets[B]; M2.sommets[1].reference=1;
        M2.sommets[2] = M.sommets[C]; M2.sommets[2].reference=1;
        // Ajout des nouveaux points
        M2.sommets[3] = AB;
        M2.sommets[4] = AC;
        M2.sommets[5] = BC;
        // Nouveaux triangles
        Triangle A2(1,4,5);   // Triangle (A,AB,AC)
        Triangle B2(2,4,6);
        Triangle C2(3,5,6);
        Triangle D2(4,5,6); // Triangle (AB,AC,BC)

        // Ajout des nouveaux triangles 
        M2.triangles.push_back(A2);
        M2.triangles.push_back(B2);
        M2.triangles.push_back(C2);
        M2.triangles.push_back(D2);
		M2.profil();
        SM.push_back(M2);
        for (int i=0; i<6; i++) SM.back().sommets[i].reference = 1;
    }
    return SM;
}

void assemblage_ME(Maillage& M){
	
	list<Maillage> SM = sous_maillage(M);
	matrice_profil_sym MM(M.sommets.size(),M.sommets.size(),M.P_), 
                       KK(M.sommets.size(),M.sommets.size(),M.P_);
	pf f = F; pf a = A;
    list<Triangle>::const_iterator itt = M.triangles.begin();
	list<Maillage>::const_iterator itm = SM.begin();

    for (; itt!=M.triangles.end(); itt++, itm++){

        (*itm).affiche();
        // calcul des matrices élémentaires
        matrice_pleine Kel = k_elem_ME(M.sommets[(*itt)[0]-1],M.sommets[(*itt)[1]-1],M.sommets[(*itt)[2]-1],*itm,a);
        matrice_pleine Mel = m_elem_ME(M.sommets[(*itt)[0]-1],M.sommets[(*itt)[1]-1],M.sommets[(*itt)[2]-1],*itm,a);
		cout<<Kel;
        cout<<Mel;
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
	vecteur FF = transforme_f(M,f); vecteur LL = MM*FF;
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