#include <iostream>
#include <set>
#include <vector>
using namespace std;

template <class T>
class dset {

    template <class U>
    struct aux {
        aux<U>* p;
        U d;
        aux (U _d, aux<U>*_p=NULL): d(_d), p(_p) {}
        aux () {}
    };

    vector <aux<T> > v;

    public:
    
    dset (vector <T> _v) {
        v.resize(0);
        for (auto i : _v) v.push_back(aux<T>(i));
        for (int i = 0; i < v.size(); i++) v[i].p = &v[i];
    }

    dset (set <T> s) { 
        vector <T> _v (s.begin(), s.end());
        *this = dset<T>(_v);
    }

    aux <T>& operator[] (const size_t p) {return v[p];}

    aux <T> *find(size_t i) {
        aux <T> * p = v[i].p;
        while (p != p->p) p = p->p;
        return p;
    }

    bool same(size_t a, size_t b=0) { return find(a)==find(b); }

    void unite (size_t a, size_t b = 0) {
        v[a].p = v[b].p;
    }

    size_t size () { return v.size(); }
};
