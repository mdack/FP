#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

const string nombArch = "reglas.txt";
const string nombFich = "configP1.txt";

int monedasHumano(int numMONEDAS);
int apuestaHumano(int eleccionM, int numMonedasH, int numMONEDAS);
int quienGana(int numMonedasM, int numMonedasH, int eleccionM, int eleccionH);
int eligeApuesta(int numMONEDAS);
int monedasMaquina(int numMONEDAS);
int apuestaMaquina(int numMonedasH, int numMONEDAS);
int menu();
int pedirMarcador();
int pedirMonedas();
bool mostrarReglas();
void juego(int marcador, int numMONEDAS);
bool cargaFichero(int &numMONEDAS, int &marcador);
void guardaFichero(int numMONEDAS, int marcador);
void juegoAutomatico(int marcador, int numMONEDAS);

int main(){
	srand(time(NULL));
	int numMONEDAS = 3;
	int MARCADOR = 2;
	bool leer;
	int op = -1;
	bool cargar = false;

	cargar = cargaFichero(numMONEDAS, MARCADOR);
	if (cargar){
		cout << "Las monedas que podras sacar son " << numMONEDAS << endl;
		cout << "El marcador empieza siendo " << MARCADOR << endl;
		cout << " " << endl;
	}

	else{
		cout << "El marcador y las monedas se incian por defecto." << endl;
		cout << " " << endl;
	}

	while (op != 0)	{
		op = menu();
		cout << " " << endl;
		switch (op){
		case 1:
			MARCADOR = pedirMarcador();
			break;
		case 2: 
			numMONEDAS = pedirMonedas();
			break;
		case 3:
			leer = mostrarReglas();
			if (!leer)
				cout << "No se ha podido abrir el archivo" << endl;
			break;
		case 4:
			juego(MARCADOR, numMONEDAS);
			break;
		case 5:
			juegoAutomatico(MARCADOR, numMONEDAS);
			break;
		}
		cout << " " << endl;
	}
	guardaFichero(numMONEDAS, MARCADOR);
	cout << "Fin del programa" << endl;
	system("pause");
	return 0;
}

int monedasHumano(int numMONEDAS){
	int coins = 0;

	cout << "Elige el numero de monedas que sacas (0 a " << numMONEDAS << ")"<< endl;
	cin >> coins;
	while ((cin.fail()) || ((coins < 0) || (coins > numMONEDAS))){
		cout << "Numero no valido" << endl;
		cin.clear();
		cin.sync();
		cout << "Elige el numero de monedas que sacas (0 a " << numMONEDAS << ")" << endl;
		cin >> coins;
	}
	return coins;
}

int apuestaHumano(int eleccionM, int numMonedasH, int numMONEDAS){
	int bet = eligeApuesta(numMONEDAS);
	while(bet == eleccionM || bet < numMonedasH){
		if (bet == eleccionM)
			cout << "No puede repetir la eleccion de la maquina... Intentalo de nuevo" << endl;
		if (bet < numMonedasH)
			cout << "No mientas... Intentalo de nuevo" << endl;
		bet = eligeApuesta(numMONEDAS);
	}
	return bet;
}

int eligeApuesta(int numMONEDAS){
	int apuesta = 0;
	int  COINS = numMONEDAS * 2;
	cout << "Introduce tu apuesta(0 a " << COINS << ")" << endl;
	cin >> apuesta;
	while (cin.fail() || apuesta < 0 || apuesta > COINS){
		cout << "Numero no valido" << endl;
		cin.clear();
		cin.sync();
		cout << "Introduce tu apuesta(0 a " << COINS << ")" << endl;
		cin >> apuesta;
	}
	return apuesta;
}

int quienGana(int numMonedasM, int numMonedasH, int eleccionM, int eleccionH){
	int winner = 0;
	int suma = numMonedasH + numMonedasM;
	cout << "La maquina saco " << numMonedasM << endl;
	cout << "El humano saco " << numMonedasH << endl;
	if (eleccionH == suma)
		winner = 2;
	if (eleccionM == suma)
		winner = 1;
	return winner;
}

int monedasMaquina(int numMONEDAS){
	int coinsM = rand() % numMONEDAS;
	return coinsM;
}

int apuestaMaquina(int numMonedasH, int numMONEDAS){
	int COINS = numMONEDAS * 2;
	int apuestaM = rand() % COINS;
	while (apuestaM < numMonedasH){
		apuestaM = rand() % COINS;
	}
	return apuestaM;
}

int menu(){
	int opcion = 0;
	cout << "1 - Cambiar el marcador" << endl;
	cout << "2 - Cambiar el numero de monedas" << endl;
	cout << "3 - Acerca del juego de los chinos" << endl;
	cout << "4 - Jugar una partida" << endl;
	cout << "5 - Jugar una partida automatica" << endl;
	cout << "0 - Salir" << endl;
	cout << "Introduce una opcion, de 0 a 4... ";
	cin >> opcion;

	//Limpia el cin no válido y vuelve a preguntar
	while (cin.fail() || opcion < 0 || opcion > 5){
		cout << "Opcion no valida" << endl;
		cin.clear();
		cin.sync();
		cin >> opcion;
	}
	return opcion;
}

