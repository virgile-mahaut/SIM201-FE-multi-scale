// Fonction qui prend en entrée un maillage et renvoie un sous-maillage en coupant chaque triangle en 4.
//   /_\
// /_\ /_\

#include <iostream>
#include "maillage.hpp"
using namespace std;

Maillage maillage_degre(Maillage &M, int n){
    for (int i=0; i<n; i++) M = sous_maillage(M);
    return M;
}

Maillage sous_maillage(Maillage &M){

    Maillage M2;

    // Peut-etre un operateur par copie ici ?
    M2.sommets = M.sommets;
    M2.triangles = M.triangles;
    M2.P_ = M.P_;

    int k = M.sommets.size();
    
    list<Triangle>::iterator it; // Iterateur sur une liste de type Triangle
    for (it=M.triangles.begin(); it!=M.triangles.end(); ++it){ // Boucle sur la liste M.triangles
        cout << *it << endl; // *it est de type Triangle
        int A = (*it)(0);    // Numéro du 1er sommet du triangle courant
        int B = (*it)(0);
        int C = (*it)(0);

        // Coordonnees des points A, B, C et ref du triangle courant
        double xA = M.sommets[A].x;
        double yA = M.sommets[A].y;
        int refA = M.sommets[A].reference;

        double xB = M.sommets[B].x;
        double yB = M.sommets[B].y;
        int refB = M.sommets[B].reference;

        double xC = M.sommets[C].x;
        double yC = M.sommets[C].y;
        int refC = M.sommets[C].reference;

        double x;
        double y;
        int ref;

        // Point AB (nouveau point entre A et B)
        x = (xA + xB)/2.; // x_AB = ( x_A + x_B )/2
        y = (yA + yB)/2.;
        if (refA == 1 && refB == 1) ref = 1; // ref(AB) = 1 ssi ref(A) = ref(B) = 1
        ref = 0;
        Point AB(x,y,0,ref);

        // Point AC
        x = (xA + xC)/2.;
        y = (yA + yC)/2.;
        if (refA == 1 && refC == 1) ref = 1;
        ref = 0;
        Point AC(x,y,0,ref);

        // Point BC
        x = (xB + xC)/2.;
        y = (yB + yC)/2.;
        if (refB == 1 && refC == 1) ref = 1;
        ref = 0;
        Point BC(x,y,0,ref);

        // Numeros des nouveaux points
        M2.sommets[k] = AB;
        M2.sommets[k+1] = AC;
        M2.sommets[k+2] = BC;

        // Nouveaux triangles
        Triangle A2(A,k,k+1);   // Triangle (A,AB,AC)
        Triangle B2(B,k,k+2);
        Triangle C2(C,k+1,k+2);
        Triangle D2(k,k+1,k+2); // Triangle (AB,AC,BC)

        // Ajout des nouveaux triangles 
        M2.triangles.push_back(A2);
        M2.triangles.push_back(B2);
        M2.triangles.push_back(C2);
        M2.triangles.push_back(D2);

        k+=3;
    }
    return M2;
}

