/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#include "Gestor.h"

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
	ofstream fichero1, fichero2;

	fichero1.open(archPartidas);
	fichero2.open(archUsers);

	guardar(gestor.listPartidas, fichero1);
	guardar(gestor.listUsers, fichero2);

	fichero1.close();
	fichero2.close();
}

bool crearCuenta(tGestor & gestor, string const& idUsu, string const& clave){
	int pos;
	bool creado = (gestor.listUsers.cont < MAX_USERS && !buscar(gestor.listUsers, idUsu, pos));
	
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
		iniciar = iniciarSesion(gestor.listUsers.users[pos], clave);
		if (iniciar){
			gestor.usuario = pos;
		}
	}
	return iniciar;
}

bool tieneAvisos(tGestor const& gestor, string & aviso){
	bool tieneA = false;
	string avisoAux = gestor.listUsers.users[gestor.usuario].avisos;
	if (avisoAux != "\n"){
		aviso = avisoAux;
		tieneA = true;
	}
	return tieneA;
}

void limpiarAvisos(tGestor & gestor){
	limpiarAvisos(gestor.listUsers.users[gestor.usuario]);
}
string resumenActividad(tGestor const& gestor){
	string cadena;
	ostringstream flujo;

	flujo << "Partidas ganadas: " << gestor.listUsers.users[gestor.usuario].pGanadas << '\n';
	flujo << "Partidas perdidas: " << gestor.listUsers.users[gestor.usuario].pPerdidas << '\n';
	flujo << "Partidas empatadas: " << gestor.listUsers.users[gestor.usuario].pEmpates << '\n';
	flujo << "Nivel actual: " << nivelToString(gestor.listUsers.users[gestor.usuario].nivel) << '\n';
	flujo << "Racha actual: " << gestor.listUsers.users[gestor.usuario].racha << '\n';
	cadena = flujo.str();

	return cadena;
}


void generarAccesos(tGestor & gestor){

	for (int i = 0; i < gestor.listPartidas.cont; i++){
		int pos = 0;
		if (gestor.listPartidas.parts[i].estPartida == EnCurso){
			tParIdEn part;
			part.id = gestor.listPartidas.parts[i].id;
			part.enlace = i;

			buscar(gestor.listUsers, gestor.listPartidas.parts[i].jug1, pos);
			if (gestor.listUsers.users[pos].listaAcceso.cont > 0){
				insertar(gestor.listUsers.users[pos].listaAcceso, part);
			}
			else{
				iniciar(gestor.listUsers.users[pos].listaAcceso);
				insertar(gestor.listUsers.users[pos].listaAcceso, part);
			}
			buscar(gestor.listUsers, gestor.listPartidas.parts[i].jug2, pos);
			if (gestor.listUsers.users[pos].listaAcceso.cont > 0){
				insertar(gestor.listUsers.users[pos].listaAcceso, part);
			}
			else{
				iniciar(gestor.listUsers.users[pos].listaAcceso);
				insertar(gestor.listUsers.users[pos].listaAcceso, part);
			}
		}
	}
}

int partidasUsuario(tGestor const& gestor){
	return gestor.listUsers.users[gestor.usuario].listaAcceso.cont;
}

string cabecera(tGestor const& gestor, int posEnCurso){
	ostringstream flujo;

	int pos = gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[posEnCurso].enlace;
	
	if (esSuTurno(gestor, pos)){
		flujo << "*    ";
	}
	else{ flujo << "     "; }

	flujo << gestor.listPartidas.parts[pos].jug1;
	for (int i = gestor.listPartidas.parts[pos].jug1.size(); i < ESPACIO; i++){
		flujo << " ";
	}
	flujo << gestor.listPartidas.parts[pos].jug2;
	for (int i = gestor.listPartidas.parts[pos].jug2.size(); i < ESPACIO; i++){
		flujo << " ";
	}
	flujo << stringFecha(gestor.listPartidas.parts[pos].lastAct, true) << "\n";
	return flujo.str();
}

void ordenar_Fecha(tGestor & gestor){
	
	for (int i = 1; i < gestor.listUsers.users[gestor.usuario].listaAcceso.cont; i++){
		tParIdEn temp = gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[i];
		int p1 = temp.enlace;
		tFecha fechAux = gestor.listPartidas.parts[p1].lastAct;
		int pos = i - 1;
		int p2 = gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[pos].enlace;
		bool enc = gestor.listPartidas.parts[p2].lastAct <= fechAux;
		while ((pos > 0) && !enc){
			gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[pos + 1] = gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[pos];
			pos--;
			p2 = gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[pos].enlace;
			enc = gestor.listPartidas.parts[p2].lastAct <= fechAux;
		}
		if (enc) { gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[pos + 1] = temp; }
		else{
			gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[1] = gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[0];
			gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[0] = temp;
		}
	}
}

