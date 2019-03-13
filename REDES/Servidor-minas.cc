#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include<signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

#include <fstream>
#include <iostream>

#include "juego.hpp"
#include "Jugador.hpp"
#include <vector>

#define MSG_SIZE 250
#define MAX_CLIENTS 50


/*

* El servidor ofrece el servicio de un chat

* El servidor ofrece el servicio de un chat

*/

int findJugador(std::vector<Jugador> &j, int i);
void cambiarEstado(std::vector<Jugador> &j, int i, int estado);
Jugador getJugador(std::vector<Jugador> &j, int i);
juego getJuego(std::vector<juego> &j, int i);
int getIndexJuego(std::vector<juego> &j, int i);
void setJuego(std::vector<juego> &juegos ,juego j, int i);
bool comprobarTurno(juego j, int i);

void manejador(int signum);
void salirCliente(int i, fd_set * readfds, std::vector<Jugador> &Jugadores, std::vector<juego> &Juegos);
int estadoCliente(int i, fd_set * readfds, int * numClientes, int arrayClientes[]);

void registrarJugador(char *buffer, int i);
void login1(char *buffer, int i, std::vector<Jugador> &Jugadores);
void login2(char *buffer, int i, std::vector<Jugador> &Jugadores);
void iniciarPartida(char *buffer, int i, std::vector<Jugador> &Jugadores, std::vector<juego> &Juegos);
void descubrirCasilla(char *buffer, int i, std::vector<juego> &Juegos, std::vector<Jugador> &Jugadores);
void mostrarTableroUsuario(std::vector<juego> &Juegos, int index);
void ponerBandera(char *buffer, int i, std::vector<juego> &Juegos, std::vector<Jugador> &Jugadores);


int findJugador(std::vector<Jugador> &j, int i);
bool findJugadorUsuario(std::vector<Jugador> &j, char * nombre);
void deleteJugador(std::vector<Jugador> &j, Jugador ju);
void deleteJuego(std::vector<juego> &j, juego ju);
void cambiarEstado(std::vector<Jugador> &j, int i, int estado);

