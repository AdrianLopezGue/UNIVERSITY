/*!
\file principalmenu.cpp
\brief Menu del programa.
\author Adrian Lopez Guerrero
\date 26/4/2018
\version 1.0
*/

#include <iostream>
#include <string>

#include "funcionesAuxiliares.hpp"

/*!
\brief   Programa principal de la práctica 4: vertices, grafos y lados
\return  int
*/
int main(int argc, char const *argv[]) {

  ed::Grafo GrafoPrincipal;
  ed::Grafo GrafoAbarcadorMinimo;

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
      std::cout<< "[1] Cargar grafo de fichero"<<std::endl;
      ed::cargarVerticesFichero(GrafoPrincipal);
      break;

      case 2:
      std::cout<< "[2] Grabar grafo en un fichero" <<std::endl;
      ed::grabarVerticesFichero(GrafoPrincipal);
      break;

      case 3:
      std::cout << "[3] Realizar prim" << std::endl;
      GrafoAbarcadorMinimo = ed::AlgoritmoPrim(GrafoPrincipal);
      break;

      case 4:
      std::cout << "[4] Realizar kruskal" << std::endl;
      GrafoAbarcadorMinimo = ed::AlgoritmoKruskal(GrafoPrincipal);
      break;

      case 5:
      std::cout << "[5] Mostrar grafo principal" << std::endl;
      ed::imprimirMatrizGrafoPrincipal(GrafoPrincipal);
      break;

      case 6:
      std::cout << "[6] Mostrar arbol abarcador de coste minimo" << std::endl;
      ed::imprimirMatrizArbol(GrafoAbarcadorMinimo);
      break;

      case 7:
      std::cout << "[7] Mostrar vertices grafo principal" << std::endl;
      ed::mostrarVertices(GrafoPrincipal);
      break;


      case 8:
      std::cout << "[8] Mostrar vertices grafo abarcador de coste minimo" << std::endl;
      ed::mostrarVertices(GrafoAbarcadorMinimo);
      break;

      case 9:
      std::cout << "[9] Mostrar lados grafo principal" << std::endl;
      ed::mostrarLados(GrafoPrincipal);
      break;

      case 10:
      std::cout << "[10] Mostrar lados grafo abarcador de coste minimo" << std::endl;
      ed::mostrarLados(GrafoAbarcadorMinimo);
      break;

      case 11:
      std::cout << "[11] Añadir vertice" << std::endl;
      ed::anadirVertice(GrafoPrincipal);
      break;

      case 12:
      std::cout << "[12] Borrar todos los vertices" << std::endl;
      ed::borrarVertices(GrafoPrincipal);
      break;

      case 13:
      std::cout << "[13] Longitud total del arbol abarcador de coste minimo" << std::endl;
      ed::longitudArbolAbarcador(GrafoAbarcadorMinimo);
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
