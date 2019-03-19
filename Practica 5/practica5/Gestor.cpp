/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#include "Gestor.h"

void terminarPartida(tUsuario &ganador, tUsuario &perdedor);
void revisaPartidas(tGestor &gestor);

bool arrancar(tGestor & gestor){
	bool arrancado = false;

	gestor.listPartidas.cont = 0;
	gestor.listUsers.cont = 0;

	ifstream archivo1, archivo2;

	archivo1.open(archPartidas);
	archivo2.open(archUsers);

	if (archivo1.is_open() && archivo2.is_open()){
		arrancado = cargar(gestor.listPartidas, archivo1) && cargar(gestor.listUsers, archivo2);
	}

	archivo1.close();
	archivo2.close();

	return arrancado;
}

void apagar(tGestor & gestor){
	revisaPartidas(gestor);
	apagar(gestor.listPartidas, archPartidas);
	apagar(gestor.listUsers, archUsers);
}

void revisaPartidas(tGestor &gestor){
	tm ltm1, ltm2;
	tFecha fechAct = fechaActual();
	int mesAct, dayAct, mes, day;

	localtime_s(&ltm1, &fechAct);
	mesAct = 1 + ltm1.tm_mon;
	dayAct = ltm1.tm_mday;
	
	for (int i = 0; i < gestor.listPartidas.cont; i++){
		localtime_s(&ltm2, &gestor.listPartidas.parts[i]->lastAct);
		mes = 1 + ltm2.tm_mon;
		day = ltm2.tm_mday;

		if ((mesAct > mes) && gestor.listPartidas.parts[i]->estPartida != Terminada){
			int d = dayAct - day;
			int m = mesAct - mes;
			if (d > 0 || m > 1){
				gestor.listPartidas.parts[i]->estPartida = Terminada;
				gestor.listPartidas.parts[i]->estJuego.estado = Ganador;
				int p1, p2;
				string id1 = gestor.listPartidas.parts[i]->jug1;
				string id2 = gestor.listPartidas.parts[i]->jug2;
				buscar(gestor.listUsers, id1, p1);
				buscar(gestor.listUsers, id2, p2);

				if (gestor.listPartidas.parts[i]->estJuego.turno == Jugador1){
					terminarPartida(*(gestor.listUsers.users[p2]), *(gestor.listUsers.users[p1]));
				}
				else{
					terminarPartida(*(gestor.listUsers.users[p1]), *(gestor.listUsers.users[p2]));
				}
			}
		}
	}
}

void terminarPartida(tUsuario &ganador, tUsuario &perdedor){
	string cad1, cad2;

	tResultado resultado1 = Gana;
	tResultado resultado2 = Pierde;

	cad1 = "Ha perdido una partida contra " + ganador.id + " el " + stringFecha(fechaActual(), false) + "por no jugar en mas de un mes";
	cad2 = "Ha ganado una partida contra " + perdedor.id + " el " + stringFecha(fechaActual(), false) + "por esperar mas de un mes para jugar";

	aplicarFinPartida(perdedor, resultado2);
	aplicarFinPartida(ganador, resultado1);

	actualizarAvisos(perdedor, cad1);
	actualizarAvisos(ganador, cad2);
}

bool crearCuenta(tGestor & gestor, string const& idUsu, string const& clave){
	int pos;
	//(gestor.listUsers.cont < MAX_USERS &&
	bool creado =  (!buscar(gestor.listUsers, idUsu, pos));
	
	if (creado){
		tUsuario usuario;
		iniciar(usuario, idUsu, clave);
		insertar(gestor.listUsers, usuario, pos);
		gestor.usuario = pos;
	}
	return creado;
}

bool iniciarSesion(tGestor & gestor, string const& idUsu, string const&	clave){
	int pos;
	bool iniciar = false;
	if (buscar(gestor.listUsers, idUsu, pos)){
		iniciar = iniciarSesion(*(gestor.listUsers.users[pos]), clave);
		if (iniciar){
			gestor.usuario = pos;
		}
	}
	return iniciar;
}

bool tieneAvisos(tGestor const& gestor, string & aviso){
	bool tieneA = false;
	string avisoAux = gestor.listUsers.users[gestor.usuario]->avisos;
	if (avisoAux != "\n"){
		aviso = avisoAux;
		tieneA = true;
	}
	return tieneA;
}

