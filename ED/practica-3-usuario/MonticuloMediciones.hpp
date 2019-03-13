/*!
\file MonticuloMediciones.hpp
\brief Se define el TAD MonticuloMediciones.
\author Adrian Lopez Guerrero
\date 18/4/2017
\version 1.0
*/

#ifndef _MONTICULO_MEDICIONES_HPP
#define _MONTICULO_MEDICIONES_HPP

#include <vector>
#include <stdlib.h>

// Para comprobar las pre y post-condiciones
#include <cassert>

#include "Medicion.hpp"

#include "MonticuloMedicionesInterfaz.hpp"


/*!
\namespace ed
\brief Espacio de nombres para la asignatura Estructuras de Datos

*/

namespace ed
{

	/*!
	\class MonticuloMediciones
	\brief Definición de la clase MonticuloMediciones
	\n  Montículo de Mediciones ordenada en función de máximos respecto a las precipitaciones
	*/

	class MonticuloMediciones : public MonticuloMedicionesInterfaz
	{
	private:

		//! \name Atributos privados de la clase MonticuloMediciones

		std::vector <ed::Medicion> vectormediciones;	//!< \brief vector stl de tipo "Medicion"

		//! \name Métodos privados de la clase MonticuloMediciones

		// \name Observadores privados
		/*!
		\brief     Getter de un elemento indicando su index
		\note      Función inline
		\note   Función de tipo "const": no puede modificar al objeto actual
		\param 		 i: entero que indica el indice del elemento
		\pre       i >= 0
		\pre			 i < size()
		\post      Ninguna
		*/

		inline ed::Medicion getElement(int i) const {
			#ifndef NDEBUG
			assert((i >= 0) &&
			(i < size()));
			#endif //NDEBUG

			return vectormediciones[i];
		}

		/*!
		\brief     Setter de un elemento indicando su index
		\note      Función inline
		\param 		 i: entero que indica el indice del elemento
		\param 		 medicion: Objeto de la clase Medicion "medicion"
		\pre       i >= 0
		\pre 			 i < size()
		\post      vectormediciones[i] == medicion
		*/

		inline void setElement(int i, ed::Medicion medicion){

			#ifndef NDEBUG
			assert((i >= 0) &&
			(i < size()));
			#endif //NDEBUG

			vectormediciones[i] = medicion;

			#ifndef NDEBUG
			assert(vectormediciones[i] == medicion);
			#endif //NDEBUG
		}

		/*!
		\brief     Getter del hijo derecho del elemento en el index que le indiquemos
		\note      Función inline
		\note   Función de tipo "const": no puede modificar al objeto actual
		\param 		 i: entero que indica el indice del elemento
		\pre       i >= 0
		\pre 			 i < size()
		\post      valorDevuelto == 2*i +1
		*/

		inline int getRightChild(int i) const{

			// Añadido comprobacion de que i sea menor o igual que el tamaño total
			#ifndef NDEBUG
			assert((i >= 0) &&
			(i < size()));
			#endif //NDEBUG

			int valorDevuelto;

			if((i*2) + 1 < size()){
				valorDevuelto = i*2 + 1;
			}
			else{
				valorDevuelto = -1;
				return valorDevuelto;

			}

			#ifndef NDEBUG
			assert(valorDevuelto == 2*i +1);
			#endif //NDEBUG

			return valorDevuelto;

		}

		/*!
		\brief     Getter del hijo izquierdo del elemento en el index que le indiquemos
		\note      Función inline
		\note   Función de tipo "const": no puede modificar al objeto actual
		\param 		 i: entero que indica el indice del elemento
		\pre       i >= 0
		\pre 			 i < size()
		\post      valorDevuelto == 2*i +2
		*/

		inline int getLeftChild(int i) const{

			// Añadido comprobacion de que i sea menor o igual que el tamaño total
			#ifndef NDEBUG
			assert((i >= 0) &&
			(i < size()));
			#endif //NDEBUG

			int valorDevuelto;

			if((i*2) + 2 < size()){
				valorDevuelto = i*2 + 2;
			}
			else{
				valorDevuelto = -1;
				return valorDevuelto;

			}

			#ifndef NDEBUG
			assert(valorDevuelto == 2*i +2);
			#endif //NDEBUG

			return valorDevuelto;
		}

