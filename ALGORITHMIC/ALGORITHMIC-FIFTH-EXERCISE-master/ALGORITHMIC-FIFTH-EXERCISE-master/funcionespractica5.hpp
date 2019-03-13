#ifndef _FUNCIONESPRACTICA5_HPP_
#define _FUNCIONESPRACTICA5_HPP_

#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#include "Moneda.hpp"
#include "SistemaMonetario.hpp"

#include "macros.hpp"

void rellenarTabla(std::vector < std::vector <int> > &c, int numeroMonedas, int dinero);
int min(int a, int b);

std::vector<int> AlgoritmoCambio(SistemaMonetario sistema, int N);

int menu();

void realizarAlgoritmoCambio();


#endif
