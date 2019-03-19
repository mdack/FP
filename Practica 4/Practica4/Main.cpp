/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#include <iostream>
using namespace std;
#include "Gestor.h"

void menuRegistro(tGestor & gestor);
/*
* Muestra el menú de registro y devuelve una opción válida por el usuario.
*/
int menuReg();
/*
* Muestra el menú del usuario y devuelve una opción válida por el usuario.
*/
int menuUser();
void menuUsuario(tGestor & gestor);
void mostrarDatosUsu(tGestor & gestor);
void mostrarPartidasEnCurso(tGestor & gestor);
void elegirPartida(tGestor & gestor);
void menuPartida(tGestor & gestor);
void leerJugada(int & col);
/*
* Muestra el menú de partida y devuelve una opción válida por el usuario.
*/
int menuPar(tGestor const& gestor);


int main(){
	tGestor gestor;

	if (arrancar(gestor)){
		generarAccesos(gestor);
		menuRegistro(gestor);
		apagar(gestor);
	}
	else{
		cout << "No se han podido cargar los ficheros" << endl;
		system("pause");
	}
	
	return 0;
}

void menuRegistro(tGestor & gestor){
	int op = -1;
	string idUser, clave;
	while (op != 0){
		op = menuReg();
		switch (op)
		{
		case 1:
			cout << endl << "ACCESO" << endl;
			cout << "Nombre de usuario: "; cin >> idUser;
			cout << "Clave: "; cin >> clave;
			if (iniciarSesion(gestor, idUser, clave)){
				cout << endl << "Ha abierto correctamente una sesion" << endl << endl;
				mostrarDatosUsu(gestor);
				menuUsuario(gestor);
			}
			else{ cout << endl << "No se ha podido iniciar la sesion" << endl << endl; }
			break;
		case 2:
			cout << endl << "REGISTRO" << endl;
			cout << "Nombre de usuario: "; cin >> idUser;
			cout << "Clave: "; cin >> clave;
			if (crearCuenta(gestor, idUser, clave)){
				cout << endl <<  "Se ha creado correctamente su usuario" << endl << endl;
				menuUsuario(gestor);
			}
			else { cout << endl << "No se ha podido crear su usuario" << endl << endl; }
			break;
		}
		
	}
	
}

int menuReg(){
	int op;
	cout << "MENU REGISTRO" << endl;
	cout << "    1. Acceder a mi cuenta" << endl;
	cout << "    2. Registrarse" << endl;
	cout << "    0. Salir" << endl;
	cout << "Elija una opcion: ";
	cin >> op;
	while (cin.fail() || op > 2 || op < 0){
		cout << "Opcion no válida, por favor, elija una opcion: ";
		cin >> op;
	}
	return op;
}

void menuUsuario(tGestor & gestor){
	int op = -1;

	while (op != 0){
		cout << "MENU USUARIO"  << endl << endl;
		mostrarPartidasEnCurso(gestor);
		cout << endl << endl;
		op = menuUser();
		switch (op)
		{
		case 1:
			elegirPartida(gestor);
			if (gestor.posPartida != -1){
				mostrarPartida(gestor);
				menuPartida(gestor);
			}
			break;
		case 2:
			if (nuevaPartida(gestor)){ cout << endl << "Se ha creado una nueva partida" << endl << endl; }
			else{
				cout << endl << "Quedas en espera" << endl << endl;
			}
			break;
		case 3:
			ordenar_Fecha(gestor);
			break;
		case 4:
			ordenar_Turno(gestor);
			break;
		}
	}
	
}

int menuUser(){
	int op;
	cout << "   1. Ver Partida" << endl;
	cout << "   2. Nueva Partida" << endl;
	cout << "   3. Partidas por actualizacion" << endl;
	cout << "   4. Partidas por turno y fecha" << endl;
	cout << "   0. Salir" << endl;
	cout << "Elija una opcion: ";
	cin >> op;
	while (cin.fail() || op > 4 || op < 0){
		cin.clear();
		cin.sync();
		cout << "Opcion no valida, por favor, elija una opcion: ";
		cin >> op;
	}
	return op;
}

void mostrarDatosUsu(tGestor & gestor){
	string avisos;
	char sn;

	if (tieneAvisos(gestor, avisos)){
		cout << "Tiene avisos: " << endl;
		cout << avisos << endl;
		cout << "Quiere borrar los avisos (S/N)? ";
		cin >> sn;
		sn = toupper(sn);
		while (sn != 'S' && sn != 'N'){
			cout << "Respuesta no valida" << endl;
			cin.clear();
			cin.sync();
			cout << "Por favor, digame que desea: ";
			cin >> sn;
			sn = toupper(sn);
		}
		if (toupper(sn) == 'S'){ limpiarAvisos(gestor); }
	}
	cout << resumenActividad(gestor) << endl;
}

void mostrarPartidasEnCurso(tGestor & gestor){

	cout << " #    T    Jugador1      Jugador2      Fecha\n";
	cout << "---------------------------------------------------------------------------\n";
	for (int i = 1; i <= gestor.listUsers.users[gestor.usuario].listaAcceso.cont; i++){
		cout << " " << i << ".   ";
		cout << cabecera(gestor, i - 1);
	}
}

void elegirPartida(tGestor & gestor){
	int op;
	cout << "Elija una partida(0 para salir): ";
	cin >> op;
	while (cin.fail() || op > gestor.listUsers.users[gestor.usuario].listaAcceso.cont || op < 0){
		cin.clear();
		cin.sync();
		cout << "Respuesta no valida" << endl;
		cout << "Elija partida(0 para salir): ";
		cin >> op;
	}
	if (op != 0){ apuntaPartida(gestor, op-1); }
	else{ gestor.posPartida = op-1; }
}

void menuPartida(tGestor & gestor){
	int op = -1;
	int col;
	
		cout << endl;
		op = menuPar(gestor);
		switch (op)
		{
		case 1:
			leerJugada(col);
			jugarPartida(gestor, col);
			mostrarPartida(gestor);
			break;
		case 2:
			abandonarPartida(gestor);
			cout << endl << "Ha abandonado la partida" << endl;
			break;
		}
}

int menuPar(tGestor const& gestor){
	int op;
	int limite = 2;

	if (esSuTurno(gestor, gestor.posPartida)){
		cout << "   1. Jugar" << endl;
		cout << "   2. Abandonar" << endl;
	}
	else{
		cout << "   1. Abandonar" << endl;
		limite = 1;
	}
	cout << "   0. Salir" << endl;
	cout << "Elija una opcion: ";
	cin >> op;
	while (cin.fail() || op > limite || op < 0){
		cin.clear();
		cin.sync();
		cout << "Opcion no valida, por favor, elija una opcion: ";
		cin >> op;
	}
	return op;
}

void leerJugada(int & col){
	cout << "Elija una columna(1..." << COLS << "): ";
	cin >> col;
	while (cin.fail() || col > COLS || col < 0){
		cin.clear();
		cin.sync();
		cout << "Columna no valida, elija una columna: ";
		cin >> col;
	}
	col = col - 1;
}