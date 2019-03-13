/*!
\file  Provincia.hpp
\brief Definición de la clase Provincia
\author Adrian Lopez Guerrero
\date 6/4/2017
\version 1.0

*/

#ifndef _PROVINCIA_HPP_
#define _PROVINCIA_HPP_

// Para comprobar las pre y post condiciones
#include <cassert>

#include <string>


#include "ListaDoblementeEnlazadaOrdenadaMunicipios.hpp"



// DEBES COMPLETAR LOS COMENTARIOS DE DOXYGEN

/*!
\namespace ed
\brief Espacio de nombres para la Provincia Estructuras de Datos

*/
namespace ed{
	/*!

	\class Provincia
	\brief Definición de la clase Provincia

	*/
	class Provincia
	{
		//!	\name Métodos públicos de la clase Provincia

	private:
		std::string      _nombre;     //!<  \brief Nombre de la Provincia
		int              _codigo;	  //!<  \brief Código de la Provincia

		ed::ListaDoblementeEnlazadaOrdenadaMunicipios _listaMunicipios; //!<  \brief Lista de municipios de la Provincia


		/////////////////////////////////////////////////////////////////////

		//!	\name  Métodos públicos de la clase Provincia

	public:

		//!	\name Constructor
		/*!
		\brief Construye una provincia estableciendo valores por defecto para nombre, codigo y municipios.
		\note  Función inline
		\post  getNombre() == nombre
		\post  getCodigo() == codigo
		\post  hayMunicipios() == false
		*/
		Provincia(std::string nombre="", int codigo=0){
			setNombre(nombre);
			setCodigo(codigo);

			#ifndef NDEBUG
			assert((getNombre() == nombre) &&
						 (getCodigo() == codigo) &&
						 (hayMunicipios() == false));
			#endif
		}


		/////////////////////////////////////////////////////////////////////

		//!	\name Observadores
		/*!
		\brief     Getter de la variable nombre
		\note      Función inline
		\return		 String con el nombre de la provincia.
		\pre       Ninguna
		\post      Ninguna
		*/
		inline std::string getNombre() const{return _nombre;}

		/*!
		\brief     Getter de la variable codigo
		\note      Función inline
		\return		 Entero con el codigo de la provincia
		\pre       Ninguna
		\post      Ninguna
		*/

		inline int getCodigo() const{return _codigo;}

		/*!
			\brief     Comprueba si existen municipios dentro de la provincia.
			\note      Función inline
			\return		 True si existen municipios; False si no hay ningun municipio
			\pre       Ninguna
			\post      Ninguna
			\sa        getNumeroMunicipios()
		*/

		inline bool hayMunicipios(){
			if(this->getNumeroMunicipios() == 0){
				return false;
			}
			else{
				return true;
			}
		}

		/*!
			\brief     Devuelve el numero de municipios de la provincia
			\note      Función inline
			\return		 Entero con el numero total de municipios de la provincia.
			\pre       Ninguna
			\post      Ninguna
			\sa        nItems()
		*/

		inline int getNumeroMunicipios() {return this->_listaMunicipios.nItems();}
		/*!
			\brief     Comprueba si existe un municipio con el nombre pasado como argumento
			\note      Función inline
			\return		 True si existe el municipio dentro la provincia; False si no hay ningun municipio coincidente.
			\pre       Ninguna
			\post      Ninguna
			\sa        find()
		*/
		inline bool existeMunicipio(std::string nombre){

			ed::Municipio municipio(nombre);
			return this->_listaMunicipios.find(municipio);

		}
		/*!
			\brief     Devuelve un municipio que coincida con el nombre pasado como argumento
			\note      Función inline
			\param     nombre: string con el nombre del municipio que se quiere buscar.
			\return  	 Municipio coincidente con el nombre.
			\pre       this->existeMunicipio(nombre) == true
			\post      Ninguna
			\sa        existeMunicipio(), getCurrentItem()
		*/
		inline ed::Municipio getMunicipio(std::string nombre){
			#ifndef NDEBUG
			assert(this->existeMunicipio(nombre) == true);
			#endif

			return _listaMunicipios.getCurrentItem();
		}
		/*!
			\brief     Devuelve el numero de hombres dentro de la provincia.
			\return 	 Entero con el numero de hombres de la provincia
			\pre       Ninguna
			\post      Ninguna
		*/
		int getTotalHombres();

