#include "vecteur.hpp"
#include <cmath>
#include <cstdlib>

//utilitaire de messages d'erreur
void stop_vect(const char * msg)
{
  cout<<"ERREUR classe vecteur, "<<msg;
  exit(-1);
}


// constructeurs-destructeurs
vecteur::vecteur(int d, double v0) //dim et val constante
{
  init(d);
  for(int i=0;i<dim_;i++) val_[i]=v0;
}

vecteur::vecteur(const vecteur & v) //constructeur par copie
{
  init(v.dim_);
  for(int i=0;i<dim_;i++) val_[i]=v[i];
}

vecteur::~vecteur() {clear();}

// outils de construction et de destruction
void vecteur::init(int d) //initialisation avec allocation dynamique
{
  if(d<=0) stop_vect("init() : dimension <=0");
  dim_=d;
  val_ = new double[d];
}

void vecteur::clear()    //désallocation
{
    if(val_!=0) delete [] val_;
    dim_=0;
}

//Surcharge d'opérateur

vecteur& vecteur :: operator=(const vecteur& v){
  if (dim_ != v.dim_){
    stop_vect("ERREUR DE DIMENSION");
  }
  for(int i=0; i<dim_; i++){
    val_[i] = v.val_[i];}
  return *this;
}

vecteur& vecteur::operator=(double x){
  for(int i=0; i<dim_; i++){
    val_[i] = x;
  }
  return *this;
}

double& vecteur :: operator[](int i){
  if (i>=dim_ || i<0){
    stop_vect("INDICE INCORRECT");
  }
  return val_[i];
}

double& vecteur :: operator[](int i) const{
  if (i>=dim_ || i<0){
    stop_vect("INDICE INCORRECT");
  }
  return val_[i];
}

double& vecteur :: operator()(int i){
  if (i>dim_ || i<=0){
    stop_vect("INDICE INCORRECT");
  }
  return val_[i-1];
}

double& vecteur :: operator()(int i) const{
  if (i>dim_ || i<=0){
    stop_vect("INDICE INCORRECT");
  }
  return val_[i-1];
}


vecteur vecteur::operator()(int i, int j) const{
  if(i<1 || i>j || j>dim_){
    stop_vect("ERREUR DE BORNE");}

  vecteur nouveau(j-i+1);
  for (int k=0; k<=j-1; k++){
    nouveau.val_[k]=val_[i+k-1];}
  return nouveau;
}

vecteur& vecteur :: operator+=(const vecteur& v){
  if (dim_ != v.dim_){
    stop_vect("ERREUR DE DIMENSION : ON NE PEUT PAS SOMMER DES VECTEURS  DE TAILLES DIFFERENTES");
  }

  for(int i=0; i<dim_; i++){
    val_[i] = val_[i] + v[i];
  }
  return *this;
}

vecteur& vecteur :: operator-=(const vecteur& v){
  if (dim_ != v.dim_){
    stop_vect("ERREUR DE DIMENSION : ON NE PEUT PAS SOUSTRAIRE DES VECTEURS  DE TAILLES DIFFERENTES");
  }

  for(int i=0; i<dim_; i++){
    val_[i] = val_[i] - v[i];
  }
  return *this;
}

vecteur& vecteur :: operator+=(const double& x){
  for(int i=0; i<dim_; i++){
    val_[i] = val_[i] + x;
  }
  return *this;
}

vecteur& vecteur :: operator-=(const double& x){
  for(int i=0; i<dim_; i++){
    val_[i] = val_[i] - x;
  }
  return *this;
}

vecteur operator+(const vecteur& v){
  return v;
}

vecteur operator+(const vecteur& v1, const vecteur& v2){
 if (v1.dim() != v2.dim()){
    stop_vect("ERREUR DE DIMENSION : ON NE PEUT PAS SOMMER DES VECTEURS  DE TAILLES DIFFERENTES");
  } 
  vecteur resultat(v1.dim());
  for(int i=0; i<v1.dim(); i++){
    resultat[i] = v1[i] + v2[i];
  }
  return resultat;
}

