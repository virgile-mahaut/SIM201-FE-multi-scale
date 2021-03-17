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
  dim_ = d;
  val_.resize(d);
  vector<double>::iterator it;
  it = val_.begin();
  for(;it != val_.end();it++) *it=v0;
}

vecteur::vecteur(const vecteur & v) //constructeur par copie
{
  dim_ = v.dim_;
  val_.resize(v.dim());

  vector<double>::iterator it_elem_courant;
  it_elem_courant = val_.begin();
  vector<double>:: const_iterator it_v;
  it_v = v.val_.begin();

  
  for(;it_elem_courant != val_.end();it_elem_courant++){
    *it_elem_courant= *it_v ;
    it_v++;
  }
}
//Surcharge d'opérateur

vecteur& vecteur :: operator=(const vecteur& v){
  if (dim_ != v.dim_){
    stop_vect("ERREUR DE DIMENSION");
  }
  vector<double>::iterator it_elem_courant;
  it_elem_courant = val_.begin();
  vector<double>:: const_iterator it_v;
  it_v = v.val_.begin();

  for(;it_elem_courant != val_.end(); it_elem_courant++){
    *it_elem_courant = *it_v;
    it_v++;}

  return *this;
}

vecteur& vecteur::operator=(double x){
  vector<double>::iterator it;
  it = val_.begin();
  for(;it != val_.end();it++) *it=x;
  return *this;
}

double& vecteur :: operator[](int i){
  if (i>=dim_ || i<0){
    stop_vect("INDICE INCORRECT");
  }
  return val_[i];
}

