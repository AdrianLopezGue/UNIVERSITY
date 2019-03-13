/*!
\file principalmenu.cpp
\brief Menu del segundo programa.
\author Adrian Lopez Guerrero
\date 18/4/2017
\version 1.0
*/

#include <iostream>
#include <string>

#include "funcionesAuxiliaresMenu.hpp"

#include "MonticuloMediciones.hpp"
#include "Medicion.hpp"

#include "macros.hpp"


/*!
\brief   Programa principal de la práctica 1: provincia y municipios
\return  int
*/
int main(int argc, char *argv[]){

  if (argc != 3)
  {
    std::cout << "Modo de ejecución" << std::endl;
    std::cout << argv[0] << " <fichero-de-mediciones>  <fichero-ordenado> "  << std::endl;

    return -1;
  }

  ed::MonticuloMediciones monticulo;

  std::string nombreFicheroEntrada(argv[1]);
  std::string nombreFicheroSalida(argv[2]);

  int opcion;

  do{
    // Se elige la opción del menún
    opcion = ed::menu();

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
      std::cout<< "[1] Mostrar informacion acerca del monticulo"<<std::endl;
      ed::mostrarInformacionMonticulo(monticulo);
      break;

      case 2:
      std::cout << "[2] Comprobar si el monticulo tiene mediciones" << std::endl;
      ed::comprobarMonticuloVacio(monticulo);
      break;

      //////////////////////////////////////////////////////////////////////////////
      case 3:
      std::cout << "[3] Cargar monticulo desde un fichero" << std::endl;
      ed::cargarMonticulo(monticulo, nombreFicheroEntrada);
      break;

      case 4:
      std::cout << "[4] Grabar el monticulo en un fichero" << std::endl;
      ed::grabarMonticulo(monticulo, nombreFicheroSalida);
      break;

      //////////////////////////////////////////////////////////////////////////////

      case 5:
      std::cout << "[5] Mostrar mediciones del monticulo: " << std::endl;
      ed::mostrarMedicionesdeMonticulo(monticulo);
      break;


      //////////////////////////////////////////////////////////////////////////////

      case 6:
      std::cout << "[6] Borrar todas las mediciones del monticulo" << std::endl;
      ed::borrarTodosLasMedicionesdeMonticulo(monticulo);
      break;

      //////////////////////////////////////////////////////////////////////////////
      case 7:
      std::cout << "[7] Consultar una medicion" << std::endl;
      ed::consultarMedicionenMonticulo(monticulo);
      break;

      case 8:
      std::cout << "[8] Insertar una medicion" << std::endl;
      ed::insertarMedicionenMonticulo(monticulo);
      break;

      case 9:
      std::cout << "[9] Borrar una medicion" << std::endl;
      ed::borrarMediciondeMonticulo(monticulo);
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
