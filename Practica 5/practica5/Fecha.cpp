/*
* Milagros del Roc�o Pe�a Quineche 1�E
* Pr�ctica 4 - Gestor de Partidas
*/
#include "Fecha.h"
#include <iostream>
#include <sstream>

tFecha fechaActual(){ return time(0); }

string stringFecha(tFecha fecha, bool hora){
	ostringstream resultado;
	tm ltm;

	localtime_s(&ltm, &fecha);
	resultado << setfill('0') << setw(4) << 1900 + ltm.tm_year << '/'
		<< setw(2) << 1 + ltm.tm_mon << '/' << setw(2) << ltm.tm_mday;
	if (hora) resultado << " (" << setw(2) << ltm.tm_hour << ':' << setw(2)
		<< ltm.tm_min << ':' << setw(2) << ltm.tm_sec << ')';

	return resultado.str();
}