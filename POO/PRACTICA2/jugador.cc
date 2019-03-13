#include "jugador.h"

using namespace std;


void Jugador :: setApuestas()
{

string dnijugador;							// dnijugador: Almacena el nombre del fichero

char cadena1[10], cadena2[10], cadena3[10];	// cadena1: Guarda el valor de tipo
											// cadena2: Guarda el valor de valor
											// cadena3: Guarda el valor de cantidad						   

dnijugador = getDNI() + ".txt"; 			// 1.- Guardamos en dnijugador el nombre del fichero de datos
fstream fichero(dnijugador.c_str()); 		// IMPORTANTE: Es necesario el uso de la funcion "c_str()" ya que esta tranforma el formato string en formato "const char*" que es el tipo de argumento que permite la funcion fstream


// VARIABLES DE LA PRIMERA FORMA.
/*int inicio, longitud;*/					// linea: almacena una linea entera del fichero de lectura.
/*string linea, cadena; */		 	 		// cadena: string auxiliar que nos va a servir para almacenar valores dentro del while  				
						
if(fichero){

	apuestas_.clear(); // 2.- Borramos todos los elementos de la lista, para guardar los elementos del fichero en la lista.
	Apuesta aux;


	while(fichero.getline(cadena1, 256, ',')){


		aux.tipo = atoi(cadena1);

		fichero.getline(cadena2, 256, ',');
		aux.valor = cadena2;

		fichero.getline(cadena3, 256, '\n');
		aux.cantidad = atoi(cadena3);

		apuestas_.push_back(aux);



	/* PRIMERA FORMA.

	// LEEMOS TIPO DE APUESTA

		inicio = 0;
		longitud = linea.find(",");
		cadena = linea.substr(inicio, longitud);
		aux.tipo = atoi(cadena.c_str());

	// LEEMOS VALOR

		inicio = longitud +1;
		longitud = linea.find(",", inicio);
		cadena = linea.substr(inicio, (longitud-inicio));
		aux.valor = cadena;
	
	// LEEMOS CANTIDAD

		inicio = longitud +1;
		longitud = linea.find('\n', inicio);
		cadena = linea.substr(inicio, (longitud-inicio));
		aux.cantidad = atoi(cadena.c_str());

	// INCLUIMOS LOS DATOS EN LA LISTA

		apuestas_.push_back(aux);
	*/


	}

	
	fichero.close();
}
	

	else{
	cout<<"ERROR: No se ha podido abrir el fichero,"<<endl;
	
	}
}