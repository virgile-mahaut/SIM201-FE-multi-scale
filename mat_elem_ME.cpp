#include "mat_elem_ME.hpp"

vecteur trace_multi_echelle (double x, double y, Point& S1, Point& S2, Point& S3){
    double x1 = S1.x;
    double y1 = S1.y;
    double x2 = S2.x;
    double y2 = S2.y;
    double x3 = S3.x;
    double y3 = S3.y;

    vecteur val(3);
    double delta = ((x2-x3)*(y3-y1)- (x3-x1)*(y2-y3));
    val(1) = ( (y2-y3)*(x-x3) - (x2-x3)*(y-y3) )/ delta;
    val(2) = ( (y3-y1)*(x-x1) - (x3-x1)*(y-y1) )/ delta;
    val(3) = ( (y1-y2)*(x-x2) - (x1-x2)*(y-y2) )/ delta;
    return val;
}

list<vecteur> resolution_local(const Maillage& M, Point& S1, Point& S2, Point& S3){
    matrice_profil_sym KKI(M.sommets.size(),M.sommets.size(),M.P_),
                       KKE(M.sommets.size(),M.sommets.size(),M.P_);
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
                if (M.sommets[I-1].reference==0){
                    if (M.sommets[i-1].reference==0){
                        KKI(I,J)+=Kel(i,j);
                    }
                        KKE(I,J)-=Kel(i,j);
                }
                else if (I==J){
                    KKI(I,I)=1;
                    KKE(I,I)=1;
                }
            }
        }
    }
	vecteur FF1 = vecteur(M.sommets.size());
    vecteur FF2 = vecteur(M.sommets.size());
    vecteur FF3 = vecteur(M.sommets.size());
    vecteur tmp(3);
    for (int i=0; i<M.sommets.size(); i++){
        tmp = trace_multi_echelle(M.sommets[i].x,M.sommets[i].y, S1, S2, S3);
        FF1(i+1) = tmp(1); FF2(i+1) = tmp(2); FF3(i+1) = tmp(3);
    }
    vecteur LL1 = KKE*FF1;
    vecteur LL2 = KKE*FF2;
    vecteur LL3 = KKE*FF3;

	vecteur UU1 = resol(KKI,LL1);
    vecteur UU2 = resol(KKI,LL2);
    vecteur UU3 = resol(KKI,LL3);
    cout<<FF1<<endl;
    cout<<FF2<<endl;
    cout<<FF3<<endl;
    list<vecteur> UU; UU.push_back(UU1); UU.push_back(UU2); UU.push_back(UU3);
    return UU;
}

matrice_pleine k_elem_ME(Point& S1,Point& S2, Point& S3, const Maillage& M, pf a){
    
    list<vecteur> UU = resolution_local(M, S1, S2, S3);
    list<vecteur>::iterator itv = UU.begin(); 
    cout<<"1"<<endl;
    vecteur UU1 = *(itv); itv++;
    vecteur UU2 = *(itv); itv++;
    vecteur UU3 = *(itv);
    matrice_pleine gradw(3,2);
    matrice_pleine Kel(3,3);
    int i,j;
    double x1, y1, x2, y2, x3, y3, z11, z12, z13, z21, z22, z23, z31, z32, z33;
    list<Triangle>::const_iterator itt = M.triangles.begin();
    for (; itt!= M.triangles.end(); itt++){
        x1 = M.sommets[(*itt)[0]-1].x;
        y1 = M.sommets[(*itt)[0]-1].y;
        z11 = UU1((*itt)[0]); z12 = UU2((*itt)[0]); z13 = UU3((*itt)[0]);
        x2 = M.sommets[(*itt)[1]-1].x;
        y2 = M.sommets[(*itt)[1]-1].y;
        z21 = UU1((*itt)[1]); z22 = UU2((*itt)[1]); z23 = UU3((*itt)[1]);
        x3 = M.sommets[(*itt)[2]-1].x;
        y3 = M.sommets[(*itt)[2]-1].y;
        z31 = UU1((*itt)[2]); z32 = UU2((*itt)[2]); z33 = UU3((*itt)[2]);
        
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
        gradw(1,1) = z21-z11;
        gradw(1,2) = z31-z11;
        gradw(2,1) = z22-z12;
        gradw(2,2) = z32-z12;
        gradw(3,1) = z23-z13;
        gradw(3,2) = z33-z13;

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
                Kel(i,j) += (vec1(1)*vec2(1)+vec1(2)*vec2(2)) * D * I;
            } 
        }
    }
    return Kel;
}

