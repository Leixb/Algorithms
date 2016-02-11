#include <iostream>
#include <sstream>
using namespace std;

enum err {DEN_EQ_0};

//template <class T>
#define T long
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

    inline frac operator+= (const frac& f) { *this = *this + f; return *this; }
    inline frac operator-= (const frac& f) { *this = *this - f; return *this; }
    inline frac operator*= (const frac& f) { *this = *this * f; return *this; }
    inline frac operator/= (const frac& f) { *this = *this / f; return *this; }

    inline bool operator== (const frac& f) const { return (N==f.N and D==f.N); }
    inline bool operator>= (const frac& f) const { return (aprox() >= f.aprox()); }
    inline bool operator<= (const frac& f) const { return (aprox() <= f.aprox()); }
    inline bool operator< (const frac& f) const { return (aprox() < f.aprox()); }
    inline bool operator> (const frac& f) const { return (aprox() > f.aprox()); }

    friend ostream& operator<< (ostream& out, const frac& f) {
        out << f.N << '/' << f.D;
        return out;
    }
    friend istream& operator>> (istream& in, frac& f) {
        string s;
        in >> s;
        T n=1, d=1;
        uint i;
        for (i = 0; i < s.size(); i++) {
            if (s[i]>='0' and s[i]<='9') n=n*10+(s[i]-'0');
            else if (s[i]=='-' and i == 0) n*=-1;
            else break;
        }
        for ( auto j = i; j < s.size(); j++) {
            if (s[j]>='0' and s[j]<='9') d=d*10+(s[j]-'0');
            else if (s[j]=='-' and j==i) d*=-1;
            else break;
        }
        f.simplify();
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
    frac f;
    cin >> f;
}
