#include<fstream>
#include<iostream>
#include<vector>
using namespace std;


int main() {
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	return 0;
}