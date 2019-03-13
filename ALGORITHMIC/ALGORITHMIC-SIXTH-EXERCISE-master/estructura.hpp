#ifndef _ESTRUCTURA_HPP_
#define _ESTRUCTURA_HPP_

#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>

class Estructura{
	private:
		int _n;
		std::vector < std::vector <int> > _estructura;

	public:
		Estructura(int n){
			setN(n);
		}

		int getN(){
			return _n;
		}

		void setN(int n){
			_n=n;
		}

		int getElementoEstructura(int i, int j){
			return _estructura[i][j];
		}

		void insertarEstructura(std::vector <int> v){
			_estructura.push_back(v);
		}

		unsigned int getSizeEstructura(){
			return _estructura.size();
		}

		void mostrarSolucion(){
			for(unsigned int i=0 ; i < getSizeEstructura(); i++){
				  std::cout<<"[";
					for(int j=0; j < getN(); j++){
						if(j == getN()-1){
							std::cout << getElementoEstructura(i, j);
						}
						else{
							std::cout << getElementoEstructura(i, j)  << ", ";
						}
					}
					std::cout<<"]"<< std::endl;
			}

		}

};

#endif
