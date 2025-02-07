#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;

struct Peli {
    int inicio, fin, duracion;
};

// Comparador para ordenar las películas por su tiempo de finalización
bool comparar(const Peli& a, const Peli& b) {
    return a.fin < b.fin;
}

// Función para encontrar la última película que no se solape con la película en índice `i`
int findLastNonOverlapping(const vector<Peli>& peliculas, int i) {
    int low = 0, high = i - 1, best = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (peliculas[mid].fin <= peliculas[i].inicio) {
            best = mid;
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return best;
}

void solve() {
    int N;
    while (cin >> N && N != 0) {
        vector<Peli> peliculas(N);

        // Leer los tiempos de inicio y duración
        for (int i = 0; i < N; i++) {
            int h, m, duracion;
            char c;
            cin >> h >> c >> m >> duracion;
            peliculas[i].inicio = h * 60 + m;
            peliculas[i].fin = peliculas[i].inicio + duracion + 10; // 10 minutos de pausa
            peliculas[i].duracion = duracion;
        }

        // Ordenar películas por tiempo de finalización
        sort(peliculas.begin(), peliculas.end(), comparar);

        // DP para encontrar el máximo tiempo de visionado
        vector<int> dp(N);
        vector<int> lastNonOverlapping(N, -1);

        // Precomputar la última película que no se solapa con cada película i
        for (int i = 0; i < N; i++) {
            lastNonOverlapping[i] = findLastNonOverlapping(peliculas, i);
        }

        // Caso base: La mejor opción para la primera película es verla
        dp[0] = peliculas[0].duracion;

        for (int i = 1; i < N; i++) {
            // Opción 1: No ver la película `i` (quedarse con la mejor opción previa)
            dp[i] = dp[i - 1];

            // Opción 2: Ver la película `i`
            int incluir = peliculas[i].duracion;
            int idx = lastNonOverlapping[i];
            if (idx != -1) {
                incluir += dp[idx];  // Sumar la mejor opción previa no solapada
            }

            // Guardar la mejor opción entre ambas
            dp[i] = max(dp[i], incluir);
        }

        // La respuesta está en dp[N-1], el mejor tiempo acumulado posible
        cout << dp[N - 1] << endl;
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
