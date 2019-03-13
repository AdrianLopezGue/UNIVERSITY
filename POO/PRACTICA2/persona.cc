#include "persona.h"
#include <string>

using namespace std;

Persona::Persona(string DNI, string nombre , string apellidos , string direccion , string localidad ,string provincia , string pais){
	
	
	setDNI(DNI);
	setNombre(nombre);
	setApellidos(apellidos);
	setDireccion(direccion);
	setLocalidad(localidad);
	setProvincia(provincia);
	setPais(pais);
}


