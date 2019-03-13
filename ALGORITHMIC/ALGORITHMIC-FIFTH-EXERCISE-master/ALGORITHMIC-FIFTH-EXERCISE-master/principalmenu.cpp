/*!
\file principalmenu.cpp
\brief Menu del programa.
\author Adrian Lopez Guerrero
\date 6/11/2018
\version 1.0
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include "funcionespractica5.hpp"

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

      std::cout<< "[1] Algoritmo de obtencion del cambio"<<std::endl;
      realizarAlgoritmoCambio();
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
