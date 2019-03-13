/*!
\file   funcionesAuxiliares.hpp
\brief  Funciones auxiliares para el programa principal de la práctica 3
\author Adrian Lopez Guerrero
\date 18/4/2017
\version 1.0
*/

#ifndef _FuncionesAuxiliares_HPP_
#define _FuncionesAuxiliares_HPP_

#include "MonticuloMediciones.hpp"

/*!
\namespace ed
\brief Espacio de nombres para la asignatura Estructuras de Datos

*/

namespace ed
{

	/*!
	\brief     Funcion auxiliar que permite cargar las mediciones del monticulo desde un fichero.
	\param     monticulo: monticulos que queremos cargar en un fichero.
	\param		 nombreFichero: nombre del fichero del que se quieren cargar las mediciones
	\pre       Ninguna
	\post      Ninguna
	*/

	void cargarMonticuloDeFichero(std::string const & nombreFichero, ed::MonticuloMediciones & monticulo);

	/*!
	\brief     Funcion auxiliar que permite grabar las mediciones del monticulo a un fichero.
	\param     monticulo: monticulos que queremos cargar en un fichero.
	\param		 nombreFichero: nombre del fichero del que se quieren cargar las mediciones
	\pre       Ninguna
	\post      Ninguna
	*/

	void grabarMonticuloEnFichero (std::string const & nombreFichero, ed::MonticuloMediciones const & monticulo);


} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FuncionesAuxiliares_HPP_
#endif
