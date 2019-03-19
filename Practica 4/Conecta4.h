#ifndef CONECTA4_H
#define CONECTA4_H

#include <fstream>
#include <string>

// El juego Conecta 4 consta de un tablero formado por siete columnas y seis filas.
// En una partida participan dos jugadores, uno con fichas verdes y otro rojas.
// Inicialmente todas las posiciones del tablero están libres. Cada jugador coloca 
// alternativamente una ficha en una columna. La ficha colocada cae por su propio peso 
// hasta el fondo de la columna correspondiente (primera fila de la columna libre).
// La partida la gana el jugador que coloque en primer lugar cuatro de sus fichas en 
// línea horizontal, vertical o en diagonal. La partida queda en tablas si ninguno 
// de los jugadores es capaz de alinear cuatro fichas después de llenar el tablero.

// Los tableros de Conecta 4 tienen 6 filas y 7 columnas
const int FILAS = 6;
const int COLS = 7;

// Enumerado que se utiliza para representar el turno del juego
typedef enum { Jugador1 = 12, Jugador2 = 10, Nadie = 0 } tTurno;

// y también la situación de cada posición del tablero
typedef tTurno tFicha;

// El juego puede estar en marcha (Jugando) o puede haber acabado por 
// dos motivos: ya hay ganador o se ha producido un bloqueo en el que 
// el tablero se ha llenado sin que ningún jugador conecte 4 fichas.
typedef enum { Jugando, Ganador, Bloqueo } tEstado;

// Tipo principal
typedef struct {
   tEstado estado;
   tTurno turno;
   int fichas;
   tFicha tablero[FILAS][COLS];
} tConecta4;

//---------------------------------------------------------------------------

// Establece el estado inicial del juego (tablero vacío, estado Jugando y turno de Jugador1)
void iniciar(tConecta4 & juego);

// Si es posible, coloca una ficha del jugador que tiene el turno en la columna col (valor entre 0 y 6).
// Devuelve un booleano que indica si ha podido realizarse la jugada
bool aplicarJugada(tConecta4 & juego, int col);

// Muestra el estado del juego: el tablero, los nombres de los jugadores (que se reciben
// como argumentos) asociados al color de su ficha, y de quién es el turno
void mostrar(tConecta4 const& juego, std::string  const& jugador1, std::string const& jugador2);

// Operaciones para cargar y guardar el estado de un juego en un fichero
void guardar(tConecta4 const& juego, std::ofstream & flujo);
bool cargar(tConecta4 & juego, std::ifstream & flujo);

#endif  // CONECTAC4_H
