#include <iostream>
#include <sstream>
using namespace std;

enum err {DEN_EQ_0};

template <class T>
class frac {

    T N, D;
    T GCD;

public:

    frac () {}
    frac (const T& n, const T& d) : N(n), D(d) {simplify();}

    void invert () { N ^= D; D ^= N; N ^= D; }
    double aprox () const { return N/D; }

    inline frac operator+ (const frac& f) const { return frac(N+f.N,D+f.D); }
    inline frac operator- (const frac& f) const { return frac(N-f.N,D-f.D); }
    inline frac operator* (const frac& f) const { return frac(N*f.N,D*f.D); }
    inline frac operator/ (const frac& f) const { return frac(N*f.D,D*f.N); }

    inline frac operator+= (const frac& f) { *this = *this + f; }
    inline frac operator-= (const frac& f) { *this = *this - f; }
    inline frac operator*= (const frac& f) { *this = *this * f; }
    inline frac operator/= (const frac& f) { *this = *this / f; }

    inline bool operator== (const frac& f) const { return (N==f.N and D==D.N); }
    inline bool operator>= (const frac& f) const { return (aprox() >= f.aprox()); }
    inline bool operator<= (const frac& f) const { return (aprox() <= f.aprox()); }
    inline bool operator< (const frac& f) const { return (aprox() < f.aprox()); }
    inline bool operator> (const frac& f) const { return (aprox() > f.aprox()); }

    friend ostream& operator<< (ostream& out, const frac& f) {
        out << f.N << '/' << f.D;
        return out;
    }
    friend istream& operator>> (istream& in, const frac& f) {
        string s;
        in >> s;
        for (int i = 0; i < s.size(); i++) {
            if (s[i]=='/') {s[i]=' '; break;}
        }
        stringstream ss;
        ss << s;
        ss >> f.N >> f.D;
        f.simplify();
        return in;
    }

    frac runfunc(T (*func)(T)) const { return frac(func(N),func(D)); }

    T n() {return N;}
    T d() {return D;}
    T gcd() {return GCD;}

    bool simplify () {
        if (N > 0 and  D < 0) {N*=-1; D*=-1;}
        else if ( N < 0 and D < 0 ) {N*=-1; D*=-1; }
        if (D == 0) throw DEN_EQ_0;
        GCD = egcd(N,D);
        N /= GCD;
        D /= GCD;
        return true;
    }
};

int main () {
    frac <long> f;
    cin >> f;
    cout << f;
}