		/*!
			\brief     Devuelve el numero de mujeres dentro de la provincia.
			\return		 Entero con el numero de mujeres de la provincia
			\pre       Ninguna
			\post      Ninguna
		*/

		int getTotalMujeres();

		/*!
			\brief     Devuelve la suma de hombres y mujeres de la provincia.
			\note      Función inline
			\pre       Ninguna
			\post      valorDevuelto == this->getTotalHombres() + this->getTotalMujeres()
		*/

		int getTotalHabitantes();


		/////////////////////////////////////////////////////////////////////

		//!	\name Modificadores

		/*!
    \brief     Setter de la variable nombre
    \note      Función inline
    \pre       Ninguna
    \post      getNombre() == nombre
    */

		inline void setNombre(std::string nombre){
			_nombre = nombre;

			#ifndef NDEBUG
			assert(getNombre() == nombre);
			#endif
		}

		/*!
    \brief     Setter de la variable codigo
    \note      Función inline
    \pre       Ninguna
    \post      getCodigo() == codigo
    */

		inline void setCodigo(int codigo){
			_codigo = codigo;

			#ifndef NDEBUG
			assert(getCodigo() == codigo);
			#endif
		}

		/*!
			\brief     Inserta el municipio pasado como argumento en la lista ordenada
			\param     municipio: Municipio que se desea insertar en la provincia.
			\pre       this->existeMunicipio(municipio.getNombre()) == false
			\post      this->existeMunicipio(municipio.getNombre()) == true
			\post      this->getNumeroMunicipios() == oldnumeromunicipios+1
		*/

		void insertarMunicipio(Municipio municipio);

		/*!
			\brief     Borra el municipio que le indiquemos por argumento.
			\param     nombre: string del municipio que se desea borrar de la lista ordenada
			\pre       this->existeMunicipio(municipio.getNombre()) == false
			\post      this->existeMunicipio(municipio.getNombre()) == true
			\post      this->getNumeroMunicipios() == oldnumeromunicipios+1
		*/

		void borrarMunicipio(std::string nombre);

		/*!
			\brief     Borra todos los municipios de la provincia.
			\pre       Ninguna
			\post      this->hayMunicipios() == false
		*/

		void borrarTodosLosMunicipios();

		/////////////////////////////////////////////////////////////////////

		//! \name Función de escritura de la clase Provincia

		/*!
			\brief     Funcion para escribir por pantalla todos los municipios de la provincia.
			\pre       Ninguna
			\post      Ninguna
		*/

		void escribirMunicipios();

		/////////////////////////////////////////////////////////////////////

		//! Operaciones con ficheros

		/*!
			\brief     Permite cargar los municipios desde un fichero con el formato correcto
			\param     nombre: string que guarda el nombre del fichero que queremos tomar los datos
			\return	   true: se ha cargado correctamente; false, no se ha podido cargar correctamente
			\pre       Ninguna
			\post      Ninguna
		*/

		bool cargarFichero(std::string nombre);

		/*!
			\brief     Permite grabar los municipios a un fichero.
			\param     nombre: string que guarda el nombre del fichero que queremos crear con los municipios de la provincia
			\return	   true: se ha grabado correctamente; false, no se ha podido grabar correctamente
			\pre       Ninguna
			\post      Ninguna
		*/

		bool grabarFichero(std::string nombre);

	}; //Fin de la clase  Provincia


} // Fin del espacio de nombres ed

#endif // _PROVINCIA_HPP_