int main ( )
{

	/*----------------------------------------------------

	Descriptor del socket y buffer de datos

	Descriptor del socket y buffer de datos

	-----------------------------------------------------*/
	int sd, new_sd;
	struct sockaddr_in sockname, from;
	char buffer[MSG_SIZE];
	socklen_t from_len;

	fd_set readfds, auxfds;
	int salida;
	int arrayClientes[MAX_CLIENTS];

	std::vector<Jugador> Jugadores; //50 JUGADORES MAXIMO
	std::vector<juego> Juegos; //25 Juegos MAXIMO

	int numClientes = 0;
	//contadores
	int i,j;
	int recibidos;

	/* --------------------------------------------------
	Se abre el socket
	---------------------------------------------------*/
	sd = socket (AF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		perror("No se puede abrir el socket cliente\n");
		exit (1);
	}

	// Activaremos una propiedad del socket que permitir· que otros
	// sockets puedan reutilizar cualquier puerto al que nos enlacemos.
	// Esto permitir· en protocolos como el TCP, poder ejecutar un
	// mismo programa varias veces seguidas y enlazarlo siempre al
	// mismo puerto. De lo contrario habrÌa que esperar a que el puerto
	// quedase disponible (TIME_WAIT en el caso de TCP)

	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(2000);
	sockname.sin_addr.s_addr =  INADDR_ANY;

	if (bind (sd, (struct sockaddr *) &sockname, sizeof (sockname)) == -1)
	{
		perror("Error en la operación bind");
		exit(1);
	}

	/*---------------------------------------------------------------------
	Del las peticiones que vamos a aceptar sólo necesitamos el
	tamaño de su estructura, el resto de información (familia, puerto,
	ip), nos la proporcionará el método que recibe las peticiones.
	----------------------------------------------------------------------*/
	from_len = sizeof (from);


	if(listen(sd,1) == -1){
		perror("Error en la operación de listen");
		exit(1);
	}

	//Inicializar los conjuntos fd_set
	FD_ZERO(&readfds);
	FD_ZERO(&auxfds);
	FD_SET(sd,&readfds);
	FD_SET(0,&readfds);


	//Capturamos la señal SIGINT (Ctrl+c)
	signal(SIGINT,manejador);

	/*-----------------------------------------------------------------------
	El servidor acepta una petición
	------------------------------------------------------------------------ */
	while(1){

		//Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)

		auxfds = readfds;

		salida = select(FD_SETSIZE,&auxfds,NULL,NULL,NULL);

		if(salida > 0){


			for(i=0; i<FD_SETSIZE; i++){

				//Buscamos el socket por el que se ha establecido la comunicación
				if(FD_ISSET(i, &auxfds)) {

					if( i == sd){

						if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1){
							perror("Error aceptando peticiones");
						}
						else
						{
							if(numClientes < MAX_CLIENTS){
								arrayClientes[numClientes] = new_sd;
								numClientes++;
								FD_SET(new_sd,&readfds);

								strcpy(buffer, "+Ok. Usuario conectado\n");

								send(new_sd,buffer,strlen(buffer),0);

							}
							else
							{
								bzero(buffer,sizeof(buffer));
								strcpy(buffer,"Demasiados clientes conectados\n");
								send(new_sd,buffer,strlen(buffer),0);
								close(new_sd);
							}
						}
					}
					else if (i == 0){
						//Se ha introducido información de teclado
						bzero(buffer, sizeof(buffer));
						fgets(buffer, sizeof(buffer),stdin);

						//Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
						if(strcmp(buffer,"SALIR\n") == 0){

							for (j = 0; j < numClientes; j++){
								send(arrayClientes[j], "Desconexion servidor\n", strlen("Desconexion servidor\n"),0);
								close(arrayClientes[j]);
								FD_CLR(arrayClientes[j],&readfds);
							}
							close(sd);
							exit(-1);


						}

						//Mensajes que se quieran mandar a los clientes (implementar)

					}
					else{
						bzero(buffer,sizeof(buffer));

						recibidos = recv(i,buffer,sizeof(buffer),0);

						if(recibidos > 0){

							if(strcmp(buffer,"SALIR\n") == 0){

								salirCliente(i, &readfds, Jugadores, Juegos);

							}
							if(strncmp(buffer,"REGISTRO -u ", 12) == 0){ //si el cliente desea registrarse

								registrarJugador(buffer, i);

							}
							//bzero(buffer, sizeof(buffer)); //Esto se usa al final de las funciones de strncmp(los if's)


							if(strncmp(buffer,"USUARIO ", strlen("USUARIO ")) == 0){

								//Si el cliente desea iniciar sesion [Parte 1]
								login1(buffer, i, Jugadores);

							} //si el cliente desea logearse

							if( ( strncmp(buffer,"PASSWORD ", strlen("PASSWORD ") ) == 0 ) && ( findJugador(Jugadores, i) == 0 ) ){

								//Si el cliente desea iniciar sesion [Parte 2]
								login2(buffer, i, Jugadores);

							} //para validar la password


							if( (strncmp(buffer,"INICIAR-PARTIDA", strlen("INICIAR-PARTIDA") ) == 0) && ( findJugador(Jugadores, i) == 1 ) ){

								//Inicia la partida y se le envia a ambos jugadores el mismo tablero
								iniciarPartida(buffer, i, Jugadores, Juegos);

							}else if((strncmp(buffer,"INICIAR-PARTIDA", strlen("INICIAR-PARTIDA") ) == 0) && (findJugador(Jugadores, i) == -1) ){
								send(i, "Necesitas iniciar sesion antes de iniciar partida\n", strlen("Necesitas iniciar sesion antes de iniciar partida\n"),0);
							}


							if( (strncmp(buffer,"DESCUBRIR ", strlen("DESCUBRIR ") ) == 0) && ( findJugador(Jugadores, i) == 2 )){

								//Descubre la casilla que dice el jugador en turno por teclado
								descubrirCasilla(buffer, i, Juegos, Jugadores);

							}


							if( (strncmp(buffer,"PONER-BANDERA ", strlen("PONER-BANDERA ") ) == 0) && ( findJugador(Jugadores, i) == 2 )){

								//Pone bandera en la casilla que dice el jugador en turno por teclado
								int index=getIndexJuego(Juegos , i);
								if( ((Juegos[index].getTurno() == 1)&&(Juegos[index].getBanderas1() == 10))||((Juegos[index].getTurno() == 2)&&(Juegos[index].getBanderas2() == 10)) ){
									send(i, "Maximo de banderas colocadas\n", strlen("Maximo de banderas colocadas\n"),0);
								}
								else{
									ponerBandera(buffer, i, Juegos, Jugadores);
								}
							}

							//If para controlar que el comando introducido NO es correcto
							if( (strncmp(buffer,"PONER-BANDERA ", strlen("PONER-BANDERA ") ) != 0)&&(strncmp(buffer,"DESCUBRIR ", strlen("DESCUBRIR ") ) != 0)&&
							(strncmp(buffer,"INICIAR-PARTIDA", strlen("INICIAR-PARTIDA") ) != 0)&&
							(strncmp(buffer,"PASSWORD ", strlen("PASSWORD ") ) != 0 )&&(strncmp(buffer,"USUARIO ", strlen("USUARIO ")) != 0)&&
							(strncmp(buffer,"REGISTRO -u ", 12) != 0)&&(strcmp(buffer,"SALIR\n") != 0)){
								send(i, "El comando introducido no es correcto\n", strlen("El comando introducido no es correcto\n"),0);
							}


						}
						//Si el cliente introdujo ctrl+c
						if(recibidos== 0)
						{
							printf("El socket %d, ha introducido ctrl+c\n", i);
							//Eliminar ese socket
							salirCliente(i, &readfds, Jugadores, Juegos);
						}
					}
				}
			}
		}
	}

	close(sd);
	return 0;

}

