/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#ifndef LISTAPARTIDAS_H
#define LISTAPARTIDAS_H

#include "Partida.h"
#include "checkML.h"

const string nombHis = "historico.txt";

typedef struct{
	tPartida **parts;
	int cont;
	int size;
}tListaPartidas;

void guardar(tListaPartidas const& partidas, ofstream & archivo);
bool cargar(tListaPartidas & partidas, ifstream & archivo);
bool insertar(tListaPartidas & partidas, tPartida const& partida);
void redimensionar(tListaPartidas &partidas);
void apagar(tListaPartidas& partidas, string nombArch);
bool buscar(const tListaPartidas &partidas, string id, int &pos);

#endif 