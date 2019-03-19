/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#ifndef GESTOR_H
#define GESTOR_H

#include "ListaPartidas.h"
#include "ListaUsuarios.h"

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

const string archPartidas = "partidas.txt";
const string archUsers = "usuarios.txt";
const int ESPACIO = 14;
typedef struct{
	tListaPartidas listPartidas;
	tListaUsuarios listUsers;
	int usuario; //pos de usuario activo
	int posPartida; //pos de la partida seleccionada por el usuario
}tGestor;

bool arrancar(tGestor & gestor);
void apagar(tGestor & gestor);
void generarAccesos(tGestor & gestor);
bool esSuTurno(tGestor const& gestor, int posPartida);

//Menu Registo del Main
bool crearCuenta(tGestor & gestor, string const& idUsu, string const& clave);
bool iniciarSesion(tGestor & gestor, string const& idUsu, string const&	clave);
bool tieneAvisos(tGestor const& gestor, string & aviso);
void limpiarAvisos(tGestor & gestor);
string resumenActividad(tGestor const& gestor);

//Menu Usuario del Main 
int partidasUsuario(tGestor const& gestor);
string cabecera(tGestor const& gestor, int posEnCurso);
void ordenar_Fecha(tGestor & gestor);
void ordenar_Turno(tGestor & gestor);
bool nuevaPartida(tGestor & gestor);
void apuntaPartida(tGestor & gestor, int posParEnCurso);

//Menu Partida
void mostrarPartida(tGestor const& gestor);
void jugarPartida(tGestor & gestor, int col);
void abandonarPartida(tGestor & gestor);

#endif