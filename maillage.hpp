#ifndef __MAILLAGE_H__
#define __MAILLAGE_H__
#include <iostream>
#include <vector>
#include <list>
#include "vecteur.hpp"
#include "matrice.hpp"
#include "EF_principal.hpp"
using namespace std;

typedef double (*pf)(double,double);
// pointeur d'une fonction double f(double, double)

class Point{
 public:
 	double x, y, u; // u = u(x,y) pour la solution u
    int reference; // vaut 1 si le point est sur le bord du maillage
    bool grossier=false; // vrai si le point appartient au maillage grossier (seulement pour les sous-maillages)
 	Point(double a=0, double b=0, int c=0, int ref=0, bool grossier=false):x(a),y(b),u(c),reference(ref), grossier(grossier){}
 	Point(const Point& P):x(P.x),y(P.y),u(P.u){}
 	Point& tf_affine(const vector<double>& A, const vector<double>& t);
    bool operator ==(const Point& P){return ((P.x==x)&&(P.y==y));}
    bool operator !=(const Point& P){return !((*this)==P);}
    Point& operator +=(const Point& P);
    Point& operator -=(const Point& P);
    Point& operator *=(double d);
    Point& operator /=(double d);
    friend ostream& operator <<(ostream& out, const Point& P);
};

Point operator +(const Point& p, const Point& q);
Point operator -(const Point& p, const Point& q);
Point operator *(const Point& p, double d);
Point operator *(double d, const Point& p);
Point operator /(const Point& p, double d);

class Triangle : public vector<int>{
// contient les numéros (références) associées à chaque sommet
 public:
    int reference;
    Triangle(int a=0, int b=0, int c=0, int ref=0);
    int operator ()(int i) const{return (*this)[i-1];}
    int& operator()(int i) {return (*this)[i-1];}
    Triangle shift(int s) const;
    friend ostream& operator<<(ostream& out, const Triangle& N);
};

vector<int> stovi(string& str);

class Maillage{
 public:
	vector<Point> sommets;
	list<Triangle> triangles;
    vector<int> P_;
	void lecture_msh(string nomFichier);
    void profil();
	void assemblage();
    Maillage(){}
    Maillage(const Maillage& M):sommets(M.sommets),triangles(M.triangles),P_(M.P_) {}
	Maillage(string nomFichier){lecture_msh(nomFichier); profil();} 
    void fusion(const list<Maillage>& SM);
    void output() const;
    void affiche() const;
};

vecteur transforme_f(Maillage& M, pf f);
list<Maillage> sous_maillage(Maillage& M);
#endif
