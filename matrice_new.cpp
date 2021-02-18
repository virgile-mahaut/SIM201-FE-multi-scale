#include "matrice_new.hpp"
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


matrice_profil :: matrice_profil(int dl, int dc){

  dim_l = dl;
  dim_c = dc;
  profil.resize(0);
  val_.resize(0);
  nbr_coef.resize(0);
  nbr_val = 0;
  for(int i=0; i<dl; i++){
      nbr_coef.push_back(0);
      profil.push_back(0);
  }
}

matrice_profil :: matrice_profil(const matrice_profil& M){
    dim_l = M.diml();
    dim_c = M.dimc();
    profil.resize(0);
    val_.resize(0);
    nbr_coef.resize(0);
    nbr_val = M.nbr_val;
    
    for(int i=0; i<M.val_.size(); i++){
        val_.push_back(M.val_[i]);
    }
    for(int i=0; i<M.profil.size(); i++){
        profil.push_back(M.profil[i]);
    }
    for(int i=0; i<M.nbr_coef.size(); i++){
        nbr_coef.push_back(M.nbr_coef[i]);
    }
    
}


matrice_profil& matrice_profil :: Id(){
    if (dim_c != dim_l){
        stop_mat("ON NE PEUT PAS TRANSFORMER UNE MATRICE RECTANGULAIRE EN L'IDENTITE");
    }

    val_.resize(dim_c);
    profil.resize(dim_c);
    nbr_coef.resize(dim_c);

  vector<float> :: iterator itv;
  itv = val_.begin();
  vector<int> :: iterator itp;
  itp = profil.begin();
  vector<int> :: iterator itnb;
  itnb = nbr_coef.begin();

  nbr_val = dim_c;

  for(int i=1; i<= dim_c; i++){
    *itv = 1;
    *itp = i;
    *itnb = i;

    itv++;
    itp++;
    itnb++;}    

    return *this;
}


float matrice_profil :: operator()(int i, int j) const{
  if (i>dim_l || i<=0){
        stop_mat("INDICE DE LIGNE INCORRECT");
  }
  else if (j>dim_c || j<=0){
        stop_mat("INDICE DE COLONNE INCORRECT");
  }

  if(i>=j){

    int debut_ligne = profil[i-1];
    if(debut_ligne == 0){ //verifie si la ligne i est vide, alors M(i,j) vaut 0
      return 0;
    }

    else{
    
    
      if (i==1){
        return val_[j-debut_ligne];
      }

      else{
        if( j< debut_ligne){
          return 0;
        }
        else{
          return val_[nbr_coef[i-2] + j-debut_ligne];
        }
    }

  }
}
else{
  return (*this)(j,i);
}

}



