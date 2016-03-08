#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.14159265359

class deg {

    double D;

    public:
    
    deg (double _r): D(_r) {}

    double rad () {return (D%360.0)*PI/180.0;}
    double d () {return D;}

    void simplify () {D%=360.0;}
};

template <class T>
class vect {

    T X,Y;

    public:

    vect ( T _x, T _y ): X(_x), Y(_y) {}
    vect ( T w, deg <double> d ) {
        X = sin(d.rad())*w;
        Y = cos(d.rad())*w;
    }

    T w() {return sqrt(X*X+Y*Y);}
    deg deg() {return atan(Y/X);}
    T x() {return X;}
    T y() {return Y;}

    vect operator+ (const vect& v) { return vect(X+v.X,Y+v.Y); }
    vect operator- (const vect& v) { return vect(X-v.X,Y-v.Y); }
    vect operator+ (const T& t) { return vect(w()+t,deg()); }
    vect operator- (const T& t) { return vect(w()-t,deg()); }
    T operator* (const vect& v) { return X*v.X + Y*v.Y; } // Dot product
    T operator% (const vect& v) { return X*v.Y - Y*v.X; } // Cross product

    void operator+= (const vect& v) { X+=v.X; Y+=v.Y; }
    void operator-= (const vect& v) { X-=v.X; Y-=v.Y; }
    void operator+= (const T& t) { *this = vect(w()+t,deg()); }
    void operator-= (const T& t) { *this = vect(w()-t,deg()); }
};

template <class T>
class line {

    T A, B, C; // Ax + By = C

    public:

    line (T a, T b, T c): A(a), B(b), C(c) {}
    line (const coord<T>& a, const coord<T>& b) {
        A = b.y-a.y;
        B = a.x-b.x;
        C = A*a.x + B*a.y;
    }
    line (T m, T n) {
    }

    T m () { return A/B; }
    T n () { return -C/B; }
};

