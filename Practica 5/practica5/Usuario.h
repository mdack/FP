/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#ifndef USUARIO_H
#define USUARIO_H

#include "Fecha.h"
#include "checkML.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

const string CENTINELA = "_X_X_X_";
const int MAX_INT_PAR = 6;
const int NRN = 3;

typedef enum {Principiante, Medio, Experto}tNivel;
typedef enum{Gana, Pierde, Empata}tResultado;

typedef struct {
	string id;
	string pass;
	tNivel nivel;
	int racha;
	bool espera;
	int pGanadas, pPerdidas, pEmpates;
	tFecha fecha;
	string avisos;
}tUsuario;

bool cargar(tUsuario &usuario, ifstream & archivo);
void guardar(tUsuario const& usuario, ofstream & archivo);
bool iniciarSesion(tUsuario & usuario, string const& clave);
void iniciar(tUsuario & usuario, string const& id, string const& pas);
void actualizarAvisos(tUsuario & usu, string const& aviso);
void limpiarAvisos(tUsuario & usu);
/*
* Crea un string que describa el nivel del usuario.
*/
string nivelToString(tNivel nivel);
//bool nuevaPartida(tUsuario & usuario, tParIdEn const& par);
bool nuevaPartida(tUsuario & usuario);
//void aplicarFinPartida(tUsuario & usuario, string const& idPar, tResultado resultado);
void aplicarFinPartida(tUsuario & usuario, tResultado resultado);

#endif USUARIO_H