#include <iostream>
#include <queue>
#include <vector>
using namespace std;

enum err {BAD_INPUT=0xf};

class vertex;

class node {
    public:
        int w;
        vertex* v, *prev;
        node (int _w=0, vertex* _v=NULL, vertex* _prev=NULL) : w(_w), v(_v),prev(_prev) {}
        inline friend bool operator> (const node& a, const node& b) { return a.w > b.w; }
        node operator+ (int n) {return node(w+n,v,prev);}
};

class vertex {
    vertex * prev;
    int d;
    public:
    static int n;
    int id;
    vector <node> v;
    vertex () : prev(NULL), d(-1), id(n++) {}

    friend int dijkstra (vertex* a, const vertex* b);
    friend void undopath(vertex *p);
};

int vertex::n=0;

int dijkstra (vertex* a, const vertex* b) {
    priority_queue <node, vector <node>, greater <node> > q;
    q.push(node(0,a));
    while (!q.empty()) {
        node n = q.top(); q.pop();
        if (n.v->d!=-1) continue;
        n.v->prev=n.prev;
        n.v->d=n.w;
        if (n.v==b) return n.w;
        for (auto i : n.v->v) q.push(i+n.w);
    }
    return -1;
}

void undopath (vertex *p) {
    if (p->prev==NULL) cout << p->id;
    else  {
        undopath(p->prev);
        cout << '-' << p->id;
    }
}

int main () {
    try {
        cout << "Number of vertices: ";
        int n;
        cin >> n;
        vector <vertex> v (n);
        cout << "Number of edges: ";
        int e;
        cin >> e;
        cout << "Input the " << e << " edges in the format: \" a b w\" where a \
and vertices and w is the weight of the edge. \
(a & b must be numbers betwen 0 and " << e-1 << ')' << endl;
        while (e--) {
            int a,b,w;
            cin >> a >> b >> w;
            if (a <0 or a >= n or b < 0 or a >= n) throw BAD_INPUT;
            v[a].v.push_back(node (w,&v[b],&v[a]));
            v[b].v.push_back(node (w,&v[a],&v[b]));
        }
        cout << "Input the two vertices to find a path using dijkstra" << endl;
        int a,b;
        cin >> a >> b;
        int r = dijkstra(&v[a],&v[b]);
        if (r>=0) {
            cout << "Lenght of path: "<< r << endl;
            cout << "Path: ";
            undopath(&v[b]);
            cout << endl;
        } else cout << "No connection between given vertices" << endl;
    } catch (err error) {
        if (error == BAD_INPUT) cerr << BAD_INPUT << endl;
    } catch (exception& e) {
        cerr << "Exception catched: " << e.what() << endl;
    } catch (...) {
        cerr << "Unknown exception catched" << endl;
    }
}
