#include <iostream>
#include <vector>
#include <list>
#include "math.h"
#include "matrice.hpp"
#include "vecteur.hpp"
#include "maillage.hpp"
using namespace std;

matrice_pleine k_elem(vecteur S1, vecteur S2, vecteur S3, Maillage M, "fonction a"){

    // Pour plus de lisibilité
    double x1 = S1(0);
    double y1 = S1(1);
    double x2 = S2(0);
    double y2 = S2(1);
    double x3 = S3(0);
    double y3 = S3(1);

    // On utilise une fonction Fl : Fl(P) = Bl(P) + Sl
    // pour passer du triangle de référence au triangle Tl
    matrice_pleine Bl(2,2);
    Bl(0,0) = x2-x1;
    Bl(0,1) = x3-x1;
    Bl(1,0) = y2-y1;
    Bl(1,1) = y3-y1;
    vecteur Sl(2);
    Sl(0) = x1; Sl(1) = y1;

    // Matrice des normales à l'arrête opposée
    // w1 = 1-x-y; w2 = x; w3 = y
    matrice_pleine gradw(3,2);
    gradw(0,0) = -1;
    gradw(0,1) = -1;
    gradw(1,0) = 1;
    gradw(1,1) = 0;
    gradw(2,0) = 0;
    gradw(2,1) = 1;

    // Sommets de quadrature
    double s0 = 1/3;
    double s1 = (6-sqrt(15))/21;
    double s2 = (6+sqrt(15))/21;
    double s3 = (9+2*sqrt(15))/21;
    double s4 = (9-2*sqrt(15))/21;
    
    // Points de quadrature
    vecteur P0; P0(0) = s0; P0(1) = s0;
    vecteur P1; P1(0) = s1; P1(1) = s1;
    vecteur P2; P2(0) = s1; P2(1) = s3;
    vecteur P3; P3(0) = s3; P3(1) = s1;
    vecteur P4; P4(0) = s2; P4(1) = s2;
    vecteur P5; P5(0) = s2; P5(1) = s4;
    vecteur P6; P6(0) = s4; P6(1) = s2;

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

    // Calcul de l'intégrale par quadrature (d'ordre 5)
    double I = w0*a(FP0)+w1*a(FP1)+w2*a(FP2)+w3*a(FP3)+w4*a(FP4)+w5*a(FP5)+w6*a(FP6);

    // Matrice élémentaire
    int n=3;
    matrice_pleine A(n,n);
    for (int i=0; i<n; i++){
        for (int j=0; i<n; i++) A[i,j] = inv(trans(Bl))[i,j]*gradw(i,:) * inv(trans(Bl))[i,j]*gradw(j,:) * D * I;
    } // Trouver une solution pour grad(i,:) -> définir vecteur<vecteur> ou utiliser matrice ou produit terme à terme

    return A;
}


vecteur vecteur_F("fonction f"){
    vecteur vecteur_F;
    matrice M(3,3);
    double D = abs((x2-x1)*(y3-y1) - (y2-y1)*(x3-x1));
    for (int i=0; i<n; i++){
        for (int j=0; i<n; i++) M[i,j] = D/24.;
        M[i,i] = D/12.;
    }
    // Il faut ensuite utiliser la matrice M globale pour avoir F : F_k = (Mf)_k
    return vecteur_F;
}