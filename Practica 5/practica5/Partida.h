/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#ifndef PARTIDA_H
#define PARTIDA_H

#include "Fecha.h"
#include "Conecta4.h"
#include "checkML.h"
#include <string>
using namespace std;

typedef enum {EnCurso, Terminada}tEstadoPartida;

typedef struct{
	string id;
	string jug1, jug2;
	tFecha ini, lastAct;
	tEstadoPartida estPartida;
	tConecta4 estJuego;
}tPartida;

void nueva(tPartida & partida, string const& jugador1, string const& jugador2);
bool cargar(tPartida & partida, ifstream & archivo);
void guardar(tPartida const& partida, ofstream & archivo);
bool aplicarJugada(tPartida & partida, int col);
void abandonar(tPartida & partida);

#endif