matrice_pleine m_elem_ME(Point& S1,Point& S2, Point& S3, const Maillage& M, pf a){
    
    list<vecteur> UU = resolution_local(M, S1, S2, S3);
    list<vecteur>::iterator itv = UU.begin(); 
    vecteur UU1 = *(itv); itv++;
    vecteur UU2 = *(itv); itv++;
    vecteur UU3 = *(itv);
    cout<<UU1;
    matrice_pleine coeffw(3,3);
    matrice_pleine Mel(3,3);

    int i,j;
    double x1, y1, x2, y2, x3, y3, z11, z12, z13, z21, z22, z23, z31, z32, z33;
    // Pour plus de lisibilité
    list<Triangle>::const_iterator itt = M.triangles.begin();
    for (; itt!= M.triangles.end(); itt++){
        x1 = M.sommets[(*itt)[0]-1].x;
        y1 = M.sommets[(*itt)[0]-1].y;
        z11 = UU1((*itt)[0]); z12 = UU2((*itt)[0]); z13 = UU3((*itt)[0]);
        x2 = M.sommets[(*itt)[1]-1].x;
        y2 = M.sommets[(*itt)[1]-1].y;
        z21 = UU1((*itt)[1]); z22 = UU2((*itt)[1]); z23 = UU3((*itt)[1]);
        x3 = M.sommets[(*itt)[2]-1].x;
        y3 = M.sommets[(*itt)[2]-1].y;
        z31 = UU1((*itt)[2]); z32 = UU2((*itt)[2]); z33 = UU3((*itt)[2]);
        
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
    
        // coefficients a x + b y + c des coordonnées barycentriques du triangle de référence
        coeffw(1,1) = z21-z11; coeffw(1,2) = z31-z11; coeffw(1,3) = z11;
        coeffw(2,1) = z22-z12; coeffw(2,2) = z32-z12; coeffw(2,3) = z12;
        coeffw(3,1) = z23-z13; coeffw(3,2) = z33-z13; coeffw(3,3) = z13;

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

        // Matrice élémentaire
        matrice_pleine Kel(3,3);
        for (int i=1; i<=3; i++){
            for (int j=1; j<=i; j++){
                Mel(i,j) +=(w0*a(FP0(1),FP0(2))*(coeffw(i,1)*FP0(1)+coeffw(i,2)*FP0(2)+coeffw(i,3))
                                               *(coeffw(j,1)*FP0(1)+coeffw(j,2)*FP0(2)+coeffw(j,3))
                          + w1*a(FP1(1),FP1(2))*(coeffw(i,1)*FP1(1)+coeffw(i,2)*FP1(2)+coeffw(i,3))
                                               *(coeffw(j,1)*FP1(1)+coeffw(j,2)*FP1(2)+coeffw(j,3))
                          + w2*a(FP2(1),FP2(2))*(coeffw(i,1)*FP2(1)+coeffw(i,2)*FP1(2)+coeffw(i,3))
                                               *(coeffw(j,1)*FP2(1)+coeffw(j,2)*FP2(2)+coeffw(j,3))
                          + w3*a(FP3(1),FP3(2))*(coeffw(i,1)*FP3(1)+coeffw(i,2)*FP2(2)+coeffw(i,3))
                                               *(coeffw(j,1)*FP3(1)+coeffw(j,2)*FP3(2)+coeffw(j,3))
                          + w4*a(FP4(1),FP4(2))*(coeffw(i,1)*FP4(1)+coeffw(i,2)*FP3(2)+coeffw(i,3))
                                               *(coeffw(j,1)*FP4(1)+coeffw(j,2)*FP4(2)+coeffw(j,3))
                          + w5*a(FP5(1),FP5(2))*(coeffw(i,1)*FP5(1)+coeffw(i,2)*FP5(2)+coeffw(i,3))
                                               *(coeffw(j,1)*FP5(1)+coeffw(j,2)*FP5(2)+coeffw(j,3))
                          + w6*a(FP6(1),FP6(2))*(coeffw(i,1)*FP6(1)+coeffw(i,2)*FP6(2)+coeffw(i,3))
                                               *(coeffw(j,1)*FP6(1)+coeffw(j,2)*FP6(2)+coeffw(j,3)))*D;
            } 
        }
    }
    return Mel;
}


