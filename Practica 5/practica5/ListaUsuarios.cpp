/*
* Milagros del Rocío Peña Quineche 1ºE
* Práctica 4 - Gestor de Partidas
*/
#include "ListaUsuarios.h"

void desplazamientoDerecha(tListaUsuarios &usuarios, int pos);
void iniciar(tListaUsuarios &usuarios, int cont);

void iniciar(tListaUsuarios &usuarios, int cont){
	usuarios.users = new tUsuario*[cont];
	usuarios.cont = 0;
	usuarios.size = cont;
	for (int i = 0; i < usuarios.size; i++){
		usuarios.users[i] = new tUsuario;
	}
}

bool cargar(tListaUsuarios & usuarios, ifstream& archivo){
	bool cargado = true;
	int cont;

	archivo >> cont;
	iniciar(usuarios, cont);

	while (cargado && (usuarios.cont < cont)){
		cargado = (cargar(*(usuarios.users[usuarios.cont]), archivo));
		usuarios.cont++;
	}
	return cargado;
}

void guardar(tListaUsuarios const& usuarios, ofstream & archivo){
	archivo << usuarios.cont << '\n';
	for (int i = 0; i < usuarios.cont; i++)
		guardar(*(usuarios.users[i]), archivo);
}

bool buscarUsuarioEsperando(tListaUsuarios const& usuarios, tNivel nivel, int & pos){
	int i = 0;
	bool enc = false;

	while ((i < usuarios.cont) && !enc){
		if (i != pos){
			if ((usuarios.users[i]->nivel == nivel) && (usuarios.users[i]->espera)){ enc = true; }
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
		if (idUser == usuarios.users[mitad]->id) enc = true;
		else if (idUser < usuarios.users[mitad]->id) fin = mitad - 1;
		else ini = mitad + 1;
	}

	if (enc) pos = mitad;
	else pos = ini;

	return enc;
}

bool insertar(tListaUsuarios & usuarios, tUsuario const& usuario, int &pos){
	bool insercion = (!buscar(usuarios, usuario.id, pos));

	if (insercion) {
		if (usuarios.cont == usuarios.size){
			redimensionar(usuarios);
		}
		if (pos < usuarios.cont)
		desplazamientoDerecha(usuarios, pos);
		// Insertamos
		*(usuarios.users[pos]) = usuario;
		usuarios.cont++;
	}
	return insercion;
}

void redimensionar(tListaUsuarios& usuarios){
	int nuevaCapacidad = (usuarios.size * 3) / 2 + 1;
	tUsuario **auxArray = new tUsuario*[nuevaCapacidad];
	usuarios.size = nuevaCapacidad;
	for (int i = 0; i < usuarios.size; i++){
		auxArray[i] = new tUsuario;
	}

	for (int i = 0; i < usuarios.cont; i++){
		auxArray[i] = usuarios.users[i];
	}
	
	delete[] usuarios.users;
	
	usuarios.users = auxArray;
}

void desplazamientoDerecha(tListaUsuarios &usuarios, int pos){
	tUsuario **auxArray = new tUsuario*[usuarios.size];
	for (int i = 0; i < usuarios.size; i++){
		auxArray[i] = new tUsuario;
	}
	for (int i = usuarios.cont; i > pos; i--) {
		auxArray[i] = usuarios.users[i - 1];
	}
	delete[] usuarios.users;
	
	usuarios.users = auxArray;
}

void apagar(tListaUsuarios& usuarios, string nombArch){
	ofstream fichero;

	fichero.open(nombArch);
	guardar(usuarios, fichero);
	fichero.close();

	//Se liberan las direcciones de memoria de cada usuario dinamico
	for (int i = 0; i < usuarios.size; i++){
		delete usuarios.users[i];
	}
	//Se libera la direccion de memoria que tenia el array usuario
	delete[] usuarios.users;
}