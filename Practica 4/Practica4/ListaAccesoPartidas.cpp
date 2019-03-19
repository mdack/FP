/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#include "ListaAccesoPartidas.h"

bool buscar(tListaAccesoPartidas const& lista, string const& id, int &pos);
void desplazarIzquierda(tListaAccesoPartidas & list, int pos);

void iniciar(tListaAccesoPartidas & lista){
	lista.cont = 0;
}

bool llena(tListaAccesoPartidas const& lista){
	if (lista.cont == MAX_PAR_US){
		return true;
	}
	else{
		return false;
	}
}

bool insertar(tListaAccesoPartidas & lista, tParIdEn par){
	bool insert = false;

	if (!llena(lista)){
		lista.accesos[lista.cont] = par;
		lista.cont++;
		insert = true;
	}
	return insert;
}

bool eliminar(tListaAccesoPartidas & lista, string const& id){
	bool eliminado = false;
	int pos;

	if (buscar(lista, id, pos)){
		desplazarIzquierda(lista, pos);
		lista.cont--;
		eliminado = true;
	}

	return eliminado;
}

bool buscar(tListaAccesoPartidas const& lista, string const& id, int &pos){
	bool enc = false;
	int i = 0;

	while (i < lista.cont && !enc){
		if (lista.accesos[i].id == id){ enc = true; }
		else{ i++; }
	}

	if (enc){ pos = i; }

	return enc;
}

void desplazarIzquierda(tListaAccesoPartidas & list, int pos){
	for (int i = pos + 1; i < list.cont; ++i)
		list.accesos[i - 1] = list.accesos[i];
}