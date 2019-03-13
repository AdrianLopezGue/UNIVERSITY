#include "funcionespractica1.hpp"
#include "macros.hpp"
#include "ClaseTiempo.hpp"
#include "sistemaEcuaciones.hpp"

void rellenarVector(std::vector<int> &v){
	for(unsigned int i = 0; i<v.size(); i++){
		v[i] = rand() % 9999;
	}
}

bool estaOrdenado(const std::vector<int> v){
	return std::is_sorted(v.begin(), v.end());
}

Data pedirValoresDatos(){

	Data data;

	std::cout<<"N minima: ";
	std::cin>>data.min_n;

	while(data.min_n<=0){
		std::cout<<"Valor de n incorrecto, vuelva a introducirlo: ";
		std::cin>>data.min_n;
	}

	std::cout<<"N maximo: ";
	std::cin>>data.max_n;

	while((data.max_n<=0) && (data.max_n < data.min_n)){
		std::cout<<"Valor de n incorrecto (menor que el valor minimo o cero), vuelva a introducirlo: ";
		std::cin>>data.max_n;
	}

	std::cout<<"Incremento: ";
	std::cin>>data.incremento;


	while(data.incremento<=0){
		std::cout<<"Valor de incremento menor o igual a cero, vuelva a introducirlo: ";
		std::cin>>data.incremento;
	}

	std::cout<<"Numero de repeticiones: ";
	std::cin>>data.num_repeticiones;

	while(data.num_repeticiones<=0){
		std::cout<<"Valor del numero de repeticiones incorrecto, vuelva a introducirlo: ";
		std::cin>>data.num_repeticiones;
	}

	return data;
}

void escribirFichero(std::string nombreFichero, std::vector<double> n, std::vector<double> tiempos, std::vector<double> tiemposEstimados){
	std::ofstream fichero(nombreFichero);

	if(fichero){

		for(unsigned int i = 0; i < n.size(); i++){
			fichero<<n[i];
			fichero<<" ";
			fichero<<tiempos[i];
			fichero<<" ";
			fichero<<tiemposEstimados[i];
			fichero<<"\n";
		}
	}

	std::cout<<"\nFichero creado con los datos de los tiempos correctamente!\n";
}

double sumatorio(std::vector<double> v1, int e1, std::vector<double> v2, int e2){


	double sumatorio = 0;
	for(unsigned int j = 0; j<v1.size(); j++){
		sumatorio += (pow(v1[j], e1) * pow(v2[j], e2));
	}

	return sumatorio;
}

double sumatorio(std::vector<double> v1, int e1){

	double sumatorio = 0;
	for(unsigned int j = 0; j<v1.size(); j++){
		sumatorio += pow(v1[j], e1);
	}

	return sumatorio;
}

void calcularMatrizA(std::vector< std::vector<double> >  &A, std::vector<double> n, int ordenPolinomio){
	for(int i=0; i<=ordenPolinomio; i++){
		for(int j=0; j<=ordenPolinomio; j++){
			if((i+j) == 0){
				A[i][j] = n.size();
			}
			else{

				A[i][j] = sumatorio(n, i+j);
			}
		}
	}
}

void calcularMatrizB(std::vector< std::vector<double> >  &B, std::vector<double> n, std::vector<double> tiempos, int ordenPolinomio){
	for(int i=0; i<=ordenPolinomio; i++){

		B[i][0] = sumatorio(n, i, tiempos, 1);
	}
}

void calcularVectorTiemposEstimados(std::vector<double> &tiemposMinimosCuadrados, std::vector<double> n, std::vector< std::vector<double> >  &X){
	for(unsigned int i = 0; i<n.size(); i++){
		for(unsigned int j = 0; j<X.size(); j++){
			tiemposMinimosCuadrados[i] += (pow(n[i], j) * X[j][0]);
		}
	}
}

double calcularVarianza(std::vector<double> v){

	double media = 0;
	double valorFinal = 0;

	media = calcularMedia(v);

	for(unsigned int i=0; i<v.size(); i++){
		v[i] -= media;
	}

	valorFinal = sqrt(sumatorio(v, 2)/v.size());
	return valorFinal;
}

double calcularMedia(std::vector<double> v){
	return sumatorio(v, 1)/v.size();
}
