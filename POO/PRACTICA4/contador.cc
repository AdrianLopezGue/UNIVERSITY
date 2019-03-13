#include "contador.h"


using namespace std;

Contador::Contador(int minimo, int maximo, int inicial){

	if(minimo>maximo){
		inicial = 0;
		minimo = 0;
		maximo = 1000;

	}

	if(inicial > maximo || inicial < minimo){
		inicial = 0;
	}

	inicial_ = inicial;
	minimo_= minimo;
	maximo_ = maximo;
	contador_ = inicial;


}

// Prefijo: ++c

Contador Contador::operator++(void){

	contador_++;

	if(contador_ >= maximo_){

		contador_ = maximo_;

	}



	estadoscontador_.push_back(contador_);

	return *this;

}

// Postfijo: c++

Contador Contador::operator++(int){

	Contador temp (*this);
	contador_++;

	if(contador_ >= maximo_){

		contador_ = maximo_;

	}



	estadoscontador_.push_back(contador_);
	return temp;

}

Contador Contador::operator--(void){

	contador_--;

	if(contador_ <= minimo_){
		contador_ = minimo_;

	}



	estadoscontador_.push_back(contador_);
	return *this;

}


Contador Contador::operator--(int){

	Contador temp (*this);
	contador_--;

	if(contador_ <= minimo_){
		contador_ = minimo_;

	}




	estadoscontador_.push_back(contador_);
	return temp;

}

	Contador operator+(int x, Contador aux){

		if(x + aux.contador_ > aux.maximo_){
			aux.contador_ = aux.maximo_;
		}
		else{
			aux.contador_ = x + aux.contador_;
		}

		aux.estadoscontador_.push_back(aux.contador_);

		return aux;

	}

	Contador operator+(Contador aux, int x){

		if(aux.contador_ + x > aux.maximo_){
			aux.contador_ = aux.maximo_;
		}
		else{
			aux.contador_ = aux.contador_ + x;
		}

		aux.estadoscontador_.push_back(aux.contador_);

		return aux;
	}


	Contador operator-(int x, Contador aux){

		if(x - aux.contador_  < aux.minimo_){
			aux.contador_ = aux.minimo_;
		}
		else{
			aux.contador_ = x - aux.contador_ ;
		}

		aux.estadoscontador_.push_back(aux.contador_);

		return aux;

	}
	Contador operator-(Contador aux, int x){

		if(aux.contador_ - x < aux.minimo_){
			aux.contador_ = aux.minimo_;
		}
		else{
			aux.contador_ = aux.contador_ - x;
		}

		aux.estadoscontador_.push_back(aux.contador_);

		return aux;
	}



bool Contador:: undo(int N){

	int size = estadoscontador_.size();
	if((size < N) || (size <= 0)){
		return false;
	}

	for(int i = 0; i<N; i++){
		estadoscontador_.pop_back();
	}

	contador_ = estadoscontador_.back();

	return true;
}
