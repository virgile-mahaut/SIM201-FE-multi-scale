#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "maillage.hpp"
#include "EF_principal.hpp"
#include "mat_elem.hpp"
using namespace std;

//================================================================
//               class Point
//================================================================
Point& Point::tf_affine(const vector<double>& A, const vector<double>& t){
	// transformation affine (x,y) -> t + (x,y)A
	double tmp=x;
	x=t[0]+A[0]*x+A[2]*y;
	y=t[1]+A[1]*tmp+A[3]*y;
	return *this;
}

Point& Point::operator +=(const Point& P){
	x+=P.x; y+=P.y;
	return *this;
}
Point& Point::operator -=(const Point& P){
	x-=P.x; y-=P.y;
	return *this;
}
Point& Point::operator *=(double d){
	x*=d; y*=d;
	return *this;
}
Point& Point::operator /=(double d){
	x/=d; y/=d;
	return *this;
}

ostream& operator <<(ostream& out, const Point& P){
	out<<"("<<P.x<<","<<P.y<<")";
	return out;
}


Point operator +(const Point& p, const Point& q){
	Point z(p);
	return z+=q;
}
Point operator -(const Point& p, const Point& q){
	Point z(p);
	return z-=q;
}
Point operator *(const Point& p, double d){
	Point z(p);
	return z*=d;
}
Point operator *(double d, const Point& p){
	return p*d;
}
Point operator /(const Point& p, double d){
	Point z(p);
	return z/=d;
}

//===============================================================
//                 class Triangle
//===============================================================

Triangle::Triangle(int a, int b, int c,int ref){
	resize(3);
	(*this)[0]=a;(*this)[1]=b;(*this)[2]=c;
	reference=ref;
}

Triangle Triangle::shift(int s) const{
	Triangle N;
	N.resize(3);
	vector<int>::const_iterator it;
	int i=0;
	for(it=this->begin(); it!=this->end(); it++,i++)
		N[i]=(*this)[i]+s;
	return N;
}

ostream& operator<<(ostream& out, const Triangle& N){
	out<<"[";
	for (uint i=0;i<N.size()-1; i++)
		out<<N[i]<<" ";
	out<<N[N.size()-1]<<"]";
	return out;
}

//===============================================================
//                 class Maillage
//===============================================================


vector<int> stovi(string& str){
	// string to vector<int>
	vector<int> vi;
	string::iterator it;
	bool reading=true;
	for (it=str.begin();it!=str.end();){
		if (reading){
			vi.push_back(stoi(str));
			reading=false;
		}
		if (*it==' ') reading=true;
		if (it!=str.end()-1)
			str.erase(it);
		else
			it++;
	}
	return vi;
}


void Maillage::lecture_msh(string nomFichier){
	ifstream maillage(nomFichier); // to modify depending on the repository

	if (maillage){
		string ligne;
		do{
			getline(maillage,ligne);
		} while (ligne.compare("$Nodes")!=0);
		getline(maillage,ligne);
		int Nbpt=stoi(ligne);
		sommets.resize(Nbpt);
		vector<int> RefneuBis(Nbpt);
		// lecture des sommets
		for (uint i=0; i< sommets.size(); i++){
			getline(maillage, ligne);
			string::iterator it=ligne.begin();
			double x,y;
			while(*it!=' ') ligne.erase(it);
			ligne.erase(it); x=stod(ligne);
			while(*it!=' ') ligne.erase(it);
			ligne.erase(it); y=stod(ligne);
			sommets[i]=Point(x,y);
		}
		// lecture points, segments, triangles
		do{
			getline(maillage,ligne);
		} while (ligne.compare("$Elements")!=0);
		getline(maillage,ligne);
		uint Nbtri = stoi(ligne);
		getline(maillage,ligne);
		vector<int> tmp = stovi(ligne);
		int test = tmp[1];
		while ((test!=15)&&(test!=1)&&(test!=2)){
			getline(maillage,ligne);tmp=stovi(ligne); 
			test=tmp[1]; Nbtri--;
		}
		// on traite les noeuds des coins
		while ((test!=1)&&(test!=2)){
			sommets[*(tmp.end()-1)].reference=*(tmp.end()-3);
			getline(maillage,ligne);tmp=stovi(ligne);
			test=tmp[1]; Nbtri--;
		}
		// on traite les noeuds du bord
		uint k=1;
		while (test!=2){
			RefneuBis[tmp[5]-1]=tmp[3];
			RefneuBis[tmp[6]-1]=tmp[3];
			// aretes si nécessaires
			getline(maillage,ligne);tmp=stovi(ligne);
			test=tmp[1];Nbtri--;k++;
		}
		for(int i=0;i<Nbpt;i++){
			if (sommets[i].reference==0) sommets[i].reference=RefneuBis[i];
		}
		// on traite les références des triangles
		for (int i=0; i<Nbtri-1; i++){
			triangles.push_back(Triangle(*(tmp.end()-3),*(tmp.end()-2),*(tmp.end()-1),*(tmp.end()-4)));
			getline(maillage, ligne); tmp=stovi(ligne);
		}
		triangles.push_back(Triangle(*(tmp.end()-3),*(tmp.end()-2),*(tmp.end()-1),*(tmp.end()-4)));
	}
}


