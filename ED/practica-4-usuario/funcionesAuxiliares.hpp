/*!
\file funcionesAuxiliares.hpp
\brief Fichero de funciones auxiliares
\author Adrian Lopez Guerrero
\date 26/5/2018
\version 1.0
*/

#ifndef _FUNCIONESAUXILIARES_HPP_
#define _FUNCIONESAUXILIARES_HPP_

#include <iostream>
#include <fstream>
#include <string>

#include "vertice.hpp"
#include "grafo.hpp"

/*!
\namespace ed
\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed{

  /*!
  \brief     Funcion que permite generar un ambiente interactivo con el usuarios con el que manejar los grafos de manera sencilla
  \pre       Ninguna
  \post      Ninguna
  */
  int menu();

  ///////////////////////////////////////////////////////////////////

  /*!
  \brief     Funcion auxiliar que carga los vertices de un fichero
  \param     grafo: grafo al que queremos cargar los vertices.
  \pre       Ninguna
  \post      Ninguna
  */

  void cargarVerticesFichero(ed::Grafo &grafo);

  /*!
  \brief     Funcion auxiliar que graba los lados del grafo en un fichero
  \param     grafo: grafo que queremos grabar los lados
  \pre       Ninguna
  \post      Ninguna
  */

  void grabarVerticesFichero(ed::Grafo &grafo);

  /*!
  \brief     Funcion auxiliar que imprime la matriz del grafo principal
  \param     grafo: grafo que queremos mostrar.
  \pre       Ninguna
  \post      Ninguna
  */

  void imprimirMatrizGrafoPrincipal(ed::Grafo &grafo);

  /*!
  \brief     Funcion auxiliar que imprime la matriz del arbol abarcador minimo
  \param     grafo: grafo que queremos mostrar.
  \pre       Ninguna
  \post      Ninguna
  */

  void imprimirMatrizArbol(ed::Grafo &grafo);

  /*!
  \brief     Funcion auxiliar que realiza el algoritmo de prim
  \param     grafo: grafo que recibira el resultado de realizar el algoritmo de prim
  \pre       Ninguna
  \post      Ninguna
  */

  Grafo AlgoritmoPrim(ed::Grafo &grafo);

  /*!
  \brief     Funcion auxiliar que realiza el algoritmo de kruskal
  \param     grafo: grafo que recibira el resultado de realizar el algoritmo de kruskal
  \pre       Ninguna
  \post      Ninguna
  */

  Grafo AlgoritmoKruskal(ed::Grafo &grafo);

  /*!
  \brief     Funcion auxiliar que añade un vertice
  \param     grafo: grafo al que vamos a añadir el vertice
  \pre       Ninguna
  \post      Ninguna
  */

  void anadirVertice(ed::Grafo &grafo);

  /*!
  \brief     Funcion auxiliar que muestra los lados del grafo que pasemos como argumento
  \param     grafo: grafo que queremos mostrar los lados
  \pre       Ninguna
  \post      Ninguna
  */

  void mostrarLados(ed::Grafo &grafo);

  /*!
  \brief     Funcion auxiliar que muestra los vertices del grafo que pasemos como argumento
  \param     grafo: grafo que queremos mostrar los vertices
  \pre       Ninguna
  \post      Ninguna
  */

  void mostrarVertices(ed::Grafo &grafo);

  /*!
  \brief     Funcion auxiliar que borra los vertices del grafo que pasemos como argumento
  \param     grafo: grafo que queremos borrar los vertices
  \pre       Ninguna
  \post      Ninguna
  */

  void borrarVertices(ed::Grafo &grafo);

  /*!
  \brief     Funcion auxiliar que calcula la longitud del arbol abarcador
  \param     grafo: arbol abarcador que queremos calcular la longitud
  \pre       Ninguna
  \post      Ninguna
  */

  void longitudArbolAbarcador(ed::Grafo &grafo);

  /*!
  \brief     Funcion auxiliar que permite mostrar si el grafo que invoque la funcion esta vacio
  \pre       Ninguna
  \post      Ninguna
  */

  void mostrarGrafoEstaVacio();
}

#endif