void salirCliente(int i, fd_set * readfds, std::vector<Jugador> &Jugadores, std::vector<juego> &Juegos){


	if( (findJugador(Jugadores,i) == 1)||(findJugador(Jugadores,i) == 0) ){
		send(i, "Saliendo del servidor...\n", strlen("Saliendo del servidor...\n"),0);
		deleteJugador(Jugadores, getJugador(Jugadores, i));

	}


	if( findJugador(Jugadores,i) == 2 ){ //Si el jugador que quiere salir esta jugando
		if(getJuego(Juegos,i).getJugador1().getIdentificador() == i){ //Si es el jugador1 que quiere salir...
			send(i, "Saliendo de la partida...\n", strlen("Saliendo de la partida...\n"),0);
			send(getJuego(Juegos,i).getJugador2().getIdentificador(), "Su contrincante abandono la partida, vuelva a INICIAR-PARTIDA...\n", strlen("Su contrincante abandono la partida, vuelva a INICIAR-PARTIDA...\n"),0);
			cambiarEstado(Jugadores, getJuego(Juegos,i).getJugador2().getIdentificador(), 1); //Cambiamos su estado a logueado

			deleteJugador(Jugadores, getJuego(Juegos,i).getJugador1()); //eliminamo el jugador que sale de la partida
			deleteJuego(Juegos, getJuego(Juegos,i)); //elimino el juego

		}
		else{
			send(i, "Saliendo de la partida...\n", strlen("Saliendo de la partida...\n"),0);
			send(getJuego(Juegos,i).getJugador1().getIdentificador(), "Su contrincante abandono la partida, vuelva a INICIAR-PARTIDA...\n", strlen("Su contrincante abandono la partida, vuelva a INICIAR-PARTIDA...\n"),0);
			cambiarEstado(Jugadores, getJuego(Juegos,i).getJugador1().getIdentificador(), 1); //Cambiamos su estado a logueado

			deleteJugador(Jugadores, getJuego(Juegos,i).getJugador2()); //eliminamo el jugador que sale de la partida
			deleteJuego(Juegos, getJuego(Juegos,i)); //elimino el juego
		}

	}


	close(i);
	FD_CLR(i,readfds);


}