void Maillage::profil(){
	// P_(i) = min{j, 1<=j<i, A_ij not equal 0}
	P_.resize(sommets.size());
	for (int i=0; i< sommets.size(); i++){
		P_[i]=i+1;
	}
	list<Triangle>::iterator itt=triangles.begin();
	for (; itt!=triangles.end();itt++){
		for (int i=0; i<3; i++){
			int ni=(*itt)[i];
			for (int j=0; j<3; j++){
				int nj=(*itt)[j];
				P_[ni-1]=min(P_[ni-1],nj);
			}
		}
	}
}


void Maillage::assemblage(){
	matrice_profil_sym MM(sommets.size(),sommets.size(),P_), 
                       KK(sommets.size(),sommets.size(),P_);
	pf f = F; pf a = A;
    list<Triangle>::const_iterator itt = triangles.begin();
    for (; itt!=triangles.end(); itt++){
        // calcul des matrices élémentaires
		cout<<"1"<<endl;
        matrice_profil_sym Kel = k_elem(sommets[(*itt)[0]-1],sommets[(*itt)[1]-1],sommets[(*itt)[2]-1],*this,a);
		cout<<"2"<<endl;
		matrice_profil_sym Mel = m_elem(sommets[(*itt)[0]-1],sommets[(*itt)[1]-1],sommets[(*itt)[2]-1]);
        cout<<"3"<<endl;
		int i,j,I,J;
        // assemblage des matrices globales
        for (i=1; i<=3; i++){
            I=(*itt)[i-1];
            for (j=1; j<=i; j++){
                J = (*itt)[j-1];
                MM(I,J)+=Mel(i,j);
                KK(I,J)+=Kel(i,j);
            }
        }
    }
	vecteur FF = transforme_f(*this,f); vecteur LL = MM*FF;
	// élimination au bord du domaine
	for (int I=1; I<=sommets.size(); I++){
		if (sommets[I-1].reference == 1){
			for (int J=I+1; J<=sommets.size(); J++){
				if (I >= P_[J-1]) KK(J,I)=0;
			}
			KK(I,I)=1; LL(I)=0;
		}
	}
	cout<<"1"<<endl;
	vecteur UU = resol(KK,LL);
	for (int i=1; i<=UU.dim();i++){
		sommets[i-1].u = UU(i);
	}
	cout<<"2"<<endl;
}


