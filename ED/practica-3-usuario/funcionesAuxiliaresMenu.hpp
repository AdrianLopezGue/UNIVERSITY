/*!
\file   funcionesAuxiliaresMenu.hpp
\brief  Funciones auxiliares para el programa principal de la práctica 3
\author Adrian Lopez Guerrero
\date 18/4/2017
\version 1.0
*/

#ifndef _FUNCIONESAUXILIARESMENU_HPP_
#define _FUNCIONESAUXILIARESMENU_HPP_

#include "MonticuloMediciones.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>

#include <fstream>

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
  \brief     Funcion auxiliar que muestra informacion relevante acerca del monticulo
  \param     monticulo: monticulo que queremos ver si esta vacio.
  \pre       Ninguna
  \post      Ninguna
  */

  void mostrarInformacionMonticulo(ed::MonticuloMediciones &monticulo);

  /*!
  \brief     Funcion auxiliar que permite comprobar si el monticulo se encuentra vacio (no tiene mediciones)
  \param     monticulo: monticulo que queremos ver si esta vacio.
  \pre       Ninguna
  \post      Ninguna
  */
  void comprobarMonticuloVacio(ed::MonticuloMediciones &monticulo);

  ///////////////////////////////////////////////////////////////////

  /*!
  \brief     Funcion auxiliar que permite cargar las mediciones del monticulo desde un fichero.
  \param     monticulo: monticulo que queremos cargar en un fichero.
  \param     nombrefichero: nombre del fichero que quieres cargar.
  \pre       Ninguna
  \post      Ninguna
  */
  void cargarMonticulo(ed::MonticuloMediciones &monticulo, std::string nombrefichero);

  /*!
  \brief     Funcion auxiliar que permite grabar las mediciones del monticulo a un fichero.
  \param     monticulo: monticulo que queremos grabar en un fichero.
  \param     nombrefichero: nombre del fichero que quieres grabar.
  \pre       Ninguna
  \post      Ninguna
  */
  void grabarMonticulo(ed::MonticuloMediciones &monticulo, std::string nombrefichero);

  ///////////////////////////////////////////////////////////////////

  /*!
  \brief     Funcion auxiliar que permite mostrar todas las mediciones de un monticulo por linea de comandos.
  \param     monticulo: monticulo que queremos mostrar por pantalla.
  \pre       Ninguna
  \post      Ninguna
  */
  void mostrarMedicionesdeMonticulo(ed::MonticuloMediciones &monticulo);

  /*!
  \brief     Funcion auxiliar que permite borrar todas las mediciones del monticulo.
  \param     monticulo: monticulo que queremos borrar.
  \pre       Ninguna
  \post      Ninguna
  */
  void borrarTodosLasMedicionesdeMonticulo(ed::MonticuloMediciones &monticulo);

  ///////////////////////////////////////////////////////////////////

  /*!
  \brief     Funcion auxiliar que permite modificar los datos que identifican los datos de una provincia.
  \param     monticulo: provincia que queremos grabar en un fichero.
  \pre       Ninguna
  \post      Ninguna
  */
  void consultarMedicionenMonticulo(ed::MonticuloMediciones &monticulo);

  /*!
  \brief     Funcion auxiliar que permite insertar una medicion en un monticulo.
  \param     monticulo: monticulo al que queremos insertar un elemento.
  \pre       Ninguna
  \post      Ninguna
  */
  void insertarMedicionenMonticulo(ed::MonticuloMediciones &monticulo);


  ///////////////////////////////////////////////////////////////////

  /*!
  \brief     Funcion auxiliar que permite borrar una medicion en especifico.
  \param     monticulo: monticulo del que queremos borrar una medicion.
  \pre       Ninguna
  \post      Ninguna
  */
  void borrarMediciondeMonticulo(ed::MonticuloMediciones &monticulo);

  /*!
  \brief     Funcion auxiliar que muestra por pantalla que el fichero esta vacío.
  \pre       Ninguna
  \post      Ninguna
  */

  void mostrarMonticuloEstaVacio();

} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FUNCIONESAUXILIARES_HPP_
#endif
