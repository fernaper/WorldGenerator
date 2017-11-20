#include <iostream>
#include <queue>
#include <map>
#include <utility>
#include <time.h>
#include <stdlib.h>

using namespace std;

pair<int,int> generaPosicion (pair<int,int> inicial, map <pair<int,int>, bool> &tablero) {
	pair<int,int> posibles [4];
	int count = 0;
	if (tablero.count (make_pair(inicial.first+1, inicial.second)) == 0) {
		posibles[count] = make_pair(inicial.first+1, inicial.second);
		count++;
	}
	if (tablero.count (make_pair(inicial.first-1, inicial.second)) == 0) {
		posibles[count] = make_pair(inicial.first-1, inicial.second);
		count++;
	}
	if (tablero.count (make_pair(inicial.first, inicial.second+1)) == 0) {
		posibles[count] = make_pair(inicial.first, inicial.second+1);
		count++;
	}
	if (tablero.count (make_pair(inicial.first, inicial.second-1)) == 0) {
		posibles[count] = make_pair(inicial.first, inicial.second-1);
		count++;
	}
		
	return posibles[rand() % count];
}

bool posibleGenerar (pair<int,int> inicial, map <pair<int,int>, bool> &tablero) {
	return 	(tablero.count (make_pair(inicial.first+1, inicial.second)) == 0 ||
			tablero.count (make_pair(inicial.first-1, inicial.second)) == 0 ||
			tablero.count (make_pair(inicial.first, inicial.second+1)) == 0 ||
			tablero.count (make_pair(inicial.first, inicial.second-1)) == 0);
}

void generaMazmorra(int limite, map <pair<int,int>, bool> &tablero) {
	queue<pair<int,int> > cola;
	pair<int,int> ficha (limite/2,limite/2);
	
	cola.push(ficha);
	tablero.insert(make_pair(ficha, true));

	int i = 1;
	while (i < limite) {
		for (int j = 0; j < 2; j++) {
			if (posibleGenerar (cola.front(), tablero)) {
				pair <int, int> posicionCrear = generaPosicion(cola.front(), tablero);
				cola.push(posicionCrear);
				tablero.insert(make_pair(posicionCrear,true));
				i++;
				if (cola.size() > 3 && (rand() % 2 == 0 || rand() % 2 == 0 || rand() % 2 == 0)) // 3 * (1/2 de posibilidades de no generar una segunda)
					break;
			} else {
				break;
			}
		}
		cola.pop();
	}
	
}

int minF (map <pair<int,int>, bool> &tablero) {
	int min = tablero.begin()->first.first;
	for (map <pair<int,int>, bool>::iterator it=tablero.begin(); it!=tablero.end(); ++it) {
		if (it->first.first < min)
			min = it->first.first;
	}
	
	return min;
}

int minC (map <pair<int,int>, bool> &tablero) {
	int min = tablero.begin()->first.second;
	for (map <pair<int,int>, bool>::iterator it=tablero.begin(); it!=tablero.end(); ++it) {
		if (it->first.second < min)
			min = it->first.second;
	}
	
	return min;
}

int maxF (map <pair<int,int>, bool> &tablero) {
	int max = 0;
	for (map <pair<int,int>, bool>::iterator it=tablero.begin(); it!=tablero.end(); ++it) {
		if (it->first.first > max)
			max = it->first.first;
	}
	
	return max;
}

int maxC (map <pair<int,int>, bool> &tablero) {
	int max = 0;
	for (map <pair<int,int>, bool>::iterator it=tablero.begin(); it!=tablero.end(); ++it) {
		if (it->first.second > max)
			max = it->first.second;
	}
	
	return max;
}

void limitesMapa (map <pair<int,int>, bool> &tablero, int &minF, int &minC, int &maxF, int &maxC) {
	minF = tablero.begin()->first.first;
	minC = tablero.begin()->first.second;
	maxF = 0;
	maxC = 0;
	
	for (map <pair<int,int>, bool>::iterator it=tablero.begin(); it!=tablero.end(); ++it) {
		if (it->first.first < minF)
			minF = it->first.first;
		if (it->first.first < minC)
			minC = it->first.second;
		if (it->first.first > maxF)
			maxF = it->first.first;
		if (it->first.first > maxC)
			maxC = it->first.second;
	}
}

