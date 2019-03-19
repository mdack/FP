/*
* Milagros del Roc�o Pe�a Quineche 1�E
* Pr�ctica 4 - Gestor de Partidas
*/
#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H

#include "Usuario.h"
#include "checkML.h"

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

//const int MAX_USERS = 5;
//typedef tUsuario tUsuarios[MAX_USERS];

typedef struct{
	tUsuario **users; //Si quisiera adem�s hacer el array de variables dinamicas a�ado esto tUsuario **users;
	int cont;
	int size;
}tListaUsuarios; //Lista con variables dinamicas y array din�mico

bool cargar(tListaUsuarios & usuarios, ifstream & archivo);
void guardar(tListaUsuarios const& usuarios, ofstream & archivo);
bool buscarUsuarioEsperando(tListaUsuarios const& usuarios, tNivel nivel, int & pos);
bool buscar(tListaUsuarios const& usuarios, string const& idUser, int &pos);
bool insertar(tListaUsuarios & usuarios, tUsuario const& usuario, int &pos);
void redimensionar(tListaUsuarios& usuarios);
void apagar(tListaUsuarios& usuarios, string nombArch);

#endif