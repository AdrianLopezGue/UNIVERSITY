/*!
\file funcionesAuxiliares.hpp
\brief Fichero de funciones auxiliares
\author Adrian Lopez Guerrero
\date 1/10/2018
\version 1.0
*/

#ifndef _FUNCIONESPRACTICA1_HPP_
#define _FUNCIONESPRACTICA1_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdint.h> // Para usar uint64_t
#include <math.h>
#include <algorithm>

/** @struct Data
 *  @brief Esta estructura guarda el valor minimo, maximo, el incremento y el numero de veces que hay que hacer el algoritmo para cada valor de n
 */

 struct Data{
  double min_n;
  double max_n;
  double num_repeticiones;
  double incremento;
};

/*!
\brief     Funcion que permite rellenar el vector con valores entre 0 y 9999
\param     v: vector pasado por referencia a rellenar
*/

 void rellenarVector(std::vector<int> &v);

/*!
\brief     Funcion que comprueba que el vector esta ordenado correctamente.
\param     v: vector a comprobar
\return	   true: si esta ordenado
\return	   false: si no esta ordenado
*/

 bool estaOrdenado(const std::vector<int> v);

/*!
\brief Funcion que pide los valores
\return	   Data: objeto de la clase Data que guarda los valores necesarios para el funcionamiento del programa.
*/

 Data pedirValoresDatos();

/*!
\brief Funcion que permite escribir el fichero necesario para utilizar gnuplot.
\param nombreFichero: string con el nombre del fichero a crear.
\param  n: vector que guarda los valores de tamaño del vector que se ha ordenado mediante los metodos Sofisticado o no Sofisticado.
\param tiempos: vector que guarda los tiempos que ha guardado tras utilizar el objeto de la clase Clock
\param tiemposEstimados: vector que guarda los tiempos normalizados mediante minimos cuadrados.
*/
 void escribirFichero(std::string nombreFichero, std::vector<double> n, std::vector<double> tiempos, std::vector<double> tiemposEstimados);


 void calcularMatrizA(std::vector< std::vector<double> >  &A, std::vector<double> n, int ordenPolinomio);
 void calcularMatrizB(std::vector< std::vector<double> >  &B, std::vector<double> n, std::vector<double> tiempos, int ordenPolinomio);

 void calcularVectorTiemposEstimados(std::vector<double> &tiemposMinimosCuadrados, std::vector<double> n, std::vector< std::vector<double> >  &X);
/*!
\brief Funcion que permite calcular la varianza del vector pasado como argumento
\param v: vector de enteros al que se le va a calcular la varianza
*/
 double calcularVarianza(std::vector<double> v);
 double calcularMedia(std::vector<double> v);

#endif
