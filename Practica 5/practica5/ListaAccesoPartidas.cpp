/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#include "ListaAccesoPartidas.h"

bool buscar(tListaAccesoPartidas const& lista, string const& id, int &pos);
void desplazarIzquierda(tListaAccesoPartidas & list, int pos);

void iniciar(tListaAccesoPartidas & lista){
	lista.cont = 0;
	for (int i = 0; i < MAX_PAR_US; i++){
		lista.partida[i] = new tPartida;
	}
}

bool llena(tListaAccesoPartidas const& lista){
	if (lista.cont == MAX_PAR_US){
		return true;
	}
	else{
		return false;
	}
}

bool insertar(tListaAccesoPartidas & lista, tPartida &par){
	bool insert = false;

	if (!llena(lista)){
		*(lista.partida[lista.cont]) = par;
		lista.cont++;
		insert = true;
	}
	return insert;
}

bool eliminar(tListaAccesoPartidas & lista, string const& id){
	bool eliminado = false;
	int pos = 0;

	if (buscar(lista, id, pos)){
		desplazarIzquierda(lista, pos);
		lista.cont--;
		eliminado = true;
	}

	return eliminado;
}

bool buscar(tListaAccesoPartidas const& lista, string const& id, int &pos){
	bool enc = false;

	if (lista.partida[pos]->id == id){
		enc = true;
	}
	else{
		pos = pos + 1;
		if (buscar(lista, id, pos)){ enc = true; }
	}
	return enc;
}


void desplazarIzquierda(tListaAccesoPartidas & list, int pos){
	for (int i = pos + 1; i < list.cont; ++i)
		list.partida[i - 1] = list.partida[i];
}

void apagar(tListaAccesoPartidas &lista){
	for (int i = 0; i < lista.cont; i++){
		delete lista.partida[i];
	}
}