#include "matrice.hpp"
#include "vecteur.hpp"
#include <cmath>
#include <cstdlib>
#include <vector>


///////////////////////////////////////////////// FONCTION GENERALE

//utilitaire de messages d'erreur
void stop_mat(const char * msg)
{
  cout<<"ERREUR : "<<msg;
  exit(-1);
}

///////////////////////////////////////////////// FONCTION DE LA CLASSE MATRICE PLEINE

matrice_pleine :: matrice_pleine(int dl, int dc, float x){
  dim_l = dl;
  dim_c = dc;
  val_.resize(dl * dc); 
  vector<float>::iterator it; 
  it = val_.begin(); 
  while(it != val_.end()){
    *it = x;
    it++;
    }
}

matrice_pleine :: matrice_pleine(const matrice_pleine& M){
  dim_l = M.dim_l;
  dim_c = M.dim_c;
  val_.resize(M.diml() * M.dimc()); 
  vector<float>::iterator it_elem_courant; 
  it_elem_courant = val_.begin(); 

  vector<float>:: const_iterator it_M;
  it_M = M.val_.begin(); 

  while(it_elem_courant != val_.end()){
    *it_elem_courant = *it_M;
    it_M++;
    it_elem_courant++;

    }
}

float& matrice_pleine :: operator()(int i, int j){ //attention les indices commencent à 1
  if (i>dim_l || i<=0){
    stop_mat("INDICE DE LIGNE INCORRECT");
  }

  else if (j>dim_c || j<=0){
    stop_mat("INDICE DE COLONNE INCORRECT");
  }
  else{
  return val_[dim_c * (i-1) + (j-1)];}
}

float matrice_pleine :: operator()(int i, int j) const{ //attention les indices commencent à 1
  if (i>dim_l || i<=0){
    stop_mat("INDICE DE LIGNE INCORRECT");
  }

  else if (j>dim_c || j<=0){
    stop_mat("INDICE DE COLONNE INCORRECT");
  }
  else{
  return val_[dim_c * (i-1) + (j-1)];}
}

ostream& operator<<(ostream &out, const matrice_pleine& M)
{

for (int i=0;i<M.diml(); i++){
  for(int j=0; j<M.dimc(); j++){
    out<<M.val_[M.dimc()*i + j]<<" ";
}
  out<<"\n";
}

return out;
}

matrice_pleine operator + (const matrice_pleine&A, const matrice_pleine& B){
  if (A.diml() != B.diml() || A.dimc() != B.dimc()){
    stop_mat("TAILLES DES MATRICES INCOMPATIBLES POUR L'ADDITION");
  }
  matrice_pleine R(A.diml(), A.dimc());
  for (int i=1; i<A.diml()+1; i++){
    for (int j=1; j<A.dimc()+1; j++){
      R(i,j) = A(i,j) + B(i,j);
    }  
  }
  return R;
}

matrice_pleine operator - (const matrice_pleine&A, const matrice_pleine& B){
  if (A.diml() != B.diml() || A.dimc() != B.dimc()){
    stop_mat("TAILLES DES MATRICES INCOMPATIBLES POUR L'ADDITION");
  }
  matrice_pleine R(A.diml(), A.dimc());
  for (int i=1; i<A.diml()+1; i++){
    for (int j=1; j<A.dimc()+1; j++){
      R(i,j) = A(i,j) - B(i,j);
    }  
  }
  return R;
}

matrice_pleine operator * (const matrice_pleine&A, const float& x){
  matrice_pleine R(A.diml(), A.dimc());
  for (int i=1; i<A.diml()+1; i++){
    for (int j=1; j<A.dimc()+1; j++){
      R(i,j) = x  * A(i,j);
    }  
  }
  return R;
  
}

matrice_pleine operator * (const float& x, const matrice_pleine&A){
  matrice_pleine R(A.diml(), A.dimc());
  for (int i=1; i<A.diml()+1; i++){
    for (int j=1; j<A.dimc()+1; j++){
      R(i,j) = x  * A(i,j);
    }  
  }
  return R;
  
}

