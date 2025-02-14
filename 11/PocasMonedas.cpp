#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;


void solve() {
    int N;
    while (cin >> N && N != 0) {
        vector<int>cubos(N);
        for (int i = 0; i < N; i++) {
            cin >> cubos[i];
        }
        vector<vector<int>>dp(N, vector<int>(N, -1));
        cout << resuelve(cubos, dp, 0, N - 1, 0) << endl;
    }
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    solve();
    return 0;
}