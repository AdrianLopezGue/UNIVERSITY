/*!
\file Medicion.hpp
\brief Fichero de la clase Medicion: medición de una estación meteorológica
\author Adrian Lopez Guerrero
\date 18/4/2017
\version 1.0
*/

#ifndef _MEDICION_HPP_
#define _MEDICION_HPP_

// Entrada y salida
#include <iostream>
#include <stdlib.h>
#include <cmath>

// Para controlar las precondiciones y postcondiciones mediante asertos
#include <cassert>

// Definición de la clase Fecha
#include "Fecha.hpp"

// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

#define COTA_ERROR   1.0e-6 //!< Cota de error para la comparación de números reales


// Se incluye la clase Medicion dentro del espacio de nombres de la asigantura: ed
namespace ed {

  //!  Definición de la clase Medicion
  class Medicion
  {
    //! \name Atributos privados de la clase Medicion
  private:

    ed::Fecha _fecha;       //!<  \brief Fecha de la medición
    float _precipitacion;   //!<  \brief Cantidad de precipitación de la medición

    //! \name Funciones o métodos públicos de la clase Medicion

  public:

    //! \name Constructor de la clase Medicion

    //!	\name Constructor

    /*!
    \brief Construye una medicion estableciendo valores por defecto para la fecha y precipitación
    \attention Función sobrecargada
    \note      Función inline
    \warning   Se requiere que las funciones de acceso tengan el modificador const
    \param     fecha: objeto de la clase Fecha con valores por defecto y real con valores por defecto
    \param     precipitacion: objeto de la clase Fecha con valores por defecto y real con valores por defecto
    \post  getFecha() == fecha
    \post  abs(precipitacion-getPrecipitacion()) < COTA_ERROR
    */

    inline Medicion(ed::Fecha fecha = ed::Fecha(1,1,1), float precipitacion=0.0){

      setFecha(fecha);
      setPrecipitacion(precipitacion);

      #ifndef NDEBUG
      assert((getFecha() == fecha) &&
      (std::abs(precipitacion-getPrecipitacion()) < COTA_ERROR));
      #endif //NDEBUG
    }

    /*!
    \brief     Constructor de "copia"
    \attention Función sobrecargada
    \note      Función inline
    \warning   Se requiere que las funciones de acceso tengan el modificador const
    \param     medicion: Objecto de la clase medición al que se igualará la medición actual
    \post      getFecha() == medicion.getFecha()
    \post      abs(medicion.getPrecipitacion()-getPrecipitacion()) < COTA_ERROR
    */

    inline Medicion(Medicion const &medicion){

      setFecha(medicion.getFecha());
      setPrecipitacion(medicion.getPrecipitacion());

      #ifndef NDEBUG

      assert((getFecha() == medicion.getFecha()) &&
      (std::abs(medicion.getPrecipitacion()-getPrecipitacion()) < COTA_ERROR));

      #endif //NDEBUG
    }

    //! \name Observadores: funciones de consulta de la clase Medicion

    /*!
    \brief     Getter de la variable fecha
    \note      Función inline
    \return		 Objeto de la clase fecha.
    \pre       Ninguna
    \post      Ninguna
    */

    inline ed::Fecha getFecha() const{return _fecha;};

    /*!
    \brief     Getter de la variable precipitación
    \note      Función inline
    \return		 Real con la precipitación de la medición
    \pre       Ninguna
    \post      Ninguna
    */

    inline float getPrecipitacion() const{return _precipitacion;};

    //! \name Funciones de modificación de la clase Medicion

    /*!
    \brief     Setter de la variable fecha
    \note      Función inline
    \pre       Ninguna
    \post      getFecha() == _fecha
    */

    inline void setFecha(ed::Fecha fecha){
      _fecha = fecha;

      #ifndef NDEBUG
      assert(getFecha() == _fecha);

      #endif //NDEBUG
    }

