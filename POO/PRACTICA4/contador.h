#ifndef _CONTADOR_H_
#define _CONTADOR_H_

#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;


class Contador
{

private:

int contador_;
int minimo_;
int maximo_;
int inicial_;
list <int> estadoscontador_;


public:

	Contador(int minimo = 0, int maximo = 1000, int inicial = 0);


	// Funciones operador. Podran ser nombradas en el codigo de esta forma (por ejemplo): Contador c; c++
	// En funcion de en que posicion escribamos el operador (++c, c++, --c...) dentro de nuestro codigo, utilizaremos una funcion u otra.


	void operator=( int contador){if(contador > maximo_) contador = maximo_; if(contador<minimo_)contador=minimo_; contador_=contador; estadoscontador_.push_back(contador);}
	void operator=(const Contador &aux){contador_ = aux.contador_; maximo_ = aux.maximo_; minimo_ = aux.minimo_; estadoscontador_.push_back(contador_);}

	Contador operator++(void); // Prefijo: ++c
	Contador operator++(int);  // Postfijo: c++

	Contador operator--(void); // Prefijo: --c
	Contador operator--(int);  // Postfijo: c--

	friend Contador operator+(int x, Contador aux); // Para 5+c
	friend Contador operator+(Contador aux, int x);	// Para c+5


	friend Contador operator-(int x, Contador aux);	// Para 5-c
	friend Contador operator-(Contador aux, int x);	// Para c-5


	bool undo(int N = 1);
	int get(){return contador_;};




};


#endif
