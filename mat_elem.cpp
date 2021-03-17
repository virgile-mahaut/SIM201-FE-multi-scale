#include <iostream>
#include <cmath>
#include "mat_elem.hpp"
using namespace std;


matrice_pleine k_elem(const Point& S1,const Point& S2, const Point& S3, const Maillage& M, pf a){

    // Pour plus de lisibilité
    double x1 = S1.x;
    double y1 = S1.y;
    double x2 = S2.x;
    double y2 = S2.y;
    double x3 = S3.x;
    double y3 = S3.y;

    // On utilise une fonction Fl : Fl(P) = Bl(P) + Sl
    // pour passer du triangle de référence au triangle Tl
    matrice_pleine Bl(2,2);
    Bl(1,1) = x2-x1;
    Bl(1,2) = x3-x1;
    Bl(2,1) = y2-y1;
    Bl(2,2) = y3-y1;
    matrice_pleine IBLT(2,2);
    IBLT(1,1)=Bl(2,2); IBLT(2,2)=Bl(1,1); IBLT(1,2)=-Bl(2,1); IBLT(2,1)=-Bl(1,2);
    IBLT = IBLT*(1/(Bl(1,1)*Bl(2,2)-Bl(1,2)*Bl(2,1)));
    vecteur Sl(2);
    Sl(1) = x1; Sl(2) = y1;

    // Matrice des normales à l'arrête opposée
    // w1 = 1-x-y; w2 = x; w3 = y
    matrice_pleine gradw(3,2);
    gradw(1,1) = -1;
    gradw(1,2) = -1;
    gradw(2,1) = 1;
    gradw(2,2) = 0;
    gradw(3,1) = 0;
    gradw(3,2) = 1;

    // Sommets de quadrature
    double s0 = 1/3.;
    double s1 = (6-sqrt(15))/21.;
    double s2 = (6+sqrt(15))/21.;
    double s3 = (9+2*sqrt(15))/21.;
    double s4 = (9-2*sqrt(15))/21.;

    // Points de quadrature
    vecteur P0(2); P0(1) = s0; P0(2) = s0;
    vecteur P1(2); P1(1) = s1; P1(2) = s1;
    vecteur P2(2); P2(1) = s1; P2(2) = s3;
    vecteur P3(2); P3(1) = s3; P3(2) = s1;
    vecteur P4(2); P4(1) = s2; P4(2) = s2;
    vecteur P5(2); P5(1) = s2; P5(2) = s4;
    vecteur P6(2); P6(1) = s4; P6(2) = s2;

    // Valeurs de quadrature
    double n0 = 9./80;
    double n1 = (155-sqrt(15))/2400.;
    double n2 = (155+sqrt(15))/2400.;

    // Poids de quadrature
    double w0 = n0;
    double w1 = n1;
    double w2 = n1;
    double w3 = n1;
    double w4 = n2;
    double w5 = n2;
    double w6 = n2;

    // Passage du triangle de référence au triangle Tl
    vecteur FP0(2); FP0 = Bl*P0+Sl;
    vecteur FP1(2); FP1 = Bl*P1+Sl;
    vecteur FP2(2); FP2 = Bl*P2+Sl;
    vecteur FP3(2); FP3 = Bl*P3+Sl;
    vecteur FP4(2); FP4 = Bl*P4+Sl;
    vecteur FP5(2); FP5 = Bl*P5+Sl;
    vecteur FP6(2); FP6 = Bl*P6+Sl;

    // D est au signe pres deux fois l'aire du triangle
    double D = abs((x2-x1)*(y3-y1) - (y2-y1)*(x3-x1));
    // Remarque : ajouter ici une erreur si D est nul ?
    if (D<=1e-12) cout<<"Error: triangle area is null.\n";

    // Calcul de l'intégrale par quadrature (d'ordre 5)
    double I = w0*a(FP0(1),FP0(2))+w1*a(FP1(1),FP1(2))+w2*a(FP2(1),FP2(2))+w3*a(FP3(1),FP3(2))
    +w4*a(FP4(1),FP4(2))+w5*a(FP5(1),FP5(2))+w6*a(FP6(1),FP6(2));
    // Matrice élémentaire
    matrice_pleine Kel(3,3);
    vecteur gradi(2); vecteur gradj(2); vecteur vec1(2); vecteur vec2(2);
    for (int i=1; i<=3; i++){
        gradi(1)=gradw(i,1); gradi(2)=gradw(i,2);
        for (int j=1; j<=i; j++){
            gradj(1)=gradw(j,1); gradj(2)=gradw(j,2);
            vec1 = IBLT*gradi; vec2=IBLT*gradj;
            Kel(i,j) = (vec1(1)*vec2(1)+vec1(2)*vec2(2)) * D * I;
        } 
    }
    return Kel;
}


matrice_pleine m_elem(const Point& S1,const Point& S2, const Point& S3){
    // Pour plus de lisibilité
    double x1 = S1.x;
    double y1 = S1.y;
    double x2 = S2.x;
    double y2 = S2.y;
    double x3 = S3.x;
    double y3 = S3.y;
    
    matrice_pleine Mel(3,3);
    double D = abs((x2-x1)*(y3-y1) - (y2-y1)*(x3-x1));
    if (D<=1e-12) cout<<"Error: triangle area is null.\n";
    for (int i=1; i<=3; i++){
        for (int j=1; j<i; j++) Mel(i,j) = D/24.;
        Mel(i,i) = D/12.;
    }
    return Mel;
}