void registrarJugador(char *buffer, int i){

	char usuario[50];
	char password[50];
	if(sscanf(buffer, "REGISTRO -u %s -p %s",usuario,password)){
		std::ifstream ficheroin("usuarios.txt");

		std::ofstream ficheroout("usuarios.txt", std::ofstream::app);

		char usuarioLeido[50];
		char passwordLeido[50];
		bool encontrado=false;

		while(ficheroin >> usuarioLeido >> passwordLeido){ //lee los usuarios del fichero
			if(strcmp(usuario, usuarioLeido) == 0){ //si el usuario ya esta registrado en el fichero
				send(i, "Usuario ya registrado\n", strlen("Usuario ya registrado\n"),0);
				encontrado=true;
				break;
			}
		}
		if(encontrado == false){

			ficheroout << usuario << " " << password << std::endl;

			send(i, "Usuario registrado correctamente\n", strlen("Usuario registrado correctamente2\n"),0);
		}

		ficheroin.close();
		ficheroout.close();
	}

};

void login1(char *buffer, int i, std::vector<Jugador> &Jugadores){
	char usuario[50];
	bool encontrado = false;

	if( (sscanf(buffer, "USUARIO %s",usuario)) && (findJugadorUsuario(Jugadores, usuario)) ){ //Para evitar repetidos
		std::ifstream fichero("usuarios.txt");
		if(!fichero.is_open()){ //si no existe el fichero
			send(i, "Error en el sistema, no se ha podido iniciar sesion\n", strlen("Error en el sistema, no se ha podido iniciar sesion\n"),0);
		}
		else{
			char usuarioLeido[50];
			char passwordLeido[50];
			while(fichero >> usuarioLeido >> passwordLeido){ //lee los usuarios del fichero
				if(strcmp(usuario, usuarioLeido) == 0){ //si el usuario ya esta registrado en el fichero
					send(i, "+Ok Usuario correcto\n", strlen("+Ok Usuario correcto\n"),0);
					encontrado = true;

					Jugador ju(i, usuario); // se crea un jugador con el estado == 0
					Jugadores.push_back(ju);

					break;
				}
			}
			if(encontrado == false){
				send(i, "-Err Error en la validacion\n", strlen("-Err Error en la validacion\n"),0);
			}
		}

		fichero.close();
	}
	else{
		send(i, "-Err Usuario ya logueado\n", strlen("-Err Usuario ya logueado\n"),0);
	}

};

void login2(char *buffer, int i, std::vector<Jugador> &Jugadores){

	char password[50];
	bool encontrado = false;

	if(sscanf(buffer, "PASSWORD %s",password)){
		char usuarioLeido[50];
		char passwordLeido[50];

		std::ifstream fichero("usuarios.txt");
		if(fichero){
			while(fichero >> usuarioLeido >> passwordLeido){ //lee los usuarios del fichero
				if(strcmp(password, passwordLeido) == 0){ //si el usuario ya esta registrado en el fichero
					send(i, "+Ok Usuario validado\n", strlen("+Ok Usuario validado\n"),0);

					cambiarEstado(Jugadores, i, 1);

					encontrado = true;
					break;
				}
			}
			if(encontrado == false){
				send(i, "-Err Error en la validacion\n", strlen("-Err Error en la validacion\n"),0);
			}

			fichero.close();
		}
		else{
			send(i, "-Err No se ha registrado aun ningun usuario\n", strlen("-Err No se ha registrado aun ningun usuario\n"),0);
		}
	}

};

void iniciarPartida(char *buffer, int i, std::vector<Jugador> &Jugadores, std::vector<juego> &Juegos){

	bool encontrado = false;

	for(unsigned int w=0; w<Jugadores.size(); w++){
		if( ( Jugadores[w].getEstado() == 1 ) && ( Jugadores[w].getIdentificador() != i ) ){
			//Se crea una nueva partida
			send(i, "+Ok Empieza la partida\n", strlen("+Ok Empieza la partida\n"),0);
			send(Jugadores[w].getIdentificador(), "+Ok Empieza la partida\n", strlen("+Ok Empieza la partida\n"),0);

			cambiarEstado(Jugadores, i, 2); //cambia el estado de los 2 jugadores a jugando
			cambiarEstado(Jugadores, Jugadores[w].getIdentificador(), 2);

			Tablero tableroInicial(10,10,10);

			juego ju(getJugador(Jugadores, i), Jugadores[w], tableroInicial); //el que hizo la peticion es el primero en empezar

			Juegos.push_back(ju);

			send(Juegos.back().getJugador1().getIdentificador(), Juegos.back().getBoard(), strlen( Juegos.back().getBoard() ),0);
			send(Juegos.back().getJugador2().getIdentificador(), Juegos.back().getBoard(), strlen( Juegos.back().getBoard() ),0);

			encontrado = true;
			break;
		}
	}

	if(encontrado==false){
		send(i, "-No hay ningun jugador disponible, espere\n", strlen("-No hay ningun jugador disponible, espere\n"),0);
	}

};

