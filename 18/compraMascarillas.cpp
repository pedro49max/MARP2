#include <iostream>
#include <vector>
#include <algorithm>
#include<queue>
#include<climits>
#include <fstream>

using namespace std;

struct Nodo {
    int universidad;
    int costeAcomulado;
    int costeOptimista;
    int costePesimista;
    vector<int> mascarillasPorUni;
    vector<int> stockRestante;
};

bool operator>(Nodo a, Nodo b) {
    return a.costeOptimista > b.costeOptimista;
}

typedef priority_queue<Nodo, vector<Nodo>, greater<Nodo>> pq;


int mascarillasRestantes(const vector<int>& necesidades) {
    int counter = 0;
    for (int i = 0; i < necesidades.size(); i++) {
        counter += necesidades[i];
    }
    return counter;
}
// Cálculo de la cota optimista con una heurística voraz
int cota_optimista(const int& sumnistradoras, const vector<int>& necesidades, const vector<int>& stock, const vector<int>& precio, const int universidadID) {//O(S*U)
    int costeEstimado = -1;
    vector<int> cantidades(sumnistradoras, 0);
    int idx = mascarillasRestantes(necesidades);
    for (int i = 0; i < sumnistradoras && idx > 0; i++) {
        if (stock[i] < idx) {
            cantidades[i] = stock[i];
            idx -= stock[i];
        }
        else if (stock[i] >= idx) {
            cantidades[i] = idx;
            idx = 0;
        }
    }
    if (idx == 0) {
        costeEstimado = 0;
        for (int j = 0; j < sumnistradoras; j++) {
            costeEstimado += precio[j] * cantidades[j];
        }
    }
    return costeEstimado;
}

int cota_pesimista(const int& sumnistradoras, const vector<int>& necesidades, const vector<int>& stock, const vector<int>& precio, const int universidadID) {//O(S*U)
    vector<int> cantidades(sumnistradoras, 0);
    int costeEstimado = -1;
    int idx = mascarillasRestantes(necesidades);
    for (int i = sumnistradoras -1; i >= 0 && idx > 0; i--) {
        if (stock[i] < idx) {
            cantidades[i] = stock[i];
            idx -= stock[i];
        }
        else if (stock[i] >= idx) {
            cantidades[i] = idx;
            idx = 0;
        }
    }
    if (idx == 0) {
        costeEstimado = 0;
        for (int j = 0; j < sumnistradoras; j++) {
            costeEstimado += precio[j] * cantidades[j];
        }
    }
    return costeEstimado;
}
// Iterativo con poda optimista-pesimista
int iterativo(const int& universidades, const int& suministradores, const vector<int>& necesidades, const vector<int>& stock, const vector<int>& precio, int& costeMinimo) {
    pq nodos;
    int cotaOptimista = cota_optimista(suministradores, necesidades, stock, precio, 0), cotaPesimista = cota_pesimista(suministradores, necesidades, stock, precio, 0);
    nodos.push({ 0,0, cotaOptimista, cotaPesimista, necesidades,stock});
    while (!nodos.empty()) {
        Nodo a = nodos.top(); nodos.pop();
        if (a.universidad == universidades) {
            return  min(a.costeAcomulado, costeMinimo);
        }
        else if (a.costeOptimista <= costeMinimo) {
            int uniID = a.universidad;
            for (int i = 0; i < suministradores; i++) {
                if (a.stockRestante[i] >0) {
                    vector<int> necesidadesPorUni = a.mascarillasPorUni;
                    vector<int> stockRestante = a.stockRestante;
                    int costeAcomulado = a.costeAcomulado;
                    if (necesidadesPorUni[uniID] >= stockRestante[i]) {
                        necesidadesPorUni[uniID] -= stockRestante[i];
                        costeAcomulado += stockRestante[i] * precio[i];
                        stockRestante[i] = 0;
                    }
                    else {
                        costeAcomulado += necesidadesPorUni[uniID] * precio[i];
                        stockRestante[i] = 0;
                        necesidadesPorUni[uniID] = 0;
                    }
                    int costeOptimista = cota_optimista(suministradores,necesidadesPorUni,stockRestante,precio,uniID+1);
                    int costePesimista = cota_pesimista(suministradores, necesidadesPorUni, stockRestante, precio, uniID + 1);
                    
                    if (costeOptimista != -1 && costePesimista != -1 && costeOptimista <= costeMinimo) {
                        nodos.push({ uniID + 1, costeAcomulado, costeOptimista, costePesimista, necesidadesPorUni, stockRestante});
                        if (costePesimista < costeMinimo)
                            costeMinimo = costePesimista;
                    }
                }
            }
        }

    }
    return -1;
}


void solve() {
    int casosDePrueba;
    cin >> casosDePrueba;
    for (int casosPrueba = 0; casosPrueba < casosDePrueba; casosPrueba++) {
        int universidades, suministradores;//n, m
        cin >> universidades >> suministradores;
        vector<int>necesidades(universidades);
        for (int i = 0; i < universidades; i++) {
            cin >> necesidades[i];
        }
        vector<int>stock(suministradores);
        for (int i = 0; i < suministradores; i++) {
            cin >> stock[i];
        }
        vector<int>precios(suministradores);
        for (int i = 0; i < suministradores; i++) {
            cin >> precios[i];
        }
        int minimo = INT_MAX;
        int answer = iterativo(universidades, suministradores, necesidades, stock, precios, minimo);

        if (answer == -1)
            cout << "NO" << endl;
        else
            cout << answer << endl;
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