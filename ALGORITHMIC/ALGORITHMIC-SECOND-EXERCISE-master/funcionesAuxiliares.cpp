#include "funcionesAuxiliares.hpp"
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

	std::cout<<"Valor minimo: ";
	std::cin>>data.min_valor;

	while(data.min_valor<=0){
		std::cout<<"Valor minimo incorrecto, vuelva a introducirlo: ";
		std::cin>>data.min_valor;
	}

	std::cout<<"Valor maximo: ";
	std::cin>>data.max_valor;

	while((data.max_valor<=0) && (data.max_valor < data.min_valor)){
		std::cout<<"Valor maximo incorrecto (menor que el valor minimo o cero), vuelva a introducirlo: ";
		std::cin>>data.max_valor;
	}

	std::cout<<"Incremento: ";
	std::cin>>data.incremento;

	while(data.min_valor<=0){
		std::cout<<"Valor de incremento menor o igual a cero, vuelva a introducirlo: ";
		std::cin>>data.incremento;
	}

	std::cout<<"Numero de repeticiones: ";
	std::cin>>data.num_repeticiones;

	while(data.min_valor<=0){
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

void calcularMatrizA(std::vector< std::vector<double> >  &A, std::vector<double> n, int ordenPolinomio){
	for(int i=0; i<=ordenPolinomio; i++){
		for(int j=0; j<=ordenPolinomio; j++){
			if((i+j) == 0){
				A[i][j] = n.size();
			}
			else{
				double aux = 0;

				for(unsigned int z = 0; z<n.size(); z++){
					aux = pow(n[z], i+j);
					A[i][j] += aux;
				}
			}
		}
	}
}

void calcularMatrizB(std::vector< std::vector<double> >  &B, std::vector<double> n, std::vector<double> tiempos, int ordenPolinomio){
	for(int i=0; i<=ordenPolinomio; i++){

		B[i][0] = 0;

		for(unsigned int j = 0; j<tiempos.size(); j++){
			B[i][0] += (pow(n[j], i) * tiempos[j]);
		}
	}
}


void MetodoSacudida(std::vector<int> &v){

	bool swapped;

	do{
		swapped = false;

		for(unsigned int i = 0; i<v.size()-2; i++){
			if(v[i]>v[i+1]){
				swap(v[i], v[i+1]);
				swapped = true;
			}
		}

		if(!swapped){
			break;
		}

		for(unsigned int i = v.size()-2; i>0; i--){
			if(v[i]>v[i+1]){
				swap(v[i], v[i+1]);
				swapped = true;
			}
		}
	} while(swapped);
}

void shiftRight(std::vector<int> &v, int menor, int mayor)
{
	int padre = menor;
	while ((padre*2)+1 <= mayor)
	{
		int hijoIzq = (padre * 2) + 1;
		int hijoDer = hijoIzq + 1;
		int indexMedio = padre;

		if (v[indexMedio] < v[hijoIzq])
		{
			indexMedio = hijoIzq;
		}

		if ((hijoDer <= mayor) && (v[indexMedio] < v[hijoDer]))
		{
			indexMedio = hijoDer;
		}

		if (indexMedio != padre)
		{
			swap(v[padre], v[indexMedio]);

			padre = indexMedio;
		}
		else
		{
			break;
		}
	}
	return;
}

void heapify(std::vector<int>  &v, int menor, int mayor)
{

	int indexMedio = (mayor - menor -1)/2;
	while (indexMedio >= 0)
	{
		shiftRight(v, indexMedio, mayor);
		indexMedio--;
	}
	return;
}

void MetodoOrdenacionMonticulo(std::vector<int> &v){

	// Crea el heap, creando este dentro del mismo vector v, reorganizandolo
	heapify(v, 0, (int)v.size()-1);
	int mayor = v.size() - 1;
	while (mayor > 0)
	{
		// El elemento con el indice mayor pasa a la cabeza y la cabeza a la posicion de ese elemento ,para poder asi formar el vector en orden ascendente
		std::swap(v[mayor], v[0]);
		mayor--;

		// El elemento que estaba en la cabeza se encuentra en una posicion que no le corresponde, por lo que se vuelve a reestructurar
		// el heap para que los elementos esten bien colocados
		// Dependiendo del valor del mayor, el area de reorganizacion ira reduciendose
		shiftRight(v, 0, mayor);
	}
}

double calcularVarianza(std::vector<double> v){

	double media = 0;
	double valorFinal = 0;

	for(unsigned int i=0; i<v.size(); i++){
		media+=v[i];
	}

	media = media/v.size();

	for(unsigned int i=0; i<v.size(); i++){
		valorFinal += pow(v[i]-media, 2);
	}

	valorFinal = sqrt(valorFinal/v.size());

	return valorFinal;
}

int menu()
{
	int opcion;
	int posicion;

	// Se muestran las opciones del menú
	posicion=2;

	// Se borra la pantalla
	std::cout << CLEAR_SCREEN;

	PLACE(1,10);
	std::cout << BIBLUE;
	std::cout << "Programa principal | Opciones del menú";
	std::cout << RESET;

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout<< "[1] Metodo no Sofisticado: Sacudida";

	PLACE(posicion++,10);
	std::cout<< "[2] Metodo Sofisticado: Ordenacion por monticulo";

	posicion++;

	PLACE(posicion++,10);
	std::cout << BIRED << "[0] Salir";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << BIGREEN;
	std::cout << "Opción: ";
	std::cout << RESET;

	// Se lee el número de opción
	std::cin >> opcion;

	// Se elimina el salto de línea del flujo de entrada
	std::cin.ignore();

	return opcion;
}

void realizarMetodo(int tipoMetodo){

	Data data;
	data = pedirValoresDatos();

	int size = data.min_valor;
	int numeroTiempos = ((data.max_valor-data.min_valor)/data.incremento) + 1;

	Clock reloj;																			// reloj que va a medir el tiempo que tarda el metodo en cada iteracion

	std::vector<double> tiempos(numeroTiempos, 0);		// vector que guarda los tiempos medios que tarda para cada n
	std::vector<double> n(numeroTiempos, 0);					// vector que guarda el tamaño de los vectores creados
	std::vector<double> nlogn(numeroTiempos, 0);			// vector que guarda los valores tras calcular n*log(n)

	double contador = 0.0;

	for(int i=0; i<numeroTiempos; i++){

		std::vector<int> v;
		contador = 0.0;

		for(int j=0 ; j<data.num_repeticiones; j++){

			v.resize(size);
			rellenarVector(v);

			// Metodo No Sofisticado
			if(tipoMetodo == 0){
				reloj.start();
				MetodoSacudida(v);
				reloj.stop();
			}
			// Metodo Sofisticado
			else  if(tipoMetodo == 1){
				reloj.start();
				MetodoOrdenacionMonticulo(v);
				reloj.stop();
			}

			if(!estaOrdenado(v)){

				std::cout<<"Error en el algoritmo para tam: "<<size<<"\n";
				exit(-1);
			}

			v.clear();
			contador+=reloj.elapsed();
		}

		tiempos[i] = contador/data.num_repeticiones;		// guardamos el tiempo medio
		n[i] = size;																		// guardamos el tamaño del vector que hemos ordenado previamente
		nlogn[i] = n[i]*log(n[i]);											// guardamos el valor de n*log(n)

		size+=data.incremento;													// aumentamos el tamaño del vector que vamos a ordenar en la siguiente iteracion
	}

	int ordenPolinomio = 0;

	if(tipoMetodo == 0){
		ordenPolinomio = 2;
	}	else if(tipoMetodo == 1){
		ordenPolinomio = 1;
	}


	// Calculamos matrices A y B para poder obtener el valor de la matriz X y asi poder ajustar la curva
	// de manera correcta

	std::vector< std::vector<double> > A(ordenPolinomio+1, std::vector<double> (ordenPolinomio+1));
	std::vector< std::vector<double> > B(ordenPolinomio+1, std::vector<double> (1));
	std::vector< std::vector<double> > X(ordenPolinomio+1, std::vector<double> (1));

	// Metodo No Sofisticado
	if(tipoMetodo == 0){
		calcularMatrizA(A, n, ordenPolinomio);
		calcularMatrizB(B, n, tiempos, ordenPolinomio);

		// Metodo Sofisticado
	}	else if(tipoMetodo == 1){
		calcularMatrizA(A, nlogn, ordenPolinomio);
		calcularMatrizB(B, nlogn, tiempos, ordenPolinomio);
	}

	resolverSistemaEcuaciones(A, B, ordenPolinomio+1, X);

	std::vector<double> tiemposMinimosCuadrados(numeroTiempos, 0);


	// Rellenamos el vector que albergará los valores estimados del tiempo que tardaran los metodos
	// utilizados previamente, para despues compararlos con los que hemos recogido anteriormente en las
	// pruebas

	// Metodo No Sofisticado
	if(tipoMetodo == 0){
		for(int i = 0; i<numeroTiempos; i++){
			for(int j = 0; j<=ordenPolinomio; j++){
				tiemposMinimosCuadrados[i] += (pow(n[i], j) * X[j][0]);			//  tiempoMinimo[i] = a0 + a1*n + a2*n^2
			}
		}

		// Metodo Sofisticado
	}	else if(tipoMetodo == 1){
		for(int i = 0; i<numeroTiempos; i++){
			tiemposMinimosCuadrados[i] = X[0][0] + (X[1][0]*nlogn[i]);		//  tiempoMinimo[i] = a0 + a1*n*log(n)
		}
	}

	std::cout<<"\nFORMULA: ";

	// Metodo No Sofisticado
	if(tipoMetodo == 0){
		std::cout<<X[0][0]<<" + "<<X[1][0]<<"*n + "<<X[2][0]<<"*n^2\n";
	}

	// Metodo Sofisticado
	else if(tipoMetodo == 1){
		std::cout<<X[0][0]<<" + "<<X[1][0]<<"*n*log(n)\n";
	}

	double varianzaTiemposEstimados = calcularVarianza(tiemposMinimosCuadrados);
	double varianzaTiemposReales = calcularVarianza(tiempos);
	float coeficienteDeterminacion = varianzaTiemposEstimados/varianzaTiemposReales;

	std::cout<<"COEFICIENTE DETERMINACION: "<<coeficienteDeterminacion<<"\n\n";

	int valorEstimacion;

	std::cout<<"Tiempo para realizar la estimacion (0 si no se desea hacer la estimacion): ";
	cin>>valorEstimacion;

	while(valorEstimacion!=0){

		if(valorEstimacion > 0){
			if(tipoMetodo == 0){
				std::cout<<"Para "<<valorEstimacion<<" el tiempo es: "<<(X[0][0]+ X[1][0]*valorEstimacion + X[2][0]*pow(valorEstimacion, 2))<<std::endl;
			} else if(tipoMetodo == 1){
				std::cout<<"Para "<<valorEstimacion<<" el tiempo es: "<<(X[0][0] + (X[1][0]*valorEstimacion*log(valorEstimacion)))<<std::endl;
			}

			std::cout<<"Introduzca otro valor (0 si no se desea hacer el calculo): ";
			cin>>valorEstimacion;
		}
		else{
			std::cout<<"El valor es negativo, solo valen valores positivos (0 si no se desea hacer el calculo): ";
			cin>>valorEstimacion;
		}
	}

	if(tipoMetodo==0){
		escribirFichero("Datos_metodo_no_sofisticado.txt", n, tiempos, tiemposMinimosCuadrados);
	}
	else{
		escribirFichero("Datos_metodo_sofisticado.txt", n, tiempos, tiemposMinimosCuadrados);
	}

	std::cin.ignore();
}
