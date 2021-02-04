#include "matrice.hpp"
#include <cmath>
#include <cstdlib>
#include <vector>

///////////////////////////////////////////////// FONCTION DE LA CLASSE MATRICE

//utilitaire de messages d'erreur
void stop_mat(const char * msg)
{
  cout<<"ERREUR : "<<msg;
  exit(-1);
}

///////////////////////////////////////////////// FONCTION DE LA CLASSE MATRICE PLEINE

matrice_pleine :: matrice_pleine(int dl, int dc, double x){
  dim_l = dl;
  dim_c = dc;
  val_.resize(dl * dc); 
  vector<double>::iterator it; 
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
  vector<double>::iterator it_elem_courant; 
  it_elem_courant = val_.begin(); 

  vector<double>:: const_iterator it_M;
  it_M = M.val_.begin(); 

  while(it_elem_courant != val_.end()){
    *it_elem_courant = *it_M;
    it_M++;
    it_elem_courant++;

    }
}

double& matrice_pleine :: operator()(int i, int j){ //attention les indices commencent à 1
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

///////////////////////////////////////////////// FONCTION DE LA CLASSE MATRICE PROFIL