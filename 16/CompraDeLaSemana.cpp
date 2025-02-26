#include <iostream>
#include <vector>
#include <algorithm>
#include<queue>
#include<climits>
#include <fstream>

using namespace std;

struct Nodo {
    int prodID;
    int costeAcomulado;
    int costeOptimista;
    int costePesimista;
    vector<int> counterSuper;
};

bool operator>(Nodo a, Nodo b) {
    return a.costeOptimista > b.costeOptimista;
}

typedef priority_queue<Nodo, vector<Nodo>, greater<Nodo>> pq;


// C�lculo de la cota optimista con una heur�stica voraz
int cota_optimista(const int &producto, const int &supers, const vector<vector<int>> &superProducto, const int producIdx) {//O(S*P)
    int costeEstimado = 0;
    vector<int> preciosMinimos(producto, INT_MAX);

    for (int i = 0; i < supers; i++) {
        for (int j = producIdx; j < producto; j++) {
            preciosMinimos[j] = min(preciosMinimos[j], superProducto[i][j]);
        }
    }

    for (int j = producIdx; j < producto; j++) {
         costeEstimado += preciosMinimos[j];
    }

    return costeEstimado;
}

int cota_pesimista(const int& producto, const int& supers, const vector<vector<int>>& superProducto, const int producIdx) {//O(S*P)
    int costeEstimado = 0;
    vector<int> preciosMaximos(producto, INT_MIN);

    for (int i = 0; i < supers; i++) {
        for (int j = producIdx; j < producto; j++) {
            preciosMaximos[j] = max(preciosMaximos[j], superProducto[i][j]);
        }
    }

    for (int j = producIdx; j < producto; j++) {
         costeEstimado += preciosMaximos[j];
    }

    return costeEstimado;
}

int contarBits(int n) {
    int counter = 0;
    while (n) {
        counter += (n & 1); // Suma 1 si el bit menos significativo es 1
        n >>= 1;          // Desplaza bits a la derecha
    }
    return counter;
}


// Backtracking con poda optimista-pesimista
void iterativo(const int &productos, const int &supers, const vector<vector<int>>& superProducto, vector<bool>& carrito, int &costeMejor) {
    pq nodos;
    int cotaOptimista = cota_optimista(productos, supers, superProducto, 0), cotaPesimista = cota_pesimista(productos, supers, superProducto, 0);
    nodos.push({ 0,0, cotaOptimista, cotaPesimista, vector<int>(supers, 0)});
    while (!nodos.empty()) {
        Nodo a = nodos.top(); nodos.pop();
        if (a.prodID == productos) {
            costeMejor = min(a.costeAcomulado, costeMejor);
            break;
        }
        else if (a.costeOptimista <= costeMejor) {
            int prodID = a.prodID;
            for (int i = 0; i < supers; i++) {
                if (a.counterSuper[i] < 3) {          
                    vector<int> counterSuper = a.counterSuper; counterSuper[i]++;
                    int costeAcomulado = a.costeAcomulado + superProducto[i][prodID];
                    int costeOptimista = costeAcomulado + cota_optimista(productos, supers, superProducto, prodID + 1);
                    int costePesimista = costeAcomulado + cota_pesimista(productos, supers, superProducto, prodID + 1);
                    if (cotaOptimista <= costeMejor) {
                        nodos.push({ prodID + 1, costeAcomulado, costeOptimista, costePesimista, counterSuper });
                        if (costePesimista < costeMejor)
                            costeMejor = costePesimista;
                    }
                }
            }
        }
        
    }
}


void solve() {
    int casosDePrueba;
    cin >> casosDePrueba;
    for (int casosPrueba = 0; casosPrueba < casosDePrueba; casosPrueba++) {
        int supers, productos;
        cin >> supers >> productos;
        vector<vector<int>> superProducto(supers, vector<int>(productos));
        for (int i = 0; i < supers; i++) {
            for (int j = 0; j < productos; j++) {
                cin >> superProducto[i][j];
            }
        }
        vector<bool> comprado(productos, false);
        int minimo = INT_MAX;
        iterativo(productos, supers, superProducto, comprado, minimo);

        cout << minimo << endl;
    }
}

int main() {
#ifndef DOMJUDGE
    ifstream in("in.txt");
    cin.rdbuf(in.rdbuf());
#endif
    solve();
    return 0;
}