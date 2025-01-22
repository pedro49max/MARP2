#include<fstream>
#include<iostream>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;

void solve() {
	int O, S;
	while (cin >> O >> S) {
		vector<int> secciones(S);
		for (int i = 0; i < S; i++) {
			cin >> secciones[i];
		}
		vector<long long> dp_ways(O + 1, 0); // número de formas de conseguir cada puntuacion
		vector<int> dp_min_dards(O + 1, INT_MAX); // mínimo número de dardos para cada puntuacion
        vector<vector<int>> puntuaciones(O + 1);//queue con las secciones del minimo de dardos para la puntuacion


        // Inicializar para longitud 0
        dp_ways[0] = 1;
        dp_min_dards[0] = 0;

        for (int i = S-1; i >=0; i--) {
            for (int j = secciones[i]; j <= O && j - secciones[i] >= 0; j++) {
                // Actualizar número de formas
                dp_ways[j] += dp_ways[j - secciones[i]]; // Al número de formas de llegar a j, se le suman el numero de formas de llegar a j - leghts[i]

                // Actualizar mínimo número de dardos
                if (dp_min_dards[j - secciones[i]] != INT_MAX) {
                    if (dp_min_dards[j - secciones[i]] + 1 < dp_min_dards[j]) {
                        dp_min_dards[j] =dp_min_dards[j - secciones[i]] + 1; // se guarda el valor del numero minimo de dardos necesarios para llegar a j
                        puntuaciones[j] = puntuaciones[j - secciones[i]]; puntuaciones[j].push_back(secciones[i]);
                    }
                    else if(dp_min_dards[j - secciones[i]] + 1 == dp_min_dards[j]){
                        int idx = 0;
                        while (idx < puntuaciones[j - secciones[i]].size() && puntuaciones[j - secciones[i]][idx] == puntuaciones[j][idx])
                            idx++;
                        if (puntuaciones[j - secciones[i]][idx] > puntuaciones[j][idx]) {
                            puntuaciones[j] = puntuaciones[j - secciones[i]]; puntuaciones[j].push_back(secciones[i]);
                        }
                    }
                }
            }
        }
        if (dp_ways[O] > 0) {
            cout << dp_min_dards[O] << ":";
            for (int i = 0; i < puntuaciones[O].size(); i++) {
                cout << " " << puntuaciones[O][i]; 
            }
            cout << endl;
        }
        else {
            cout << "Imposible" << endl;
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