		/*!
		\brief     Getter del padre del elemento en el index que le indiquemos
		\note      Función inline
		\note   Función de tipo "const": no puede modificar al objeto actual
		\param 		 i: entero que indica el indice del elemento
		\pre       i >= 1
		\pre 			 i < size()
		\post      valorDevuelto == (i-1)/2
		*/


		inline int getParent(int i) const{

			// Añadido comprobacion de que i sea menor o igual que el tamaño total
			#ifndef NDEBUG
			assert((i >= 1) &&
			(i < size()));
			#endif //NDEBUG

			int valorDevuelto = (i-1)/2;

			#ifndef NDEBUG
			assert(valorDevuelto == (i-1)/2);
			#endif //NDEBUG

			return valorDevuelto;

		}

		/*!
		\brief  El elemento indicado por el índice es subido en el montículo hasta que se verifica la ordenación de máximos.
		\param 		 i: entero que indica el indice del elemento
		\pre       i >= 0
		\pre 			 i < size()
		\post		 Si el elemento no esta en la cabeza: getElement(index).getPrecipitacion() <= getElement(getParent(index)).getPrecipitacion()
		\post		 Si el elemento tiene un hijo izquierdo: getElement(index).getPrecipitacion() > getElement(getLeftChild(index)).getPrecipitacion()
		\post		 Si el elemento tiene un hijo derecho: getElement(index).getPrecipitacion() > getElement(getRightChild(index)).getPrecipitacion()
		*/

		void shiftUp(int i);

		/*!
		\brief  El elemento indicado por el índice es bajado en el montículo hasta que se verifica la ordenación de máximos.
		\param 		 i: entero que indica el indice del elemento
		\pre       i >= 0
		\pre 			 i < size()
		\post		 Si el elemento no esta en la cabeza: getElement(index).getPrecipitacion() <= getElement(getParent(index)).getPrecipitacion()
		\post		 Si el elemento tiene un hijo izquierdo: getElement(index).getPrecipitacion() > getElement(getLeftChild(index)).getPrecipitacion()
		\post		 Si el elemento tiene un hijo derecho: getElement(index).getPrecipitacion() > getElement(getRightChild(index)).getPrecipitacion()
		*/

		void shiftDown(int i);

		/*!
		\brief     Se comprueba si la medición está incluida en el montículo.
		\note      Función inline
		\param 		 medicion: Objeto de tipo Medicion "medicion"
		\pre 			 Ninguna
		\post      Ninguna
		\return 	true: si se encuentra dentro del monticulo; false: si no se encuentra dentro de este
		*/

		inline bool has(ed::Medicion medicion){

			for(int i = 0; i < size(); i++){
				if(medicion == getElement(i)){
					return true;
				}
			}

			return false;
		}

		/////////////////////////////////////////////////////////////////////////////////////

		//! \name Métodos públicos de la clase MonticuloMediciones
	public:

		//! \name Constructor

		/*!
		\brief     Constructor de la clase MonticuloMediciones
		\note      Función inline
		\pre       Ninguna
		\post      isEmpty() == true
		*/

		inline MonticuloMediciones(){

			#ifndef NDEBUG
			assert(isEmpty() == true);
			#endif //NDEBUG
		}


		//! \name Observadores publicos

		/*!
		\brief  Comprueba si el montículo está vacío
		\note      Función inline
		\attention Función sobrecargada
		\note   Función de tipo "const": no puede modificar al objeto actual
		\post 	Devuelve verdadero si no tiene mediciones; falso, en caso contrario.
		\return true, si el montículo está vacío; false, en caso contrario
		*/

		inline bool isEmpty() const{

			bool valorDevuelto;

			if(size() == 0){
				valorDevuelto = true;
			}
			else{
				valorDevuelto = false;
			}

			#ifndef NDEBUG
			assert(valorDevuelto == (size() == 0));
			#endif //NDEBUG

			return valorDevuelto;
		}

		/*!
		\brief  Devuelve el número de mediciones del montículo
		\note   Función de tipo "const": no puede modificar al objeto actual
		\return Número entero que representa el número de elementos o ítems del monticulo
		*/

		inline int size() const{ return vectormediciones.size();}

