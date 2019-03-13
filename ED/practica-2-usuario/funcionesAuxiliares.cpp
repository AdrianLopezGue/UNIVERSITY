/*!
  \file   funcionesAuxiliares.cpp
  \brief  Código de las funciones auxiliares del programa principal de la provincia
	\author Adrian Lopez Guerrero
	\date 6/4/2017
*/

#include <iostream>
#include <string>

// Para usar atoi
#include <stdlib.h>

#include "Provincia.hpp"

#include "Municipio.hpp"

#include "funcionesAuxiliares.hpp"


#include "macros.hpp"

int ed::menu()
{
	int opcion;
	int posicion;

	// Se muestran las opciones del menú
	posicion=2;

	// Se borra la pantalla
	std::cout << CLEAR_SCREEN;

	PLACE(1,10);
	std::cout << BIBLUE;
	std::cout << "Programa principial | Opciones del menú";
	std::cout << RESET;

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout <<  "[1] Comprobar si la provincia tiene municipios";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[2] Cargar la provincia desde un fichero";

	PLACE(posicion++,10);
	std::cout << "[3] Grabar la provincia en un fichero";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[4] Consultar datos de la provincia";

	PLACE(posicion++,10);
	std::cout <<  "[5] Mostrar municipios de la provincia";

	PLACE(posicion++,10);
	std::cout << "[6] Modificar datos de la provincia: código o nombre";

	PLACE(posicion++,10);
	std::cout << "[7] Borrar todos los municipios de una provincia";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[8] Consultar un municipio";

	PLACE(posicion++,10);
	std::cout << "[9] Insertar un municipio";

	PLACE(posicion++,10);
	std::cout << "[10] Borrar un municipio";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << BIRED << "[0] Salir";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << BIGREEN;
	std::cout << "Opción: ";
	std::cout << RESET;

	// Se lee el número de opción
	std::cin >> opcion;

    // Se elimina el salto de línea del flujo de entrada
    std::cin.ignore();

	return opcion;
}


//////////////////////////////////////////////////////////////////////////////

