#ifndef JUGADOR_H
#define JUGADOR_H

#include "persona.h"
#include <string>
#include <list>
#include <fstream> 
#include <iostream>
#include <cstdlib>

using namespace std;

struct Apuesta
	{
		int tipo;
		string valor;
		int cantidad;
	};



class Jugador : public Persona{

private:

	int dinero_;
	string codigo_;
	list <Apuesta> apuestas_;


public:
	
	Jugador(string DNI, string codigo,  string nombre="", string apellidos="", string direccion = "", string localidad = "",string provincia = "",string pais = "",int dinero=1000): Persona(DNI, nombre, apellidos, direccion, localidad, provincia, pais){setCodigo(codigo); setDinero(dinero);};
	
	void setCodigo(const string codigo){codigo_ = codigo;};
	void setDinero(const int dinero){dinero_ = dinero;};
	void setApuestas();

	string getCodigo(){return codigo_;};
	int getDinero(){return dinero_;};
	list <Apuesta> getApuestas(){return apuestas_;};
	
};



#endif

