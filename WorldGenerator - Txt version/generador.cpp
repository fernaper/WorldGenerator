#include <iostream>
#include <queue>
#include <map>
#include <utility>
#include <time.h>
#include <stdlib.h>

using namespace std;

pair<int, int> generaPosicion(pair<int, int> inicial, map <pair<int, int>, bool> &tablero) {
	pair<int, int> posibles[4];
	int count = 0;
	if (tablero.count(make_pair(inicial.first + 1, inicial.second)) == 0) {
		posibles[count] = make_pair(inicial.first + 1, inicial.second);
		count++;
	}
	if (tablero.count(make_pair(inicial.first - 1, inicial.second)) == 0) {
		posibles[count] = make_pair(inicial.first - 1, inicial.second);
		count++;
	}
	if (tablero.count(make_pair(inicial.first, inicial.second + 1)) == 0) {
		posibles[count] = make_pair(inicial.first, inicial.second + 1);
		count++;
	}
	if (tablero.count(make_pair(inicial.first, inicial.second - 1)) == 0) {
		posibles[count] = make_pair(inicial.first, inicial.second - 1);
		count++;
	}

	return posibles[rand() % count];
}

bool posibleGenerar(pair<int, int> inicial, map <pair<int, int>, bool> &tablero) {
	return 	(tablero.count(make_pair(inicial.first + 1, inicial.second)) == 0 ||
		tablero.count(make_pair(inicial.first - 1, inicial.second)) == 0 ||
		tablero.count(make_pair(inicial.first, inicial.second + 1)) == 0 ||
		tablero.count(make_pair(inicial.first, inicial.second - 1)) == 0);
}

void generaMazmorra(int limite, map <pair<int, int>, bool> &tablero) {
	queue<pair<int, int> > cola;
	pair<int, int> ficha(limite / 2, limite / 2);

	cola.push(ficha);
	tablero.insert(make_pair(ficha, true));

	int i = 1;
	while (i < limite) {
		for (int j = 0; j < 2; j++) {
			if (posibleGenerar(cola.front(), tablero)) {
				pair <int, int> posicionCrear = generaPosicion(cola.front(), tablero);
				cola.push(posicionCrear);
				tablero.insert(make_pair(posicionCrear, true));
				i++;
				if (cola.size() > 3 && (rand() % 2 == 0 || rand() % 2 == 0 || rand() % 2 == 0)) // 3 * (1/2 de posibilidades de no generar una segunda)
					break;
			}
			else {
				break;
			}
		}
		cola.pop();
	}

}

int numAdyacentes(pair<int, int> inicial, map <pair<int, int>, bool> &tablero) {
	int count = 0;
	if (tablero.count(make_pair(inicial.first + 1, inicial.second)) != 0)
		count++;
	if (tablero.count(make_pair(inicial.first - 1, inicial.second)) != 0)
		count++;
	if (tablero.count(make_pair(inicial.first, inicial.second + 1)) != 0)
		count++;
	if (tablero.count(make_pair(inicial.first, inicial.second - 1)) != 0)
		count++;

	return count;
}

pair<int, int> generaPosicionLab(pair<int, int> inicial, map <pair<int, int>, bool> &tablero) {
	pair<int, int> posibles[4];
	int count = 0;
	if (tablero.count(make_pair(inicial.first + 1, inicial.second)) == 0 && 1 == numAdyacentes(make_pair(inicial.first + 1, inicial.second), tablero)) {
		posibles[count] = make_pair(inicial.first + 1, inicial.second);
		count++;
	}
	if (tablero.count(make_pair(inicial.first - 1, inicial.second)) == 0 && 1 == numAdyacentes(make_pair(inicial.first - 1, inicial.second), tablero)) {
		posibles[count] = make_pair(inicial.first - 1, inicial.second);
		count++;
	}
	if (tablero.count(make_pair(inicial.first, inicial.second + 1)) == 0 && 1 == numAdyacentes(make_pair(inicial.first, inicial.second + 1), tablero)) {
		posibles[count] = make_pair(inicial.first, inicial.second + 1);
		count++;
	}
	if (tablero.count(make_pair(inicial.first, inicial.second - 1)) == 0 && 1 == numAdyacentes(make_pair(inicial.first, inicial.second - 1), tablero)) {
		posibles[count] = make_pair(inicial.first, inicial.second - 1);
		count++;
	}

	return posibles[rand() % count];
}