    /*!
    \brief     Setter de la variable precipitación
    \note      Función inline
    \pre       precipitacion >= 0.0
    \post      abs(_precipitacion-getPrecipitacion()) < COTA_ERROR
    */

    inline void setPrecipitacion(float precipitacion){
      #ifndef NDEBUG
      assert(precipitacion >= 0.0);

      #endif //NDEBUG

      _precipitacion = precipitacion;

      #ifndef NDEBUG
      assert(std::abs(_precipitacion-getPrecipitacion()) < COTA_ERROR);
      #endif //NDEBUG
    }


    //! \name Operadores

    /*!
    \brief     Operador de igualdad: compara si las dos mediciones tiene la misma fecha
    \attention Se sobrecarga el operador de igualdad "=="
    \note      Función inline
    \param     medicion: objeto de la clase Medicion pasado como referencia constante
    \return	   true: si las mediciones son iguales; false, en caso contrario
    \pre       Ninguna
    \post      valorDevuelto == (getFecha() == medicion.getFecha())
    */

    inline bool operator== (Medicion const &medicion) const{
      bool valorDevuelto;

      if(getFecha() == medicion.getFecha()){
        valorDevuelto = true;
      }
      else{
        valorDevuelto = false;
      }

      #ifndef NDEBUG
      assert(valorDevuelto == (getFecha() == medicion.getFecha()));

      #endif //NDEBUG

      return valorDevuelto;
    }

    /*!
    \brief     Operador de asignación
    \attention Se sobrecarga el operador de asignación "="
    \note      Función inline
    \warning   Se requiere que las funciones de acceso tengan el modificador const
    \param     medicion: objeto de la clase Medicion pasado como referencia constante
    \pre       La medición "medicion" debe ser diferente de la medicion actual
    \post      getFecha() == medicion.getFecha()
    \post      abs(medicion.getPrecipitacion()-getPrecipitacion()) < COTA_ERROR
    */

    inline Medicion & operator =(Medicion const &medicion){

      if(this != &medicion){
        this->setFecha(medicion.getFecha());
        this->setPrecipitacion(medicion.getPrecipitacion());

        #ifndef NDEBUG
        assert((getFecha() == medicion.getFecha()) &&
        (std::abs(medicion.getPrecipitacion()-getPrecipitacion()) < COTA_ERROR));
        #endif //NDEBUG
      }

      return *this;
    }


    //! \name Funciones de lectura y escritura de la clase Medicion

    /*!
    \brief   Permite al usuario asignar los valores de Fecha y precipitación por teclado
    \pre     Ninguna
    \post    Ninguna
    */

    void leerMedicion();

    /*!
    \brief Escribe por pantalla los valores de los atributos de una Medicion
    \note  Formato: dia-mes-año precipitación
    \pre   Ninguna
    \post  Ninguna
    */

    void escribirMedicion();



  }; // Fin de la definición de la clase Medicion


  //! \name Funciones externas de la clase Medicion: sobrecarga de los operadores de flujo

  /*!
  \brief     Sobrecarga del operador de salida o escritura "<<"
  \n Se escriben los datos teniendo en cuenta el formato: dia-mes-año precipitación
  \param     stream: flujo de salida
  \param     medicion: objeto de la clase Medicion pasado como referencia "constante"
  \pre       Ninguna
  \post      Ningguna
  \sa        operator>>()
  */

  ostream &operator<<(ostream &stream, Medicion const &medicion);

  /*!
  \brief     Sobrecarga del operador de entrada o lectura ">>"
  \n  Se lee una medicion con el formato: dia-mes-año precipitación
  \attention Función amiga de la clase Medicion
  \param     stream: flujo de salida
  \param     medicion: objeto de la clase Medicion pasado como referencia
  \pre       Ninguna
  \post      Ninguna
  \sa        operator<<()
  */

  istream &operator>>(istream &stream, Medicion &medicion);


} // \brief Fin de namespace ed.

//  _MEDICION_HPP_
#endif
