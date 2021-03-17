#ifndef matrice_h
#define matrice_h

#include <iostream>
#include "vecteur.hpp"
using namespace std;


void stop_mat(const char * msg); //message d'arrêt

///////////////////////////////////////////////CLASSE MATRICE///////////////////////////////////////////////

class matrice : public vector<float>
{
public :
    int dim_l, dim_c;   //dimension de la matrice
    vector<float> val_;

public :
    int diml() const{return dim_l;}
    int dimc() const{return dim_c;}
};

///////////////////////////////////////////////CLASSE MATRICE PLEINE///////////////////////////////////////////////

class matrice_pleine : public matrice
{
public :
    matrice_pleine(int dl, int dc, float x=0);
    matrice_pleine(const matrice_pleine& M);

//SURCHARGE D'OPERATEUR
    friend ostream& operator<<(ostream &out, const matrice_pleine& M);
    float& operator() (int i, int j); //accède au terme (i,j) attention l'indexation commence à 1
    float operator() (int i, int j) const; //accède au terme (i,j) attention l'indexation commence à 1

};

matrice_pleine transpose(const matrice_pleine&A);
matrice_pleine operator + (const matrice_pleine&A, const matrice_pleine& B);
matrice_pleine operator - (const matrice_pleine&A, const matrice_pleine& B);
matrice_pleine operator * (const matrice_pleine&A, const float& x);
matrice_pleine operator * (const float& x, const matrice_pleine&A);
vecteur operator * (const matrice_pleine& A, const vecteur& v);


///////////////////////////////////////////////CLASSE MATRICE PROFIL SYMETRIQUE///////////////////////////////////////////////
class matrice_profil_sym : public matrice {

//Vu que les matrices sont symétriques, on ne regarde que les coef triangulaires inférieurs, les autres sont retrouvés par symétrie

public:
    int nbr_val;
    vector<int> profil; //contient les indices de lignes à partir de premier non nuls, l'indexation commence à 1, vaut i si la ligne ne contient que des zéros
    //vu qu'on ne stock que les coefs inférieur et qu'on retrouve les autres par symetrie on a toujours profil[i-1]<=i
    vector<int> nbr_coef; //le i-ème terme vaut le nombre de coefficient stocké dans val_ cumulé des i première lignes, le premier terme vaut 0 par convention

    matrice_profil_sym(const matrice_profil_sym& M);
    matrice_profil_sym(int dl, int dc); //crée une matrice profil nulle
    matrice_profil_sym(int dl, int dc, const vector<int>& v); //crée une matrice nulle dont le profil est donnée par le vecteur v : profil[i] = v[i]

//SURCHARGE D'OPERATEUR

float& operator () (int i, int j); //permet de donner au coef (i,j) la valeur coef, indexaation commence à 1, LE COEF DOIT ETRE DANS LE PROFIL, SINON ERREUR
float operator() (int i, int j) const; //accède au terme (i,j) attention l'indexation commence à 1


matrice_profil_sym& operator=(const matrice_profil_sym& M);
matrice_profil_sym& operator+=(const matrice_profil_sym& M);
matrice_profil_sym& operator-=(const matrice_profil_sym& M);
matrice_profil_sym& Id(); //transforme une matrice carre en l'identite
matrice_profil_sym& J(); //transforme une matrice carre en la matrice qui ne contient que des 1 : utilisé pour tester mes fonctions
void info_mat(); //renvoie val_, profil et nbr_coef


};

ostream& operator<<(ostream &out, const matrice_profil_sym& M);
matrice_profil_sym operator + (const matrice_profil_sym&A,const matrice_profil_sym& B) ;
matrice_profil_sym operator - (const matrice_profil_sym&A, const matrice_profil_sym& B);
matrice_profil_sym operator * (const matrice_profil_sym&A, const float& x);
matrice_profil_sym operator * (const float& x, const matrice_profil_sym&A);
vecteur operator * (const matrice_profil_sym& A, const vecteur& v);


///////////////////////////////////////// FONCTION AVANCEES /////////////////////////////////

matrice_profil_sym cholesky(const matrice_profil_sym& A);
vecteur resol(const matrice_profil_sym& A, const vecteur& y);





#endif