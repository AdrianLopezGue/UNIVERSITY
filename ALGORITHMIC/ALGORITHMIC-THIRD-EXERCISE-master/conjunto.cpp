#include "conjunto.hpp"

void Conjunto::rellenarVector(){
  srand(time(NULL));

  for(unsigned int i = 0; i< tamConjunto(); i++){
    _conjunto[i] = rand() %10001 + 1;
  }
}

void Conjunto::insertarElementoConjunto(int valor){
	_conjunto.push_back(valor);
}

void Conjunto::borrarElementoConjunto(int index){

  _conjunto.erase(_conjunto.begin() + index);
}

int Conjunto::accederElementoConjunto(int index){
	if(index < 0 || index >= (int)tamConjunto()){
    std::cout<<"Index incorrecto.\n";

    return -1;
  }

	return _conjunto[index];
}
