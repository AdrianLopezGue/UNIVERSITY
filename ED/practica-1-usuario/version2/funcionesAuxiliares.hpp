/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 1
	\author Adrian Lopez Guerrero
  \date     2018-2-26
  \version  2.0
*/

#ifndef _FUNCIONESAUXILIARES_HPP_
#define _FUNCIONESAUXILIARES_HPP_

#include "Vector3D.hpp"


namespace ed
{
	/*!
		\brief   Muestra el menú del programa principal
		\return  Devuelve el número de opción elegido
	*/
	int menu();

	/*!
	\brief  Lee los vectores pasados como argumento.
	\param  &u Vector3D
	\param  &v Vector3D
	\param  &w Vector3D
	\return void
	\pre    Ninguna
	\post   Ninguna
	*/

	void leerVectores(ed::Vector3D &u, ed::Vector3D &v, ed::Vector3D &w);

	/*!
	\brief  Escribe el valor de los vectores pasados como argumento.
	\param  &u Vector3D
	\param  &v Vector3D
	\param  &w Vector3D
	\attention El usuario necesita introducir por teclado los valores
	\return void
	\pre    Ninguna
	\post   Ninguna
	*/

	void escribirVectores(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D const &w);

	/*!
	\brief  Muestra el comportamiento de los observadores creados de la clase Vector3D.
	\param  &u Vector3D
	\param  &v Vector3D
	\return void
	\pre    Ninguna
	\post   Ninguna
	*/

	void observadoresDeVectores(ed::Vector3D const &u, ed::Vector3D const &v);

	/*!
	\brief  Muestra el funcionamiento de las funciones modificadoras de la clase Vector3D (sumConst, sumVect, multVect, multConst).
	\param  &u Vector3D
	\param  &v Vector3D
	\param  k double
	\return void
	\pre    Ninguna
	\post   Ninguna
	*/

	void modificarVector(ed::Vector3D &u, ed::Vector3D const &v, double k);

	/*!
	\brief  Muestra el resultado devuelto de la funcion "dotProduct", que realiza el producto escalar de los vectores3D pasados como argumento.
	\param  &u Vector3D
	\param  &v Vector3D
	\return void
	\pre    Ninguna
	\post   Ninguna
	*/

	void mostrarProductoEscalar(ed::Vector3D const &u, ed::Vector3D const &v);

	/*!
	\brief  Muestra el resultado devuelto de la funcion "crossProduct", que realiza el producto vectorial de los vectores3D pasados como argumento.
	\param  &u Vector3D
	\param  &v Vector3D
	\return void
	\pre    Ninguna
	\post   Ninguna
	*/

	void mostrarProductoVectorial(ed::Vector3D const &u, ed::Vector3D const &v);

	/*!
	\brief  Muestra el resultado devuelto de la funcion "productoMixto", que realiza el producto mixto de los 3 vectores3D pasados como argumento.
	\param  &u Vector3D
	\param  &v Vector3D
	\param  &w Vector3D
	\return void
	\pre    Ninguna
	\post   Ninguna
	*/

	void mostrarProductoMixto(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D const &w);

	/*!
	\brief  Muestra el resultado de la ejecucion de cada uno de los operadores de la clase Vector3D.
	\param  &u Vector3D
	\param  &v Vector3D
	\param  &w Vector3D
	\param  k double
	\return void
	\pre    Ninguna
	\post   Ninguna
	*/

	void mostrarOperadores(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D &w,  double k);



} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FUNCIONESAUXILIARES_HPP_
#endif
