#ifndef _CONJUNTO_HPP_
#define _CONJUNTO_HPP_

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

class Conjunto {

	private:
		std::vector<int> _conjunto;

	public:

		Conjunto(){
			_conjunto.resize(0);
		}

		Conjunto(int size){
			_conjunto.resize(size);
			rellenarVector();
		}

		unsigned int tamConjunto(){
      return _conjunto.size();
    }

		void rellenarVector();
    void insertarElementoConjunto(int valor);
    void borrarElementoConjunto(int index);
  	int accederElementoConjunto(int index);

		std::vector <int> devolverConjunto() {return _conjunto;}

		void setValor(int index, int valor){
			_conjunto[index]=valor;
		}
};

#endif