void limpiarAvisos(tGestor & gestor){
	limpiarAvisos(*(gestor.listUsers.users[gestor.usuario]));
}
string resumenActividad(tGestor const& gestor){
	string cadena;
	ostringstream flujo;

	flujo << "Partidas ganadas: " << gestor.listUsers.users[gestor.usuario]->pGanadas << '\n';
	flujo << "Partidas perdidas: " << gestor.listUsers.users[gestor.usuario]->pPerdidas << '\n';
	flujo << "Partidas empatadas: " << gestor.listUsers.users[gestor.usuario]->pEmpates << '\n';
	flujo << "Nivel actual: " << nivelToString(gestor.listUsers.users[gestor.usuario]->nivel) << '\n';
	flujo << "Racha actual: " << gestor.listUsers.users[gestor.usuario]->racha << '\n';
	cadena = flujo.str();

	return cadena;
}


void generarAccesos(tGestor & gestor){
	
	iniciar(gestor.listAccesos);

	for (int i = 0; i < gestor.listPartidas.cont; i++){
		int pos = 0;
		if (gestor.listPartidas.parts[i]->estPartida == EnCurso){
			tPartida pAux = *(gestor.listPartidas.parts[i]);
			tUsuario usuAux = *(gestor.listUsers.users[gestor.usuario]);
				
			if ((pAux.jug1 == usuAux.id) || (pAux.jug2 == usuAux.id)){
				insertar(gestor.listAccesos, pAux);
			} 
		}
	}
}

int partidasUsuario(tGestor const& gestor){
	return gestor.listAccesos.cont;
}

string cabecera(tGestor const& gestor, int posEnCurso){
	ostringstream flujo;

	int pos = posEnCurso;
	
	if (esSuTurno(gestor, *(gestor.listAccesos.partida[pos]))){
		flujo << "*    ";
	}
	else{ flujo << "     "; }

	flujo << gestor.listAccesos.partida[pos]->jug1;
	for (int i = gestor.listAccesos.partida[pos]->jug1.size(); i < ESPACIO; i++){
		flujo << " ";
	}
	flujo << gestor.listAccesos.partida[pos]->jug2;
	for (int i = gestor.listAccesos.partida[pos]->jug2.size(); i < ESPACIO; i++){
		flujo << " ";
	}
	flujo << stringFecha(gestor.listAccesos.partida[pos]->lastAct, true) << "\n";
	return flujo.str();
}

void ordenar_Fecha(tGestor & gestor){
	int cont = partidasUsuario(gestor);
	tPartida *temp = new tPartida;
	for (int i = 1; i < cont; i++){
		temp = gestor.listAccesos.partida[i];
		tFecha fechAux = temp->lastAct;
		int pos = i - 1;
		bool enc = gestor.listAccesos.partida[pos]->lastAct <= fechAux;
		while ((pos > 0) && !enc){
			gestor.listAccesos.partida[pos+1] = gestor.listAccesos.partida[pos];
			pos--;
			enc = gestor.listAccesos.partida[pos]->lastAct <= fechAux;
		}
		if (enc) { gestor.listAccesos.partida[pos + 1] = temp; }
		else{
			gestor.listAccesos.partida[1] = gestor.listAccesos.partida[0];
			gestor.listAccesos.partida[0] = temp;
		}
	}
}

void ordenar_Turno(tGestor & gestor){
	int pUser = gestor.usuario;
	int cont = partidasUsuario(gestor);
	tPartida *temp = new tPartida;
	tPartida *p2 = new tPartida;
	for (int i = 1; i < cont; i++){
		 temp = gestor.listAccesos.partida[i];
		int pos = i - 1;
		p2 = gestor.listAccesos.partida[pos];
		bool enc = ((esSuTurno(gestor, *temp) && esSuTurno(gestor, *p2)) || (!esSuTurno(gestor, *temp) && !esSuTurno(gestor, *p2)));
		while ((pos > 0) && !enc){
			gestor.listAccesos.partida[pos + 1] = gestor.listAccesos.partida[pos];
			pos--;
			p2 = gestor.listAccesos.partida[pos];
			enc = ((esSuTurno(gestor, *temp) && esSuTurno(gestor, *p2)) || (!esSuTurno(gestor, *temp) && !esSuTurno(gestor, *p2)));
		}
		if (enc) { gestor.listAccesos.partida[pos + 1] = temp; }
		else{
			gestor.listAccesos.partida[1] = gestor.listAccesos.partida[0];
			gestor.listAccesos.partida[0] = temp;
		}
	}
}

bool esSuTurno(tGestor const& gestor, tPartida &partida){
	bool turno = false;
	if (partida.jug1 == gestor.listUsers.users[gestor.usuario]->id){
		if (partida.estJuego.turno == Jugador1){
			turno = true;
		}
	}
	if (partida.jug2 == gestor.listUsers.users[gestor.usuario]->id){
		if (partida.estJuego.turno == Jugador2){
			turno = true;
		}
	}
	return turno;
}

