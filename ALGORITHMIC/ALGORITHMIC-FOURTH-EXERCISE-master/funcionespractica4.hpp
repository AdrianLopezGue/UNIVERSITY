#ifndef _FUNCIONESPRACTICA4_HPP_
#define _FUNCIONESPRACTICA4_HPP_

#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#include "Moneda.hpp"
#include "SistemaMonetario.hpp"

#include "Material.hpp"
#include "SistemaMateriales.hpp"

#include "macros.hpp"

std::vector <int> AlgoritmoCambio(SistemaMonetario sistema, float dinero);
int AlgoritmoMochila(SistemaMateriales sistema, int V, std::vector<int> & D);

int menu();

void realizarAlgoritmoCambio();
void realizarAlgoritmoMochila();


#endif