void descubrirCasilla(char *buffer, int i, std::vector<juego> &Juegos, std::vector<Jugador> &Jugadores){

	int index=getIndexJuego(Juegos , i);

	if(comprobarTurno(Juegos[index], i)){				// Comprueba que es el turno del jugador que ha realizado la peticion
		char letra;
		int numero;

		if(sscanf(buffer, "DESCUBRIR %c %d",&letra, &numero)){
			numero--;
			if(Juegos[index].getTablero().getUserSelection(letra, numero)){	// Comprueba que las coordenadas introducidas son correctas


				int x = letra - 'a';
				Tablero tableroAux = Juegos[index].getTablero();
				bool comprobarSeleccionUsuario=tableroAux.userSelection( x, numero, 0, Juegos[index].getTurno() );
				Juegos[index].setTablero(tableroAux);

				if( comprobarSeleccionUsuario == false ){	// Pulsa una casilla. Si habia una mina, pierde (TRUE). Si no, comprueba si hay o no minas alrededor y cambia el tablero que el usuario ve.
					if((Juegos[index].getTurno() == 1 && Juegos[index].getBanderas1() == 10) || (Juegos[index].getTurno() == 2 && Juegos[index].getBanderas2() == 10)){
						if(Juegos[index].getTablero().checkForWin(Juegos[index].getTurno(),10) == false){
							mostrarTableroUsuario(Juegos, index);

							Juegos[index].cambiarTurno();

						}
						else{
							if(Juegos[index].getTurno() == 1){ //Gana jugador 1
								send(Juegos[index].getJugador1().getIdentificador(), "+Ok. Has ganado\n", strlen( "+Ok. Has ganado\n" ),0);
								send(Juegos[index].getJugador2().getIdentificador(), "+Ok. Has perdido\n", strlen( "+Ok. Has perdido\n" ),0);

								cambiarEstado(Jugadores, Juegos[index].getJugador1().getIdentificador(), 1); //cambia el estado de los 2 jugadores
								cambiarEstado(Jugadores, Juegos[index].getJugador2().getIdentificador(), 1);
								deleteJuego(Juegos, getJuego(Juegos,i)); //elimino el juego
							}
							else if(Juegos[index].getTurno() == 2){ //Gana jugador 2
								send(Juegos[index].getJugador1().getIdentificador(), "+Ok. Has perdido\n", strlen( "+Ok. Has perdido\n" ),0);
								send(Juegos[index].getJugador2().getIdentificador(), "+Ok. Has ganado\n", strlen( "+Ok. Has ganado\n" ),0);

								cambiarEstado(Jugadores, Juegos[index].getJugador1().getIdentificador(), 1); //cambia el estado de los 2 jugadores
								cambiarEstado(Jugadores, Juegos[index].getJugador2().getIdentificador(), 1);
								deleteJuego(Juegos, getJuego(Juegos,i)); //elimino el juego
							}
						}
					}
					else{

						mostrarTableroUsuario(Juegos, index);

						Juegos[index].cambiarTurno();

					}
				}
				else{		// TOCA MINA
					if(Juegos[index].getTurno() == 1){ //Gana jugador 2
						send(Juegos[index].getJugador2().getIdentificador(), "+Ok. Has ganado\n", strlen( "+Ok. Has ganado\n" ),0);
						send(Juegos[index].getJugador1().getIdentificador(), "+Ok. Has perdido\n", strlen( "+Ok. Has perdido\n" ),0);

						cambiarEstado(Jugadores, Juegos[index].getJugador1().getIdentificador(), 1); //cambia el estado de los 2 jugadores
						cambiarEstado(Jugadores, Juegos[index].getJugador2().getIdentificador(), 1);
						deleteJuego(Juegos, getJuego(Juegos,i)); //elimino el juego
					}
					else if(Juegos[index].getTurno() == 2){ //Gana jugador 1
						send(Juegos[index].getJugador2().getIdentificador(), "+Ok. Has perdido\n", strlen( "+Ok. Has perdido\n" ),0);
						send(Juegos[index].getJugador1().getIdentificador(), "+Ok. Has ganado\n", strlen( "+Ok. Has ganado\n" ),0);

						cambiarEstado(Jugadores, Juegos[index].getJugador1().getIdentificador(), 1); //cambia el estado de los 2 jugadores
						cambiarEstado(Jugadores, Juegos[index].getJugador2().getIdentificador(), 1);
						deleteJuego(Juegos, getJuego(Juegos,i)); //elimino el juego
					}
				}
			}
			else{
				send(i, "-Err. Las coordenadas introducidas no son correctas\n", strlen("-Err. Las coordenadas introducidas no son correctas\n"),0);
			}
		}
	}
	else{
		send(i, "-Err. Debe esperar su turno\n", strlen("-Err. Debe esperar su turno\n"),0);
	}

};

