#include "matrice.hpp"
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

matrice_pleine operator + (matrice_pleine&A, matrice_pleine& B){
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

matrice_pleine operator - (matrice_pleine&A, matrice_pleine& B){
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

matrice_pleine operator * (matrice_pleine&A, const float& x){
  matrice_pleine R(A.diml(), A.dimc());
  for (int i=1; i<A.diml()+1; i++){
    for (int j=1; j<A.dimc()+1; j++){
      R(i,j) = x  * A(i,j);
    }  
  }
  return R;
  
}
matrice_pleine operator * (const float& x, matrice_pleine&A){
  matrice_pleine R(A.diml(), A.dimc());
  for (int i=1; i<A.diml()+1; i++){
    for (int j=1; j<A.dimc()+1; j++){
      R(i,j) = x  * A(i,j);
    }  
  }
  return R;
  
}

///////////////////////////////////////////////// FONCTION DE LA CLASSE MATRICE PROFIL

matrice_profil :: matrice_profil(const matrice_pleine& M){

  dim_l = M.diml();
  dim_c = M.dimc();
  row.resize(0);
  column.resize(0);
  val_.resize(0);

  int i;
  int j;
  for(i=0; i<dim_l; i++){
    for(j=0; j<dim_c; j++){
      
      if ( M(i+1,j+1) != 0){
        row.push_back(j+1);
        column.push_back(i+1);
        val_.push_back(M(i+1,j+1));
      }
    }
  }
  nbr_val = val_.size();
}

matrice_profil :: matrice_profil(int dl, int dc){

  dim_l = dl;
  dim_c = dc;
  row.resize(0);
  column.resize(0);
  val_.resize(0);
  nbr_val = 0;
}

matrice_profil :: matrice_profil(const matrice_profil& M){
  dim_l = M.diml();
  dim_c = M.dimc();
  row.resize(0);
  column.resize(0);
  val_.resize(0);
  nbr_val = M.nbr_val;

  for(int i=0; i<M.nbr_val; i++){
    row.push_back(M.row[i]);
    column.push_back(M.column[i]);
    val_.push_back(M.val_[i]);
    }

}

float matrice_profil :: operator() (int i, int j) const{
  if (i>dim_l || i<=0){
    stop_mat("INDICE DE LIGNE INCORRECT");
  }

  else if (j>dim_c || j<=0){
    stop_mat("INDICE DE COLONNE INCORRECT");
  }

  int r=0;
  for(r=0; r<nbr_val; r++){
    if ( row[r] == i && column[r] == j ){
      return val_[r];
    }
  }
  return 0;
}

void matrice_profil :: operator() (int i, int j, float coef){
  if (i>dim_l || i<=0){
    stop_mat("INDICE DE LIGNE INCORRECT");
  }

  else if (j>dim_c || j<=0){
    stop_mat("INDICE DE COLONNE INCORRECT");
  }

  int r=0;
  bool coef_nul = true;
  for(r=0; r<nbr_val; r++){
    if ( row[r] == i && column[r] == j ){
      val_[r] = coef;
      coef_nul = false;
    }
  }
  if (coef_nul){
    row.push_back(i);
    column.push_back(j);
    val_.push_back(coef);
    nbr_val = nbr_val+1;
  }
}


matrice_profil& matrice_profil :: operator+=(const matrice_profil& M){
  if (dim_l != M.diml() || dim_c != M.dimc()){
    stop_mat("TAILLES DES MATRICES INCOMPATIBLES POUR L'ADDITION");
  }
  for (int j=0; j<M.nbr_val; j++){
    float coef_act = (*this)(M.row[j],M.column[j]);
    (*this)(M.row[j],M.column[j], coef_act + M.val_[j]);
  }
  return *this;
}

matrice_profil& matrice_profil :: operator=(const matrice_profil& M){
  if ( dim_c != M.dim_c || dim_l != M.dim_l){
    stop_mat("ERREUR DE DIMENSION");
  }
  row.resize(M.nbr_val);
  column.resize(M.nbr_val);
  val_.resize(M.nbr_val);
  nbr_val = M.nbr_val;

  int i =0;
  for(i=0; i<M.nbr_val; i++){
    row[i] = M.row[i];
    column[i] = M.column[i];
    val_[i] = M.val_[i];
    }

  return *this;
}

ostream& operator<<(ostream &out, const matrice_profil& M)
{

for (int i=0;i<M.diml(); i++){
  for(int j=0; j<M.dimc(); j++){
    out<<M(i+1,j+1)<<" ";
}
  out<<"\n";
}

return out;
}

matrice_profil operator + (matrice_profil&A, matrice_profil& B){
  if (A.diml() != B.diml() || A.dimc() != B.dimc()){
    stop_mat("TAILLES DES MATRICES INCOMPATIBLES POUR L'ADDITION");
  }
  matrice_profil R(A);

  for (int j=0; j<B.nbr_val; j++){
    float coef_act = R(B.row[j],B.column[j]);
    R(B.row[j],B.column[j], coef_act + B.val_[j]);
  }
  return R;
}

matrice_profil operator - (matrice_profil&A, matrice_profil& B){
  if (A.diml() != B.diml() || A.dimc() != B.dimc()){
    stop_mat("TAILLES DES MATRICES INCOMPATIBLES POUR L'ADDITION");
  }
  matrice_profil R(A);

  for (int j=0; j<B.nbr_val; j++){
    float coef_act = R(B.row[j],B.column[j]);
    R(B.row[j],B.column[j], coef_act - B.val_[j]);
  }
  return R;
}


matrice_profil operator * (matrice_profil&A, const float& x){
  matrice_profil P(A.diml(), A.dimc() );
  P.nbr_val = A.nbr_val;
  for (int i=1; i<P.diml()+1; i++){
    for (int j=1; j<P.dimc()+1; j++){
      float coef = x * A(i,j);
      if (coef != 0){
        P.row.push_back(i);
        P.column.push_back(j);
        P.val_.push_back(coef);
      }
    }  
  }
  return P;
}

matrice_profil operator * (const float& x, matrice_profil&A){
  matrice_profil P(A.diml(), A.dimc() );
  P.nbr_val = A.nbr_val;
  for (int i=1; i<P.diml()+1; i++){
    for (int j=1; j<P.dimc()+1; j++){
      float coef = x * A(i,j);
      if (coef != 0){
        P.row.push_back(i);
        P.column.push_back(j);
        P.val_.push_back(coef);
      }
    }  
  }
  return P;
}


matrice_profil& matrice_profil :: Id(){
  if (dim_c != dim_l){
    stop_mat("ON NE PEUT PAS TRANSFORMER UNE MATRICE RECTANGULAIRE EN L'IDENTITE");
  }
  val_.resize(dim_c);
  column.resize(dim_c);
  row.resize(dim_c);
  vector<float> :: iterator itv;
  itv = val_.begin();
  vector<int> :: iterator itc;
  itc = column.begin();
  vector<int> :: iterator itr;
  itr = row.begin();

  nbr_val = dim_c;

  for(int i=1; i<= dim_c; i++){
    *itc = i;
    *itr = i;
    *itv = 1;
    itv++;
    itc++;
    itr++;
      }

    return *this;
}

/*matrice_profil operator * (matrice_profil&A, const float& x){
  matrice_pleine r(A.diml(),A.dimc());
  matrice_profil R(r);

  for (int j=0; j<A.nbr_val; j++){
    float coef = x * A.val_[j];
    R(A.row[j],A.column[j], coef );
  }
  return R;
}*/

/*matrice_profil operator * (const float& x, matrice_profil&A){
  matrice_pleine r(A.diml(),A.dimc());
  matrice_profil R(r);

  for (int j=0; j<A.nbr_val; j++){
    float coef = x * A.val_[j];
    R(A.row[j],A.column[j], coef);
  }
  return R;
}

*/

/*float matrice_profil :: operator() (int i, int j) const{
  if (i>dim_l || i<=0){
    stop_mat("INDICE DE LIGNE INCORRECT");
  }

  else if (j>dim_c || j<=0){
    stop_mat("INDICE DE COLONNE INCORRECT");
  }

  vector<int> :: const_iterator itr;
  itr = row.begin();
  vector<int> :: const_iterator itc;
  itc = column.begin();
  vector<float> :: const_iterator itv;
  itv = val_.begin();
  
  for(; itr != row.end(); itr++,itv++,itc++){
    if ( *itr == i && *itc == j ){
      return *itv;
    }
  }
  return 0;
}

void matrice_profil :: operator() (int i, int j, float coef){
  if (i>dim_l || i<=0){
    stop_mat("INDICE DE LIGNE INCORRECT");
  }

  else if (j>dim_c || j<=0){
    stop_mat("INDICE DE COLONNE INCORRECT");
  }

  vector<int> :: iterator itr;
  itr = row.begin();
  vector<int> :: iterator itc;
  itc = column.begin();
  vector<float> :: iterator itv;
  itv = val_.begin();

  bool coef_nul = true;
  for(; itr != row.end(); itr++,itv++,itc++){
    if ( *itr == i && *itc == j ){
      *itv = coef;
      coef_nul = false;
    }
  }
  if (coef_nul){
    row.push_back(i);
    column.push_back(j);
    val_.push_back(coef);
  }
}*/