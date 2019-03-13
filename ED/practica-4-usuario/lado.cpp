/*!
\file  lado.cpp
\brief Fichero que contiene el código de las funciones de la clase lado
*/

#include "lado.hpp"

namespace ed{

  // Sobrecarga del operador de salida
  ostream &operator<<(ostream &stream, Lado const &lado)
  {
    stream << lado.first();
    stream << " --- ";
    stream << lado.second();
    stream << " : ";
    stream << lado.getData();
    stream << "\n";

    return stream;
  }

} // Fin del espacio de nombres ed
