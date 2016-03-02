#include <iostream> 
#include <vector>
using namespace std;

/*  Coordinate class
 *
 *  - access vector matrix members at coord with operator()
 *  - ! postfix operator adds to y and prefix to x
 *  - if limits defined (bool lim set to yes) if there is an overflow it will
 *      go to the next row and viceversa (see the check() behaviour)
 *  - runfunc allows to run any func to the both coordinates
 *  - apply flag sets if the changes should be applied, it can be used with:
 *      - runfunc()
 *      - swap()
 *      - operate()
 *  - supports typecast to pair  
 *  - supports i/o from stream
 *  - suports some common operators, if need of a custom operation you can use 
 *      runfunc()
 *  - you can swap the two coordinates using swap
 *  - you can addition two different values to the coordinates using operate
 */

template <class T>
class coord {

    bool lim;

    T lx,ly;
    T mx,my;

    void check () {
        if (!lim) return;
        while ( x>=mx or y>=my ) {
            if (x >= mx) { x=lx; y++; }
            if (y >= my) { y=ly; }
        }
        while ( x<lx or y<ly ) {
            if (x < lx) { x=mx-1; y--; }
            if (y < ly) { y=my-1; }
        }
    }

public:

    T x,y;

    coord (T _x=0, T _y=0) : x(_x), y(_y), lx(0),ly(0),mx(0),my(0),lim(0) {}

    void limits(T _mx, T _my, T _lx=0, T _ly=0) {
        mx = _mx; my = _my;
        lx = _lx; ly = _ly;
        lim = true;
    }
    template <class U>
    void limits(vector <vector <U> >& v) {mx=v.size(); my=v[0].size();};

    coord operator++ () {
        x++; check();
        return *this;
    }
    coord operator++ (int) {
        y++; check();
        return *this;
    }
    coord operator-- () {
        x--; check();
        return *this;
    }
    coord operator-- (int) {
        y--; check();
        return *this;
    }

    operator pair<T,T>() {return pair <T,T> (x,y);}

    bool operator== (const coord& c) {return (c.x==x and c.y==y);}
    bool operator!= (const coord& c) {return (c.x!=x or c.y!=y);}

    coord operator+ (const coord& c) {return coord(x+c.x,y+c.y);}
    coord operator- (const coord& c) {return coord(x-c.x,y-c.y);}
    coord operator+ (const T& f) {return coord(x+f,y+f);}
    coord operator- (const T& f) {return coord(x-f,y-f);}
    coord operator* (const coord& c) {return coord(c.x*x,c.y*y);}
    coord operator/ (const coord& c) {return coord(c.x/x,c.y/y);}
    coord operator* (const T& f) {return coord(x*f,y*f);}
    coord operator/ (const T& f) {return coord(x/f,y/f);}

    coord operator+= (const coord& c) { x=x+c.x;y=y+c.y; return *this;}
    coord operator-= (const coord& c) {x=x-c.x;y=y-c.y; return *this;}
    coord operator+= (const T& f) {x=x+f;y=y+f; return *this;}
    coord operator-= (const T& f) {x=x-f;y=y-f; return *this;}
    coord operator*= (const coord& c) {x=c.x*x;y=c.y*y; return *this;}
    coord operator/= (const coord& c) {x=c.x/x;y=c.y/y; return *this;}
    coord operator*= (const T& f) {x=x*f;y=y*f; return *this;}
    coord operator/= (const T& f) {x=x/f;y=y/f; return *this;}

    coord operator= (const coord& c) {x=c.x; y=c.y; if (c.lim) {lim=1; mx=c.mx; my=c.my; lx=c.lx; ly=c.ly;}}

    coord runfunc (T(*func)(T),bool apply=0) {if (apply) {x=func(x); y=func(y); check(); return *this;} return coord(func(x),func(y));}
    coord swap(bool apply=0) {if (apply) {swap(x,y); check(); return *this;} return coord(y,x);}

    coord operate (T a, T b, bool apply=1) {
        if (apply) { x+=a; y+=b; check(); return coord(x,y); }
        return coord(x+a,y+b);
    }

    friend ostream& operator<< (ostream& out, const coord& c) {
        out << '(' << c.x << ',' << c.y <<')';
        return out;
    }

    friend istream& operator>> (istream& in, coord& c) {
        in >> c.x >> c.y;
        return in;
    }

    template <class U>
    T& operator() (vector <vector <U> >& v) {return v[x][y];}
};
