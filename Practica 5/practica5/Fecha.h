/*
* Milagros del Roc�o Pe�a Quineche 1�E
* Pr�ctica 4 - Gestor de Partidas
*/
#ifndef FECHA_H
#define FECHA_H

#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

typedef time_t tFecha;

tFecha fechaActual();
string stringFecha(tFecha fecha, bool hora);

#endif