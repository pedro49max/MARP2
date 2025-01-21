#include<fstream>
#include<iostream>
#include<vector>
using namespace std;

void solve() {
	int n, L;
	while (cin >> n >> L) {
		vector<int> leghts(n);
		vector<int> costs(n);
		for (int i = 0; i < n; i++)
			cin >> leghts[i] >> costs[i];
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