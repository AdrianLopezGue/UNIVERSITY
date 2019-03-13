/*!
\file MonticuloMedicionesInterfaz.hpp
\brief Se define la interfaz del TAD MonticuloMediciones.
\author Adrian Lopez Guerrero
\date 18/4/2017
\version 1.0
*/

#ifndef _MONTICULO_MEDICIONES_INTERFAZ_HPP
#define _MONTICULO_MEDICIONES_INTERFAZ_HPP

#include "Medicion.hpp"

/*!
\namespace ed
\brief Espacio de nombres para la asignatura Estructuras de Datos
*/

namespace ed
{
	/*!
	\class MonticuloMedicionesInterfaz
	\brief Definición de la clase abstracta MonticuloMedicionesInterfaz
	\n  Montículo de Mediciones ordenada en función de máximos respecto a las precipitaciones
	*/
	class MonticuloMedicionesInterfaz
	{

		//! \name Funciones o métodos públicos de la clase MonticuloMedicionesInterfaz

	public:

		//! \name Observadores públicos

		/*!
		\brief  Comprueba si el montículo está vacío
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
		\note   Función de tipo "const": no puede modificar al objeto actual
		\post 	Devuelve verdadero si no tiene mediciones; falso, en caso contrario.
		\return true, si el montículo está vacío; false, en caso contrario
		*/

		virtual bool isEmpty() const = 0;

		/*!
		\brief  Devuelve la cima del montículo
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
		\note   Función de tipo "const": no puede modificar al objeto actual
		\pre 	  isEmpty() == falso
		\post 	valorDevuelto == getElement(0)
		\return Objeto de tipo medicion que representa el top del montículo.
		*/

		virtual ed::Medicion top() const = 0;

		//! \name Modificadores públicos

		/*!
		\brief  Inserta una nueva medición en el montículo
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
		\param 		medicion: Objeto de tipo medicion que se va a insertar
		\post 	  isEmpty() == falso
		\post 		has(medicion) == true)
		*/

		virtual void insert(ed::Medicion medicion) = 0;

		/*!
		\brief  Borra la medición que ocupa la cima
		\note   Función virtual pura, que deberá ser redefinida en la clase heredera
		\pre 	  isEmpty() == falso
		*/

		virtual void remove() = 0;


	}; // Clase MonticuloMedicionesInterfaz

} // Espacio de nombres ed

#endif //  _MONTICULO_MEDICIONES_INTERFAZ_HPP
