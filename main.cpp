#include <iostream>
#include "graphs.h"
#include "fractions.h"
#include "geometry.h"
using namespace std;

int func (int n) {return n^2;}

int main () {
    // Sample usage
    try {
        int n;
        adj<unsigned long long>::simple = false;
        cin >> n;
        adj <unsigned long long> mat (n);
        cin >> mat;
        cout << "Matrix" << endl << mat << endl;
        cout << "Prim" << endl << mat.prim() << endl;
        cout << "Kruskal" << endl << mat.kruskal() << endl;
        unsigned long long a,b;
        cout << "Dijkstra" << endl << "Input dijkstra points (start at 0): ";
        cin >> a >> b;
        if (cin.fail()) throw error::INVALID_INPUT;
        if ( a >= mat.size() or b >= mat.size() ) throw error::OUT_OF_BOUNDS;
        cout << "Minimum distance from " << a << " to " << b << " = "<< mat.dijkstra(a,b) << endl;
    } catch (error::graphs e) {
        cerr << "ERROR " << e << ": ";
        if (e == error::INVALID_INPUT) cerr << "INVALID INPUT" << endl;
        else if (e == error::ERR_READ_FILE) cerr << "CANT OPEN FILE" << endl;
        else if (e == error::NOT_SIMPLE_DIRECTED) cerr << "GRAPH IS DIRECTED, NOT SIMPLE, INVALID INPUT" << endl;
        else if (e == error::NOT_SIMPLE_LOOP) cerr << "GRAPH HAS VERTEXS WITH CONNECTIONS TO THEMSELVES, NOT SIMPLE, INVALID INPUT" << endl;
        else if (e == error::INV_COORD) cerr << "INVALID COORDINATE" << endl;
        else if (e == error::INV_MEM) cerr << "INVALID MEMORY REFERENCE" << endl;
        else if (e == error::NOT_CONNECTED) cerr << "NOT NOT CONNECTED" << endl;
        else if (e == error::OUT_OF_BOUNDS) cerr << "POSITION OUT OF BOUNDS" << endl;
        return e;
    } catch (...) {
        cerr << "Got Unknown exception, exiting" << endl;
        return 0xfe;
    }
    try {
        long a, b;
        cin >> a >> b;
        frac f (a,b);
        cout << f << endl;
        frac f2;
        cin >> f2;
        cout << f2 << endl;
        cout << f2.invert().runfunc(func) << endl;
    } catch (error::frac e) {
        if (e == error::DEN_EQ_0) cerr << 'E' << error::DEN_EQ_0 <<": Denominator is 0." << endl;
        if (e == error::INVALID_FRACTION_INPUT) cerr << 'E' << error::INVALID_INPUT <<": Invalid inputstream separator." << endl;
        if (e == error::INVALID_SEPARATOR) cerr << 'E' << error::INVALID_SEPARATOR <<": Invalid fraction separator." << endl;
        if (e == error::INVALID_USEPARATOR) cerr << 'E' << error::INVALID_USEPARATOR <<": Invalid unproper fraction separator." << endl;
        return e;
    } catch (...) {
        cerr << "Unknown error" << endl;
        return 0;
    }
}
