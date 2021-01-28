#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "projet.hpp"
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
	resize(4);
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


void Maillage::lecture_msh(){
	ifstream maillage("geomCarre.msh"); // to modify depending on the repository

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
		list<Triangle>::iterator itt = triangles.begin();
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

void Maillage::affiche(){
	cout<<"sommets : ("<<sommets.size()<<" sommets)\n";
	vector<Point>::iterator its=sommets.begin();
	int i=1;
	for (;its!=sommets.end();its++,i++){
		cout<<"sommet "<<i<<" : "<<(*its)<<" Reference : "<<(*its).reference<<endl;
	}
	cout<<"triangles : ("<<triangles.size()<<" triangles)\n";
	list<Triangle>::iterator itt=triangles.begin();
	i=1;
	for (;itt!=triangles.end();itt++,i++){
		cout<<"Triangle "<<i<<" : "<<(*itt)<<" Reference : "<<(*itt).reference<<endl;
	}
}