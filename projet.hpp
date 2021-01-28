#ifndef __projet_H__
#define __projet_H__
#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Point{
 private:
 	double x, y;
 public:
    int reference;
 	Point(double a=0, double b=0, int ref=0):x(a),y(b),reference(ref){}
 	Point(const Point& P):x(P.x),y(P.y){}
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
	void lecture_msh();
	Maillage(){lecture_msh();}
    void affiche();
};

#endif