bool posibleGenerarLab(pair<int, int> inicial, map <pair<int, int>, bool> &tablero) {
	int count = 0;
	if (tablero.count(make_pair(inicial.first + 1, inicial.second)) == 0 && 1 == numAdyacentes(make_pair(inicial.first + 1, inicial.second), tablero)) {
		count++;
	}
	if (tablero.count(make_pair(inicial.first - 1, inicial.second)) == 0 && 1 == numAdyacentes(make_pair(inicial.first - 1, inicial.second), tablero)) {
		count++;
	}
	if (tablero.count(make_pair(inicial.first, inicial.second + 1)) == 0 && 1 == numAdyacentes(make_pair(inicial.first, inicial.second + 1), tablero)) {
		count++;
	}
	if (tablero.count(make_pair(inicial.first, inicial.second - 1)) == 0 && 1 == numAdyacentes(make_pair(inicial.first, inicial.second - 1), tablero)) {
		count++;
	}

	return (count != 0);
}

void sumaFichaLab(queue<pair<int, int> > &cola, map <pair<int, int>, bool> &tablero) {
	pair <int, int> *datos = new pair<int,int>[tablero.size()];
	int count = 0;

	// Recorro el tablero y solo meto en la lista
	for (map <pair<int, int>, bool>::iterator it = tablero.begin(); it != tablero.end(); ++it) {
		if (posibleGenerarLab(it->first, tablero)) {
			datos[count] = it->first;
			count++;
		}
	}

	if (count > 0) {
		cola.push(datos[rand() % count]);
	}

	delete[] datos;
}

void generaLaberinto(int limite, map <pair<int, int>, bool> &tablero) {
	queue<pair<int, int> > cola;
	pair<int, int> ficha(limite / 2, limite / 2);

	cola.push(ficha);
	tablero.insert(make_pair(ficha, true));

	int i = 1;
	while (i < limite) {
		if (posibleGenerarLab(cola.front(), tablero)) {
			pair <int, int> posicionCrear = generaPosicionLab(cola.front(), tablero);
			cola.push(posicionCrear);
			tablero.insert(make_pair(posicionCrear, true));
		}

		if (rand() % 2 == 0 || rand() % 2 == 0)
			cola.pop();

		i++;
		// Si por ahí no puedo seguir cojo desde otro punto válido y sigo
		if (cola.size() < 3 && i < limite) {
			sumaFichaLab(cola, tablero);
		}
	}
}

int minF(map <pair<int, int>, bool> &tablero, int limite) {
	int min = limite;
	for (map <pair<int, int>, bool>::iterator it = tablero.begin(); it != tablero.end(); ++it) {
		if (it->first.first < min)
			min = it->first.first;
	}

	return min;
}

int minC(map <pair<int, int>, bool> &tablero, int limite) {
	int min = limite;
	for (map <pair<int, int>, bool>::iterator it = tablero.begin(); it != tablero.end(); ++it) {
		if (it->first.second < min)
			min = it->first.second;
	}

	return min;
}

int maxF(map <pair<int, int>, bool> &tablero) {
	int max = 0;
	for (map <pair<int, int>, bool>::iterator it = tablero.begin(); it != tablero.end(); ++it) {
		if (it->first.first > max)
			max = it->first.first;
	}

	return max;
}

int maxC(map <pair<int, int>, bool> &tablero) {
	int max = 0;
	for (map <pair<int, int>, bool>::iterator it = tablero.begin(); it != tablero.end(); ++it) {
		if (it->first.second > max)
			max = it->first.second;
	}

	return max;
}

void mostrar(map <pair<int, int>, bool> &tablero, int limite) {
	int iniF = minF(tablero, limite), iniC = minC(tablero, limite);
	int finF = maxF(tablero), finC = maxC(tablero);
	bool **tableroArray = new bool* [finF - iniF + 1];
	for (int i = 0; i < finF - iniF + 1; ++i)
		tableroArray[i] = new bool[finC - iniC + 1];

	for (int i = 0; i <= finF - iniF; i++) {
		for (int j = 0; j <= finC - iniC; j++) {
			tableroArray[i][j] = false;
		}
	}

	for (map <pair<int, int>, bool>::iterator it = tablero.begin(); it != tablero.end(); ++it) {
		tableroArray[it->first.first - iniF][it->first.second - iniC] = it->second;
	}

	for (int i = 0; i <= finF - iniF; i++) {
		for (int j = 0; j <= finC - iniC; j++) {
			cout << ' ';
			if (tableroArray[i][j]) {
				cout << 'X';
			}
			else {
				cout << ' ';
			}
		}
		cout << endl;
	}

	for (int i = 0; i < finF - iniF + 1; ++i) {
		delete[] tableroArray[i];
	}
	delete[] tableroArray;
}

int main() {
	srand(time(NULL));
	map < pair<int, int>, bool> tablero;
	int dim;
	char ml;
	cerr << "Mapa o Laberinto[M/L]: ";
	cin >> ml;
	cerr << "Dimension: ";
	cin >> dim;

	if (ml == 'm')
		generaMazmorra(dim, tablero);
	else
		generaLaberinto(dim, tablero); // Limite 1465

	mostrar(tablero, dim);

	return 0;
}