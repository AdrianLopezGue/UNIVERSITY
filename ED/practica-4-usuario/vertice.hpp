/*!
\file vertice.hpp
\brief Fichero de la clase Vertice: vertice de un grafo
\author Adrian Lopez Guerrero
\date 26/5/2018
\version 1.0
*/

#ifndef _VERTICE_HPP_
#define _VERTICE_HPP_

#include <iostream>
// Para controlar las precondiciones y postcondiciones mediante asertos
#include <cassert>
#include <stdlib.h>
#include <cmath>
#include "macros.hpp"
#include "verticeInterfaz.hpp"
// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

#define COTA_ERROR   1.0e-6 //!< Cota de error para la comparación de números reales

/*!
\namespace ed
\brief Espacio de nombres para la asignatura Estructuras de Datos

*/
namespace ed {

  /*!
  \class Vertice
  \brief Definición de la clase Vertice
  \n  Vertice especificado con coordenadas 2D
  */

  class Vertice : public VerticeInterfaz
  {
    //! \name Atributos privados de la clase Vertice
  private:
    float _x;  //!< coordenada x
    float _y;  //!< coordenada y
    int _label; //!< identificador
    //! \name Funciones o métodos públicos de la clase Vertice
  public:

    //! \name Constructores de la clase Vertice

    //!	\name Constructor

    /*!
    \brief     Constructor que crea un Vertice
    \attention Función sobrecargada
    \note      Función inline
    \warning   Los parámetros tienen valores por defecto
    \param     x: coordenada x; valor por defecto: 0
    \param     y: coordenada y; valor por defecto: 0
    \pre       Ninguna
    \post      Las coordenadas deben de haberse introducido correctamente
    \sa        setX, setY()
    */


    inline Vertice(float x = 0, float y = 0)
    {
      this->setX(x);
      this->setY(y);
      this->setLabel(-1);

      #ifndef NDEBUG
      // Se comprueba la postcondición
      assert((std::abs(x-getX()) < COTA_ERROR) &&
      (std::abs(y-getY()) < COTA_ERROR));
      #endif //NDEBUG

    }

    /*!
    \brief     Constructor de "copia" que crea un vertice a partir de otro vertice
    \attention Función sobrecargada
    \note      Función inline
    \warning   Se requiere que las funciones de acceso getX() y getY() tengan el modificador const
    \param     objeto de la clase Vertice utilizado para proporcionar los valores iniciales del nuevo vertice
    \pre       Ninguna
    \post      Los atributos _x e _y deben tener los valores de los atributos del objeto pasado como argumento
    \sa        getX(), getY()
    */
    inline Vertice(Vertice const &objeto)
    {

      this->setX(objeto.getX());
      this->setY(objeto.getY());
      this->setLabel(objeto.getLabel());

      #ifndef NDEBUG
      // Se comprueba la postcondición
      assert((std::abs(objeto.getX()-this->getX()) < COTA_ERROR) &&
      (std::abs(objeto.getY()-this->getY()) < COTA_ERROR) &&
      (objeto.getLabel() == this->getLabel()));
      #endif //NDEBUG
    }

    //! \name Observadores: funciones de consulta de la clase Vertice

    /*!
    \brief   Función que devuelve la coordenada X de un vertice
    \attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
    \note    Función inline
    \return  Valor del atributo que representa la coordenada X (tipo float)
    \pre     Ninguna
    \post    Ninguna
    */
    inline float getX() const
    {
      return this->_x;
    }

    /*!
    \brief   Función que devuelve la coordenada Y de un vertice
    \attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
    \note    Función inline
    \return  Valor del atributo que representa la coordenada Y (tipo float)
    \pre     Ninguna
    \post    Ninguna
    */
    inline float getY() const
    {
      return 	this->_y;
    }

    /*!
    \brief   Función que devuelve la etiqueta de un vertice
    \attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
    \note    Función inline
    \return  Valor del atributo que representa la etiqueta (tipo int)
    \pre     Ninguna
    \post    Ninguna
    */

    inline int getLabel() const
    {
      return 	this->_label;
    }


    //! \name Funciones de modificación de la clase Vertice

    /*!
    \brief Función que asigna un nuevo valor a la coordenada X del vertice
    \note  Función inline
    \param x: nuevo valor de la coordenada X
    \pre   Ninguna
    \post  El atributo _x de Vertice debe tener el valor "x"
    \sa    getX()
    */
    inline void setX(float x)
    {
      this->_x = x;

      #ifndef NDEBUG
      // Se comprueba la postcondición
      assert((std::abs(x-getX()) < COTA_ERROR));
      #endif //NDEBUG
    }


