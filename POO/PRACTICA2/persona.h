#ifndef PERSONA_H
#define PERSONA_H

#include <string>
using namespace std;

class Persona
{

private:
	string DNI_;
	string nombre_;
	string apellidos_;
	string direccion_;
	string localidad_;
	string provincia_;
	string pais_;

public:

	Persona(string DNI, string nombre = "", string apellidos = "", string direccion = "", string localidad = "",string provincia = "",string pais = "");

  void setDNI(const string name){DNI_ = name;};
	void setNombre(const string name){nombre_ = name;};
	void setApellidos(const string name){apellidos_ = name;};
	void setDireccion(const string name){direccion_ = name;};
	void setLocalidad(const string name){localidad_ = name;};
	void setProvincia(const string name){provincia_ = name;};
	void setPais(const string name){pais_ = name;};

	string getDNI(){return DNI_;};
	string getNombre(){return nombre_;};
	string getApellidos(){return apellidos_;};
	string getDireccion(){return direccion_;};
	string getLocalidad(){return localidad_;};
	string getProvincia(){return provincia_;};
	string getPais(){return pais_;};

	string getApellidosyNombre(){return apellidos_+", "+nombre_;};

};



#endif