void ordenar_Turno(tGestor & gestor){
	int pUser = gestor.usuario;

	for (int i = 1; i < gestor.listUsers.users[pUser].listaAcceso.cont; i++){
		tParIdEn temp = gestor.listUsers.users[pUser].listaAcceso.accesos[i];
		int p1 = temp.enlace;
		int pos = i - 1;
		int p2 = gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[pos].enlace;
		bool enc = esSuTurno(gestor, p1) && esSuTurno(gestor, p2);
		while ((pos > 0) && !enc){
			gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[pos + 1] = gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[pos];
			pos--;
			p2 = gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[pos].enlace;
			enc = esSuTurno(gestor, p1) && esSuTurno(gestor, p2);
		}
		if (enc) { gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[pos + 1] = temp; }
		else{
			gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[1] = gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[0];
			gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[0] = temp;
		}
	}
}

bool esSuTurno(tGestor const& gestor, int posPartida){
	bool turno = false;
	if (gestor.listPartidas.parts[posPartida].jug1 == gestor.listUsers.users[gestor.usuario].id){
		if (gestor.listPartidas.parts[posPartida].estJuego.turno == Jugador1){
			turno = true;
		}
	}
	if (gestor.listPartidas.parts[posPartida].jug2 == gestor.listUsers.users[gestor.usuario].id){
		if (gestor.listPartidas.parts[posPartida].estJuego.turno == Jugador2){
			turno = true;
		}
	}
	return turno;
}

bool nuevaPartida(tGestor & gestor){
	tUsuario usuario = gestor.listUsers.users[gestor.usuario];
	int pos = gestor.usuario; 
	bool nPartida = false;

	if (usuario.listaAcceso.cont < MAX_PAR_US && !usuario.espera){
		if (buscarUsuarioEsperando(gestor.listUsers, usuario.nivel, pos)){
			gestor.listUsers.users[pos].espera = false;
			tPartida partida;
			nueva(partida, usuario.id, gestor.listUsers.users[pos].id);
			if (insertar(gestor.listPartidas, partida)){
				tParIdEn par;
				par.id = partida.id;
				par.enlace = gestor.listPartidas.cont - 1;
				if (insertar(gestor.listUsers.users[gestor.usuario].listaAcceso, par) && insertar(gestor.listUsers.users[pos].listaAcceso, par)){
					nPartida = true;
				}
			}
		}
		else{
			gestor.listUsers.users[gestor.usuario].espera = true;
		}
	}
	else{
		gestor.listUsers.users[gestor.usuario].espera = true; 
	}
	return nPartida;
}

void apuntaPartida(tGestor & gestor, int posParEnCurso){
	gestor.posPartida = gestor.listUsers.users[gestor.usuario].listaAcceso.accesos[posParEnCurso].enlace;
}

void mostrarPartida(tGestor const& gestor){
	mostrar(gestor.listPartidas.parts[gestor.posPartida].estJuego, gestor.listPartidas.parts[gestor.posPartida].jug1, gestor.listPartidas.parts[gestor.posPartida].jug2);
}

void jugarPartida(tGestor & gestor, int col){
	tUsuario usu = gestor.listUsers.users[gestor.usuario];
	tFecha fecha = fechaActual();
	string cad;
	tResultado resultado1, resultado2;
	int pos;
	
	if (aplicarJugada(gestor.listPartidas.parts[gestor.posPartida], col)){
		if (gestor.listPartidas.parts[gestor.posPartida].estJuego.estado == Ganador || gestor.listPartidas.parts[gestor.posPartida].estJuego.estado == Bloqueo){
			switch (gestor.listPartidas.parts[gestor.posPartida].estJuego.estado)
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
			
			gestor.listPartidas.parts[gestor.posPartida].estPartida = Terminada;
			if (usu.id == gestor.listPartidas.parts[gestor.posPartida].jug1){
				buscar(gestor.listUsers, gestor.listPartidas.parts[gestor.posPartida].jug2, pos);
			}
			else{
				buscar(gestor.listUsers, gestor.listPartidas.parts[gestor.posPartida].jug1, pos);
			}
			aplicarFinPartida(gestor.listUsers.users[gestor.usuario], gestor.listPartidas.parts[gestor.posPartida].id, resultado1);
			aplicarFinPartida(gestor.listUsers.users[pos], gestor.listPartidas.parts[gestor.posPartida].id, resultado2);
		}
		else{
			cad = "Es tu turno en una partida contra " + usu.id + " iniciada el " + stringFecha(gestor.listPartidas.parts[gestor.posPartida].ini, false);
			if (usu.id == gestor.listPartidas.parts[gestor.posPartida].jug1){
				buscar(gestor.listUsers, gestor.listPartidas.parts[gestor.posPartida].jug2, pos);
			}
			else{
				buscar(gestor.listUsers, gestor.listPartidas.parts[gestor.posPartida].jug1, pos);
			}
		}
		gestor.listPartidas.parts[gestor.posPartida].lastAct = fecha;
		
		actualizarAvisos(gestor.listUsers.users[pos], cad);
	}
}

void abandonarPartida(tGestor & gestor){
	tPartida partida = gestor.listPartidas.parts[gestor.posPartida];
	tUsuario usu = gestor.listUsers.users[gestor.usuario];
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
	actualizarAvisos(gestor.listUsers.users[pos], cad);

	aplicarFinPartida(gestor.listUsers.users[gestor.usuario], partida.id, r1);
	aplicarFinPartida(gestor.listUsers.users[pos], partida.id, r2);

	abandonar(gestor.listPartidas.parts[gestor.posPartida]);
}