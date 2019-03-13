/*!
\file  Medicion.cpp
\brief Fichero que contiene el código de las funciones de la clase Medicion
\author Adrian Lopez Guerrero
\date 18/4/2017
\version 1.0
*/


// Ficheros de cabecera
#include <iostream>

// atoi, atof
#include <stdlib.h>

#include "Medicion.hpp"


void ed::Medicion::leerMedicion(){
  double precipitacionaux;

  getFecha().leerFecha();

  std::cout << " Precipitacion --> ";
  std::cin >> precipitacionaux;

  setPrecipitacion(precipitacionaux);
}

void ed::Medicion::escribirMedicion(){
  std::cout << getFecha().getDia() << "-"
  << getFecha().getMes() << "-"
  << getFecha().getAgno() << " "
  << getPrecipitacion() << std::endl;
}


////////////////////////////////////////////////////////////////////////////////


// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{

  // Sobrecarga del operador de salida
  ostream &operator<<(ostream &stream, ed::Medicion const &medicion)
  {

    stream << medicion.getFecha();
    stream << " ";
    stream << medicion.getPrecipitacion();
    stream << "\n";

    return stream;
  }

  // Sobrecarga del operador de entrada
  istream &operator>>(istream &stream, ed::Medicion &medicion)
  {

    std::string cadena;
    ed::Fecha fechaaux;

    fechaaux.leerFecha();

    medicion.setFecha(fechaaux);

    std::getline(stream,cadena,' ');
    medicion.setPrecipitacion(atoi(cadena.c_str()));

    return stream;
  }

} // Fin del espacio de nombres ed
