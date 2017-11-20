#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <exception>

#include <iostream>
#include <queue>
#include <map>
#include <utility>
#include <time.h>
#include <stdlib.h>

#include <sstream>
#include <thread>

using namespace std;

pair<int, int> generaPosicion(pair<int, int> inicial, map <pair<int, int>, int> &tablero) {
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

bool posibleGenerar(pair<int, int> inicial, map <pair<int, int>, int> &tablero) {
	return 	(tablero.count(make_pair(inicial.first + 1, inicial.second)) == 0 ||
		tablero.count(make_pair(inicial.first - 1, inicial.second)) == 0 ||
		tablero.count(make_pair(inicial.first, inicial.second + 1)) == 0 ||
		tablero.count(make_pair(inicial.first, inicial.second - 1)) == 0);
}

void generaMazmorra(int limite, map <pair<int, int>, int> &tablero, char bioma) {
	queue<pair<int, int> > cola;
	pair<int, int> ficha(limite / 2, limite / 2);
	int biomaActual = 1; // 1 = Tierra | 2 = Desierto | 3 = Nieve

	if (bioma == 't') {
		biomaActual = 1;
		tablero.insert(make_pair(ficha, 1));
	}
	else if (bioma == 'd'){
		biomaActual = 2;
		tablero.insert(make_pair(ficha, 4));
	}
	else if (bioma == 'n'){
		biomaActual = 3;
		tablero.insert(make_pair(ficha, 7));
	}

	cola.push(ficha);

	int i = 1;
	while (i < limite) {
		for (int j = 0; j < 2 && i < limite; j++) {
			if (posibleGenerar(cola.front(), tablero)) {
				pair <int, int> posicionCrear = generaPosicion(cola.front(), tablero);
				cola.push(posicionCrear);

				int probabilidad = rand() % 100;

				// Vamos a dar posibilidades a otros gráficos
				if (probabilidad <= 90) {
					if (biomaActual == 1) {
						tablero.insert(make_pair(posicionCrear, 1)); // Tierra
					}
					else if (biomaActual == 2) {
						tablero.insert(make_pair(posicionCrear, 4)); // Desierto
					}
					else if (biomaActual == 3) {
						tablero.insert(make_pair(posicionCrear, 7)); // Nieve
					}
				}
				else if (probabilidad <= 96) {
					if (biomaActual == 1) {
						tablero.insert(make_pair(posicionCrear, 2));
					}
					else if (biomaActual == 2) {
						tablero.insert(make_pair(posicionCrear, 5));
					}
					else if (biomaActual == 3) {
						tablero.insert(make_pair(posicionCrear, 8));
					}
				}
				else {
					if (biomaActual == 1) {
						tablero.insert(make_pair(posicionCrear, 3));
					}
					else if (biomaActual == 2) {
						tablero.insert(make_pair(posicionCrear, 6));
					}
					else if (biomaActual == 3) {
						tablero.insert(make_pair(posicionCrear, 9));
					}
				}

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

int numAdyacentes(pair<int, int> inicial, map <pair<int, int>, int> &tablero) {
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

pair<int, int> generaPosicionLab(pair<int, int> inicial, map <pair<int, int>, int> &tablero) {
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

bool posibleGenerarLab(pair<int, int> inicial, map <pair<int, int>, int> &tablero) {
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

void sumaFichaLab(queue<pair<int, int> > &cola, map <pair<int, int>, int> &tablero) {
	pair <int, int> *datos = new pair<int,int>[tablero.size()];
	int count = 0;

	// Recorro el tablero y solo meto en la lista
	for (map <pair<int, int>, int>::iterator it = tablero.begin(); it != tablero.end(); ++it) {
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

void generaLaberinto(int limite, map <pair<int, int>, int> &tablero) {
	queue<pair<int, int> > cola;
	pair<int, int> ficha(limite / 2, limite / 2);

	cola.push(ficha);
	tablero.insert(make_pair(ficha, 50));

	int i = 1;
	while (i < limite) {
		if (posibleGenerarLab(cola.front(), tablero)) {
			pair <int, int> posicionCrear = generaPosicionLab(cola.front(), tablero);
			cola.push(posicionCrear);
			tablero.insert(make_pair(posicionCrear, 50));
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
/*
void parteSala(map <pair<int, int>, int> &tablero, pair<int,int> &salaOrigen, pair<int,int> &salaDestino) {
	if ((salaDestino.first - salaOrigen.first) * (salaDestino.second - salaOrigen.second) > 50){
		if (rand() % 2 == 0) { // Divido en horizontal
			int a = rand() % (salaDestino.first - salaOrigen.first);
			if (tablero.count(make_pair(a - 1, salaOrigen.second)) != 0) {
				a++;
			} else if (tablero.count(make_pair(a + 1, salaOrigen.second)) != 0) {
				a--;
			}

			for (int i = salaOrigen.second + 1; i < salaDestino.second; i++) {
				tablero.insert(make_pair(make_pair(a, i), 1));
			}

			pair<int, int> *nuevo = new pair <int, int>();
			nuevo->first = a;
			nuevo->second = salaDestino.second;

			parteSala(tablero, salaOrigen, *nuevo);
			parteSala(tablero, make_pair(a, salaOrigen.second), salaDestino);

			delete[] nuevo;
		}
		else { // Divido en vertical
			int a = rand() % (salaDestino.second - salaOrigen.second);

			if (tablero.count(make_pair(salaOrigen.first, a - 1)) != 0) {
				a++;
			}
			else if (tablero.count(make_pair(salaOrigen.first, a + 1)) != 0) {
				a--;
			}

			for (int i = salaOrigen.first + 1; i < salaDestino.first; i++) {
				tablero.insert(make_pair(make_pair(i, a), 1));
			}

			pair<int, int> *nuevo = new pair <int, int>();
			nuevo->first = salaOrigen.first;
			nuevo->second = a;

			parteSala(tablero, salaOrigen, make_pair(salaDestino.first, a));
			parteSala(tablero, *nuevo, salaDestino);
			
			delete[] nuevo;
		}
	}
}

void generaHabitaciones(int limite, map <pair<int, int>, int> &tablero) {
	queue<pair<int, int> > cola;
	// Hacemos el marco
	for (int i = 0; i < limite; i++) {
		tablero.insert(make_pair(make_pair(i,0), 1));
		tablero.insert(make_pair(make_pair(0, i), 1));
		tablero.insert(make_pair(make_pair(i, limite-1), 1));
		tablero.insert(make_pair(make_pair(limite-1, i), 1));
	}

	parteSala(tablero, make_pair(0, 0), make_pair(limite-1, limite-1));
}
*/

map <pair<int, int>, int> generaRoom(int limite_room, int fichas_room) {
	map <pair<int, int>, int> room;
	queue<pair<int, int> > cola;
	pair <int, int> ficha = make_pair(limite_room / 2, limite_room / 2);

	// Inserto la primera ficha en el medio
	room.insert(make_pair(ficha, 1));

	cola.push(ficha);

	for (int i = 1; i < fichas_room; i++) {

	}

	return room;
}

void generaCastillo(int rooms, int limite_room, map <pair<int, int>, int> &tablero) {
	// Genera n rooms, con limite_room por room

	for (int i = 0; i < rooms; i++) {
		//map <pair<int, int>, int> room = generaRoom(limite_room, );
	}
}

int minF(map <pair<int, int>, int> &tablero, int limite) {
	int min = limite;
	for (map <pair<int, int>, int>::iterator it = tablero.begin(); it != tablero.end(); ++it) {
		if (it->first.first < min)
			min = it->first.first;
	}

	return min;
}

int minC(map <pair<int, int>, int> &tablero, int limite) {
	int min = limite;
	for (map <pair<int, int>, int>::iterator it = tablero.begin(); it != tablero.end(); ++it) {
		if (it->first.second < min)
			min = it->first.second;
	}

	return min;
}

int maxF(map <pair<int, int>, int> &tablero) {
	int max = 0;
	for (map <pair<int, int>, int>::iterator it = tablero.begin(); it != tablero.end(); ++it) {
		if (it->first.first > max)
			max = it->first.first;
	}

	return max;
}

int maxC(map <pair<int, int>, int> &tablero) {
	int max = 0;
	for (map <pair<int, int>, int>::iterator it = tablero.begin(); it != tablero.end(); ++it) {
		if (it->first.second > max)
			max = it->first.second;
	}

	return max;
}

void mostrar(map <pair<int, int>, int> &tablero, int limite) {
	int iniF = minF(tablero, limite), iniC = minC(tablero, limite);
	int finF = maxF(tablero), finC = maxC(tablero);
	int **tableroArray = new int* [finF - iniF + 1];
	for (int i = 0; i < finF - iniF + 1; ++i)
		tableroArray[i] = new int[finC - iniC + 1];

	for (int i = 0; i <= finF - iniF; i++) {
		for (int j = 0; j <= finC - iniC; j++) {
			tableroArray[i][j] = 0;
		}
	}

	for (map <pair<int, int>, int>::iterator it = tablero.begin(); it != tablero.end(); ++it) {
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

void mostrarVisual(map <pair<int, int>, int> &tablero, int limite, char ml) {
	sf::RenderWindow ventana;
	sf::Event eventosVentana;

	ventana.create(sf::VideoMode(800, 800), "World Generator - 2.1.0", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);	// Creo la ventana
	ventana.setFramerateLimit(20);																			// Limite de FPS
	ventana.setVerticalSyncEnabled(true);																	// Se verá mejor los movimientos
	ventana.setKeyRepeatEnabled(false);																		// Me permitirá detectar mejor cada letra

	sf::Texture tMar, tTierra, tTierra2, tTierra3, tRocasTierra, tArbolTierra, tMalla, tMuro, tFoto, tDesierto, tDesierto2, tDesierto3, tNieve, tNieve2, tNieve3;
	sf::Sprite gMar, gTierra, gTierra2, gTierra3, gRocasTierra, gArbolTierra, gMalla, gMuro, gDesierto, gDesierto2, gDesierto3, gNieve, gNieve2, gNieve3;

	if (!tMar.loadFromFile("tiles/mar4.png") ||
		!tTierra.loadFromFile("tiles/tierra4.png") ||
		!tTierra2.loadFromFile("tiles/tierra4Alternativa1.png") ||
		!tTierra3.loadFromFile("tiles/tierra4Alternativa2.png") ||
		!tDesierto.loadFromFile("tiles/arena.png") ||
		!tDesierto2.loadFromFile("tiles/arenaAlternativa.png") ||
		!tDesierto3.loadFromFile("tiles/arenaAlternativa2.png") ||
		!tNieve.loadFromFile("tiles/nieve.png") ||
		!tNieve2.loadFromFile("tiles/nieveAlternativa.png") ||
		!tNieve3.loadFromFile("tiles/nieveAlternativa2.png") ||
		!tRocasTierra.loadFromFile("tiles/rocas.png") ||
		!tArbolTierra.loadFromFile("tiles/arbolEsp.png") ||
		!tMuro.loadFromFile("tiles/muro3.png") ||
		!tMalla.loadFromFile("tiles/malla.png")) {
		// Ya lanzará un error de carga de imagenes
		throw std::exception("Error en la carga de gráficos.");
	}

	// Referente a graficos
	tFoto.create(800, 800);
	gMar.setTexture(tMar);
	gTierra.setTexture(tTierra);
	gTierra2.setTexture(tTierra2);
	gTierra3.setTexture(tTierra3);
	gDesierto.setTexture(tDesierto);
	gDesierto2.setTexture(tDesierto2);
	gDesierto3.setTexture(tDesierto3);
	gNieve.setTexture(tNieve);
	gNieve2.setTexture(tNieve2);
	gNieve3.setTexture(tNieve3);
	gMalla.setTexture(tMalla);
	gMuro.setTexture(tMuro);

	int iniF = minF(tablero, limite), iniC = minC(tablero, limite);
	int finF = maxF(tablero), finC = maxC(tablero);
	int **tableroArray = new int*[finF - iniF + 1];
	for (int i = 0; i < finF - iniF + 1; ++i)
		tableroArray[i] = new int[finC - iniC + 1];

	float VEscala32 = (800.f / (finF - iniF + 1))/32;
	float HEscala32 = (800.f / (finC - iniC + 1))/32;
	
	gTierra.setScale(HEscala32, VEscala32);
	gTierra2.setScale(HEscala32, VEscala32);
	gTierra3.setScale(HEscala32, VEscala32);
	gDesierto.setScale(HEscala32, VEscala32);
	gDesierto2.setScale(HEscala32, VEscala32);
	gDesierto3.setScale(HEscala32, VEscala32);
	gNieve.setScale(HEscala32, VEscala32);
	gNieve2.setScale(HEscala32, VEscala32);
	gNieve3.setScale(HEscala32, VEscala32);
	gMar.setScale(HEscala32, VEscala32);

	float VEscala16 = (800.f / (finF - iniF + 1)) / 16;
	float HEscala16 = (800.f / (finC - iniC + 1)) / 16;
	gMuro.setScale(HEscala16, VEscala16);
	gMalla.setScale(1 + HEscala16, 1 + VEscala16);

	for (int i = 0; i <= finF - iniF; i++) {
		for (int j = 0; j <= finC - iniC; j++) {
			tableroArray[i][j] = 0;
		}
	}

	for (map <pair<int, int>, int>::iterator it = tablero.begin(); it != tablero.end(); ++it) {
		tableroArray[it->first.first - iniF][it->first.second - iniC] = it->second;
	}

	bool usando = true;
	bool refresh = true;

	while (usando) {
		ventana.pollEvent(eventosVentana);
		if (eventosVentana.type == sf::Event::Closed) { // Si pulsa cerrar
			ventana.close();
			usando = false;
		}

		if (eventosVentana.type == sf::Event::Resized) {
			refresh = true;
		}

		if (eventosVentana.type == sf::Event::KeyPressed && eventosVentana.key.code == sf::Keyboard::F1)	{
			tFoto.update(ventana);
			sf::Image img = tFoto.copyToImage();
			std::thread t([img]() {
				img.saveToFile("foto.png");
			});
			t.detach();
		}

		if (refresh) {
			ventana.clear(sf::Color(0xFF0000FF));
			refresh = false;
			for (int i = 0; i <= finF - iniF; i++) {
				for (int j = 0; j <= finC - iniC; j++) {
					if (tableroArray[i][j]) {
						if (tableroArray[i][j] == 1) {
							gTierra.setPosition(sf::Vector2f(j * (800.f / (finC - iniC + 1)), i * (800.f / (finF - iniF + 1))));
							ventana.draw(gTierra);
						}
						else if (tableroArray[i][j] == 2) {
							gTierra2.setPosition(sf::Vector2f(j * (800.f / (finC - iniC + 1)), i * (800.f / (finF - iniF + 1))));
							ventana.draw(gTierra2);
						}
						else if (tableroArray[i][j] == 3) {
							gTierra3.setPosition(sf::Vector2f(j * (800.f / (finC - iniC + 1)), i * (800.f / (finF - iniF + 1))));
							ventana.draw(gTierra3);
						}
						else if (tableroArray[i][j] == 4) {
							gDesierto.setPosition(sf::Vector2f(j * (800.f / (finC - iniC + 1)), i * (800.f / (finF - iniF + 1))));
							ventana.draw(gDesierto);
						}
						else if (tableroArray[i][j] == 5) {
							gDesierto2.setPosition(sf::Vector2f(j * (800.f / (finC - iniC + 1)), i * (800.f / (finF - iniF + 1))));
							ventana.draw(gDesierto2);
						}
						else if (tableroArray[i][j] == 6) {
							gDesierto3.setPosition(sf::Vector2f(j * (800.f / (finC - iniC + 1)), i * (800.f / (finF - iniF + 1))));
							ventana.draw(gDesierto3);
						}
						else if (tableroArray[i][j] == 7) {
							gNieve.setPosition(sf::Vector2f(j * (800.f / (finC - iniC + 1)), i * (800.f / (finF - iniF + 1))));
							ventana.draw(gNieve);
						}
						else if (tableroArray[i][j] == 8) {
							gNieve2.setPosition(sf::Vector2f(j * (800.f / (finC - iniC + 1)), i * (800.f / (finF - iniF + 1))));
							ventana.draw(gNieve2);
						}
						else if (tableroArray[i][j] == 9) {
							gNieve3.setPosition(sf::Vector2f(j * (800.f / (finC - iniC + 1)), i * (800.f / (finF - iniF + 1))));
							ventana.draw(gNieve3);
						}
						else if (tableroArray[i][j] == 50) {
							gMuro.setPosition(sf::Vector2f(j * (800.f / (finC - iniC + 1)), i * (800.f / (finF - iniF + 1))));
							ventana.draw(gMuro);
						}
					}
					else {
						gMar.setPosition(sf::Vector2f(j * (800.f / (finC - iniC + 1)), i * (800.f / (finF - iniF + 1))));
						ventana.draw(gMar);
					}
					if (finF - iniF + 1 < 150 || finC - iniC + 1 < 150) {
						gMalla.setPosition(sf::Vector2f(j * (800.f / (finC - iniC + 1)), i * (800.f / (finF - iniF + 1))));
						ventana.draw(gMalla);
					}
				}
			}
			ventana.display();
		}
	}

	for (int i = 0; i < finF - iniF + 1; ++i) {
		delete[] tableroArray[i];
	}
	delete[] tableroArray;
}

int main() {
	while (true) {
		srand(time(NULL));
		map < pair<int, int>, int> tablero;
		int dim;
		char ml, bioma;
		cerr << "Mapa o Laberinto[M/L/T]: ";
		cin >> ml;
		if (ml == '.')
			return 0;
		cerr << "Dimension: ";
		cin >> dim;
		cerr << "Bioma[T/D/N]: ";
		cin >> bioma;

		if (ml == 'm') {
			generaMazmorra(dim, tablero, bioma);
		} else if (ml == 'l') {
			generaLaberinto(dim, tablero);
		} else {
			generaCastillo(dim, tablero);
		}

		//mostrar(tablero, dim);
		mostrarVisual(tablero, dim, ml);
	}

	return 0;
}