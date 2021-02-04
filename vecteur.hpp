#ifndef vecteur_h
#define vecteur_h

#include <iostream>
using namespace std;


void stop(const char * msg);                     //message d'arrêt


///////////////////////////////////////////////CLASSE VECTEUR///////////////////////////////////////////////

class vecteur
{
private :
  int dim_;          //dimension du vecteur
  double * val_;     //tableaux de valeurs

public:
  vecteur(int d=0, double v0=0); //dim et val constante
  vecteur(const vecteur & v);    //constructeur par copie
  ~vecteur();

  //tools
  void init(int d);              //allocation
  void clear();                  //désallocation
  int dim() const {return dim_;} //accès dimension

//SURCHARGE OPERATEUR

vecteur& operator=(const vecteur& v);
vecteur& operator=(double x);
double& operator[](int i);
double& operator[](int i) const;
double& operator()(int i);
double& operator()(int i) const;
vecteur operator()(int i, int j)const; //récupère les élément du vecteur situés entre i et j


vecteur& operator+=(const vecteur& v);
vecteur& operator-=(const vecteur& v);
vecteur& operator+=(const double& x);
vecteur& operator-=(const double& x);
vecteur& operator*=(const double& x);
vecteur& operator/=(const double& x);
friend ostream& operator<<(ostream &out, const vecteur& v);

};



vecteur operator+(const vecteur& v);
vecteur operator+(const vecteur& v1, const vecteur& v2);
vecteur operator+(const vecteur& v, const double& x);
vecteur operator+(const double& x, const vecteur& v);
vecteur operator-(const vecteur& v);
vecteur operator-(const vecteur& v1, const vecteur& v2);
vecteur operator-(const vecteur& v, const double& x);
vecteur operator-(const double& x, const vecteur& v);
vecteur operator*(const vecteur& v, const double& x);
vecteur operator*(const double& x, const vecteur& v);
vecteur operator/(const vecteur& v, const double& x);
double operator|(const vecteur& v1, const vecteur& v2);
vecteur operator , (const vecteur& v1, const vecteur& v2);

bool operator==(const vecteur& v1, const vecteur& v2);
bool operator!=(const vecteur& v1, const vecteur& v2);





#endif