// OPCION 1
void ed::comprobarProvinciaVacia(ed::Provincia &provincia)
{
	if(provincia.hayMunicipios() == true){
		std::cout << BIBLUE;
		std::cout<<"\n--> LA PROVINCIA NO ESTA VACIA. <--\n";
		std::cout << RESET;
	}
	else{
		std::cout << BIBLUE;
		std::cout<<"\n--> LA PROVINCIA ESTA VACIA. <--\n";
		std::cout << RESET;
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////

// OPCION 2
void ed::cargarProvincia(ed::Provincia &provincia)
{
	std::string nombrefichero;

	std::cout<<"Introduce el nombre del fichero: ";
	std::getline(std::cin,nombrefichero);

	if(provincia.cargarFichero(nombrefichero) == true){
		std::cout << BIGREEN;
		std::cout<<"\n\n\n--> CARGADO CORRECTAMENTE <--\n";
		std::cout << RESET;
	}
	else{
		std::cout << BIRED;
		std::cout<<"\n\n\n--> NO SE HA CARGADO CORRECTAMENTE <--\n";
		std::cout << RESET;
	}

	return;
}

// OPCION 3
void ed::grabarProvincia(ed::Provincia  &provincia)
{
	std::string nombrefichero;

	std::cout<<"Introduce el nombre del fichero a crear: ";
	std::getline(std::cin,nombrefichero);

	if(provincia.grabarFichero(nombrefichero) == true){
		std::cout << BIGREEN;
		std::cout<<"\n\n\n--> GRABADO CORRECTAMENTE <--\n";
		std::cout << RESET;
	}
	else{
		std::cout << BIRED;
		std::cout<<"\n\n\n--> NO SE HA GRABADO CORRECTAMENTE <--\n";
		std::cout << RESET;
	}

	return;
}

//////////////////////////////////////////////////////////////////////

// OPCION 4
void ed::consultarDatosDeProvincia(ed::Provincia &provincia)
{
	std::cout<< BIYELLOW  <<"NOMBRE: "<< RESET <<provincia.getNombre()<<"\n";
  	std::cout<< BIYELLOW  <<"\nCODIGO: "<< RESET <<provincia.getCodigo()<<"\n";

	return;
}


//

// OPCION 5
void ed::mostrarMunicipiosDeProvincia(ed::Provincia & provincia)
{
	provincia.escribirMunicipios();

	return;
}


////////////////////////////////////////////////////////////////////////

// OPCION 6
void ed::modificarDatosDeProvincia(ed::Provincia &provincia)
{

	int opcion, codigo;
	std::string nombre;

	do{
		std::cout << BIYELLOW  << "Nombre de la provincia: "  << RESET
				  << provincia.getNombre() << std::endl;
		std::cout << BIYELLOW << "Código de la provincia: " << RESET
				  << provincia.getCodigo() << std::endl  << std::endl;

		std::cout << "Indique qué dato desea modificar: " << std::endl;
		std::cout << BIBLUE << "(1) Nombre " << std::endl;
		std::cout << BIBLUE << "(2) Código" << std::endl  << std::endl;
		std::cout << BIRED << "(0) Salir" << std::endl << std::endl  << std::endl;
		std::cout << BIGREEN;
		std::cout << "Opción: ";
		std::cout << RESET;

		// Se lee el número de opción
		std::cin >> opcion;

    	// Se elimina el salto de línea del flujo de entrada
	    std::cin.ignore();

		std::cout << std::endl;

		switch(opcion)
		{
			case 0:
					// Fin de las modificaciones
					break;
			case 1:
					std::cout << BIGREEN;
					std::cout << "Nuevo nombre de la provincia: ";
					std::cout << RESET;
					std::getline(std::cin,nombre);
					provincia.setNombre(nombre);
					break;

			case 2:
					std::cout << BIGREEN;
					std::cout << "Nuevo código de la provincia: ";
					std::cout << RESET;
					std::cin >> codigo;
					provincia.setCodigo(codigo);
					break;
			default:
					std::cout << BIRED << "Opción incorrecta:" << RESET
							  << opcion << std::endl;
		}
	}while (opcion != 0);

	return;
}

// OPCION 7
void ed::borrarTodosLosMunicipiosDeProvincia(ed::Provincia &provincia)
{

	provincia.borrarTodosLosMunicipios();

	std::cout<< BIBLUE <<"\n\n\n--> TODOS LOS MUNICIPIOS BORRADOS. <--\n"<< RESET ;

	return;
}

// OPCION 8
void ed::consultarMunicipioDeProvincia(ed::Provincia &provincia)
{
	std::string nombreMunicipioBuscar;

	std::cout << BIBLUE;
	std::cout<<"NOMBRE DEL MUNICIPIO A CONSULTAR: ";
	std::cout << RESET;
	std::getline(std::cin,nombreMunicipioBuscar);

	if(provincia.existeMunicipio(nombreMunicipioBuscar) == true){
		provincia.getMunicipio(nombreMunicipioBuscar).escribirMunicipio();
	}
	else{
		std::cout << BIRED;
		std::cout<<"\n\n\n--> EL MUNICIPIO CON ESE NOMBRE NO EXISTE EN LA LISTA. <--\n";
		std::cout << RESET;
	}

	return;
}

// OPCION 9
void ed::insertarMunicipioEnProvincia(ed::Provincia &provincia)
{
	ed::Municipio municipioaux("", -1,-1,-1);
	municipioaux.leerMunicipio();

	if(provincia.existeMunicipio(municipioaux.getNombre()) == false){
		provincia.insertarMunicipio(municipioaux);

		std::cout << BIGREEN;
		std::cout<<"\n\n\n--> MUNICIPIO INSERTADO CORRECTAMENTE <--\n";
		std::cout << RESET;
	}
	else{
		std::cout << BIRED;
		std::cout<<"\n\n\n--> YA EXISTE UN MUNICIPIO CON ESE NOMBRE EN LA LISTA. <--\n";
		std::cout << RESET;
		return;
	}

	return;
}

// OPCION 10
void ed::borrarMunicipioDeProvincia(ed::Provincia &provincia)
{
	std::string nombreMunicipioBorrar;

	std::cout << BIBLUE;
	std::cout<<"INTRODUCE EL NOMBRE DEL MUNICIPIO A BORRAR: ";
	std::cout << RESET;
	std::getline(std::cin,nombreMunicipioBorrar);

	if(provincia.existeMunicipio(nombreMunicipioBorrar) == true){
		provincia.borrarMunicipio(nombreMunicipioBorrar);

		std::cout << BIGREEN;
		std::cout<<"\n\n\n--> MUNICIPIO BORRADO CORRECTAMENTE <--\n";
		std::cout << RESET;
	}
	else{
		std::cout << BIRED;
		std::cout<<"\n\n\n--> NO EXISTE UN MUNICIPIO CON ESE NOMBRE EN LA LISTA. <--\n";
		std::cout << RESET;	
	}

	return;
}
