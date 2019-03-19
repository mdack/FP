/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H

#include "Usuario.h"

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

const int MAX_USERS = 5;

typedef tUsuario tUsuarios[MAX_USERS];

typedef struct{
	tUsuarios users;
	int cont;
}tListaUsuarios;

bool cargar(tListaUsuarios & usuarios, ifstream & archivo);
void guardar(tListaUsuarios const& usuarios, ofstream & archivo);
bool buscarUsuarioEsperando(tListaUsuarios const& usuarios, tNivel nivel, int & pos);
bool buscar(tListaUsuarios const& usuarios, string const& idUser, int &pos);
bool insertar(tListaUsuarios & usuarios, tUsuario const& usuario, int &pos);

#endif