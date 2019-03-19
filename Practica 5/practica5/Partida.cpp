/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#include "Partida.h"
#include <iostream>
#include <sstream>

void nueva(tPartida & partida, string const& jugador1, string const& jugador2){
	stringstream id;
	
	partida.jug1 = jugador1;
	partida.jug2 = jugador2;
	partida.ini = fechaActual();
	partida.lastAct = fechaActual();

	id << partida.lastAct << "_" << partida.jug1 << "_" << partida.jug2;
	partida.id = id.str();
	partida.estPartida = EnCurso;
	iniciar(partida.estJuego);
}

bool cargar(tPartida & partida, ifstream & archivo){
	string auxiliar;
	unsigned long int num;
	bool cargado;

	archivo >> auxiliar; partida.id = auxiliar;
	archivo >> auxiliar; partida.jug1 = auxiliar;
	archivo >> auxiliar; partida.jug2 = auxiliar;
	archivo >> num; partida.ini = num;
	archivo >> num; partida.lastAct = num;
	archivo >> num; partida.estPartida = tEstadoPartida(num);
	cargado = cargar(partida.estJuego, archivo);

	return (cargado && !archivo.fail()); 

}

void guardar(tPartida const& partida, ofstream & archivo){
	archivo << partida.id << '\n';
	archivo << partida.jug1 << '\n';
	archivo << partida.jug2 << '\n';
	archivo << partida.ini << ' ' << partida.lastAct << '\n';
	archivo << partida.estPartida << '\n';
	guardar(partida.estJuego, archivo);
}

bool aplicarJugada(tPartida & partida, int col){
	bool aplicada = aplicarJugada(partida.estJuego, col);
	return aplicada;
}

void abandonar(tPartida & partida){
	partida.estPartida = Terminada;
	partida.lastAct = fechaActual();
}