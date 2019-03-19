/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#include "ListaUsuarios.h"

void desplazamientoDerecha(tListaUsuarios &usuarios, int pos);

bool cargar(tListaUsuarios & usuarios, ifstream& archivo){
	bool cargado = true;
	int cont;

	archivo >> cont;

	if (cont <= MAX_USERS){
		while (cargado && usuarios.cont < cont){
			cargado = (cargar(usuarios.users[usuarios.cont], archivo));
			usuarios.cont++;
		}
	}
	return cargado;
}

void guardar(tListaUsuarios const& usuarios, ofstream & archivo){
	archivo << usuarios.cont << '\n';
	for (int i = 0; i < usuarios.cont; i++)
		guardar(usuarios.users[i], archivo);
}

bool buscarUsuarioEsperando(tListaUsuarios const& usuarios, tNivel nivel, int & pos){
	int i = 0;
	bool enc = false;

	while ((i < usuarios.cont) && !enc){
		if (i != pos){
			if (usuarios.users[i].listaAcceso.cont < MAX_PAR_US){
				if ((usuarios.users[i].nivel == nivel) && (usuarios.users[i].espera)){ enc = true; }
			}
		}
		i++;
	}
	if (enc) 
		pos = i - 1;
	
	return enc;
}

bool buscar(tListaUsuarios const& usuarios, string const& idUser, int &pos){
	bool enc = false;
	int ini = 0, fin = usuarios.cont - 1, mitad;

	while (ini <= fin && !enc) {
		mitad = (ini + fin) / 2;
		if (idUser == usuarios.users[mitad].id) enc = true;
		else if (idUser < usuarios.users[mitad].id) fin = mitad - 1;
		else ini = mitad + 1;
	}

	if (enc) pos = mitad;
	else pos = ini;

	return enc;
}

bool insertar(tListaUsuarios & usuarios, tUsuario const& usuario, int &pos){
	bool insercion = ((usuarios.cont < MAX_USERS) && !buscar(usuarios, usuario.id, pos));

	if (insercion) {
		desplazamientoDerecha(usuarios, pos);
		// Insertamos
		usuarios.users[pos] = usuario;
		usuarios.cont++;
	}
	return insercion;
}

void desplazamientoDerecha(tListaUsuarios &usuarios, int pos){
	for (int i = usuarios.cont; i > pos; i--) {
		usuarios.users[i] = usuarios.users[i - 1];
	}
}