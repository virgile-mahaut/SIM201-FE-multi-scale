#ifndef matrice_h
#define matrice_h

#include <iostream>
#include <vector>
using namespace std;

#include <iostream>
#include <vector>
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

matrice_pleine operator + (matrice_pleine&A, matrice_pleine& B);
matrice_pleine operator - (matrice_pleine&A, matrice_pleine& B);
matrice_pleine operator * (matrice_pleine&A, const float& x);
matrice_pleine operator * (const float& x, matrice_pleine&A);




///////////////////////////////////////////////CLASSE MATRICE PROFIL///////////////////////////////////////////////
class matrice_profil : public matrice {

//LES MATRICES SONT SUPPOSEES TRIANGULAIRE INFERIEURE

public:
    int nbr_val;
    vector<int> profil; //contient les indices de lignes à partir de premier non nuls, l'indexation commence à 1, vaut 0 si la ligne ne contient que des zéros
    vector<int> nbr_coef; //le i-ème terme vaut le nombre de coefficient stocké dans val_ cumulé des i-1 première ligne

    matrice_profil(const matrice_pleine& M); // rend creuse les matrices pleines
    matrice_profil(const matrice_profil& M);
    matrice_profil(int dl, int dc); //crée une matrice profil nulle

//SURCHARGE D'OPERATEUR
friend ostream& operator<<(ostream &out, const matrice_profil& M);
void operator () (int i, int j, float coef); //permet de donner au coef (i,j) la valeur coef, indexaation commence à 1
float operator() (int i, int j) const; //accède au terme (i,j) attention l'indexation commence à 1
matrice_profil& operator=(const matrice_profil& M);
matrice_profil& operator+=(const matrice_profil& M);
matrice_profil& Id(); //transforme une matrice carre en l'identite

};

int test();

#endif