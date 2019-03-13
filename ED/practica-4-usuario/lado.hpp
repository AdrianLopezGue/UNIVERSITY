/*!
\file lado.hpp
\brief Fichero de la clase Lado: lado de un grafo
\author Adrian Lopez Guerrero
\date 26/5/2018
\version 1.0
*/

#ifndef _LADO_HPP_
#define _LADO_HPP_

// Entrada y salida
#include <iostream>
#include <stdlib.h>
#include <cmath>

// Para controlar las precondiciones y postcondiciones mediante asertos
#include <cassert>

// Definición de la clase Fecha
#include "vertice.hpp"


// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;


/*!
\namespace ed
\brief Espacio de nombres para la asignatura Estructuras de Datos

*/

namespace ed {

  /*!
  \class Lado
  \brief Definición de la clase Lado
  \n  Lado creado con dos vertices
  */
  class Lado
  {
    //! \name Atributos privados de la clase Medicion
  private:

    ed::Vertice _first;       //!<  \brief Primer vertice del lado
    ed::Vertice _second;       //!<  \brief Segundo vertice del lado
    int _data;   //!<  \brief Peso del lado

    //! \name Métodos privados de la clase Grafo

    /*!
    \brief     Calcula la distancia euclidea entre dos vertices mediante sus coordenadas
    \note      Función inline
    \param 		 a: primer vertice pasado como referencia constante
    \param 		 b: segundo vertice pasado como referencia constante
    \pre       Ninguna
    \post      Ninguna
    */

    inline int calcularDistancia(ed::Vertice const &a, ed::Vertice const &b){
      int distancia = sqrt((pow(b.getX() - a.getX(), 2)) + (pow(b.getY() - a.getY(), 2)));
      return distancia;
    }

  public:

    //! \name Constructor de la clase Lado

    //!	\name Constructor

    /*!
    \brief Construye un lado tomando como argumento dos vertices, que ocuparan la primera y la segunda posicion
    \attention Función sobrecargada
    \note      Función inline
    \warning   Se requiere que las funciones de acceso tengan el modificador const
    \param     first: objeto de la vertice
    \param     second: objeto de la vertice
    \pre       Comprobar que los dos vertices sean diferentes
    \post      El elemento _first es igual al argument "first" y que el elemento _second sea igual a "second"
    */

    inline Lado(ed::Vertice first, ed::Vertice second){

      #ifndef NDEBUG
      assert(first != second);
      #endif //NDEBUG

      setFirst(first);
      setSecond(second);
      setData(calcularDistancia(first, second));

      #ifndef NDEBUG
      assert(this->first() == first);
      assert(this->second() == second);
      #endif //NDEBUG
    };

    /*!
    \brief     Constructor de "copia" que crea un lado a partir de otro lado
    \attention Función sobrecargada
    \note      Función inline
    \warning   Se requiere que las funciones de acceso first(), second() tengan el modificador const
    \param     objeto de la clase Lado utilizado para proporcionar los valores iniciales del nuevo lado
    \pre       El vertice primero pasado como argumento sea diferente al segundo vertice
    \post      l elemento _first es igual al argument "first" y que el elemento _second sea igual a "second"
    \sa        first(), second(), setFirst(), setSecond(), calcularDistancia()
    */

    inline Lado(Lado const &objeto){

      #ifndef NDEBUG
      assert(objeto.first() != objeto.second());
      #endif //NDEBUG

      setFirst(objeto.first());
      setSecond(objeto.second());
      setData(calcularDistancia(objeto.first(), objeto.second()));

      #ifndef NDEBUG
      assert(this->first() == objeto.first());
      assert(this->second() == objeto.second());
      #endif //NDEBUG
    };

    //! \name Observadores: funciones de consulta de la clase Lado

    /*!
    \brief     Getter de la variable _data
    \note      Función inline
    \return		 Entero con el peso del lado
    \pre       Ninguna
    \post      Ninguna
    */

    inline int getData() const{return _data;};

    /*!
    \brief     Getter de la variable _first
    \note      Función inline
    \return		 Objeto de la clase vertice
    \pre       Ninguna
    \post      Ninguna
    */

    inline ed::Vertice first() const{return _first;};

