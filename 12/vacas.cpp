#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;

void comeDevoradora(const vector<int>& cubos, int &ini, int &fin) {
    if (ini > fin || ini >= cubos.size() || fin < 0)
        return;
    if (cubos[ini] >= cubos[fin])
        ini++;
    else
        fin--;
}

int resuelve(const vector<int>& cubos, vector<vector<int>>&dp, int ini, int fin, int comida, bool devoradora) {
    //cout << "comienzo iteracion con ini=" << ini << " y fin=" << fin << endl;
    int result;
    if (devoradora) {
        //cout << "STACK OVERFLOW con " << ini << " " << fin << endl;
        int nextIni = ini, nextFin = fin;
        comeDevoradora(cubos, nextIni, nextFin);
        result = resuelve(cubos,dp, nextIni, nextFin, comida, false);
    }
    else if (ini >= fin || ini >= cubos.size() || fin <0)
        result = comida + cubos[ini];
    else if (fin - ini == 1)
        result = comida + max(cubos[ini], cubos[fin]);
    else {
        result = max(resuelve(cubos,dp, ini + 1, fin, comida + cubos[ini], true), resuelve(cubos,dp, ini, fin - 1, comida + cubos[fin], true));
    }
    if (dp[ini][fin] != -1 && result > dp[ini][fin])
        cout << "FUCK" << endl;
    dp[ini][fin] = result;
    return result;
}


void solve() {
    int N;
    while (cin >> N && N != 0) {
        vector<int>cubos(N);
        for (int i = 0; i < N; i++) {
            cin >> cubos[i];
        }
        vector<vector<int>>dp(N, vector<int>(N, -1));
        cout << resuelve(cubos, dp,0, N - 1, 0, false) << endl;
    }
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    solve();
    return 0;
}