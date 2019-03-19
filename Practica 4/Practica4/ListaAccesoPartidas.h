/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#ifndef LISTAACCESOPARTIDAS_H
#define LISTAACCESOPARTIDAS_H

#include <string>
using namespace std;

const int MAX_PAR_US = 5;

typedef struct{
	string id;
	int enlace;
}tParIdEn;

typedef tParIdEn tAccesosPartidas[MAX_PAR_US];

typedef struct{
	tAccesosPartidas accesos;
	int cont;
}tListaAccesoPartidas;

void iniciar(tListaAccesoPartidas & lista);
bool llena(tListaAccesoPartidas const& lista);
bool insertar(tListaAccesoPartidas & lista, tParIdEn par);
bool eliminar(tListaAccesoPartidas & lista, string const& id);

#endif 