/*!
\file principalmenu.cpp
\brief Menu del programa.
\author Adrian Lopez Guerrero
\date 26/4/2018
\version 1.0
*/

#include <iostream>
#include <string>
#include <stdlib.h>

#include "funcionesAuxiliares.hpp"
#include "macros.hpp"

/*!
\brief   Programa principal de la práctica 4: vertices, grafos y lados
\return  int
*/
int main(int argc, char const *argv[]) {

  srand(time(NULL));
  int opcion;

  do{
    // Se elige la opción del menún
    opcion = menu();

    std::cout << CLEAR_SCREEN;
    PLACE(3,1);

    // Se ejecuta la opción del menú elegida
    switch(opcion)
    {
      case 0:
      std::cout << INVERSE;
      std::cout << "Fin del programa" << std::endl;
      std::cout << RESET;
      break;

      ///////////////////////////////////////////////////////////////////

      case 1:
      std::cout<< "[1] Metodo no Sofisticado: Sacudida"<<std::endl;
      realizarMetodo(0);
      break;

      case 2:
      std::cout<< "[2] Metodo Sofisticado: Ordenacion por monticulo"<<std::endl;
      realizarMetodo(1);
      break;

      //////////////////////////////////////////////////////////////////////////////
      default:
      std::cout << BIRED;
      std::cout << "Opción incorrecta ";
      std::cout << RESET;
      std::cout << "--> ";
      std::cout << ONIRED;
      std::cout << opcion << std::endl;
      std::cout << RESET;
    }

    if (opcion !=0)
    {
      PLACE(25,1);
      std::cout << "Pulse ";
      std::cout << BIGREEN;
      std::cout << "ENTER";
      std::cout << RESET;
      std::cout << " para mostrar el ";
      std::cout << INVERSE;
      std::cout << "menú";
      std::cout << RESET;

      // Pausa
      std::cin.ignore();

      std::cout << CLEAR_SCREEN;
    }
  }while(opcion!=0);

  return 0;
}