vecteur operator+(const vecteur& v, const double& x){
  vecteur resultat(v.dim());
  for(int i=0; i<v.dim(); i++){
    resultat[i] = v[i] + x;
  }
  return resultat;
}

vecteur operator+(const double& x, const vecteur& v){
  vecteur resultat(v.dim());
  for(int i=0; i<v.dim(); i++){
    resultat[i] = v[i] + x;
  }
  return resultat;
}

vecteur operator-(const vecteur& v){
  vecteur resultat(v.dim());
  for (int i=0; i<v.dim(); i++){
    resultat[i] = -v[i];
  }
  return resultat;
}


vecteur operator-(const vecteur& v1, const vecteur& v2){
 if (v1.dim() != v2.dim()){
    stop_vect("ERREUR DE DIMENSION : ON NE PEUT PAS SOUSTRAIRE DES VECTEURS  DE TAILLES DIFFERENTES");
  } 
  vecteur resultat(v1.dim());
  for(int i=0; i<v1.dim(); i++){
    resultat[i] = v1[i] - v2[i];
  }
  return resultat;
}

vecteur operator-(const vecteur& v, const double& x){
  vecteur resultat(v.dim());
  for(int i=0; i<v.dim(); i++){
    resultat[i] = v[i] - x;
  }
  return resultat;
}

vecteur operator-(const double& x, const vecteur& v){
  vecteur resultat(v.dim());
  for(int i=0; i<v.dim(); i++){
    resultat[i] = v[i] - x;
  }
  return resultat;
}

vecteur& vecteur:: operator*=(const double& x){
  for(int i=0; i<dim_; i++){
    val_[i] = val_[i] * x;
  }
  return *this;

}

vecteur& vecteur:: operator/=(const double& x){
  if (x==0){
    stop_vect("ERREUR: DIVISION PAR 0");
  }
  for(int i=0; i<dim_; i++){
    val_[i] = val_[i] / x;
  }
  return *this;

}


vecteur operator*(const vecteur& v, const double& x){
  vecteur resultat(v.dim());
  for(int i=0; i<v.dim(); i++){
    resultat[i] = v[i] * x;
  }
  return resultat;
}

vecteur operator*(const double& x, const vecteur& v){
  vecteur resultat(v.dim());
  for(int i=0; i<v.dim(); i++){
    resultat[i] = v[i] * x;
  }
  return resultat;
}

vecteur operator/(const vecteur& v, const double& x){
  if (x==0){
    stop_vect("ERREUR: DIVISION PAR 0");
  }
  vecteur resultat(v.dim());
  for(int i=0; i<v.dim(); i++){
    resultat[i] = v[i] / x;
  }
  return resultat;
}

double operator|(const vecteur& v1, const vecteur& v2){
    //cout<<v1.dim()<<" "<<v2.dim()<<"\n";
   if (v1.dim() != v2.dim()){
    stop_vect("ERREUR DE DIMENSION : TAILLES INCOMPATIBLES POUR LE PRODUIT SCALAIRE");
  }
    double PS = 0;
    for(int i=0; i<v1.dim(); i++){
        PS = PS + v1[i]*v2[i];
  }
  return PS;

}

vecteur operator,(const vecteur& v1, const vecteur& v2){
  int new_dim = v1.dim() + v2.dim();
  vecteur Resultat(new_dim);
  int i;
  for (i=0; i<v1.dim(); i++){
    Resultat[i] = v1[i];
  }
  for (i=0; i<v1.dim(); i++){
    Resultat[v1.dim() + i] = v2[i];
  }
  return Resultat;

}

bool operator==(const vecteur& v1, const vecteur& v2){
  if (v1.dim() != v2.dim()){
    return false;
  } 
  for(int i=0; i<v1.dim(); i++){
    if (v1[i] != v2[i]){
      return false;}
  } 
  return true;
  
}

bool operator!=(const vecteur& v1, const vecteur& v2){
  return !(v1 == v2);
  
}


ostream& operator<<(ostream &out, const vecteur& v)
{
  out<<"(";

for (int i=0;i<v.dim()-1;i++ ){
  out<<v.val_[i]<<",";
}

cout<<v.val_[v.dim()-1]<<")";
return out;
}


