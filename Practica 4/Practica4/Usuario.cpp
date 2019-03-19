/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#include "Usuario.h"

bool cargar(tUsuario & usuario, ifstream & archivo){
	bool cargado;
	string id, auxiliar;
	char espacio;
	unsigned long int num;

	archivo >> id;
	cargado = (id != CENTINELA);
	if (cargado){
		usuario.id = id;
		archivo >> usuario.pass;
		archivo >> num; usuario.nivel = tNivel(num);
		archivo >> num; usuario.racha = num;
		archivo >> usuario.espera;
		archivo >> num; usuario.pGanadas = num;
		archivo >> num; usuario.pPerdidas = num;
		archivo >> num; usuario.pEmpates = num;
		archivo >> num; usuario.fecha = tFecha(num);
		archivo.get(espacio);

		string aux, avisos;
		getline(archivo, aux);
		while (aux != CENTINELA) {
			avisos += aux;
			avisos += '\n';
			getline(archivo, aux);
		}
		usuario.avisos = avisos;
	}
	return cargado;
}

void guardar(tUsuario const& usuario, ofstream & archivo){
	string aux;

	archivo << usuario.id << '\n';
	archivo << usuario.pass << '\n';
	archivo << usuario.nivel << ' ' << usuario.racha << ' ' << usuario.espera << '\n'; 
	archivo << usuario.pGanadas << ' ' << usuario.pPerdidas << ' ' << usuario.pEmpates << '\n';
	archivo << usuario.fecha << '\n';
	archivo << usuario.avisos;
	archivo << CENTINELA << '\n';
}

bool iniciarSesion(tUsuario & usuario, string const& clave){
	bool ok = (usuario.pass == clave);

	if (ok){ usuario.fecha = fechaActual(); }

	return ok;
}

void iniciar(tUsuario & usuario, string const& id, string const& pas){
	usuario.id = id;
	usuario.pass = pas;
	
	usuario.nivel = Principiante;
	usuario.racha = 0;
	usuario.espera = false;

	usuario.pGanadas = 0;
	usuario.pPerdidas = 0;
	usuario.pEmpates = 0;

	usuario.fecha = fechaActual();

	usuario.avisos = "\n";
	iniciar(usuario.listaAcceso);
}

void actualizarAvisos(tUsuario & usu, string const& aviso){
	if (usu.avisos != "\n"){ usu.avisos = usu.avisos + aviso + "\n"; }
	else{ usu.avisos = aviso + "\n"; }
}

void limpiarAvisos(tUsuario & usu){
	usu.avisos = "\n";
}

string nivelToString(tNivel nivel){
	string level;

	switch (nivel)
	{
	case 0:
		level = "Principiante";
		break;
	case 1:
		level = "Medio";
		break;
	case 2:
		level = "Experto";
		break;
	}
	return level;
}

bool nuevaPartida(tUsuario & usuario, tParIdEn const& par){
	bool ok = false;

	if (usuario.listaAcceso.cont < MAX_PAR_US){
		insertar(usuario.listaAcceso, par);
		if (usuario.listaAcceso.cont == MAX_PAR_US){ usuario.espera = true; }
		usuario.espera = false;
		ok = true;
	}
	else{ usuario.espera = true; }
	return ok;
}

void aplicarFinPartida(tUsuario & usuario, string const& idPar, tResultado resultado){
	switch (resultado)
	{
	case Gana:
		usuario.pGanadas++;
		if (usuario.racha < 0){ usuario.racha = 0; }
		usuario.racha++;
		if (usuario.racha == NRN){
			switch (usuario.nivel)
			{
			case Principiante:
				usuario.nivel = Medio;
				break;
			case Medio:
				usuario.nivel = Experto;
				break;
			}
			usuario.racha = 0;
		}
		break;
	case Pierde:
		usuario.pPerdidas++;
		if (usuario.racha > 0){ usuario.racha = 0; }
		usuario.racha--;
		if (usuario.racha == -NRN){
			switch (usuario.nivel)
			{
			case Experto:
				usuario.nivel = Medio;
				break;
			case Medio:
				usuario.nivel = Principiante;
				break;
			}
			usuario.racha = 0;
		}
		break;
	case Empata:
		usuario.pEmpates++;
		usuario.racha = 0;
		break;
	}
	eliminar(usuario.listaAcceso, idPar);
}