vecteur operator * (const matrice_pleine& A, const vecteur& v){
  if (v.dim() != A.dimc()){
    stop_mat("VECTEUR ET MATRICE INCOMPATIBLES POUR LE PRODUIT");
  }

  vecteur produit(A.diml());
  for(int i=1; i<A.diml()+1; i++){
    for(int k=1; k<v.dim()+1;k++){
      produit(i) += v(k)*A(i,k);
    }
  }
  return produit;
}

///////////////////////////////////////////////// FONCTION DE LA CLASSE MATRICE PROFIL SYMETRQUE


matrice_profil_sym :: matrice_profil_sym(int dl, int dc){

  dim_l = dl;
  dim_c = dc;
  profil.resize(0);
  val_.resize(0);
  nbr_coef.resize(0);
  nbr_val = 0;

  nbr_coef.push_back(0); //le premier terme vaut 0 par convention et sert a avoir des formule sans problèmes d'indices
  for(int i=0; i<dl; i++){
    val_.push_back(0);
    nbr_coef.push_back(0);
    profil.push_back(i+1);
  }
}

matrice_profil_sym :: matrice_profil_sym(const matrice_profil_sym& M){
    dim_l = M.diml();
    dim_c = M.dimc();
    profil.resize(0);
    val_.resize(0);
    nbr_coef.resize(0);
    nbr_val = M.nbr_val;
    
    for(int i=0; i< (int) M.val_.size(); i++){
        val_.push_back(M.val_[i]);
    }
    for(int i=0; i< (int) M.profil.size(); i++){
        profil.push_back(M.profil[i]);
    }
    for(int i=0; i< (int) M.nbr_coef.size(); i++){
        nbr_coef.push_back(M.nbr_coef[i]);
    }
    
}

matrice_profil_sym :: matrice_profil_sym(int dl, int dc, const vecteur& v){
  dim_l = dl;
  dim_c = dc;
  profil.resize(0);

  nbr_val = 0;
  for (int i=1; i<v.dim()+1; i++){
    nbr_val += i-v(i)+1;
  }
  val_.resize(0);
  nbr_coef.resize(0);

  nbr_coef.push_back(0); //le premier terme vaut 0 par convention et sert a avoir des formule sans problèmes d'indices
  for(int i=0; i<nbr_val; i++){
    val_.push_back(0);
  }

  int somme_nbr_coef = 0;
  for(int i=0; i<dl; i++){
    somme_nbr_coef += i+1-v(i+1)+1;
    nbr_coef.push_back(somme_nbr_coef);
    if (v[i] > i+1){
      stop_mat("PROFIL INCOMPATIBLE AVEC LA TAILLE DE LA MATRICE");
    }
    profil.push_back(v[i]);
  }
}


matrice_profil_sym& matrice_profil_sym :: Id(){
  if (dim_c != dim_l){
      stop_mat("ON NE PEUT PAS TRANSFORMER UNE MATRICE RECTANGULAIRE EN L'IDENTITE");
  }

  val_.resize(dim_c);
  profil.resize(dim_c);
  nbr_coef.resize(dim_c+1);

  vector<float> :: iterator itv;
  itv = val_.begin();
  vector<int> :: iterator itp;
  itp = profil.begin();
  vector<int> :: iterator itnb;
  itnb = nbr_coef.begin();

  nbr_val = dim_c;

  *itnb = 0;
  itnb++;

  for(int i=1; i<= dim_c; i++){
    *itv = 1;
    *itp = i;
    *itnb = i;

    itv++;
    itp++;
    itnb++;}    

    return *this;
}

matrice_profil_sym& matrice_profil_sym :: J(){
  if (dim_c != dim_l){
      stop_mat("ON NE PEUT PAS TRANSFORMER UNE MATRICE RECTANGULAIRE EN MATRICE CARRE");
  }

  val_.resize((dim_l*(dim_l+1))/2);
  profil.resize(dim_c);
  nbr_coef.resize(dim_c+1);

  vector<float> :: iterator itv;
  itv = val_.begin();
  vector<int> :: iterator itp;
  itp = profil.begin();
  vector<int> :: iterator itnb;
  itnb = nbr_coef.begin();

  nbr_val = (dim_l*(dim_l+1)) /2;

  *itnb = 0;
  itnb++;

  for(int i=1; i<= dim_l; i++){
    *itp = 1;
    *itnb = i + nbr_coef[i-1];
    itnb++;
    itp++;
}    

  
  for(int i=1; i<= nbr_val; i++){
    *itv = 1;
    itv++;} 

    return *this;
}


