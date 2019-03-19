/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#ifndef LISTAACCESOPARTIDAS_H
#define LISTAACCESOPARTIDAS_H

#include "ListaPartidas.h"
#include "checkML.h"

#include <string>
using namespace std;

const int MAX_PAR_US = 3;

typedef struct{
	tPartida *partida[MAX_PAR_US];
	int cont;
}tListaAccesoPartidas;

void iniciar(tListaAccesoPartidas & lista);
bool llena(tListaAccesoPartidas const& lista);
bool insertar(tListaAccesoPartidas & lista, tPartida &par);
bool eliminar(tListaAccesoPartidas & lista, string const& id);
void apagar(tListaAccesoPartidas &lista);

#endif 