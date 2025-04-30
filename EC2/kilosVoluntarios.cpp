//Pedro Tobalina Navarro y Jorge Polo Peires
//DNI:71369690T y 06594921Q
//GRUPO: 44

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

//Descripcion del espacio de soluciones y del arbol de exploracion
/**
* Asigmanos a cada voluntario a una de las poblaciones que necesiten kilos todavía
* Nuestro arbol de exploración será para cada uno de los n voluntarios, m opciones para
* asignar. => factor de ramificación = m^n
*
* Funcioón de poda: quitamos nodos cuyo completados + (n-k) < l. Es decir, nodos que no puedan
* cumplir la restriccion de satisfacer a l pueblos.
* Además, nodos cuyos kilos estimados sea menor a la cota inferior de la mejor solucion encontrada.
*/


//Explicacion detallada deL tipo de los nodos
struct tNodo
{
	vi sol; // (0 a m-1) -> cantidad de kilos recibidos a cada poblado
	int k;//nivel del nodo
	int kilos; // kilos repartidos
	int kilos_est; // estimacion optimista
	int completados; // num poblados satisfechos
	//...

	bool operator<(tNodo const& n) const {
		return kilos_est < n.kilos_est; // maximizar
	}

};

//PODAS DE OPTIMALIDAD

// Estimacion optimista: para los voluntarios que nos quedan, usamos los kilos máximos que puedan repartir 
// y lo sumamos a los kilos que llevabamos repartidos
int kilos_est_opt(const vi& kilosMaxVoluntarios, const  tNodo& x) {
	int cota_opt = 0;
	cota_opt += x.kilos;
	int k = x.k + 1;

	for (int i = k; i < kilosMaxVoluntarios.size(); i++) {
		cota_opt += kilosMaxVoluntarios[i];
	}

	return cota_opt;
}

void kilos_rp(vi const& pob, vvi const& vol, vi const& vol_max, const int l, int& best, bool& res) {
	int n = vol.size(), m = pob.size();
	tNodo Y;
	Y.completados = 0; Y.k = -1;
	Y.sol = vi(m, 0);
	Y.kilos = 0;
	Y.kilos_est = kilos_est_opt(vol_max, Y);
	Y.k++;

	priority_queue<tNodo, vector<tNodo>, less<tNodo>> pq;
	pq.push(Y);

	while (!pq.empty() && pq.top().kilos_est >= best) {
		Y = pq.top(); pq.pop();
		if (Y.completados + (n - Y.k) < l)
			continue;

		for (int p = 0; p < m; ++p) {
			if (Y.sol[p] == pob[p])
				continue;

			tNodo X = Y;
			X.kilos = Y.kilos + min(pob[p] - Y.sol[p], vol[Y.k][p]);
			X.sol[p] = min(pob[p], Y.sol[p] + vol[Y.k][p]);
			X.completados = (X.sol[p] == pob[p]) ? X.completados + 1 : X.completados;
			X.kilos_est = kilos_est_opt(vol_max, X);
			X.k++;
			if (X.kilos_est >= best) {
				if (X.k == n || X.completados == m) {
					best = X.kilos;
					res = true;
				}
				else {
					pq.push(X);
				}
			}
		}

		Y.kilos_est = kilos_est_opt(vol_max, Y);
		Y.k++;
		if (Y.kilos_est >= best) {
			if (Y.k == n || Y.completados == m) {
				best = Y.kilos;
				res = true;
			}
			else {
				pq.push(Y);
			}
		}
	}
}



void resuelveCaso()
{

	int n, m, l;
	cin >> n >> m >> l;
	//n voluntarios
	//m poblaciones
	//al menos l poblaciones con sus necesidades cubiertas

	vector<int> poblaciones(m);
	vector<vector<int>> voluntarios(n, vector<int>(m));
	vi vol_max(n, 0);

	//Leemos las ayudas que necesitan las poblaciones
	for (int i = 0; i < m; i++) {
		cin >> poblaciones[i];
	}

	//Leemos lo que pueden repartir los voluntarios
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; ++j)
		{
			cin >> voluntarios[i][j];
			vol_max[i] = max(vol_max[i], voluntarios[i][j]);
		}


	//Inicializa para hacer la llamada
	int mejorAyuda = 0;//cantidad maxima de ayuda que se puede repartir
	bool exito = false; //se hara cierto si es posible cubrir las necesidades completamente de al menos l poblaciones

	//ALGORITMO DE RP
	kilos_rp(poblaciones, voluntarios, vol_max, l, mejorAyuda, exito);


	if (exito)
	{
		cout << mejorAyuda << "\n";
	}
	else
	{
		cout << "IMPOSIBLE\n";
	}

}





int main() {
	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) resuelveCaso();

	// restablecimiento de cin
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}