		/*!
		\brief  Devuelve la cima del montículo
		\attention Función sobrecargada
		\note      Función inline
		\note   Función de tipo "const": no puede modificar al objeto actual
		\pre 	  isEmpty() == falso
		\post 	valorDevuelto == getElement(0)
		\return Objeto de tipo medicion que representa el top del montículo.
		*/

		inline ed::Medicion top() const{

			#ifndef NDEBUG
			assert(isEmpty() == false);
			#endif //NDEBUG

			ed::Medicion valorDevuelto = getElement(0);

			#ifndef NDEBUG
			assert(valorDevuelto == getElement(0));
			#endif //NDEBUG

			return valorDevuelto;
		}

		////////////////////////////////////////////////////////////

		//! \name Operaciones de modificación

		/*!
		\brief  Inserta una nueva medición en el montículo
		\attention Función sobrecargada
		\note      Función inline
		\param 		medicion: Objeto de tipo medicion que se va a insertar
		\post 	  isEmpty() == falso
		\post 		has(medicion) == true)
		*/

		inline void insert(ed::Medicion medicion){

			if(has(medicion) == false){
				vectormediciones.push_back(medicion);

				shiftUp(size()-1);

				#ifndef NDEBUG
				assert((isEmpty() == false) &&
				(has(medicion) == true));
				#endif //NDEBUG
			}
			else{
				std::cout<< IRED << "MEDICION YA EXISTENTE DENTRO DEL MONTICULO.\n" << RESET;
			}
		}

		/*!
		\brief  Borra la medición que ocupa la cima
		\attention Función sobrecargada
		\note      Función inline
		\pre 	  isEmpty() == falso
		*/

		inline void remove(){
			#ifndef NDEBUG
			assert((isEmpty() == false));
			#endif //NDEBUG

			if(size() == 1){
				removeAll();
			}
			else{

				setElement(0 , getElement(size()-1));

				vectormediciones.pop_back();

				shiftDown(0);
			}
		}

		/*!
		\brief  Borra todos los elementos del montículo
		\note      Función inline
		\post 	  isEmpty() == true
		*/

		inline void removeAll(){

			vectormediciones.clear();

			#ifndef NDEBUG
			assert((isEmpty() == true));
			#endif //NDEBUG
		}

		/*!
		\brief  Modifica la medición que ocupa la cima y actualiza el montículo para que esté ordenado.
		\note      Función inline
		\pre 	  isEmpty() == false
		\post		has(medicion) == true
		*/

		inline void modify(ed::Medicion medicion){

			setElement(0, medicion);

			shiftDown(0);

			#ifndef NDEBUG
			assert((isEmpty() == false) &&
			(has(medicion) == true));
			#endif //NDEBUG
		}



		//! \name Operadores

		/*!
		\brief     Operador de asignación
		\attention Se sobrecarga el operador de asignación "="
		\note      Función inline
		\warning   Se requiere que las funciones de acceso tengan el modificador const
		\param     m: objeto de la clase MonticuloMediciones pasado como referencia constante
		\pre       El MonticuloMedición "m" debe ser diferente de la medicion actual
		\post      Ninguna
		\return 	 Monticulo de mediciones igual al elemento pasado como argumento
		*/

		inline MonticuloMediciones & operator=(MonticuloMediciones const &m){

			#ifndef NDEBUG
			assert(this != &m);
			#endif //NDEBUG

			this->vectormediciones = m.vectormediciones;

			return *this;
		}


		////////////////////////////////////////////////////////////////////

		//! \name Función de escritura

		/*!
		\brief  Muestra por pantalla todas las mediciones del monticulo
		\note      Función inline
		*/

		inline void print(){

			std::vector <Medicion>::iterator it;
			int iteracionmostrar = 0;
			int pagina=0;

			for(it = vectormediciones.begin(); it != vectormediciones.end(); it++){

				it->escribirMedicion();

				iteracionmostrar++;

				if(iteracionmostrar == 22){
					iteracionmostrar = 0;
					std::cin.ignore();

					pagina++;

					std::cout<<"PAGINA "<<pagina<<"\n";
				}
			}
		}

	}; // Clase MonticuloMediciones

} // Espacio de nombres ed


#endif // _MONTICULO_MEDICIONES_HPP
