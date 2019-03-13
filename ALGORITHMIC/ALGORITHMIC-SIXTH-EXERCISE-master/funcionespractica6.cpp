#include "funcionespractica6.hpp"

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
  std::cout<< "[1] Obtener solucion n reinas - BACKTRACKING";

  posicion++;

  PLACE(posicion++,10);
  std::cout<< "[2] Obtener solucion n reinas - VEGAS";

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

bool Lugar(int k, std::vector <int> & x){
  for(int i=0; i < k ; i++){
    if(x[i]==x[k] || abs(x[i]-x[k])==abs(i-k)){
      return false;
    }
  }
  return true;
}


void AlgoritmoReinasBacktracking(Estructura & estructura){
  std::vector <int> x;
  int n=estructura.getN();
  int k=0;

  x.resize(n);

  x[0]=0;

  while(k >= 0){
    x[k]=x[k]+1;
    while(x[k]<=n && Lugar(k,x) == false){
      x[k]=x[k]+1;
    }
    if(x[k]<=n){
      if(k==(n-1)){
        estructura.insertarEstructura(x);
      }else{
        k++;
        x[k]=0;
      }
    }else{
      k--;
    }
  }
}

void realizarBacktrackingReinas(){
  int n;

  std::cout << "DIMENSION NXN DEL TABLERO: ";
  std::cin >> n;

  Estructura estructura(n);

  AlgoritmoReinasBacktracking(estructura);

  std::cout<<"NUMERO SOLUCIONES: "<<estructura.getSizeEstructura() <<std::endl<<std::endl;

  estructura.mostrarSolucion();

  std::cout << std::endl << std::endl;
  std::cin.ignore();
}

bool AlgoritmoReinasVegas(Estructura & estructura){

  std::vector <int> x;
  std::vector <int> ok;

  int n=estructura.getN();

  x.resize(n);
  ok.resize(n);

  int contador;
  int columna;

  for(int i=0; i < n ; i++){
    x[i]=0;
  }

  for(int k=0; k<n ; k++){
    contador=0;

    for(int j=0; j<n ; j++){
      x[k]=j;
      if(Lugar(k,x)==true){
        contador++;
        ok[contador] = j;
      }
    }

    if(contador==0){
      return false;
    }

    int randomvalue = rand()%contador +1;

    columna=ok[randomvalue];
    x[k]=columna;
  }


  if(contador==0){
    return false;
  }
  else{
    estructura.insertarEstructura(x);
    return true;
  }
}

void realizarVegasReinas(){
  int n;

  std::cout << "DIMENSION NXN DEL TABLERO: ";
  std::cin >> n;

  Estructura estructura(n);

  int intentos = 1;

  bool resultado = AlgoritmoReinasVegas(estructura);

  while(resultado == false){
    resultado = AlgoritmoReinasVegas(estructura);
    intentos++;
  }

  std::cout<<"INTENTOS: "<<intentos<<std::endl<<std::endl;

  estructura.mostrarSolucion();

  std::cout << std::endl << std::endl;
  std::cin.ignore();

}
