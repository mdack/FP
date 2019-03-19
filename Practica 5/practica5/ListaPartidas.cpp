/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#include "ListaPartidas.h"
#include <iostream>
using namespace std;

void iniciar(tListaPartidas &partidas, int cont);
void guardarCont(int cont, string nombre);

void iniciar(tListaPartidas &partidas, int cont){
	partidas.parts = new tPartida*[cont];
	partidas.cont = 0;
	partidas.size = cont;
	for (int i = 0; i < partidas.size; i++){
		partidas.parts[i] = new tPartida;
	}
}

void guardar(tListaPartidas const& partidas, ofstream & archivo){
	ofstream flujo;
	int c1 = 0, c2 = 0;

	flujo.open(nombHis, ios::app);
	archivo << c1 << endl;
	flujo.seekp(0, ios::beg);
	flujo << c2 << endl;
	for (int i = 0; i < partidas.cont; i++){
		if (partidas.parts[i]->estPartida == EnCurso){
			guardar(*(partidas.parts[i]), archivo);
			c1++;
		}
		else{
			flujo.seekp(0, ios::end);
			guardar(*(partidas.parts[i]), flujo);
			c2++;
		}
	}
	flujo.close();

	guardarCont(c1, "partidas.txt");
	guardarCont(c2, nombHis);
}

void guardarCont(int cont, string nombre){
	int ent;
	fstream f;
	f.open(nombre, ios::in | ios::out);
	f.seekg(0, ios::beg);
	f >> ent;
	f.seekp(0, ios::beg);
	f << ent + cont << endl;
	f.close();
}

bool cargar(tListaPartidas & partidas, ifstream & archivo){
	tPartida auxiliar;
	int num;
	bool cargado = true;

	archivo >> num; 
	iniciar(partidas, num);

	while (cargado && partidas.cont < num) {
		cargado = (cargar(*(partidas.parts[partidas.cont]), archivo) && (partidas.cont < num));
		partidas.cont++;
	}
	
	return cargado;
}

bool insertar(tListaPartidas & partidas, tPartida const& partida){
	bool insercion = true;

	if (partidas.cont == partidas.size){
		redimensionar(partidas);
	}
	
	
	*(partidas.parts[partidas.cont]) = partida;
	partidas.cont++;

	return insercion;
}

void redimensionar(tListaPartidas &partidas){
	int nuevaCapacidad = (partidas.size * 3) / 2 + 1;
	tPartida **auxArray = new tPartida*[nuevaCapacidad];
	partidas.size = nuevaCapacidad;
	for (int i = 0; i < partidas.size; i++){
		auxArray[i] = new tPartida;
	}

	for (int i = 0; i < partidas.cont; i++){
		auxArray[i] = partidas.parts[i];
	}

	delete[] partidas.parts;

	partidas.parts = auxArray;
}

void apagar(tListaPartidas& partidas, string nombArch){
	ofstream fichero;

	fichero.open(nombArch);
	guardar(partidas, fichero);
	fichero.close();

	//Se liberan las direcciones de memoria de cada usuario dinamico
	for (int i = 0; i < partidas.size; i++){
		delete partidas.parts[i];
	}
	//Se libera la direccion de memoria que tenia el array usuario
	delete[] partidas.parts;
}

bool buscar(const tListaPartidas &partidas, string id, int &pos){
	int i = 0;
	bool enc = false;

	while (i < partidas.cont && !enc){
		if (partidas.parts[i]->id == id){ enc = true; }
		i++;
	}

	if (enc){
		pos = i - 1;
	}

	return enc;
}