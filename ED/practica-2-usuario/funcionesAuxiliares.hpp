/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 2
  \author Adrian Lopez Guerrero
  \date 6/4/2017
*/

#ifndef _FUNCIONESAUXILIARES_HPP_
#define _FUNCIONESAUXILIARES_HPP_

#include "Provincia.hpp"


// SE DEBEN INCLUIR LOS COMENTARIOS DE DOXYGEN DE CADA FUNCIÓN

namespace ed
{

  /*!
    \brief     Funcion que permite generar un ambiente interactivo con el usuarios con el que manejar las listas de municipìos de manera organizada
    \pre       Ninguna
    \post      Ninguna
  */
  int menu();

	///////////////////////////////////////////////////////////////////

  /*!
    \brief     Funcion auxiliar que permite comprobar si la provincia se encuentra vacia (no tiene municipios)
    \param     provincia: provincia que queremos ver si esta vacia.
    \pre       Ninguna
    \post      Ninguna
    \sa        hayMunicipios()
  */
	void comprobarProvinciaVacia(ed::Provincia & provincia);

	///////////////////////////////////////////////////////////////////

  /*!
    \brief     Funcion auxiliar que permite cargar los municipios de la provincia desde un fichero.
    \param     provincia: provincia que queremos cargar en un fichero.
    \pre       Ninguna
    \post      Ninguna
    \sa        cargarFichero()
  */
	void cargarProvincia(ed::Provincia & provincia);

  /*!
    \brief     Funcion auxiliar que permite grabar los municipios de la provincia a un fichero.
    \param     provincia: provincia que queremos grabar en un fichero.
    \pre       Ninguna
    \post      Ninguna
    \sa        grabarFichero()
  */
	void grabarProvincia(ed::Provincia & provincia);

	///////////////////////////////////////////////////////////////////

  /*!
    \brief     Funcion auxiliar que permite consultar los datos de una provincia.
    \param     provincia: provincia que queremos grabar en un fichero.
    \pre       Ninguna
    \post      Ninguna
  */
	void consultarDatosDeProvincia(ed::Provincia & provincia);

  /*!
    \brief     Funcion auxiliar que permite mostrar todos los municipios de una provincia por linea de comandos.
    \param     provincia: provincia que queremos grabar en un fichero.
    \pre       Ninguna
    \post      Ninguna
    \sa        escribirMunicipios()
  */
	void mostrarMunicipiosDeProvincia(ed::Provincia & provincia);

	///////////////////////////////////////////////////////////////////

  /*!
    \brief     Funcion auxiliar que permite modificar los datos que identifican los datos de una provincia.
    \param     provincia: provincia que queremos grabar en un fichero.
    \pre       Ninguna
    \post      Ninguna
    \sa        getNombre(),getCodigo(),setNombre(),setCodigo()
  */
	void modificarDatosDeProvincia(ed::Provincia & provincia);

  /*!
    \brief     Funcion auxiliar que permite borrar todos los municipios de la provincia.
    \param     provincia: provincia que queremos grabar en un fichero.
    \pre       Ninguna
    \post      Ninguna
    \sa        borrarTodosLosMunicipios()
  */
	void borrarTodosLosMunicipiosDeProvincia(ed::Provincia & provincia);


	///////////////////////////////////////////////////////////////////

  /*!
    \brief     Funcion auxiliar que permite consultar los datos de un municipio que se encuentre en la provincia.
    \param     provincia: provincia que queremos grabar en un fichero.
    \pre       El municipio a consultar exista dentro de la provincia.
    \post      Ninguna
    \sa        existeMunicipio(), getMunicipio(),escribirMunicipio()
  */
	void consultarMunicipioDeProvincia(ed::Provincia & provincia);

  /*!
    \brief     Funcion auxiliar que permite insertar un municipio dentro de la provincia.
    \param     provincia: provincia que queremos grabar en un fichero.
    \pre       Ninguna
    \post      Ninguna
    \sa        leerMunicipio(), existeMunicipio(), getNombre(), insertarMunicipio()
  */
	void insertarMunicipioEnProvincia(ed::Provincia & provincia);

  /*!
    \brief     Funcion auxiliar que permite borrar un municipìo dado su nombre, si este existe dentro de la provincia.
    \param     provincia: provincia que queremos grabar en un fichero.
    \pre       Exista un municipio con el nombre dentro de la provincia.
    \post      Ninguna
    \sa        existeMunicipio(),borrarMunicipio()
  */
	void borrarMunicipioDeProvincia(ed::Provincia & provincia);


} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FUNCIONESAUXILIARES_HPP_
#endif
