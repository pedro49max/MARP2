#include<fstream>
#include<iostream>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;

void solve() {
	int n;
	while (cin >> n) {
		vector<vector<int>> matriz(n, vector<int>(n));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> matriz[i][j];
			}
		}
		vector<int> sumaAnetior(n, 0);
		vector<int> sumaNueva(n);
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++) {
				int maxi = sumaAnetior[c];
				if (c - 1 >= 0 && maxi < sumaAnetior[c - 1]) {
					maxi = sumaAnetior[c - 1];
				}			
				if (c + 1 < n  && maxi< sumaAnetior[c + 1]) {
					maxi = sumaAnetior[c + 1];
				}
				sumaNueva[c] = maxi + matriz[r][c];
				//cout << "ROW:" << r << " COL:" << c << " suma:" << sumaNueva[c] << " columnaInicial:" << columnaNueva[c] << endl;
			}
			sumaAnetior = sumaNueva;
		}
		int maxi = -1;
		int c;
		for (int i = 0; i < n; i++) {
			if (sumaAnetior[i] > maxi) {
				maxi = sumaAnetior[i];
				c = i;
			}
		}
		cout << maxi << " " << c + 1 << endl;
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