#include <iostream>
#include <vector>
#include <algorithm>
#include<queue>
#include<climits>
#include <fstream>

using namespace std;

struct Nodo {
    int costeOptimista;
    //int costePesimista;//No se como hacerlo
    int costeAcomulado;
    int comensal;
    vector<int> ocupados;
};

bool operator>(Nodo a, Nodo b) {
    return a.costeOptimista < b.costeOptimista;
}

typedef priority_queue<Nodo, vector<Nodo>, greater<Nodo>> pq;

int cota_optimista(const int& comensales, const vector<vector<int>>& relaciones, const int& comensalID) {
    int maximo = 0;

    for (int i = comensalID; i < comensales; i++) {
        for (int j = 0; j < i; j++) {
            if (relaciones[i][j])
                maximo++;
        }
    }

    return maximo;
}

bool sitioValido(const int &comensalID,const int &plazaID, const vector<int> ocupados, const int& plazas, const vector<vector<double>>& distancias, const vector<vector<int>>& relaciones) {
    bool valido = true;
    for (int i = 0; i < plazas && valido; i++) {
        if (i != plazaID && ocupados[i] != -1) {
            if (distancias[i][plazaID] < 2 && relaciones[ocupados[i]][comensalID] == 0)
                valido = false;
        }
    }

    return valido;
}
int countPareja (const int& comensalID, const int& plazaID, const vector<int> ocupados, const int& plazas, const vector<vector<double>>& distancias, const vector<vector<int>>& relaciones) {
    int pareja = 0;
    for (int i = 0; i < plazas; i++) {
        if (i != plazaID && ocupados[i] != -1) {
            if (distancias[i][plazaID] < 2 && relaciones[ocupados[i]][comensalID] == 1)
                pareja ++;
        }
    }
    return pareja;
}

void iterativo(const int &plazas, const int& comensales, const vector<vector<double>>& distancias, const vector<vector<int>>& relaciones, int& costeMejor, bool& todosSentados) {
    pq nodos;
    int cOpt = cota_optimista(comensales, relaciones, 0);
    vector<vector<bool>> antiRep(comensales + 1, vector<bool>(cOpt + 10, false));
    antiRep[0][0] = true;
    nodos.push({ cOpt, 0, 0, vector<int>(plazas, -1) });
    while (!nodos.empty()) {
        Nodo a = nodos.top(); nodos.pop();
        if (a.comensal == comensales) {
            todosSentados = true;
            costeMejor = a.costeAcomulado;
        }
        else {
            for (int i = 0; i < plazas; i++) {
                if (a.ocupados[i] == -1 && sitioValido(a.comensal, i, a.ocupados,plazas, distancias, relaciones)) {
                    int costeAcomulado = a.costeAcomulado + countPareja(a.comensal, i, a.ocupados, plazas, distancias, relaciones);
                    vector<int> ocupados = a.ocupados;
                    ocupados[i] = a.comensal;
                    int comensal = a.comensal + 1;
                    int costeOptimista = costeAcomulado + cota_optimista(comensales,relaciones,comensal);
                    if (!antiRep[comensal][costeOptimista] && costeOptimista >= costeMejor) {
                        antiRep[comensal][costeOptimista] = true;
                        nodos.push({ costeOptimista, costeAcomulado, comensal, ocupados });
                        if (costeAcomulado > costeMejor)
                            costeMejor = costeAcomulado;
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
        int plazas, comensales;//n, m
        cin >> plazas >> comensales;
        vector<vector<double>>distancias(plazas, vector<double>(plazas));
        for (int i = 0; i < plazas; i++) {
            for (int j = 0; j < plazas; j++)
            cin >> distancias[i][j];
        }
        vector<vector<int>>relaciones(comensales, vector<int>(comensales));
        for (int i = 0; i < comensales; i++) {
            for (int j = 0; j < comensales; j++)
                cin >> relaciones[i][j];
        }
        int maximo = 0;
        bool todosSentados = false;
        iterativo(plazas, comensales, distancias, relaciones, maximo, todosSentados);

        if (!todosSentados)
            cout << "CANCELA" << endl;
        else
            cout << "PAREJAS " << maximo << endl;
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