float matrice_profil_sym :: operator()(int i, int j) const{
  if (i>dim_l || i<=0){
        stop_mat("INDICE DE LIGNE INCORRECT");
  }
  else if (j>dim_c || j<=0){
        stop_mat("INDICE DE COLONNE INCORRECT");
  }

  if(i>=j){

    int debut_ligne = profil[i-1];
    if(j < debut_ligne){ //verifie si l'on cherche un coef dans le profil
      return 0;
    }

    else if(j>=debut_ligne){
      return val_[nbr_coef[i-1] + j- debut_ligne ];
    }

}

else{
  return (*this)(j,i);
}

}

void matrice_profil_sym :: operator()(int i, int j,float coef){
  if (i>dim_l || i<=0){
        stop_mat("INDICE DE LIGNE INCORRECT");
  }
  else if (j>dim_c || j<=0){
        stop_mat("INDICE DE COLONNE INCORRECT");
  }

  if(i>=j){

    int debut_ligne = profil[i-1];
    if(j < debut_ligne){ //verifie si l'on cherche un coef dans le profil
      stop_mat("ERREUR : MODIFICATION DU PROFIL");
    }

    else if(j>=debut_ligne){
      val_[nbr_coef[i-1] + j - debut_ligne ] = coef;
    }

}

else{
  (*this)(j,i);
}

}

ostream& operator<<(ostream &out, const matrice_profil_sym& M)
{

for (int i=0;i<M.diml(); i++){
  for(int j=0; j<M.dimc(); j++){
    out<<M(i+1,j+1)<<" ";
}
  out<<"\n";
}

return out;
}

matrice_profil_sym& matrice_profil_sym :: operator=(const matrice_profil_sym& M){
val_.resize(M.val_.size());
profil.resize(M.profil.size());
nbr_coef.resize(M.nbr_coef.size());
dim_c = M.dimc();
dim_l = M.diml();

for(int i=0; i< (int) M.val_.size(); i++){
  val_[i] = M.val_[i];
}

for(int i=0; i< (int) M.nbr_coef.size(); i++){
  nbr_coef[i] = M.nbr_coef[i];
}

for(int i=0; i<(int) M.profil.size(); i++){
  profil[i] = M.profil[i];
}
return *this;
}

matrice_profil_sym& matrice_profil_sym :: operator +=(const matrice_profil_sym& M){
  if (dim_l != M.diml() || dim_c != M.dimc()){
    stop_mat("TAILLES DES MATRICES INCOMPATIBLES POUR L'ADDITION");
  }
  for(int i=0; i< (int) profil.size(); i++){
    if (profil[i] != M.profil[i]){
      stop_mat("ERREUR : ON NE PEUT PAS ADDITIONER 2 MATRICES AUX PROFILS DIFFRENTS");
      break;
    }
  }

  for (int j=0; j< (int) M.val_.size(); j++){
    val_[j] = val_[j] + M.val_[j];
  }
  return *this;
}

matrice_profil_sym& matrice_profil_sym :: operator -=(const matrice_profil_sym& M){
  if (dim_l != M.diml() || dim_c != M.dimc()){
    stop_mat("TAILLES DES MATRICES INCOMPATIBLES POUR L'ADDITION");
  }
  for(int i=0; i< (int) profil.size(); i++){
    if (profil[i] != M.profil[i]){
      stop_mat("ERREUR : ON NE PEUT PAS ADDITIONER 2 MATRICES AUX PROFILS DIFFRENTS");
      break;
    }
  }

  for (int j=0; j<(int)M.val_.size(); j++){
    val_[j] = val_[j] - M.val_[j];
  }
  return *this;
}


matrice_profil_sym operator + (const matrice_profil_sym&A, const matrice_profil_sym& B){
  if (A.diml() != B.diml() || A.dimc() != B.dimc()){
      stop_mat("TAILLES DES MATRICES INCOMPATIBLES POUR L'ADDITION");
    }
  for(int i=0; i< (int) A.profil.size(); i++){
    if (A.profil[i] != B.profil[i]){
      stop_mat("ERREUR : ON NE PEUT PAS ADDITIONER 2 MATRICES AUX PROFILS DIFFRENTS");
      break;
    }
  }

  matrice_profil_sym Somme(A);
  Somme+=B;
  return Somme;

}