bool nuevaPartida(tGestor & gestor){
	int cont = gestor.listAccesos.cont;
	tUsuario usuario = *(gestor.listUsers.users[gestor.usuario]);
	int pos = gestor.usuario; 
	bool nPartida = false;

	if (cont < MAX_PAR_US && !usuario.espera){
		if (buscarUsuarioEsperando(gestor.listUsers, usuario.nivel, pos)){
			gestor.listUsers.users[pos]->espera = false;
			tPartida partida;
			nueva(partida, usuario.id, gestor.listUsers.users[pos]->id);
			if (insertar(gestor.listPartidas, partida) && insertar(gestor.listAccesos, partida)){
					nPartida = true;
			}
		}
		else{
			gestor.listUsers.users[gestor.usuario]->espera = true;
		}
	}
	else{
		if (cont == MAX_PAR_US){ cout << "Tiene demasiadas partidas en curso" << endl; }
		else{ gestor.listUsers.users[gestor.usuario]->espera = true; }
	}
	return nPartida;
}

void apuntaPartida(tGestor & gestor, int posParEnCurso){
	gestor.partida = gestor.listAccesos.partida[posParEnCurso];
}

void mostrarPartida(tGestor const& gestor){
	mostrar(gestor.partida->estJuego, gestor.partida->jug1, gestor.partida->jug2);
}

void jugarPartida(tGestor & gestor, int col){
	tUsuario usu = *(gestor.listUsers.users[gestor.usuario]);
	tFecha fecha = fechaActual();
	string cad;
	tResultado resultado1, resultado2;
	int pos;
	
	if (aplicarJugada(*(gestor.partida), col)){
		tEstado estado = gestor.partida->estJuego.estado;
		if (estado == Ganador || estado == Bloqueo){
			switch (estado)
			{
			case Ganador:
				cad = "Ha perdido una partida contra " + usu.id + " el " + stringFecha(fecha, false);
				resultado1 = Gana;
				resultado2 = Pierde;
				break;
			case Bloqueo:
				cad = "Ha empatado en una partida contra " + usu.id + " el " + stringFecha(fecha, false);
				resultado1 = Empata;
				resultado2 = Empata;
				break;
			}
			gestor.partida->estPartida = Terminada;
			if (usu.id == gestor.partida->jug1){
				buscar(gestor.listUsers, gestor.partida->jug2, pos);
			}
			else{
				buscar(gestor.listUsers, gestor.partida->jug1, pos);
			}
			aplicarFinPartida(*(gestor.listUsers.users[gestor.usuario]), resultado1);
			aplicarFinPartida(*(gestor.listUsers.users[pos]), resultado2);
			eliminar(gestor.listAccesos, gestor.partida->id);
		}
		else{
			cad = "Es tu turno en una partida contra " + usu.id + " iniciada el " + stringFecha(gestor.partida->ini, false);
			if (usu.id == gestor.partida->jug1){
				buscar(gestor.listUsers, gestor.partida->jug2, pos);
			}
			else{
				buscar(gestor.listUsers, gestor.partida->jug1, pos);
			}
		}
		gestor.partida->lastAct = fecha;
		int p = 0;
		if (buscar(gestor.listPartidas, gestor.partida->id, p)){
			gestor.listPartidas.parts[p] = gestor.partida;
		}

		actualizarAvisos(*(gestor.listUsers.users[pos]), cad);
	}
}

void abandonarPartida(tGestor & gestor){
	tPartida partida = *(gestor.partida);
	tUsuario usu = *(gestor.listUsers.users[gestor.usuario]);
	string cad = "Ha ganada una partida por abandono contra " + usu.id + " el " + stringFecha(fechaActual(), false);
	int pos;
	tResultado r1, r2;

	r1 = Pierde;
	r2 = Gana;
	if (usu.id == partida.jug1){
		buscar(gestor.listUsers, partida.jug2, pos);
	}
	else{
		buscar(gestor.listUsers, partida.jug1, pos);
	}
	actualizarAvisos(*(gestor.listUsers.users[pos]), cad);

	aplicarFinPartida(*(gestor.listUsers.users[gestor.usuario]), r1);
	aplicarFinPartida(*(gestor.listUsers.users[pos]), r2);

	abandonar(*(gestor.partida));

	int p = 0;
	buscar(gestor.listPartidas, partida.id, p);
	gestor.listPartidas.parts[p] = gestor.partida;

	eliminar(gestor.listAccesos, partida.id);
}