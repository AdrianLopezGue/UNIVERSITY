#include "funcionespractica5.hpp"

void rellenarTabla(std::vector < std::vector <int> > &c, int numeroMonedas, int dinero){
  c.resize(numeroMonedas);
  for(int i=0 ; i<numeroMonedas ; i++){
    c[i].resize(dinero+1);
  }

  for(int i=0 ; i<numeroMonedas ; i++){
    for(int j=0 ; j<(dinero+1) ; j++){
      c[i][j]=0;
    }
  }
}

int min(int a, int b){
  if(a<b){
    return a;
  }
  else{
    return b;
  }
}

std::vector<int> AlgoritmoCambio(SistemaMonetario sistema, int N){

  std::vector < std::vector <int> > c;
  std::vector<int> solucion;

  int maxInt = 214748364;

  rellenarTabla(c, sistema.getSizeMonedas(), N);
  solucion.resize(sistema.getSizeMonedas());

  for(unsigned int i=0 ; i < sistema.getSizeMonedas() ; i++){
    for(int j=1 ; j < N+1 ; j++){
      if(i==0 && j < sistema.getValorMoneda(i)){
        c[i][j] = maxInt;
      }else{
        if(i==0){
          c[i][j] = 1 + c[i][j-sistema.getValorMoneda(0)];
        }else{
          if(j<sistema.getValorMoneda(i)){
            c[i][j] = c[i-1][j];
          }else{
            c[i][j] = min(c[i-1][j], 1 + c[i][j-sistema.getValorMoneda(i)]);
          }
        }
      }
    }
  }

  int cant = N;

  if(c[sistema.getSizeMonedas()-1][N]<maxInt){

    int i = sistema.getSizeMonedas() -1;
    int j = N;

    while(cant!=0){
      if(i==0){
        solucion[i]++;
        cant=cant-sistema.getValorMoneda(i);
      }else if(c[i][j] == c[i-1][j]){
        i--;
      }else{
        solucion[i]++;
        cant=cant-sistema.getValorMoneda(i);
        j=j-sistema.getValorMoneda(i);
      }
    }

  }else{
    std::cout << "ERROR: No se puede dar cambio para las monedas introducidas" << endl;
  }

  return solucion;
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
