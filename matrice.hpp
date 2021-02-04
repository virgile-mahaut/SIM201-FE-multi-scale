#ifndef matrice_h
#define matrice_h

#include <iostream>
#include <vector>
using namespace std;


void stop_mat(const char * msg); //message d'arrêt

///////////////////////////////////////////////CLASSE MATRICE///////////////////////////////////////////////

class matrice : public vector<double>
{
protected :
    int dim_l, dim_c;   //dimension de la matrice
    vector<double> val_;

public :
    int diml() const{return dim_l;}
    int dimc() const{return dim_c;}
};

///////////////////////////////////////////////CLASSE MATRICE PLEINE///////////////////////////////////////////////

class matrice_pleine : public matrice
{
public :
    matrice_pleine(int dl, int dc, double x=0);
    matrice_pleine(const matrice_pleine& M);

//SURCHARGE D'OPERATEUR
    friend ostream& operator<<(ostream &out, const matrice_pleine& M);
    double& operator() (int i, int j);
    

};

matrice_pleine operator + (matrice_pleine&A, matrice_pleine& B);
matrice_pleine operator - (matrice_pleine&A, matrice_pleine& B);



///////////////////////////////////////////////CLASSE MATRICE PROFIL///////////////////////////////////////////////

#endif