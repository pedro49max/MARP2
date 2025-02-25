#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

vector<vector<int>> MatrizAhorro(const vector<vector<int>>& superProducto) {//O(S*2*P) -> O(S*P)
    vector<vector<int>> ahorro(superProducto.size(), vector<int>(superProducto[0].size()));
    for (int producto = 0; producto < superProducto[0].size(); producto++) {
        int maximo= 0;
        for (int tienda = 0; tienda < superProducto.size(); tienda++) {
            if (superProducto[tienda][producto] > maximo)
                maximo = superProducto[tienda][producto];
        }
        for (int tienda = 0; tienda < superProducto.size(); tienda++) {
            ahorro[tienda][producto] = superProducto[tienda][producto] - maximo;
        }
    }
    return ahorro;
}

void prodMin(const vector<vector<int>>& superProducto, const vector<bool>& comprado, int &super, int &prod) { //O(S*P)
    int mini = -1;
    for(int j = 0; j < superProducto.size(); j++)
        for (int i = 0; i < superProducto[j].size(); i++) {
            if (!comprado[i] && (mini == -1 || superProducto[j][i] < mini)) {
                super = j;
                prod = i;
                mini = superProducto[j][i];
            }
        }
}
bool faltanProductos(const vector<bool>& comprado) { //O(P)
    bool faltaAlgo = false;
    for (int i = 0; i < comprado.size() && !faltaAlgo; i++) {
        if (!comprado[i])
            faltaAlgo = true;
    }
    return faltaAlgo;
}

void podadora(const vector<vector<int>> &superProducto, vector<vector<int>> &ahorro, vector<bool> &comprado, int &minimo) {
    int costeAcomulado = 0;
    vector<int> comprasPorTienda(superProducto.size(), 0);
    while (faltanProductos(comprado)) {
        int super = -1, prod = -1;
        prodMin(ahorro, comprado, super, prod);
        if (comprasPorTienda[super] < 3) {
            comprado[prod] = true;
            comprasPorTienda[super]++;
            costeAcomulado += superProducto[super][prod];
            cout << "I take the shop " << super << " and the product " << prod << " and now I have a sum of " << costeAcomulado << endl;
        }
        else {
            for(int i = 0; i < ahorro[super].size(); i++)
                ahorro[super][i] = 1;
        }
    }
    minimo = costeAcomulado;
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
        vector<vector<int>> ahorro = MatrizAhorro(superProducto);
        int minimo = INT_MAX;
        podadora(superProducto,ahorro, comprado, minimo);

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