    /*!
    \brief Función que asigna un nuevo valor a la coordenada Y del vertice
    \note  Función inline
    \param y: nuevo valor de la coordenada Y
    \pre   ninguna
    \post  El atributo _y de Vertice debe tener el valor "y"
    \sa    getY()
    */
    inline void setY(float y)
    {
      this->_y = y;

      #ifndef NDEBUG
      // Se comprueba la postcondición
      assert((std::abs(y-getY()) < COTA_ERROR));
      #endif //NDEBUG
    }

    /*!
    \brief Función que asigna un nuevo valor a la etiqueta del vertice
    \note  Función inline
    \param label: nuevo valor de la etiqueta
    \pre   ninguna
    \post  El atributo _label de Vertice debe tener el valor "label"
    \sa    getY()
    */
    inline void setLabel(int label)
    {
      this->_label = label;

      #ifndef NDEBUG
      // Se comprueba la postcondición
      assert((this->getLabel() == label));
      #endif //NDEBUG
    }

    //! \name Operadores

    /*!
    \brief     Operador de asignación: operador que "copia" un vertice en otro vertice
    \attention Se sobrecarga el operador de asignación "="
    \note      Función inline
    \warning   Se requiere que las funciones de acceso getX, getY y getLabel tengan el modificador const
    \param     objeto de la clase vertice pasado como referencia constante
    \pre       El objeto es distinto del objeto actual
    \post      Los atributos _x y _y _label deben tener los valores de los atributos del objeto pasado como argumento
    \sa        getX(), getY()
    */
    inline Vertice & operator=(Vertice const &objeto)
    {
      // Se comprueba que no sean el mismo objeto
      if (this != &objeto)
      {
        this->setX(objeto.getX());
        this->setY(objeto.getY());
        this->setLabel(objeto.getLabel());

        #ifndef NDEBUG
        // Se comprueba la postcondición
        assert((std::abs(objeto.getX()-this->getX()) < COTA_ERROR) &&
        (std::abs(objeto.getY()-this->getY()) < COTA_ERROR) &&
        (objeto.getLabel() == this->getLabel()));
        #endif //NDEBUG
      }

      return *this;
    }


    /*!
    \brief     Operador de igualdad: compara si dos vertices son iguales
    \attention Se sobrecarga el operador de asignación "=="
    \note      Función inline
    \param     objeto: Vertice pasado como referencia constante
    \pre       Ninguna
    \post      Ninguna
    \sa        getX(), getY()
    */
    inline bool operator == (Vertice const &objeto) const
    {
      return (( this->getX() == objeto.getX() ) &&
      ( this->getY() == objeto.getY() )
    );
  }

  /*!
  \brief     Operador de desigualdad: compara si dos vertices no son iguales
  \attention Se sobrecarga el operador de asignación "!="
  \note      Función inline
  \param     objeto: Vertice pasado como referencia constante
  \pre       Ninguna
  \post      Ninguna
  \sa        getX(), getY()
  */

  inline bool operator != (Vertice const &objeto) const
  {
    return (
      ( this->getX() != objeto.getX() ) or
      ( this->getY() != objeto.getY() ) or
      ( this->getLabel() != objeto.getLabel())
    );
  }


  //! \name Funciones de lectura y escritura de la clase Fecha

  /*!
  \brief Escribe por pantalla los valores de los atributos de un vertice
  \pre   Ninguna
  \post  Ninguna
  \sa    getY(), getX()
  */
  void escribirVertice()const;

  /*!
  \brief   Lee desde el teclado los nuevos valores de los atributos de una fecha
  \warning Se deben teclear números
  \pre     ninguna
  \post    La fecha debe ser correcta
  \sa      setX(), setY()
  */
  void leerVertice();


}; // Fin de la definición de la clase Fecha


//! \name Funciones externas de la clase Fecha: sobrecarga de los operadores de flujo

/*!
\brief     Sobrecarga del operador de salida o escritura "<<"
\n         Se escribe la fecha por pantalla con el formato (x) (y)
\param     stream Flujo de salida
\param     vertice pasado como referencia constante
\pre       Ninguna
\post      Ninguna
\sa        operator>>()
*/
ostream &operator<<(ostream &stream, Vertice const &vertice);

/*!
\brief     Sobrecarga del operador de entrada o lectura ">>"
\param     stream Flujo de entrada
\param     vertice pasado como referencia
\pre       Ninguna
\post      Ninguna
\sa        operator<<()
*/
istream &operator>>(istream &stream, Vertice &vertice);




} // \brief Fin de namespace ed.

#endif
