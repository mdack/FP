/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#include "ListaPartidas.h"
#include <iostream>
using namespace std;

bool buscar(const tListaPartidas &partidas, string id);

void guardar(tListaPartidas const& partidas, ofstream & archivo){
	archivo << partidas.cont << '\n';
	for (int i = 0; i < partidas.cont; i++) {
		guardar(partidas.parts[i], archivo);
	}
}

bool cargar(tListaPartidas & partidas, ifstream & archivo){
	tPartida auxiliar;
	int num;
	bool cargado = true;

	archivo >> num; 
	if (num <= MAX_PARTIDAS){
		
		bool insert = true;

		while (cargado && insert && partidas.cont < num) {
			cargado = (cargar(auxiliar, archivo) && (partidas.cont < num));
			insert = insertar(partidas, auxiliar);
		}
	}
	else{ cargado = false; }
	return cargado;
}

bool insertar(tListaPartidas & partidas, tPartida const& partida){
	bool insercion = (partidas.cont < MAX_PARTIDAS);
	
	if (insercion){
		//Insertamos
		partidas.parts[partidas.cont] = partida;
		partidas.cont++;
	}

	return insercion;
}
