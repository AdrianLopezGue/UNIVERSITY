#include "funcionespractica3.hpp"

int calcularKMenores(int iz, int de, int k, Conjunto & v){
  int i,j,x,aux;

  i=iz;
  j=de;
  x=v.accederElementoConjunto((iz+de)/2);

  do{
    while(v.accederElementoConjunto(i) < x){
      i++;
    }
    while(v.accederElementoConjunto(j) > x){
      j--;
    }
    if(i<=j){
      aux=v.accederElementoConjunto(i);
      v.setValor(i,v.accederElementoConjunto(j));
      v.setValor(j,aux);
      i++;
      j--;
    }
  }while(i<=j);

  if(k==i){

    int posicion = 10;

    PLACE(posicion,27);
    std::cout<<BIYELLOW<<"___________________________________________"<<RESET<<"\n";

    posicion++;

    PLACE(posicion,26);
    std::cout<<BIYELLOW<<"|"<<RESET;
    PLACE(posicion,70);
    std::cout<<BIYELLOW<<"|"<<RESET<<"\n";


    posicion++;

    PLACE(posicion,26);
    std::cout<<BIYELLOW<<"|"<<RESET;
    PLACE(posicion,44);
    std::cout << IBLUE << "K-MENORES "<<RESET;
    PLACE(posicion,70);
    std::cout << BIYELLOW<<"|\n"<<RESET;

    posicion++;

    PLACE(posicion,26);
    std::cout<<BIYELLOW<<"|"<<RESET;

    PLACE(posicion,35);

    int carry = 0;

    for(int f=0;f<k;f++){

      std::cout << IGREEN << v.accederElementoConjunto(f) << "," ;
      carry++;

      if(carry == 5){
        PLACE(posicion,70);
        std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

        posicion++;

        PLACE(posicion,26);
        std::cout<<BIYELLOW<<"|"<<RESET;

        PLACE(posicion,35);

        carry = 0;
      }
    }

    PLACE(posicion,70);
    std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

    posicion++;

    PLACE(posicion,26);
    std::cout<<BIYELLOW<<"|___________________________________________|\n"<<RESET;

    posicion = 24;

    PLACE(posicion,0);
    std::cout<<"Pulse ";
    std::cout<<BIGREEN<<"ENTER"<<RESET;
    std::cout<<" para ";
    std::cout<<INVERSE;
    std::cout<<"seguir";
    std::cout<<RESET;

    std::cin.ignore();
    std::cin.ignore();

    return 0;
  }
  else{
    if(k < i){

      return 1+calcularKMenores(iz,j,k,v);
    }else{

      return 1+calcularKMenores(i,de,k,v);
    }
  }

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
  std::cout<< "[1] Obtener k-menores";

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

void realizarKMenores(){
  int kmenores;
  int tamanioConjunto,mostrar;

  int posicion = 4;

  PLACE(posicion,27);
  std::cout<<BIYELLOW<<"___________________________________________"<<RESET<<"\n";

  posicion++;

  PLACE(posicion,26);
  std::cout<<BIYELLOW<<"|"<<RESET;
  PLACE(posicion,70);
  std::cout<<BIYELLOW<<"|"<<RESET<<"\n";


  posicion++;

  PLACE(posicion,26);
  std::cout<<BIYELLOW<<"|"<<RESET;
  PLACE(posicion,35);
  std::cout << IBLUE << "ELEMENTOS DEL CONJUNTO: "<<RESET;
  PLACE(posicion,70);
  std::cout << BIYELLOW<<"|\n"<<RESET;

  posicion++;

  PLACE(posicion,26);
  std::cout<<BIYELLOW<<"|"<<RESET;
  PLACE(posicion,70);
  std::cout<<BIYELLOW<<"|"<<RESET<<"\n";


  posicion++;

  PLACE(posicion,26);
  std::cout<<BIYELLOW<<"|"<<RESET;
  PLACE(posicion,28);
  std::cout << IBLUE << "¿CUANTOS K-MENORES DESEA CALCULAR?: "<<RESET;
  PLACE(posicion,70);
  std::cout << BIYELLOW<<"|\n"<<RESET;

  posicion++;

  PLACE(posicion,26);
  std::cout<<BIYELLOW<<"|___________________________________________|\n"<<RESET;

  std::cout << PLACE(posicion-3, 59) << "\b";
  std::cout << " \b";
  std::cin >> tamanioConjunto;
  std::cout << PLACE(posicion-1, 64) << "\b";
  std::cout << " \b";
  std::cin >> kmenores;

  if(tamanioConjunto <=0 || kmenores <= 0){
    posicion++;

    PLACE(posicion,27);
    std::cout<<BIYELLOW<<"___________________________________________"<<RESET<<"\n";

    posicion++;

    PLACE(posicion,26);
    std::cout<<BIYELLOW<<"|"<<RESET;
    PLACE(posicion,70);
    std::cout << BIYELLOW<<"|\n"<<RESET;

    posicion++;

    PLACE(posicion,26);
    std::cout<<BIYELLOW<<"|"<<RESET;
    PLACE(posicion,42);
    std::cout << IRED << "NO SE PERMITEN"<<RESET;
    PLACE(posicion,70);
    std::cout << BIYELLOW<<"|\n"<<RESET;

    posicion++;

    PLACE(posicion,26);
    std::cout<<BIYELLOW<<"|"<<RESET;
    PLACE(posicion,40);
    std::cout << IRED << "NUMEROS NEGATIVOS"<<RESET;
    PLACE(posicion,70);
    std::cout << BIYELLOW<<"|\n"<<RESET;

    posicion++;

    PLACE(posicion,26);
    std::cout<<BIYELLOW<<"|___________________________________________|\n"<<RESET;

    std::cin.ignore();

  }else{
    Conjunto conjunto(tamanioConjunto);

    if(kmenores < tamanioConjunto){

      int llamadas = calcularKMenores(0, (conjunto.tamConjunto()-1), kmenores, conjunto);

      std::cout << CLEAR_SCREEN;

      posicion = 4;

      PLACE(posicion,27);
      std::cout<<BIYELLOW<<"___________________________________________"<<RESET<<"\n";

      posicion++;

      PLACE(posicion,26);
      std::cout<<BIYELLOW<<"|"<<RESET;
      PLACE(posicion,70);
      std::cout << BIYELLOW<<"|\n"<<RESET;

      posicion++;

      PLACE(posicion,26);
      std::cout<<BIYELLOW<<"|"<<RESET;
      PLACE(posicion,33);
      std::cout << IGREEN << "NUMERO DE LLAMADAS REALIZADAS: "<<RESET;
      std::cout << IBLUE << llamadas<<RESET;
      PLACE(posicion,70);
      std::cout << BIYELLOW<<"|\n"<<RESET;

      posicion++;

      PLACE(posicion,26);
      std::cout<<BIYELLOW<<"|"<<RESET;
      PLACE(posicion,31);
      std::cout << IBLUE << "¿MOSTRAR EL VECTOR? SI(0) NO(1): "<<RESET;
      PLACE(posicion,70);
      std::cout << BIYELLOW<<"|\n"<<RESET;

      posicion++;

      PLACE(posicion,26);
      std::cout<<BIYELLOW<<"|___________________________________________|\n"<<RESET;

      std::cout << PLACE(posicion-1, 64) << "\b";
      std::cout << " \b";
      std::cin >> mostrar;

      posicion++;

      int carry = 0;

      if(mostrar==0){

        PLACE(posicion,27);
        std::cout<<BIYELLOW<<"___________________________________________"<<RESET<<"\n";

        posicion++;

        PLACE(posicion,26);
        std::cout<<BIYELLOW<<"|"<<RESET;

        PLACE(posicion,70);
        std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

        posicion++;

        PLACE(posicion,26);
        std::cout<<BIYELLOW<<"|"<<RESET;

        PLACE(posicion,35);

        for(int i=0; i < (int)conjunto.tamConjunto() ; i++ ){
          if(i < kmenores){

            std::cout << IRED <<conjunto.accederElementoConjunto(i) << "," ;
            carry++;

            if(carry == 5 || ((i == kmenores-1) && carry!=5) ){
              PLACE(posicion,70);
              std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

              posicion++;

              PLACE(posicion,26);
              std::cout<<BIYELLOW<<"|"<<RESET;

              if((i < kmenores) &&  (i != kmenores-1)){
                PLACE(posicion,35);
              }
              else if(carry!=5){
                PLACE(posicion,28);
              }

              carry = 0;
            }
          }
          else{

            std::cout << IBLUE <<conjunto.accederElementoConjunto(i) << "," ;
            carry++;

            if(carry == 8){
              PLACE(posicion,70);
              std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

              posicion++;

              PLACE(posicion,26);
              std::cout<<BIYELLOW<<"|"<<RESET;

              PLACE(posicion,28);

              carry = 0;
            }
          }
        }

        PLACE(posicion,70);
        std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

        posicion++;

        PLACE(posicion,26);
        std::cout<<BIYELLOW<<"|___________________________________________|\n"<<RESET;

        std::cin.ignore();
      }
      else{
        std::cin.ignore();
      }
    }else{
      posicion++;

      PLACE(posicion,27);
      std::cout<<BIYELLOW<<"___________________________________________"<<RESET<<"\n";

      posicion++;

      PLACE(posicion,26);
      std::cout<<BIYELLOW<<"|"<<RESET;
      PLACE(posicion,70);
      std::cout << BIYELLOW<<"|\n"<<RESET;

      posicion++;

      PLACE(posicion,26);
      std::cout<<BIYELLOW<<"|"<<RESET;
      PLACE(posicion,33);
      std::cout << IRED << "NUMERO DE K-MENORES MAYOR"<<RESET;
      PLACE(posicion,70);
      std::cout << BIYELLOW<<"|\n"<<RESET;

      posicion++;

      PLACE(posicion,26);
      std::cout<<BIYELLOW<<"|"<<RESET;
      PLACE(posicion,36);
      std::cout << IRED << "QUE TAMANIO DEL VECTOR"<<RESET;
      PLACE(posicion,70);
      std::cout << BIYELLOW<<"|\n"<<RESET;

      posicion++;

      PLACE(posicion,26);
      std::cout<<BIYELLOW<<"|___________________________________________|\n"<<RESET;

      std::cin.ignore();
    }
  }
}
