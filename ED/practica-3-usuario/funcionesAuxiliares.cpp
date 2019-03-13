/*!
\file   funcionesAuxiliares.cpp
\brief  Código de las funciones auxiliares para el programa principal de la práctica 1
\author Adrian Lopez Guerrero
\date 18/4/2017
\version 1.0
*/


#include <iostream>

#include <fstream>

#include <string>

#include "funcionesAuxiliares.hpp"

#include "MonticuloMediciones.hpp"

#include "Medicion.hpp"

#include "macros.hpp"

void ed::cargarMonticuloDeFichero(std::string const & nombreFichero, ed::MonticuloMediciones & monticulo)
{
  // COMPLETAR
  std::ifstream fichero(nombreFichero.c_str());

  if(fichero){

    char cadenaaux[256];

    double precipitacionaux;
    ed::Fecha fechaaux;

    monticulo.removeAll();

    while(fichero.getline(cadenaaux, 256, '-') != NULL){
      fechaaux.setDia(atoi(cadenaaux));

      fichero.getline(cadenaaux, 256, '-');
      fechaaux.setMes(atoi(cadenaaux));

      fichero.getline(cadenaaux, 256, ' ');
      fechaaux.setAgno(atoi(cadenaaux));

      fichero.getline(cadenaaux, 256, '\n');
      precipitacionaux = atof(cadenaaux);

      ed::Medicion medicionaux(fechaaux, precipitacionaux);

      monticulo.insert(medicionaux);
    }

    fichero.close();
  }
}


void ed::grabarMonticuloEnFichero(std::string const & nombreFichero,
  ed::MonticuloMediciones const & monticulo)
  {
    if(monticulo.isEmpty() == true){
      std::cout<<"No se puede grabar el monticulo (VACIO)\n";
      return;
    }

    std::ofstream fichero(nombreFichero.c_str());

    if(fichero){

      ed::MonticuloMediciones monticuloaux = monticulo;

      while(monticuloaux.size() != 0){

        fichero<<monticuloaux.top();

        monticuloaux.remove();
      }

      fichero.close();
    }
  }
