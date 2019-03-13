#ifndef _FUNCIONESPRACTICA6_HPP_
#define _FUNCIONESPRACTICA6_HPP_

#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include "estructura.hpp"
#include "macros.hpp"

int menu();

bool Lugar(int k, std::vector <int> & x);

void AlgoritmoReinasBacktracking(Estructura & estructura);
void realizarBacktrackingReinas();

bool AlgoritmoReinasVegas(Estructura & estructura);
void realizarVegasReinas();

#endif