void mostrar(map <pair<int,int>, bool> &tablero) {
	int iniF = minF(tablero), iniC = minC(tablero);
	int finF = maxF(tablero), finC = maxC(tablero);
	bool tableroArray [finF - iniF + 1][finC - iniC + 1];
	
	for (int i = 0; i <= finF-iniF; i++) {
		for (int j = 0; j <= finC-iniC; j++) {
			tableroArray[i][j] = false;
		}
	}
	
	for (map <pair<int,int>, bool>::iterator it=tablero.begin(); it!=tablero.end(); ++it) {
		tableroArray[it->first.first - iniF][it->first.second - iniC] = it->second;
	}
	
	for (int i = 0; i <= finF-iniF; i++) {
		for (int j = 0; j <= finC-iniC; j++) {
			cout << ' ';
			if (tableroArray[i][j]) {
				cout << 'X';
			} else {
				cout << ' ';
			}
		}
		cout << endl;
	}
}

map <pair<int,int>, bool> unirSalas(queue <map <pair<int,int>, bool> > &salas, int separacion) {
	map <pair<int,int>, bool> tablero;
	
	int minFAnterior; 
	int minCAnterior;
	int maxFAnterior;
	int maxCAnterior;
	
	int minFActual; 
	int minCActual;
	int maxFActual;
	int maxCActual;
	
	tablero = salas.front();
	
	limitesMapa(tablero, minFAnterior, minCAnterior, maxFAnterior, maxCAnterior);
	
	/*minFAnterior = minF(tablero); 
	minCAnterior = minC(tablero);
	maxFAnterior = maxF(tablero);
	maxCAnterior = maxC(tablero);*/
	
	salas.pop();	
	
	while (salas.size() != 0) {
		map <pair<int,int>, bool> sala = salas.front();
		
		/*minFActual = minF(sala); 
		minCActual = minC(sala);
		maxFActual = maxF(sala);
		maxCActual = maxC(sala);*/
		limitesMapa(tablero, minFActual, minCActual, maxFActual, maxCActual);
		
		// Puedo ponerlo en una de las cuatro direcciones desde la sala
		switch (rand () % 4) {
			case 0:
				// Quiero colocar esta sala debajo de la anterior // minF
				for (map <pair<int,int>, bool>::iterator it=sala.begin(); it!=sala.end(); ++it) {
					
				}
			break;
			case 1:
				// Quiero colocar esta sala a la derecha de la anterior // minC
				for (map <pair<int,int>, bool>::iterator it=sala.begin(); it!=sala.end(); ++it) {
					
				}
			break;
			case 2:
				// Quiero colocar esta sala arriba de la anterior // maxF
				for (map <pair<int,int>, bool>::iterator it=sala.begin(); it!=sala.end(); ++it) {
					
				}
			break;
			case 3:
				// Quiero colocar esta sala a la izquierda de la anterior // maxC
				for (map <pair<int,int>, bool>::iterator it=sala.begin(); it!=sala.end(); ++it) {
					
				}
			break;
		}
		salas.pop();
		
		/*minFAnterior = minFActual;
		minCAnterior = minCActual;
		maxFAnterior = maxFActual;
		maxCAnterior = maxCActual;*/
		limitesMapa(tablero, minFAnterior, minCAnterior, maxFAnterior, maxCAnterior);
	}
	
	return tablero;
}

int main () {
	srand (time(NULL));
	map <pair<int,int>, bool> tablero;
	queue <map <pair<int,int>, bool> > colaSalas; 
	int dim, salas;
	
	cin >> dim;
	cin >> salas;
	for (int i = 0; i < salas; i++) {
		map <pair<int,int>, bool> sala;
		generaMazmorra(dim, sala);
		colaSalas.push(sala);
	}
	
	tablero = unirSalas(colaSalas, 10);
	mostrar(tablero);
	
	return 0;
}