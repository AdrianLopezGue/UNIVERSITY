/*!
\file  vertice.cpp
\brief Fichero que contiene el código de las funciones de la clase vertice
*/


// Ficheros de cabecera
#include <iostream>

// atof
#include <stdlib.h>

#include "vertice.hpp"

/*
Definiciones de las funciones de lectura y escritura de la clase Fecha
*/

void ed::Vertice::escribirVertice()const
{
  std::cout << this->getX() << " "  << this->getY() << " " << this->getLabel() << std::endl;
}


void ed::Vertice::leerVertice()
{
  float x, y;

  std::cout<<"Coordenada X: ";
  std::cin>>x;

  std::cout<<"Coordenada Y: ";
  std::cin>>y;

  // Se asignan los valores leídos a los atributos del vertice
  this->setX(x);
  this->setY(y);
}


////////////////////////////////////////////////////////////////////////////////


// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{

  // Sobrecarga del operador de salida
  ostream &operator<<(ostream &stream, ed::Vertice const &vertice)
  {
    stream << vertice.getX();
    stream << " ";
    stream << vertice.getY();
    stream << " ";
    stream << vertice.getLabel();

    return stream;
  }

  // Sobrecarga del operador de entrada
  istream &operator>>(istream &stream, ed::Vertice &vertice)
  {
    // Se lee la fecha teniendo en cuenta el formato: DD-MM-AAAA
    std::string cadena;

    std::getline(stream,cadena,' ');
    vertice.setX(atof(cadena.c_str()));

    std::getline(stream,cadena,'\n');
    vertice.setY(atof(cadena.c_str()));

    return stream;
  }

} // Fin del espacio de nombres ed
