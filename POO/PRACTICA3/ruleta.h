#ifndef RULETA_H
#define RULETA_H

#include <list>
#include <string>
#include <fstream>
#include "persona.h"
#include "crupier.h"
#include "jugador.h"

using namespace std;


class Ruleta
{

private:

	int banca_;
	int bola_;
	int numerotiradas_;
	list <Jugador> jugadores_;
	Crupier crupier_;


public:
	Ruleta(Crupier c): crupier_ (c){ banca_ = 1000000; bola_=-1; srand(time(NULL));numerotiradas_=0;}; // crupier_ no se inicia dentro del constructor por que este es un "miembo objeto" de la clase crupier (APARTADO 23 - APUNTES C++)

	int getBanca(){return banca_;};
	int getBola(){return bola_;};
	Crupier getCrupier(){return crupier_;};
	list<Jugador> getJugadores(){return jugadores_;};

	bool setBanca(const int valor);
	bool setBola(const int valor);
	void setCrupier(const Crupier aux){crupier_ = aux;};
	void giraRuleta();

	bool addJugador(Jugador aux);
	int deleteJugador(const string aux);
	int deleteJugador(Jugador aux);

	void escribeJugadores();
	void leeJugadores();
	void getPremios();

	int validacion(const Apuesta aux);
	string transformarbolaencolor();

	void getEstadoRuleta(int &njugadores, int &dinero, int &lanzamientos, int &ganancia, Ruleta aux);
	
};


#endif