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
		vector<int> dp_min_dards(O + 1, INT_MAX); // mínimo número de dardos para cada puntuacion
        vector<int> backtrack(O + 1, -1); // Para rastrear qué puntuación llevó al estado óptimo


        // Inicializar para longitud 0
        dp_min_dards[0] = 0;


        // Programación dinámica
        for (int i = 0; i < S; ++i) {
            for (int j = secciones[i]; j <= O; ++j) {
                if (dp_min_dards[j - secciones[i]] != INT_MAX && dp_min_dards[j - secciones[i]] + 1 <= dp_min_dards[j]) {
                    // Actualizar si encontramos una solución más corta o igual
                    if (dp_min_dards[j - secciones[i]] + 1 < dp_min_dards[j] ||
                        (backtrack[j - secciones[i]] != -1 && secciones[i] > secciones[backtrack[j]])) {
                        dp_min_dards[j] = dp_min_dards[j - secciones[i]] + 1;
                        backtrack[j] = i; // Guardamos el índice de la puntuación usada
                    }
                }
            }
        }
        // Construir resultado
        if (dp_min_dards[O] == INT_MAX) {
            cout << "Imposible" << endl;
        }
        else {
            cout << dp_min_dards[O] << ":";
            vector<int> resultado;
            int current = O;

            // Rastreamos las puntuaciones utilizadas
            while (current > 0) {
                resultado.push_back(secciones[backtrack[current]]);
                current -= secciones[backtrack[current]];
            }

            // Ordenar las puntuaciones de mayor a menor
            sort(resultado.rbegin(), resultado.rend());

            for (int puntuacion : resultado) {
                cout << " " << puntuacion;
            }
            cout << endl;
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