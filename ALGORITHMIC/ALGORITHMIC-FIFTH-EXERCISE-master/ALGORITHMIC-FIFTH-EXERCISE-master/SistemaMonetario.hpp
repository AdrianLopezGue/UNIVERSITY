#ifndef _SISTEMAMONETARIO_HPP_
#define _SISTEMAMONETARIO_HPP_

#include <fstream>
#include <string>
#include <vector>

#include "Moneda.hpp"
#include "macros.hpp"

class SistemaMonetario{

private:

	std::vector< Moneda > _monedas;

public:

	SistemaMonetario(){
		_monedas.resize(0);
	}

	Moneda getMoneda(int index){
		return _monedas[index];
	}

	void setMoneda(int index, Moneda moneda){
		_monedas[index] = moneda;
	}

	int getValorMoneda(int index){
		return getMoneda(index).getValor();
	}

	int getTipoMoneda(int index){
		return getMoneda(index).getTipo();
	}

	unsigned int getSizeMonedas(){
		return _monedas.size();
	}

	void insertarMoneda(Moneda moneda){
		_monedas.push_back(moneda);
	}

	void ordenarMonedas();
	bool leerFichero(string nombreFichero);

};


#endif
