//Pedro Tobalina Navarro
#include<fstream>
#include<iostream>
#include<vector>
#include <algorithm>
#include <climits>
using namespace std;

void solve() {
	int n, L;
	while (cin >> n >> L) {
		vector<int> leghts(n);//vector con las longitudes
		vector<int> costs(n);//vector con los costes
		for (int i = 0; i < n; i++)
			cin >> leghts[i] >> costs[i];
        // DP arrays
        vector<long long> dp_ways(L + 1, 0); // número de formas de conseguir cada longitud
        vector<int> dp_min_cords(L + 1, INT_MAX); // mínimo número de cordeles para cada longitud
        vector<long long> dp_min_cost(L + 1, LLONG_MAX); // mínimo coste para cada longitud

        // Inicializar para longitud 0
        dp_ways[0] = 1;
        dp_min_cords[0] = 0;
        dp_min_cost[0] = 0;

        for (int i = 0; i < n; i++) {
            for (int j = L; j >= leghts[i]; j--) {
                // Actualizar número de formas
                dp_ways[j] += dp_ways[j - leghts[i]]; // Al número de formas de llegar a j, se le suman el numero de formas de llegar a j - leghts[i]

                // Actualizar mínimo número de cordeles
                if (dp_min_cords[j - leghts[i]] != INT_MAX) {
                    dp_min_cords[j] = min(dp_min_cords[j], dp_min_cords[j - leghts[i]] + 1); // se guarda el valor del numero minimo de cordeles necesarios para llegar a j
                }

                // Actualizar mínimo coste
                if (dp_min_cost[j - leghts[i]] != LLONG_MAX) {
                    dp_min_cost[j] = min(dp_min_cost[j], dp_min_cost[j - leghts[i]] + costs[i]);//Se guarda el valor del numero minimo de coste necesarios para llegar a j
                }
            }
        }

        if (dp_ways[L] > 0) {
            cout << "SI " << dp_ways[L] << " " << dp_min_cords[L] << " " << dp_min_cost[L] << endl;
        }
        else {
            cout << "NO" << endl;
        }
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