/*!
\file funcionesAuxiliares.hpp
\brief Fichero de funciones auxiliares
\author Adrian Lopez Guerrero
\date 1/10/2018
\version 1.0
*/

#ifndef _FUNCIONESAUXILIARES_HPP_
#define _FUNCIONESAUXILIARES_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdint.h> // Para usar uint64_t
#include <math.h>
#include <algorithm>

double calcularCombinatoriaRecursiva(int n, int k);
double calcularCombinatoriaIterativa(int n, int k);
double calcularCombinatoriaRecursivaTabla(const double &n, const double &k,std::vector< std::vector<double> >  &tabla);

void AlgoritmoHanoi(int m, int i, int j, int k);
/*!
\brief     Funcion que permite generar un ambiente interactivo con el usuarios con el que manejar los grafos de manera sencilla
\pre       Ninguna
\post      Ninguna
*/
int menu();

/*!
\brief Funcion que realizara el metodo que le indiquemos con sus correspondientes funciones.
\param tipoMetodo: entero que si es igual a cero, realizara el metodo Sofisticado y si es uno el no Sofisticado
*/
void realizarCombinatoria(int tipoMetodo);
void realizarCalculoMovimientosHanoi();
void mostrarPasosHanoi();

#endif
