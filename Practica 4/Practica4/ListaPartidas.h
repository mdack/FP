/*
* Milagros del Roc�o Pe�a Quineche 1�E
* Pr�ctica 4 - Gestor de Partidas
*/
#ifndef LISTAPARTIDAS_H
#define LISTAPARTIDAS_H

#include "Partida.h"

const int MAX_PARTIDAS = 10;
typedef tPartida tPartidas[MAX_PARTIDAS];

typedef struct{
	tPartidas parts;
	int cont;
}tListaPartidas;

void guardar(tListaPartidas const& partidas, ofstream & archivo);
bool cargar(tListaPartidas & partidas, ifstream & archivo);
bool insertar(tListaPartidas & partidas, tPartida const& partida);

#endif 