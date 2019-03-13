#include "SistemaMonetario.hpp"

bool SistemaMonetario::leerFichero(string nombreFichero){

	std::ifstream ficheroin(nombreFichero.c_str());

	if(ficheroin){
		Moneda monedaaux;

		int valor;
		int tipo;

		while(ficheroin >> valor >> tipo){

			monedaaux.setValor(valor);
			monedaaux.setTipo(tipo);

			insertarMoneda(monedaaux);
		}

		ficheroin.close();
		return true;
	}
	
	else{
		return false;
	}
}

void SistemaMonetario::ordenarMonedas(){

	Moneda monedaaux;

	for(unsigned int i=0; i< getSizeMonedas(); i++){
		for(unsigned int j=i+1 ; j< getSizeMonedas(); j++){
			if(getValorMoneda(i) < getValorMoneda(j)){
				monedaaux = getMoneda(i);
				setMoneda(i, getMoneda(j));
				setMoneda(j, monedaaux);
			}
		}
	}
}
