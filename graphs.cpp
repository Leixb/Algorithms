#include <iostream>
#include <limits>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#define INF numeric_limits<T>::max()

enum err {INVALID_INPUT=0xff, ERR_READ_FILE, NOT_CONNECTED, NOT_SIMPLE_DIRECTED, NOT_SIMPLE_LOOP, INV_MEM, INV_COORD, OUT_OF_BOUNDS};

struct coord {
    size_t x,y;
    coord (size_t _X=0, size_t _Y=0): x(_X), y(_Y) {}

    bool operator== (const coord& c2) const {return (c2.x==x and c2.y==y);}
};

struct edge {
    size_t w, a, b;
    edge (size_t W, size_t A, size_t B):  w(W), a(A), b(B) {}
};

struct comp { bool operator() (edge e1, edge e2) { return e1.w > e2.w; } };

template <class T>
class adj {

    static const bool simple = true;
    mutable vector <bool> fetsbfs;

    public:

    vector <vector <T> > v;

    adj (size_t N=0) { v = vector <vector <T> > (N, vector <T> (N,0)); }

    vector <T>& operator[] (const size_t& p) { if (p < v.size()) return v[p]; else throw INV_MEM; }
    T& operator[] (const coord& p) { if(p.x < v.size() and p.y < v.size()) return v[p.x][p.y]; else throw INV_MEM; }
    T& operator[] (const edge& e) { if(e.a < v.size() and e.b < v.size()) return v[e.a][e.b]; else throw INV_MEM; }
    
    size_t size() { return v.size(); }

    friend ostream& operator<< (ostream& out, const adj& mat) {
        for (size_t i = 0; i < mat.v.size(); i++) {
            for (size_t j = 0; j < mat.v[i].size(); j++) {
                if (j!=0) cout << ' ';
                cout << mat.v[i][j];
            }
            cout << endl;
        }
        return out;
    }

    friend istream& operator>> (istream& in, adj& mat) {
        size_t c = 0;
        string s;
        getline(in,s);
        stringstream ss (s);
        while (ss >> s) c++;
        mat = adj <T> (c);
        in.seekg(0);
        for (size_t i = 0; i < mat.v.size(); i++)
            for (size_t j = 0; j < mat.v[i].size(); j++) if (!(in >> mat.v[i][j])) throw INVALID_INPUT;
        if (in.fail()) throw INVALID_INPUT;
        if (adj::simple) mat.check();
        return in;
    }

    bool bfs (size_t b, const size_t& e, bool flag=1) const {
        if (flag) fetsbfs = vector <bool> (v.size(),false);
        if (b == e) return true;
        if (fetsbfs[b]) return false;
        fetsbfs[b]=true;
        for (size_t i = 0; i < v.size(); i++)
            if (v[b][i]!=0) if (bfs(i,e,0)) return true;
        return false;
    }

    adj kruskal () const { 
        priority_queue <edge,vector <edge>, comp > q; 
        for (size_t i = 0; i < v.size(); i++) for (int j = i+1; j < v.size(); j++) q.push(edge(v[i][j],i,j));
        adj <T> mat (v.size());
        size_t c = 0;
        while (!q.empty()) {
            edge ed = q.top(); q.pop();
            if (c == v.size()-1) return mat;
            if (ed.w != 0) 
                if (!mat.bfs(ed.a,ed.b)) {
                    mat[ed.a][ed.b] = ed.w;
                    mat[ed.b][ed.a] = ed.w;
                    c++;
                }   
        }
        throw NOT_CONNECTED;
    }

    adj prim () const {
        priority_queue <edge,vector <edge>, comp> q; 
        for (size_t i = 1; i < v.size(); i++) q.push(edge(v[0][i],0,i));
        adj <T> mat (v.size());
        vector <bool> fets (v.size(),false);
        size_t c = 0;
        fets[0]=true;
        while (!q.empty()) {
            edge ed = q.top(); q.pop();
            if (c == v.size()-1) return mat;
            if (!fets[ed.b] and ed.w != 0) {
                mat[ed.a][ed.b] = ed.w;
                mat[ed.b][ed.a] = ed.w;
                c++;
                fets[ed.b] = true;
                for (size_t i = 0; i < v.size(); i++) q.push(edge(v[ed.b][i],ed.b,i));
            }
        }
        throw NOT_CONNECTED;
    }

    T dijkstra (size_t b, const size_t& e) const {
        vector <T> d (v.size(), INF);
        d[b]=0;
        priority_queue <pair <T, size_t>, vector <pair <T, size_t> >, greater<pair<T,size_t> > > q;
        q.push(pair <T, size_t> (0,b));
        while (!q.empty()) {
            size_t pos = q.top().second; 
            if (q.top().first > d[pos]) {
                q.pop();
                continue;
            }
            if (pos == e) return d[pos];
            q.pop();
            for (size_t i = 0; i < v.size(); i++)
                if (v[pos][i]!=0 and d[i] > d[pos] + v[pos][i]) {
                    d[i] = d[pos] + v[pos][i];
                    q.push(pair <T, size_t> (d[i],i));
                }
        }
        throw NOT_CONNECTED;
    }

    T weight () const {
        T c = 0;
        for (int i = 0; i < v.size(); i++) 
            for (int j = 0; j < v[i].size(); j++) c += v[i][j];
        return (simple)? c/2 : c;
    }

    private:

    bool check () const {
        for (size_t i  = 0; i < v.size(); i++)
            for (size_t j = 0; j < v[i].size(); j++) if (v[i][j] != v[j][i]) throw NOT_SIMPLE_DIRECTED;
        for (size_t i = 0; i < v.size(); i++) if (v[i][i] != 0) throw NOT_SIMPLE_LOOP;
        return true;
    }
};

int main () {
    try {
        fstream file;
        file.open("in.txt");
        if (!file.good()) throw ERR_READ_FILE;
        adj <unsigned long long> mat;
        file >> mat;
        file.close();
        cout << "Matrix" << endl << mat << endl;
        cout << "Prim" << endl << mat.prim() << endl;
        cout << "Kruskal" << endl << mat.kruskal() << endl;
        unsigned long long a,b;
        cout << "Dijkstra" << endl << "Input dijkstra points (start at 0): ";
        cin >> a >> b;
        if (cin.fail()) throw INVALID_INPUT;
        if ( a >= mat.size() or b >= mat.size() ) throw OUT_OF_BOUNDS;
        cout << "Minimum distance from " << a << " to " << b << " = "<< mat.dijkstra(a,b) << endl;
    } catch (err e) {
        cerr << "ERROR " << e << ": ";
        if (e == INVALID_INPUT) cerr << "INVALID INPUT" << endl;
        else if (e == ERR_READ_FILE) cerr << "CANT OPEN FILE" << endl;
        else if (e == NOT_SIMPLE_DIRECTED) cerr << "GRAPH IS DIRECTED, NOT SIMPLE, INVALID INPUT" << endl;
        else if (e == NOT_SIMPLE_LOOP) cerr << "GRAPH HAS VERTEXS WITH CONNECTIONS TO THEMSELVES, NOT SIMPLE, INVALID INPUT" << endl;
        else if (e == INV_COORD) cerr << "INVALID COORDINATE" << endl;
        else if (e == INV_MEM) cerr << "INVALID MEMORY REFERENCE" << endl;
        else if (e == NOT_CONNECTED) cerr << "NOT NOT CONNECTED" << endl;
        else if (e == OUT_OF_BOUNDS) cerr << "POSITION OUT OF BOUNDS" << endl;
        return e;
    } catch (...) {
        cerr << "Got Unknown exception, exiting" << endl;
        return 0xfe;
    }
}