matrice_profil_sym operator - (const matrice_profil_sym&A, const matrice_profil_sym& B){
  if (A.diml() != B.diml() || A.dimc() != B.dimc()){
      stop_mat("TAILLES DES MATRICES INCOMPATIBLES POUR L'ADDITION");
    }
  for(int i=0; i<(int) A.profil.size(); i++){
    if (A.profil[i] != B.profil[i]){
      stop_mat("ERREUR : ON NE PEUT PAS SOUSTRAIRE 2 MATRICES AUX PROFILS DIFFRENTS");
      break;
    }
  }
  matrice_profil_sym Difference(A);
  Difference-=B;
  return Difference;
}

matrice_profil_sym operator * (const float& x, const matrice_profil_sym&A){
  matrice_profil_sym Produit(A);
  for (int j=0; j<(int) A.val_.size(); j++){
    Produit.val_[j] = x*Produit.val_[j];
  }
  return Produit;
}

matrice_profil_sym operator * (const matrice_profil_sym&A, const float& x){

  return x*A;
}

vecteur operator * (const matrice_profil_sym& A, const vecteur& v){
  if (v.dim() != A.dimc()){
    stop_mat("VECTEUR ET MATRICE INCOMPATIBLES POUR LE PRODUIT");
  }
  vecteur produit(A.diml());
  for(int i=1; i<A.diml()+1; i++){
    for(int k=A.profil[i-1]; k<v.dim()+1;k++){
      produit(i) += v(k)*A(i,k);
    }
  }
  return produit;


}

void matrice_profil_sym :: info_mat(){
  for(int i=0; i<(int) val_.size();i++){
      cout<<"val_ "<<val_[i]<<" ";
  }
  cout<<"\n";

  for(int i=0; i<(int) profil.size();i++){
      cout<<"profil "<<profil[i]<<" ";
  }
cout<<"\n";

for(int i=0; i<(int) nbr_coef.size();i++){
  cout<<"nbr_coef "<<nbr_coef[i]<<" ";
}
cout<<"\n";
}


///////////////////////////////////////// FONCTION AVANCEES /////////////////////////////////

matrice_profil_sym cholesky(const matrice_profil_sym& A){

  //Factorisation de cholesky d'une matrice défini positive
  vecteur v(A.diml());
  for (int i=0; i<A.diml(); i++){
    v[i] = A.profil[i];
  }
  matrice_profil_sym L(A.diml(),A.dimc(), v);

  for(int p=1; p<= A.dimc();p++){
    float valeur = A(p,p);
    for (int k=1; k<= p-1; k++){
      valeur -= L(p,k)*L(p,k);
    }
    valeur = sqrt(valeur);
    L(p,p,valeur);

    for(int i=p+1; i<=A.dimc(); i++){
      if (p>= A.profil[i-1]){
        float valeur = A(i,p);
        for (int k=1; k<= p-1; k++){
          valeur -= L(i,k)*L(p,k);
          }
        valeur = valeur /L(p,p);
        L(i,p,valeur);
      }

    }

  }

  return L;

}


vecteur resol(const matrice_profil_sym& A, const vecteur& b){
 // résout le problème Ax=b en utilisant la factorisation de Cholesky A =LLt

 if (A.diml() != b.dim()){
   stop_mat("TAILLES INCOMPATIBLES POUR LA RESOLUTION DE SYSTEMES LINEAIRES");
 }
  matrice_profil_sym L(A);
  L = cholesky(A);
 //on résout d'abord Ly = b 
  
  vecteur y(L.diml());
  for (int i=1; i<b.dim()+1; i++){
    float valeur =b(i);
    for (int j= L.profil[i-1]; j<i; j++){
      valeur -= y(j)* L(i,j);
    }
    y(i) = (valeur)/L(i,i);

  }

  cout<<"valeur de y = "<<y<<"\n";

  //on résout maintenant Ltx= y
  vecteur x(L.diml());
  for (int i=b.dim(); i>=1; i--){
    float valeur = y(i);
    for (int j= L.dimc(); j>i; j--){
      valeur -= x(j)*L(i,j);
    }
    x(i) = (valeur)/L(i,i);

  }

  return x; 

}