void mostrarTableroUsuario(std::vector<juego> &Juegos, int index){
	send(Juegos[index].getJugador1().getIdentificador(), Juegos[index].getBoard(), strlen( Juegos[index].getBoard() ),0);
	send(Juegos[index].getJugador2().getIdentificador(), Juegos[index].getBoard(), strlen( Juegos[index].getBoard() ),0);
}

void ponerBandera(char *buffer, int i, std::vector<juego> &Juegos, std::vector<Jugador> &Jugadores){

	int index=getIndexJuego(Juegos , i);

	if(comprobarTurno(Juegos[index], i)){				// Comprueba que es el turno del jugador que ha realizado la peticion
		char letra;
		int numero;

		if(sscanf(buffer, "PONER-BANDERA %c %i",&letra, &numero)){
			numero--;
			if(Juegos[index].getTablero().getUserSelection(letra, numero)){		// Comprueba que las coordenadas introducidas son correctas

				int x = letra - 'a';
				Tablero tableroAux = Juegos[index].getTablero();
				tableroAux.userSelection( x, numero, 1, Juegos[index].getTurno() );
				Juegos[index].setTablero(tableroAux);

				if(Juegos[index].getTurno() == 1){
					if( (Juegos[index].getTablero().getCell(x, numero) == '-')||(Juegos[index].getTablero().getCell(x, numero) == 'B') ){
						Juegos[index].decrementarBandera(1);
					}
					else if( (Juegos[index].getTablero().getCell(x, numero) == 'A')||(Juegos[index].getTablero().getCell(x, numero) == 'F') ){
						Juegos[index].aumentarBandera(1);
					}
				}
				else{
					if( (Juegos[index].getTablero().getCell(x, numero) == '-')||(Juegos[index].getTablero().getCell(x, numero) == 'A') ){
						Juegos[index].decrementarBandera(2);
					}
					else if( (Juegos[index].getTablero().getCell(x, numero) == 'B')||(Juegos[index].getTablero().getCell(x, numero) == 'F') ){
						Juegos[index].aumentarBandera(2);
					}
				}

				if( (Juegos[index].getBanderas1() == 10) || (Juegos[index].getBanderas2() == 10) ){
					if(Juegos[index].getTablero().checkForWin(Juegos[index].getTurno(),10) == false){
						mostrarTableroUsuario(Juegos, index);
						Juegos[index].cambiarTurno();

					}
					else{
						if(Juegos[index].getTurno() == 1){ //Gana jugador 1
							send(Juegos[index].getJugador1().getIdentificador(), "+Ok. Has ganado\n", strlen( "+Ok. Has ganado\n" ),0);
							send(Juegos[index].getJugador2().getIdentificador(), "+Ok. Has perdido\n", strlen( "+Ok. Has perdido\n" ),0);

							cambiarEstado(Jugadores, Juegos[index].getJugador1().getIdentificador(), 1); //cambia el estado de los 2 jugadores
							cambiarEstado(Jugadores, Juegos[index].getJugador2().getIdentificador(), 1);
							deleteJuego(Juegos, getJuego(Juegos,i)); //elimino el juego
						}
						else if(Juegos[index].getTurno() == 2){ //Gana jugador 2
							send(Juegos[index].getJugador1().getIdentificador(), "+Ok. Has perdido\n", strlen( "+Ok. Has perdido\n" ),0);
							send(Juegos[index].getJugador2().getIdentificador(), "+Ok. Has ganado\n", strlen( "+Ok. Has ganado\n" ),0);

							cambiarEstado(Jugadores, Juegos[index].getJugador1().getIdentificador(), 1); //cambia el estado de los 2 jugadores
							cambiarEstado(Jugadores, Juegos[index].getJugador2().getIdentificador(), 1);
							deleteJuego(Juegos, getJuego(Juegos,i)); //elimino el juego
						}
					}
				}
				else{
					mostrarTableroUsuario(Juegos, index);
					Juegos[index].cambiarTurno();
				}
			}
			else{
				send(i, "-Err. Las coordenadas introducidas no son correctas\n", strlen("-Err. Las coordenadas introducidas no son correctas\n"),0);
			}
		}
	}
	else{
		send(i, "-Err. Debe esperar su turno\n", strlen("-Err. Debe esperar su turno\n"),0);
	}

};