double vecteur :: operator[](int i) const{ //enlever le & après double, ca a ptet tout niqué
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

double vecteur :: operator()(int i) const{ 
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

  vector<double>::iterator it_elem_courant;
  it_elem_courant = val_.begin();
  vector<double>:: const_iterator it_v;
  it_v = v.val_.begin();

  for(;it_elem_courant != val_.end(); it_elem_courant++){
    *it_elem_courant = *it_elem_courant + *it_v;
    it_v++;}

  return *this;
}

vecteur& vecteur :: operator-=(const vecteur& v){
  if (dim_ != v.dim_){
    stop_vect("ERREUR DE DIMENSION : ON NE PEUT PAS SOUSTRAIRE DES VECTEURS  DE TAILLES DIFFERENTES");
  }

  vector<double>::iterator it_elem_courant;
  it_elem_courant = val_.begin();
  vector<double>:: const_iterator it_v;
  it_v = v.val_.begin();

  for(;it_elem_courant != val_.end(); it_elem_courant++){
    *it_elem_courant = *it_elem_courant - *it_v;
    it_v++;}
  return *this;
}

vecteur& vecteur :: operator+=(const double& x){
  vector<double>::iterator it_elem_courant;
  it_elem_courant = val_.begin();

  for(;it_elem_courant != val_.end(); it_elem_courant++){
    *it_elem_courant = *it_elem_courant + x;
    }
  return *this;
}

vecteur& vecteur :: operator-=(const double& x){
  vector<double>::iterator it_elem_courant;
  it_elem_courant = val_.begin();

  for(;it_elem_courant != val_.end(); it_elem_courant++){
    *it_elem_courant = *it_elem_courant - x;
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

  vector<double> :: iterator it;
  it = resultat.val_.begin();
  vector<double> :: const_iterator it1;
  it1 = v1.val_.begin();
  vector<double> :: const_iterator it2;
  it2 = v2.val_.begin();

  for(; it != resultat.val_.end(); it++){
    *it = *it1 + *it2;
    it2++;
    it1++;
  }
  return resultat;
}

vecteur operator+(const vecteur& v, const double& x){
  vecteur resultat(v.dim());

  vector<double> :: const_iterator itv;
  itv = v.val_.begin();
  vector<double> :: iterator itres;
  itres = resultat.val_.begin();
  for(;itres != resultat.val_.end(); itres++){
    *itres = *itv + x;
    itv++;
  }

  return resultat;
}

vecteur operator+(const double& x, const vecteur& v){
  vecteur resultat(v.dim());

  vector<double> :: const_iterator itv;
  itv = v.val_.begin();
  vector<double> :: iterator itres;
  itres = resultat.val_.begin();
  for(;itres != resultat.val_.end(); itres++){
    *itres = *itv + x;
    itv++;
  }

  return resultat;
}

vecteur operator-(const vecteur& v){
  vecteur resultat(v.dim());

  vector<double> :: iterator itres;
  itres = resultat.val_.begin();
  vector<double> :: const_iterator itv;
  itv = v.val_.begin();

  for (; itres != resultat.val_.end(); itres++){
    *itres = -*itv;
    itv++;
  }
  return resultat;
}


vecteur operator-(const vecteur& v1, const vecteur& v2){
 if (v1.dim() != v2.dim()){
    stop_vect("ERREUR DE DIMENSION : ON NE PEUT PAS SOUSTRAIRE DES VECTEURS  DE TAILLES DIFFERENTES");
  } 
  vecteur resultat(v1.dim());

  vector<double> :: iterator it;
  it = resultat.val_.begin();
  vector<double> :: const_iterator it1;
  it1 = v1.val_.begin();
  vector<double> :: const_iterator it2;
  it2 = v2.val_.begin();

  for(; it != resultat.val_.end(); it++){
    *it = *it1 - *it2;
    it2++;
    it1++;
  }
  return resultat;
}

vecteur operator-(const vecteur& v, const double& x){
  vecteur resultat(v.dim());

  vector<double> :: const_iterator itv;
  itv = v.val_.begin();
  vector<double> :: iterator itres;
  itres = resultat.val_.begin();
  for(;itres != resultat.val_.end(); itres++){
    *itres = *itv + x;
    itv++;
  }
  return resultat;
}

vecteur operator-(const double& x, const vecteur& v){
  vecteur resultat(v.dim());
  
  vector<double> :: const_iterator itv;
  itv = v.val_.begin();
  vector<double> :: iterator itres;
  itres = resultat.val_.begin();
  for(;itres != resultat.val_.end(); itres++){
    *itres = *itv + x;
    itv++;
  }
  return resultat;
}

vecteur& vecteur:: operator*=(const double& x){
  vector<double>::iterator it_elem_courant;
  it_elem_courant = val_.begin();

  for(;it_elem_courant != val_.end(); it_elem_courant++){
    *it_elem_courant = *it_elem_courant * x;
    }
  return *this;

}

vecteur& vecteur:: operator/=(const double& x){
  if (x==0){
    stop_vect("ERREUR: DIVISION PAR 0");
  }
  vector<double>::iterator it_elem_courant;
  it_elem_courant = val_.begin();

  for(;it_elem_courant != val_.end(); it_elem_courant++){
    *it_elem_courant = *it_elem_courant / x;
    }
  return *this;

}


vecteur operator*(const vecteur& v, const double& x){
  vecteur resultat(v.dim());

  vector<double> :: const_iterator itv;
  itv = v.val_.begin();
  vector<double> :: iterator itres;
  itres = resultat.val_.begin();
  for(;itres != resultat.val_.end(); itres++){
    *itres = *itv * x;
    itv++;
  }

  return resultat;
}

vecteur operator*(const double& x, const vecteur& v){
  vecteur resultat(v.dim());
  vector<double> :: const_iterator itv;
  itv = v.val_.begin();
  vector<double> :: iterator itres;
  itres = resultat.val_.begin();
  for(;itres != resultat.val_.end(); itres++){
    *itres = *itv * x;
    itv++;
  }
  return resultat;
}

vecteur operator/(const vecteur& v, const double& x){
  if (x==0){
    stop_vect("ERREUR: DIVISION PAR 0");
  }
  vecteur resultat(v.dim());
  vector<double> :: const_iterator itv;
  itv = v.val_.begin();
  vector<double> :: iterator itres;
  itres = resultat.val_.begin();
  for(;itres != resultat.val_.end(); itres++){
    *itres = *itv / x;
    itv++;
  }
  return resultat;
}

double operator|(const vecteur& v1, const vecteur& v2){
    //cout<<v1.dim()<<" "<<v2.dim()<<"\n";
   if (v1.dim() != v2.dim()){
    stop_vect("ERREUR DE DIMENSION : TAILLES INCOMPATIBLES POUR LE PRODUIT SCALAIRE");
  }
    double PS = 0;
    vector<double> :: const_iterator itv1;
    itv1 = v1.val_.begin();
    vector<double> :: const_iterator itv2;
    itv2 = v2.val_.begin();
    for(;itv1 != v1.val_.end(); itv1++){
    PS = PS + (*itv1) * (*itv2);
  }
  return PS;

}

vecteur operator,(const vecteur& v1, const vecteur& v2){
  int new_dim = v1.dim() + v2.dim();
  vecteur Resultat(new_dim);

  vector<double> :: iterator it;
  it = Resultat.val_.begin();
  vector<double> :: const_iterator it1;
  it1 = v1.val_.begin();
  vector<double> :: const_iterator it2;
  it2 = v2.val_.begin();

  for(; it1 != v1.val_.end(); it1++){
    *it = *it1;
    it++;
  }
  for(; it2 != v2.val_.end(); it2++){
    *it = *it2;
    it++;
  }
  return Resultat;

}

bool operator==(const vecteur& v1, const vecteur& v2){
  if (v1.dim() != v2.dim()){
    return false;
  } 
  vector<double> :: const_iterator it1;
  it1 = v1.val_.begin();
  vector<double> :: const_iterator it2;
  it2 = v2.val_.begin();
  for(; it1 != v1.val_.end(); it1++){
    if (*it1 != *it2){
      return false;}
    it2++;
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


