#ifndef CRUPIER_H
#define CRUPIER_H

#include <string>
#include "persona.h"
using namespace std;

class Crupier: public Persona{

private:

	string codigo_;

public:
	Crupier(string DNI, string codigo, string nombre="", string apellidos="", string direccion = "", string localidad = "",string provincia = "",string pais = "") : Persona(DNI, nombre, apellidos, direccion, localidad, provincia, pais){setCodigo(codigo);};
	
	void setCodigo(const string codigo){codigo_ = codigo;};
	string getCodigo(){return codigo_;};
};


#endif