int findJugador(std::vector<Jugador> &j, int i){
	for(unsigned int k=0; k<j.size(); k++){
		if( (i == j[k].getIdentificador() ) ){
			return j[k].getEstado();
		}
	}
	return -1;

};

bool findJugadorUsuario(std::vector<Jugador> &j, char * nombre){
	std::string nombreAux(nombre);
	for(unsigned int k=0; k<j.size(); k++){
		if( (nombreAux == j[k].getNombre() ) ){
			return false;
		}
	}
	return true;

};

void deleteJugador(std::vector<Jugador> &j, Jugador ju){
	for(unsigned int k=0; k<j.size(); k++){
		if( (ju.getIdentificador() == j[k].getIdentificador() ) ){
			j.erase(j.begin() + k);
		}
	}
}

void deleteJuego(std::vector<juego> &j, juego ju){
	for(unsigned int k=0; k<j.size(); k++){
		if( (ju.getJugador1().getIdentificador() == j[k].getJugador1().getIdentificador())&&(ju.getJugador2().getIdentificador() == j[k].getJugador2().getIdentificador()) ){
			j.erase(j.begin() + k);
		}
	}
}

void cambiarEstado(std::vector<Jugador> &j, int i, int estado){
	for(unsigned int k=0; k<j.size(); k++){
		if( (i == j[k].getIdentificador() ) ){
			j[k].setEstado(estado);
			return;
		}
	}

};

Jugador getJugador(std::vector<Jugador> &j, int i){
	for(unsigned int k=0; k<j.size(); k++){
		if( (i == j[k].getIdentificador() ) ){
			return j[k];
		}
	}
	return j[1]; //Para evitar warning
}

juego getJuego(std::vector<juego> &j, int i){
	for(unsigned int k=0; k<j.size(); k++){
		if( (i == j[k].getJugador1().getIdentificador() ) || (i == j[k].getJugador2().getIdentificador() )){
			return j[k];
		}
	}
	return j[1]; //Para evitar warning
}

int getIndexJuego(std::vector<juego> &j, int i){
	for(unsigned int k=0; k<j.size(); k++){
		if( (i == j[k].getJugador1().getIdentificador() ) || (i == j[k].getJugador2().getIdentificador() )){
			return k;
		}
	}
	return -1; //Para evitar warning
}

void setJuego(std::vector<juego> &juegos ,juego j, int i){
	for(unsigned int k=0; k<juegos.size(); k++){
		if( (i == juegos[k].getJugador1().getIdentificador() ) || (i == juegos[k].getJugador2().getIdentificador() )){
			juegos[k] = j;
		}
	}
}

bool comprobarTurno(juego j, int i){
	if((j.getJugador1().getIdentificador() == i) && (j.getTurno() == 1)){
		return true;
	}
	else if((j.getJugador2().getIdentificador() == i) && (j.getTurno() == 2)){
		return true;
	}
	else{
		return false;
	}
}


void manejador (int signum){

	printf("\nSe ha recibido la señal sigint\n");
	signal(SIGINT,manejador);

	//Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor

	printf("\nSe ha recibido la señal sigint\n");
	signal(SIGINT,manejador);

	//Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor

}
