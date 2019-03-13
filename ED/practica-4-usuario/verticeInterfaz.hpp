/*!
\file verticeInterfaz.hpp
\brief  Fichero de la clase Vertice: interfaz de la clase vertice
\author Adrian Lopez Guerrero
\date 26/5/2018
\version 1.0
*/


#ifndef _VERTICEINTERFAZ_HPP_
#define _VERTICEINTERFAZ_HPP_

#include <string>
#include <fstream>
#include <limits>
#include <vector>
#include <iostream>

/*!
\namespace ed
\brief Espacio de nombres para la asignatura Estructuras de Datos
*/

namespace ed{

	/*!
	\class VerticeInterfaz
	\brief Indica los métodos virtuales puros deberán ser redefinidos en las clases herederas
	*/

	class VerticeInterfaz{


		/*!
		\name Funciones o métodos públicos de la clase Vertice
		*/
	public:


		/*!
		\name Observadores
		*/

		/*!
		\brief   Método público que permite escribir el vertice en la terminal
		\warning Función virtual pura: se debe redefinir en la clase heredera
		\pre     Ninguna
		\post    Ninguna
		\return  Devuelve el valor del campo informativo del vertice
		*/

		virtual void escribirVertice() const= 0;


		/*!
		\brief   Método público que permite leer el vertice en la terminal
		\warning Función virtual pura: se debe redefinir en la clase heredera
		\pre     Ninguna
		\post    El valor del campo informativo debe ser igual al item pasado como argumento
		\return  void
		*/

		virtual void leerVertice() = 0;


		// Fin de la clase VerticeInterfaz
	};


	// Fin del espacio de nombres ed
}


//Fin  _VERTICEINTERFAZ_HPP_
#endif