    /*!
    \brief     Getter de la variable _second
    \note      Función inline
    \return		 Objeto de la clase vertice
    \pre       Ninguna
    \post      Ninguna
    */

    inline ed::Vertice second() const{return _second;};

    //! \name Funciones de modificación de la clase Lado

    /*!
    \brief     Setter de la variable _data
    \note      Función inline
    \pre       Ninguna
    \post      getData() == data
    */

    inline void setData(int data){
      _data = data;

      #ifndef NDEBUG
      assert(getData() == data);

      #endif //NDEBUG
    }

    /*!
    \brief     Setter de la variable _first
    \note      Función inline
    \pre       Ninguna
    \post      this->first() == first
    */

    inline void setFirst(const Vertice &first){
      _first = first;

      #ifndef NDEBUG
      assert(this->first() == first);

      #endif //NDEBUG
    }

    /*!
    \brief     Setter de la variable _second
    \note      Función inline
    \pre       Ninguna
    \post      this->second() == second
    */

    inline void setSecond(const Vertice &second){
      _second = second;

      #ifndef NDEBUG
      assert(this->second() == second);

      #endif //NDEBUG
    }

    /*!
    \brief     Setter de la variable precipitación
    \note      Función inline
    \pre       precipitacion >= 0.0
    \post      abs(_precipitacion-getPrecipitacion()) < COTA_ERROR
    */

    inline bool has(ed::Vertice u){
      return u == first() || u == second();
    }



    inline ed::Vertice other(ed::Vertice u){
      #ifndef NDEBUG
      assert(has(u) == true);

      #endif //NDEBUG

      ed::Vertice retVal;

      if(u == first()){
        retVal = second();
      }
      else{
        retVal = first();
      }

      #ifndef NDEBUG
      assert((has(retVal) == true));

      #endif //NDEBUG

      return retVal;
    }

    //! \name Operadores

    /*!
    \brief     Operador de igualdad: compara si los dos lados tiene los mismos elementos
    \attention Se sobrecarga el operador de igualdad "=="
    \note      Función inline
    \param     lado: objeto de la clase Lado pasado como referencia constante
    \return	   true: si los lados son iguales; false, en caso contrario
    \pre       Ninguna
    \post      valorDevuelto == ((first() == lado.first()) && (second() == lado.second()))
    */

    inline bool operator== (Lado const &lado) const{
      bool valorDevuelto;

      if((first() == lado.first()) &&
      (second() == lado.second())){
        valorDevuelto = true;
      }
      else{
        valorDevuelto = false;
      }

      #ifndef NDEBUG
      assert(valorDevuelto == ((first() == lado.first()) &&
      (second() == lado.second())));

      #endif //NDEBUG

      return valorDevuelto;
    }

    /*!
    \brief     Operador de asignación
    \attention Se sobrecarga el operador de asignación "="
    \note      Función inline
    \warning   Se requiere que las funciones de acceso tengan el modificador const
    \param     objeto: objeto de la clase Lado pasado como referencia constante
    \pre       La medición "objeto" debe ser diferente del lado actual
    \post      this->first() == objeto.first()
    \post      this->second() == objeto.second()
    */

    inline Lado & operator=(Lado const &objeto)
    {
      // Se comprueba que no sean el mismo objeto
      if (this != &objeto)
      {
        this->setFirst(objeto.first());
        this->setSecond(objeto.second());

        #ifndef NDEBUG
        // Se comprueba la postcondición
        assert(this->first() == objeto.first());
        assert(this->second() == objeto.second());
        #endif //NDEBUG
      }

      return *this;
    }

  }; // Fin de la definición de la clase Lado

  //! \name Funciones externas de la clase Lado: sobrecarga de los operadores de flujo

  /*!
  \brief     Sobrecarga del operador de salida o escritura "<<"
  \n Se escriben los datos teniendo en cuenta el formato: first ------ second - peso
  \param     stream: flujo de salida
  \param     lado: objeto de la clase Lado pasado como referencia "constante"
  \pre       Ninguna
  \post      Ningguna
  \sa        operator>>()
  */

  ostream &operator<<(ostream &stream, Lado const &lado);


} // \brief Fin de namespace ed.

//  _MEDICION_HPP_
#endif