void Maillage::output() const{
	string const nomFichier("output.txt");
	ofstream Flux(nomFichier.c_str());
    if(Flux)    
    {
		Flux<<"sommets"<<endl;
		Flux<<sommets.size()<<endl;
		vector<Point>::const_iterator its=sommets.begin();
		int i=1;
		for (;its!=sommets.end();its++,i++){
			Flux<<i<<" "<<(*its).x<<" "<<(*its).y<<" "<<(*its).u<<endl;
		}
		Flux<<"triangles"<<endl;
		Flux<<triangles.size()<<endl;
		list<Triangle>::const_iterator itt=triangles.begin();
		i=1;
		for (;itt!=triangles.end();itt++,i++){
			Flux<<i<<" "<<(*itt)[0]<<" "<<(*itt)[1]<<" "<<(*itt)[2]<<endl;
		}
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}

void Maillage::affiche() const{
	cout<<"sommets : ("<<sommets.size()<<" sommets)\n";
	vector<Point>::const_iterator its=sommets.begin();
	int i=1;
	for (;its!=sommets.end();its++,i++){
		cout<<"sommet "<<i<<" : "<<(*its)<<" Reference : "<<(*its).reference<<endl;
	}
	cout<<"triangles : ("<<triangles.size()<<" triangles)\n";
	list<Triangle>::const_iterator itt=triangles.begin();
	i=1;
	for (;itt!=triangles.end();itt++,i++){
		cout<<"Triangle "<<i<<" : "<<(*itt)<<" Reference : "<<(*itt).reference<<endl;
	}
	cout<<"Profil"<<endl;
	vector<int>::const_iterator itp = P_.begin();
	i=1;
	for(;itp!=P_.end();itp++,i++){
		cout<<"P_("<<i<<") = "<<(*itp)<<endl;
	}
}

vecteur transforme_f(Maillage& M, pf f){
    // calcule le vecteur (f(M_k))
    vecteur v(M.sommets.size());
    for (int i=0; i<M.sommets.size(); i++){
        v(i+1)=f(M.sommets[i].x,M.sommets[i].y);
    }
    return v;
}

void Maillage::fusion(const list<Maillage>& SM){
	list<Maillage>::const_iterator itm=SM.begin();
	list<Triangle>::const_iterator itt;
	triangles.clear();
	Triangle T;
	int k=0;
	for (; itm!=SM.end(); itm++){
		for (itt=(*itm).triangles.begin(); itt!=(*itm).triangles.end(); itt++){
			T(1) = (*itt)(1)+k; T(2) = (*itt)(2)+k; T(3) = (*itt)(3)+k;
			triangles.push_back(T);
			for (int i=0; i<3; i++){
				if (!((*itm).sommets[(*itt)[i]].grossier)){
					sommets.push_back((*itm).sommets[(*itt)[i]]);
				}
			}
		}
		k+=6;
	}
	profil();
	cout<<"1"<<endl;
}

list<Maillage> sous_maillage(Maillage &M){
    list<Maillage> SM;
    
    list<Triangle>::iterator it; // Iterateur sur une liste de type Triangle
    for (it=M.triangles.begin(); it!=M.triangles.end(); ++it){ // Boucle sur la liste M.triangles
        Maillage M2; M2.sommets.resize(6);

        int A = (*it)[0];    // Numéro du 1er sommet du triangle courant
        int B = (*it)[1];
        int C = (*it)[2];

        // Coordonnees des points A, B, C et ref du triangle courant
        double xA = M.sommets[A].x;
        double yA = M.sommets[A].y;
        int refA = M.sommets[A].reference;

        double xB = M.sommets[B].x;
        double yB = M.sommets[B].y;
        int refB = M.sommets[B].reference;

        double xC = M.sommets[C].x;
        double yC = M.sommets[C].y;
        int refC = M.sommets[C].reference;

        double x;
        double y;
        int ref;
        // Point AB (nouveau point entre A et B)
        x = (xA + xB)/2.; // x_AB = ( x_A + x_B )/2
        y = (yA + yB)/2.;
        ref = 0;
        if (refA == 1 && refB == 1) ref = 1; // ref(AB) = 1 ssi ref(A) = ref(B) = 1
        Point AB(x,y,0,ref);

        // Point AC
        x = (xA + xC)/2.;
        y = (yA + yC)/2.;
        ref = 0;
        if (refA == 1 && refC == 1) ref = 1;
        Point AC(x,y,0,ref);

        // Point BC
        x = (xB + xC)/2.;
        y = (yB + yC)/2.;
        ref = 0;
        if (refB == 1 && refC == 1) ref = 1;
        Point BC(x,y,0,ref);

        // Ajout des points déjà existants
        M2.sommets[0] = M.sommets[A]; M2.sommets[0].grossier = true;
        M2.sommets[1] = M.sommets[B]; M2.sommets[1].grossier = true;
        M2.sommets[2] = M.sommets[C]; M2.sommets[2].grossier = true;
        // Ajout des nouveaux points
        M2.sommets[3] = AB;
        M2.sommets[4] = AC;
        M2.sommets[5] = BC;
        // Nouveaux triangles
        Triangle A2(1,4,5);   // Triangle (A,AB,AC)
        Triangle B2(2,4,6);
        Triangle C2(3,5,6);
        Triangle D2(4,5,6); // Triangle (AB,AC,BC)

        // Ajout des nouveaux triangles 
        M2.triangles.push_back(A2);
        M2.triangles.push_back(B2);
        M2.triangles.push_back(C2);
        M2.triangles.push_back(D2);

		M2.profil();

        SM.push_back(M2);
    }
    return SM;
}