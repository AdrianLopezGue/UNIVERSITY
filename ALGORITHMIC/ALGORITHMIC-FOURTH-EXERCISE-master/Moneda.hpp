#ifndef _MONEDA_HPP_
#define _MONEDA_HPP_

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "macros.hpp"

using namespace std;

class Moneda{

	private:
		int _valor;
		int _tipo;			// tipo = 0 ---> MONEDA
										// tipo = 1 ---> BILLETE

	public:

		Moneda(){
			_valor = 0;
			_tipo = 0;
		}

		void setValor(int valor){
			_valor = valor;
		}

		void setTipo(int tipo){
			_tipo = tipo;
		}

		int getValor(){
			return _valor;
		}

		int getTipo(){
			return _tipo;
		}

};



#endif
