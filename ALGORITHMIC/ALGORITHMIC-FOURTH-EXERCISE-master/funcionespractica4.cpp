#include "funcionespractica4.hpp"

std::vector <int> AlgoritmoCambio(SistemaMonetario sistema, int dinero){

  std::vector <int> solucion;
  int i=0;

  solucion.resize(sistema.getSizeMonedas());

  for(unsigned int j=0;j<solucion.size();j++){
    solucion[j]=0;
  }

  while(dinero!=0){

    if(dinero>=sistema.getValorMoneda(i)){
      solucion[i] = dinero/sistema.getValorMoneda(i);
      dinero = dinero % sistema.getValorMoneda(i);
      i++;
    }
    else{
      i++;
    }
  }

  return solucion;
}

int AlgoritmoMochila(SistemaMateriales sistema, int V, std::vector<int> & D){

  int resto = V;
  D.resize(sistema.getSizeMateriales());

  int precioMaximo;
  int materialMaximo;
  bool materialDisponible;

  for (unsigned int i = 0; i < sistema.getSizeMateriales(); i++){
    D[i] = 0;
  }

  do{

    precioMaximo = 0;
    materialMaximo = 0;
    materialDisponible = false;

    for (unsigned int i = 0; i < sistema.getSizeMateriales(); i++){
      if (D[i] == 0){
        materialDisponible = true;

        if (sistema.getMaterial(i).getPrecio() > precioMaximo){
          precioMaximo = sistema.getMaterial(i).getPrecio();
          materialMaximo = i;
        }
      }
    }

    if (materialDisponible == true){
      if ( resto >= sistema.getMaterial(materialMaximo).getVolumen() ){
        D[materialMaximo] = -1;
        resto -= sistema.getMaterial(materialMaximo).getVolumen();
      }
      else{
        D[materialMaximo] = resto;
        resto = 0;
      }
    }
  }while( resto != 0 && materialDisponible == true );

  return resto;
}

int menu()
{
  int opcion;
  int posicion;

  // Se muestran las opciones del menú
  posicion=2;

  // Se borra la pantalla
  std::cout << CLEAR_SCREEN;

  PLACE(1,10);
  std::cout << BIBLUE;
  std::cout << "Programa principal | Opciones del menú";
  std::cout << RESET;

  //////////////////////////////////////////////////////////////////////////////
  posicion++;

  PLACE(posicion++,10);
  std::cout<< "[1] Algoritmo de obtencion del cambio";

  posicion++;

  PLACE(posicion++,10);
  std::cout<< "[2] Algoritmo de la mochila";

  posicion++;

  PLACE(posicion++,10);
  std::cout << BIRED << "[0] Salir";

  //////////////////////////////////////////////////////////////////////////////
  posicion++;

  PLACE(posicion++,10);
  std::cout << BIGREEN;
  std::cout << "Opción: ";
  std::cout << RESET;

  // Se lee el número de opción
  std::cin >> opcion;

  // Se elimina el salto de línea del flujo de entrada
  std::cin.ignore();

  return opcion;
}



void realizarAlgoritmoCambio(){

  SistemaMonetario sistema;
  string nombreFichero;

  bool resultadoLectura;

  resultadoLectura = sistema.leerFichero("SistemaMonetarioEuropeo.txt");

  if(resultadoLectura == false){
    std::cout<<"\nNOMBRE FICHERO INTRODUCIDO INCORRECTO.\n";

    exit(-1);
 }

  sistema.ordenarMonedas();

  int dineroInt;

  std::cout << "INTRODUCIR DINERO EN CENTIMOS: ";
  std::cin >> dineroInt;

  while(dineroInt <= 0){
    std::cout<<"DINERO EN CENTIMOS NEGATIVO, VUELVA A INTRODUCIR CENTIMOS:";
    std::cin >> dineroInt;
  }

  std::vector<int> cambio;

  cambio = AlgoritmoCambio(sistema, dineroInt);

  std::cout << std::endl;


  for(unsigned int i=0;i<cambio.size();i++){
    if(cambio[i]!=0){
      if(sistema.getTipoMoneda(i) == 1){
        if(cambio[i]>1){
          std::cout << cambio[i] << " billetes de " << sistema.getValorMoneda(i)/100 << " euros" << std::endl;
        }else{
          std::cout << cambio[i] << " billete de " << sistema.getValorMoneda(i)/100 << " euros" << std::endl;
        }

      }else{
        if(cambio[i]!=1){
          if(sistema.getValorMoneda(i)>= 100){
            std::cout << cambio[i] << " monedas de " << sistema.getValorMoneda(i) << " euros" << std::endl;
          }
          else{
            std::cout << cambio[i] << " monedas de " << sistema.getValorMoneda(i) << " centimos" << std::endl;
          }
        }
        else{
          if(sistema.getValorMoneda(i)>= 100){
            std::cout << cambio[i] << " moneda de " << sistema.getValorMoneda(i)/100 << " euros" << std::endl;
          }
          else{
            std::cout << cambio[i] << " moneda de " << sistema.getValorMoneda(i) << " centimos" << std::endl;
          }


        }
      }
    }
  }

  std::cout << std::endl << std::endl;

  std::cin.ignore();
}




void realizarAlgoritmoMochila(){

  SistemaMateriales sistema;
  string nombreFichero;

  bool resultadoLectura;

  resultadoLectura = sistema.leerFichero("Materiales.txt");

  if(resultadoLectura == false){
    std::cout<<"\nNOMBRE FICHERO INTRODUCIDO INCORRECTO.\n";

    exit(-1);
 }

  int volumenMochila;

  std::cout << "VOLUMEN DE LA MOCHILA: ";
  std::cin >> volumenMochila;

  while(volumenMochila <= 0){
    std::cout<<"VOLUMEN NEGATIVO, VUELVA A INTRODUCIR VOLUMEN:";
    std::cin >> volumenMochila;
  }

  std::vector<int> D;


  int resto = AlgoritmoMochila(sistema, volumenMochila, D);

  std::cout << std::endl;

  if (resto !=0){

    std::cout << "MOCHILA INCOMPLETA. VOLUMEN RESTANTE: " << resto << "\n\n";

    std::cout << "---------MATERIALES---------\n";
    for (unsigned int i = 0; i < D.size(); i++)
    {
      if(D[i] == -1){
        std::cout << "TIPO " << sistema.getMaterial(i).getEtiqueta() << " USADO COMPLETAMENTE.\n";
      }

      if(D[i] > 0){
        std::cout << "TIPO " << sistema.getMaterial(i).getEtiqueta() << " NO COMPLETADO. USADO: " << D[i] << "\n";
      }
    }
    std::cout << "\n\n";
  }

  else{

    std::cout << "MOCHILA COMPLETA\n\n";

    std::cout << "---------MATERIALES---------\n";
    for (unsigned int i = 0; i < D.size(); i++)
    {
      if(D[i] == -1)
      std::cout << "TIPO " << sistema.getMaterial(i).getEtiqueta() << " USADO COMPLETAMENTE.\n";

      if(D[i] > 0)
      std::cout << "TIPO " << sistema.getMaterial(i).getEtiqueta() << " NO COMPLETADO. USADO: " << D[i] << "\n";

    }
    std::cout << "\n";
  }

  std::cout << "\n\n";

  std::cin.ignore();
}