int pedirMarcador(){
	int marcador;

	cout << "Introduce un valor para el marcador ";
	cin >> marcador;

	return marcador;
}

int pedirMonedas(){
	int monedas;

	cout << "Introduce el numero de monedas con el que deseas jugar ";
	cin >> monedas;

	return monedas;
}

bool mostrarReglas(){
	bool ok = false;
	ifstream archivo;
	string cadena;

	archivo.open(nombArch);

	if (archivo.is_open()){
		getline(archivo, cadena);
		while (cadena != "XXX"){
			cout << cadena << endl;
			getline(archivo, cadena);
		}
		ok = true;
	}

	archivo.close();

	return ok;
}

void juego(int marcador, int numMONEDAS){
	int numMonedasH, numMonedasM;
	int eleccionM, eleccionH;
	int jugador;
	int M = 0, H = 0;

	while (M < marcador && H < marcador){
		numMonedasH = monedasHumano(numMONEDAS);
		numMonedasM = monedasMaquina(numMONEDAS);
		eleccionM = apuestaMaquina(numMonedasH, numMONEDAS);
		cout << "Creo que hemos sacado " << eleccionM << " monedas entre los dos" << endl;
		cout << "Ahora es tu turno..." << endl;
		eleccionH = apuestaHumano(eleccionM, numMonedasH, numMONEDAS);
		jugador = quienGana(numMonedasM, numMonedasH, eleccionM, eleccionH);
		cout << " " << endl;
		switch (jugador){
		case 0:
			cout << "No ha ganado nadie" << endl;
			break;
		case 1:
			cout << "Gana la maquina" << endl;
			M++;
			break;
		case 2:
			cout << "Gana el humano" << endl;
			H++;
			break;
		}
		cout << "----------------------------------" << endl;
	}
	if (jugador == 1){
		cout << "La maquina ha ganado la partida!!!" << endl;
		cout << "El humano gano " << H << " ronda(s)" << endl;
	}
	else{
		cout << "El humano ha ganado la partida!!!" << endl;
		cout << "La maquina gano " << M << " ronda(s)" << endl;
	}
}

bool cargaFichero(int &numMONEDAS, int &marcador){
	ifstream fichero;
	bool load = false;
	char aux;

	fichero.open(nombFich);

	if (fichero.is_open()){
		fichero >> numMONEDAS;
		fichero.get(aux);
		fichero >> marcador;
		load = true;
	}
	
	else{
		numMONEDAS = 3;
		marcador = 2;
	}

	fichero.close();

	return load;
}

void guardaFichero(int numMONEDAS, int marcador){
	ofstream fichero;

	fichero.open(nombFich);

	fichero << numMONEDAS << endl;
	fichero << marcador << endl;

	fichero.close();
}

void juegoAutomatico(int marcador, int numMONEDAS){
	int numMonedas1, numMonedas2;
	int eleccion1, eleccion2;
	int M1 = 0, M2 = 0;
	while (M1 < marcador || M2 < marcador){
		numMonedas1 = monedasMaquina(numMONEDAS);
		numMonedas2 = monedasMaquina(numMONEDAS);
		eleccion1 = apuestaMaquina(numMonedas2, numMONEDAS);
		cout << "La maquina 1 saco " << numMonedas1 << endl;
		cout << "La maquina 2 saco " << numMonedas2 << endl;
		cout << endl << "HABLA LA MAQUINA 1..." << endl;
		cout << endl << "Creo que hemos sacado " << eleccion1 << " moneda(s) entre los dos" << endl;
		int suma = numMonedas1 + numMonedas2;
		if (suma == eleccion1){
			cout << "Gana la maquina 1" << endl;
			M1++;
		}
		else{
			cout << "Ahora es el turno de la maquina 2..." << endl;
			cout << "HABLA LA MAQUINA 2..." << endl;
			if (numMonedas1 != 0 && numMonedas2 != 0)
				eleccion2 = (rand() % numMonedas1) + (rand() % numMonedas2);
			else if (numMonedas1 != 0)
				eleccion2 = rand() % numMonedas1 + numMonedas2;
			else if (numMonedas2 != 0)
				eleccion2 = rand() % numMonedas2 + numMonedas1;
			cout << endl << "Creo que hemos sacado " << eleccion2 << " moneda(s) entre los dos" << endl;
			if (suma == eleccion2){
				cout << "Gana la maquina 2" << endl;
				M2++;
			}
			else
				cout << "No ha ganado nadie" << endl;
		}
		cout << "--------------------------" << endl;
		system("pause");
	}
}