/*void matrice_profil :: operator()(int i, int j, float coef){
  if (i>dim_l || i<=0){
        stop_mat("INDICE DE LIGNE INCORRECT");
  }
  else if (j>dim_c || j<=0){
        stop_mat("INDICE DE COLONNE INCORRECT");
  }

  if (i>= j)
  {
  int debut_ligne = profil[i-1];

    if (i==1){ //pour une question d'indicage dans les formules, on traite le cas de la première ligne à part

      if(debut_ligne == 0){ //si la première ligne n'est constituée que de zéro
        nbr_val = nbr_val + 1;
        profil[i-1] = j;
        val_.insert( val_.begin(), coef );//la matrice est stocké en triangulaire inférieur, pas besoin de compléter par des zéros la fin de la ligne

        for(int k = i-1; k<nbr_coef.size();k++){
          nbr_coef[k] = nbr_coef[k] + 1;
        }
      }
      else if(debut_ligne != 0){ //je prejère bien spécifier dans le else dans quel cas on est pour ne pas pedre le fil dans le code
        if( j< debut_ligne){
          nbr_val = nbr_val + 1;
          val_.insert( val_.begin(), coef );
          profil[i-1] = j;
          for(int k = i-1; k<nbr_coef.size();k++){
            nbr_coef[k] = nbr_coef[k] + 1;
            }
        }
        else if (j>= debut_ligne){
          val_[j-debut_ligne] = coef;
          }
      }
    }

    else if (i!=1){
      if(debut_ligne == 0){ //si la ligne i n'est constitué que de zéro
        nbr_val = nbr_val + 1;
        profil[i-1] = j;
        val_.insert( val_.begin() + nbr_coef[i-2] + 1, coef );
        for(int k=j+1; k< debut_ligne;k++){
          val_.insert( val_.begin() + nbr_coef[i-2] + 2, 0  );
        }
        for(int k = i-1; k<nbr_coef.size();k++){
          nbr_coef[k] = nbr_coef[k] + 1;
        }
      }

      else if(debut_ligne != 0){
        if( j< debut_ligne){
          nbr_val = nbr_val + 1;
          profil[i-1] = j;
          val_.insert( val_.begin() + nbr_coef[i-2] , coef );
          for(int k=j+1; k< debut_ligne;k++){
            val_.insert( val_.begin() + nbr_coef[i-2] + 1, 0  );
          }
          for(int k = i-1; k<nbr_coef.size();k++){
            nbr_coef[k] = nbr_coef[k] + 1;
          }

      }

      else if(j>= debut_ligne){
          if (val_[nbr_coef[i-2] + j-debut_ligne] != 0){//si le nombre modifié est un zéro, alors le nombre de coefficient non nul augmente
            for(int k = i-1; k<nbr_coef.size();k++){
              nbr_coef[k] = nbr_coef[k] + 1;
          }
          }
          val_[nbr_coef[i-2] + j-debut_ligne]=coef;
        }

      }
         


    }
  }

  else if (i<j){
    (*this)(j,i,coef);
  }
  


}*/

void matrice_profil :: operator()(int i, int j, float coef){

  if (i>dim_l || i<=0){
        stop_mat("INDICE DE LIGNE INCORRECT");
  }
  else if (j>dim_c || j<=0){
        stop_mat("INDICE DE COLONNE INCORRECT");
  }

  if (i>= j)
  {

    vector<float> nv_val_;
    nv_val_.resize(0);

    vector<int> nv_profil;
    nv_profil.resize(dim_l);

    bool ajout = false;

    for(int n=1; n<dim_l+1; n++){
      
      if (n != i){
        nv_profil[n-1] = profil[n-1];
        for(int m = profil[n-1]; m<=n;m++){
          nv_val_.push_back((*this)(n,m));}
      }

      else if (n == i){
          
        if (j<profil[n-1]){
          if (coef != 0){
            nv_profil[n-1] = j;
            ajout = true; //on garde en memoire le fait qu'on a ajouté une valeur a val et que nbr_ceof va changer
            nv_val_.push_back(coef);
            for (int l = j+1; l<profil[i-1]; l++){
              nv_val_.push_back(0);
            }
            for (int l = profil[n-1]; l<=n; l++){
              nv_val_.push_back((*this)(n,l));
            }
          }

        }
        else if(j>= profil[n-1]){
          nv_profil[n-1] = profil[n-1];
          for (int l = profil[n-1]; l<=n; l++){
            if (l != j){
              nv_val_.push_back((*this)(n,l));
            }
        
            else if(l ==j ){
              nv_val_.push_back(coef);
            }

          }
        }
      }

    }

  val_.resize(nv_val_.size());
  for (int s=0; s<nv_val_.size();s++){
    val_[s] = nv_val_[s];
  }

  for (int s=0; s<nv_profil.size();s++){
    profil[s] = nv_profil[s];
  }

  if (ajout == true){
    for(int z=1; z<dim_l+1; z++){
      if(z<i){
        nbr_coef[z-1] = nbr_coef[z-1];
      }
      else{
        nbr_coef[z-1] = nbr_coef[z-1]+1;
      }
      int a = nbr_coef[z-1];
    }
}



  


  }
  else if (j>i){
    (*this)(j,i,coef);
  }

}




