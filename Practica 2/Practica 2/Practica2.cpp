/*
* Milagros del Rocío Peña Quineche
* Práctica 2 - Simón dice
* Ingeniería Software - 1ºE
*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

const int MAX_COLORES_SEQ = 20;
const int MAX_COLORES_DIFICIL = 15;
const int MAX_COLORES_FACIL = 12;
const int NUM_AYUDAS = 3;
const int MAX_JUGADORES = 10;
const float vDificil = 1.5;
const string nomArch = "top.txt";
typedef enum tColores{Rojo, Verde, Azul, Dorado, Blanco, Marron, Naranja, Nada};
typedef enum tModo{Facil, Dificil};
typedef tColores tSecuencia[MAX_COLORES_SEQ];
typedef struct{
	string jugador;
	float puntuacion;
}tJugadores;
typedef tJugadores tLista[MAX_JUGADORES];

tColores charToColor(char color);
tColores intToColor(int numero);
void generarSecuencia(tSecuencia secuenciaColores, tModo modo, int numColores);
bool comprobarColor(const tSecuencia secuenciaColores, int indice, tColores color);
void mostrarSecuencia(const tSecuencia secuenciaColores, int numero);
float comenzarJuego(string nombre, tModo modo, int Ayudas);
bool utilizarAyuda(const tSecuencia secuenciaColores, int indice, int &numAyudas);

//Recibe un tipo de color y crea un string dependiendo del color que sea
string coloToString(tColores color);

//Recibe la respuesta del jugador y comprueba que es correcta
bool busquedaFallo(const tSecuencia secuencia, int numSec, int &Ayudas, float &puntos, tModo modo);
int Menu();
void escribirRanking(const tLista lista, int cont);
void cargarRanking(tLista lista, int &cont);

//Encargada de ordenar la lista de puntuaciones con sus jugadores correspondientes
//el ordén es de menor(posición 0) a mayor(como mucho posición 9)
void ordenarLista(tLista lista, int cont);

//Si la lista aún no está completa introduce la nueva puntuación con su respectivo jugador
//Si la lista ya está al completo,
//primero comprueba que la nueva puntuación sea mayor que la puntuación más pequeña de la lista
//si es mayor la nueva puntuación, entonces se introduce en esa posición y devuelve true
//sino la ignora y devuelve false
bool buscaHueco(tLista lista, string nomb, float puntos, int &cont);
void visualizarBestPlayer(const tLista lista, int cont);
void visualizarRanking(const tLista lista, int cont);

//Pide al usuario el caracter correspondiente al color que se encuentra en la posición que le está pidiendo
//Si no es un carácter correspondiente a ese modo de juego vuelve a pedir el carácter
//Si es un carácter válido, entonces obtiene el color correspondiente y lo devuelve
tColores compruebaCaracter(const tSecuencia sec, int pos, int &nAyudas, float &puntos, tModo modo);

//Muestra la puntuación que ha obtenido el jugador cuando acaba la partida.
void muestraPuntos(float puntos);

//Al cargar el nombre del jugador de esa habitación,
//para borra el espacio de antes del nombre,
//se crea otro string que tenga el nombre escrito correctamente
string obtieneNombre(string nombAux);

//Muestra un mensaje de bienvenida 
//y pide el nombre que tendrá como jugador.
string cabecera();

//Realiza la acción del system("pause")
void siguePartida();

int main(){
	string nombre;
	tModo modo;
	tLista lista;
	float puntos;
	int ayudas = NUM_AYUDAS;
	int opcion = -1;
	int cont = 0;
	srand(time(NULL));

	cargarRanking(lista, cont);

	while (opcion != 0){
		opcion = Menu();
		cout << endl;
		switch (opcion){
		case 1:
			modo = Facil;
			nombre = cabecera();
			puntos = comenzarJuego(nombre, modo, ayudas);
			if (buscaHueco(lista, nombre, puntos, cont)){
				cout << "Enhorabuena has entrado entre los 10 mejores jugadores" << endl;
				ordenarLista(lista, cont);
				escribirRanking(lista, cont);
			}
			else{ cout << "No has entrado entre los mejores jugadores" << endl; }
			break;
		case 2:
			modo = Dificil;
			nombre = cabecera();
			puntos = comenzarJuego(nombre, modo, ayudas);
			if (buscaHueco(lista, nombre, puntos, cont)){
				cout << "Enhorabuena has entrado entre los 10 mejores jugadores" << endl;
				ordenarLista(lista, cont);
				escribirRanking(lista, cont);
			}
			else{ cout << "No has entrado entre los mejores jugadores" << endl; }
			break;
		case 3:
			visualizarRanking(lista, cont);
			break;
		case 4:
			visualizarBestPlayer(lista, cont);
			break;
		}
		puntos = 0;
		system("pause");
		system("cls");
	}
	return 0;
}

string cabecera(){
	char car = ' ';
	string nombre = "";

	cout << "Bienvenido a Simon dice!!" << endl; 
	cout << "Como te llamas? ";
	cin.get(car);
	car = ' ';
	while (car != '\n'){
		cin.get(car);
		if (car != '\n'){ nombre += car; }
	} 

	return nombre;
}

void siguePartida(){
	char caracter;

	do{
		cin.get(caracter);
	} while (caracter != '\n');
	system("cls");
}

tColores charToColor(char color){
	char c = toupper(color);
	tColores colores = Nada;

	switch (c){
		case 'R':
			colores = Rojo;
		break;
		case 'V':
			colores = Verde;
			break;
		case 'A':
			colores = Azul;
			break;
		case 'D':
			colores = Dorado;
			break;
		case 'B':
			colores = Blanco;
			break;
		case 'M':
			colores = Marron;
			break;
		case 'N':
			colores = Naranja;
			break;
	}

	return colores;
}

tColores intToColor(int numero){
	tColores colores;

	switch (numero){
	case 0:
		colores = Rojo;
		break;
	case 1:
		colores = Verde;
		break;
	case 2:
		colores = Azul;
		break;
	case 3:
		colores = Dorado;
		break;
	case 4:
		colores = Blanco;
		break;
	case 5:
		colores = Marron;
		break;
	case 6:
		colores = Naranja;
		break;
	}

	return colores;
}

void generarSecuencia(tSecuencia secuenciaColores,tModo modo, int numColores){
	int color;
	switch (modo){
	case Facil:
		for (int i = 0; i < numColores; i++){
			color = rand() % 4;
			secuenciaColores[i] = intToColor(color);
		}
		break;
	case Dificil:
		for (int i = 0; i < numColores; i++){
			color = rand() % 7;
			secuenciaColores[i] = intToColor(color);
		}
		break;
	}
}

bool comprobarColor(const tSecuencia secuenciaColores, int indice, tColores color){
	bool ok = false;
	if (secuenciaColores[indice] == color) { ok = true; }
	
	return ok;
}

void mostrarSecuencia(const tSecuencia secuenciaColores, int numero){
	string color;
	cout << "Secuencia numero " << numero-2 << " : ";
	for (int i = 0; i < numero; i++){
		color = coloToString(secuenciaColores[i]);
		if (i == numero - 1){
			cout << color << endl;
		}
		else{
			cout << color << " - ";
		}
	}

	cout << "Memoriza la secuencia y " << system("pause");
	system("cls");
}

float comenzarJuego(string nombre, tModo modo, int ayudas){
	tSecuencia secuencia;
	int fin = MAX_COLORES_SEQ;
	bool ok = true;
	int numSec;
	int pos = 3;
	float puntuacion = 0;

	system("cls");
	cout <<"Hola " << nombre << ", pulsa una tecla para empezar a jugar... ";
	siguePartida();
	
	generarSecuencia(secuencia, modo, fin);

	if (modo == Facil){ numSec = MAX_COLORES_FACIL; }
	else { numSec = MAX_COLORES_DIFICIL; }

	while (ok && pos <= numSec){
		mostrarSecuencia(secuencia, pos);
		cout << "Ayudas disponibles: " << ayudas;
		cout << "                            Puntos: ";
		if (modo == Dificil){ cout << puntuacion*vDificil << endl; }
		else { cout << puntuacion << endl; }

		cout << nombre << ", introduce la secuencia de " << pos << " colores:" << endl;
		ok = busquedaFallo(secuencia, pos, ayudas, puntuacion, modo);
		if (ok){
			puntuacion = puntuacion + 10;
			cout << "Enhorabuena, has acertado la secuencia" << endl << endl;
			system("pause");
			system("cls");
		}
		pos++;
	}
	if (modo == Dificil) { puntuacion = puntuacion * vDificil; }
	if (!ok){
		cout << "Lo siento, has fallado, ";
		muestraPuntos(puntuacion);
	}
	else{
		cout << "Felicidades, has ganado la partida,  ";
		muestraPuntos(puntuacion);
	}

	return puntuacion;
}

void muestraPuntos(float puntos){
	cout << "has obtenido ";
	if (puntos < 0){cout << 0 << " puntos." << endl;}
	else{ cout << puntos << " puntos" << endl; }
	cout << endl;
	system("pause");
	system("cls");
}

bool busquedaFallo(const tSecuencia secuencia, int numSec, int &Ayudas, float &puntos, tModo modo){
	int i = 0;
	bool fallo = true;
	tColores aux;

	while (i < numSec && fallo){
		aux = compruebaCaracter(secuencia, i, Ayudas, puntos, modo);
		if (aux != Nada){//Podría ser nada si se utiliza la x para pedir ayuda
			fallo = comprobarColor(secuencia, i, aux);
			if (fallo){	puntos += 5;}
			else{cout << endl << "El color correcto era el " << coloToString(secuencia[i]) << endl;}
		}
		i++;
	}

	return fallo;
}

string coloToString(tColores color){
	string c;
	switch (color)
	{
	case Rojo:
		c = "Rojo";
		break;
	case Verde:
		c = "Verde";
		break;
	case Azul:
		c = "Azul";
		break;
	case Dorado:
		c = "Dorado";
		break;
	case Blanco:
		c = "Blanco";
		break;
	case Marron:
		c = "Marron";
		break;
	case Naranja:
		c = "Naranja";
		break;
	}
	return c;
}

bool utilizarAyuda(const tSecuencia secuenciaColores, int indice, int &numAyudas){
	bool ayudaDisponibles = false;
	string color;

	if (numAyudas == 0){
		cout << "Lo siento, no te queda ninguna ayuda, introduce un color." << endl;
	}
	else{
		ayudaDisponibles = true;
		numAyudas--;
		color = coloToString(secuenciaColores[indice]);
		cout << "El siguiente color es el " << color << ". Te quedan " << numAyudas << " ayudas." << endl;
	}
	return ayudaDisponibles;
}

int Menu(){
	int op = -1;

	cout << "Elija una opcion para continuar:" << endl;
	cout << "0: Salir." << endl;
	cout << "1: Jugar en modo sencillo." << endl;
	cout << "2: Jugar en modo dificil." << endl;
	cout << "3: Ver 10 mejores jugadores." << endl;
	cout << "4: Ver jugador(es) con la puntuacion mas alta." << endl;
	cout << "Opcion: ";
	cin >> op;
	while (op > 4 || op < 0 || cin.fail()){
		cin.sync();
		cin.clear();
		cout << "Por favor, introduzca una opcion valida: ";
		cin >> op;
	}

	return op;
}

void escribirRanking(const tLista lista, int cont){
	ofstream fichero;

	fichero.open(nomArch);

		for(int i = cont-1; i >= 0; i--){
			fichero << lista[i].puntuacion << " ";
			fichero << lista[i].jugador << endl;
		}

	fichero.close();
}

void cargarRanking(tLista lista, int &cont){
	ifstream fichero;
	int i = 0;
	float num;
	string nombAux;
	fichero.open(nomArch);

	if (fichero.is_open()){
		fichero >> num;
		while (!fichero.eof() && i < MAX_JUGADORES){
			if (num >= 0){
				lista[i].puntuacion = num;
				getline(fichero, nombAux);
				lista[i].jugador = obtieneNombre(nombAux);
				i++;
			}
			else{
				getline(fichero, nombAux);
			}
			fichero >> num;
		}
		ordenarLista(lista, i);
	}

	else { cout << "No se ha podido cargar la lista de puntuaciones" << endl; }

	fichero.close();
	cont = i;
}

string obtieneNombre(string nombAux){
	string nombJugador = "";
	int n = nombAux.size();

	for (int i = 0; i < n-1; i++){
		nombJugador += nombAux[i + 1];
	}
	return nombJugador;
}

void ordenarLista(tLista lista, int cont){
	string aux;

	for (int i = 1; i < cont; i++){
		float elemento = lista[i].puntuacion;
		string nombre = lista[i].jugador;
		int pos = i - 1;
		bool enc = lista[pos].puntuacion <= elemento;

		while (pos > 0 && !enc){
			lista[pos + 1] = lista[pos];
			pos--;
			enc = lista[pos].puntuacion <= elemento;
		}
		if (enc){
			lista[pos + 1].puntuacion = elemento;
			lista[pos + 1].jugador = nombre;
		}
		else{
			lista[1] = lista[0];
			lista[0].puntuacion = elemento;
			lista[0].jugador = nombre;
		}
	}
}

bool buscaHueco(tLista lista, string nomb, float puntos, int &cont){
	bool insertado = false;
	if (puntos >= lista[0].puntuacion){
		if (cont == MAX_JUGADORES){
			lista[0].puntuacion = puntos;
			lista[0].jugador = nomb;
		}
		else{
			lista[cont].puntuacion = puntos;
			lista[cont].jugador = nomb;
			cont++;
		}
		insertado = true;
	}
	else{
		if (cont < MAX_JUGADORES && puntos >= 0){
			lista[cont].puntuacion = puntos;
			lista[cont].jugador = nomb;
			cont++;
			insertado = true;
		}
	}
	return insertado;
}

void visualizarRanking(const tLista lista, int cont){
	int j = 1;
	for (int i = cont-1; i >= 0; i--){
		cout << " " << j << ".- " << lista[i].puntuacion << " " << lista[i].jugador << endl;
		j++;
	}
}

void visualizarBestPlayer(const tLista lista, int cont){
	int i = cont-1;
	int j = 1;

	if (cont > 0){
		if (lista[i].puntuacion != lista[i - 1].puntuacion){
			cout << " " << j << ".- " << lista[i].puntuacion << " " << lista[i].jugador << endl;
		}
		else{
			while (lista[i].puntuacion == lista[i - 1].puntuacion){
				cout << " " << j << ".- " << lista[i].puntuacion << " " << lista[i].jugador << endl;
				i--;
				j++;
			}
			cout << " " << j << ".- " << lista[i].puntuacion << " " << lista[i].jugador << endl;
		}
	}
	else{
		cout << "Por ahora no existe ningun jugador con la mejor puntuacion" << endl;
	}
}

tColores compruebaCaracter(const tSecuencia sec, int pos, int &nAyudas, float &puntos, tModo modo){
	tColores color = Nada;
	char col;
	bool ayudas = false;

	do{
		cin >> col;
		if (toupper(col) == 'X'){
			ayudas = utilizarAyuda(sec, pos, nAyudas);
			if (ayudas) { puntos = puntos - 7; }
		}
		else{ 
			color = charToColor(toupper(col));
			if (modo == Facil && color > Dorado){ color = Nada; }
			if (color == Nada){
				cout << "Por favor, introduzca un color valido" << endl;
			}
		}
	} while ((cin.fail() || color == Nada) && !ayudas);

	return color;
}
