#include "funcionespractica1.hpp"
#include "funcionespractica2.hpp"
#include "macros.hpp"
#include "ClaseTiempo.hpp"
#include "sistemaEcuaciones.hpp"

double calcularCombinatoriaRecursiva(int n, int k){
	if(k == 0 || k == n){
		return 1;
	}
	else{
		return calcularCombinatoriaRecursiva(n-1, k-1) + calcularCombinatoriaRecursiva(n-1, k);
	}
}

double calcularCombinatoriaIterativa(int n, int k){
	double resultado=1;

	if( (k==0)||(n==k) ){
		return 1;
	}

	for(double i=1; i<=k; i++){
		resultado= resultado*( n-i +1)/i;
	}
	return resultado;
}

double calcularCombinatoriaRecursivaTabla(const double &n, const double &k,std::vector< std::vector<double> >  &tabla){

	if( tabla[n][k]!=-1 ){
		return tabla[n][k];
	}
	else{
		double aux;
		aux= calcularCombinatoriaRecursivaTabla(n-1,k-1,tabla) + calcularCombinatoriaRecursivaTabla(n-1,k,tabla);
		tabla[n][k]=aux;
		return aux;
	}
}

void AlgoritmoHanoi(int m, int i, int j){

	if(m > 0){
		AlgoritmoHanoi(m-1, i, 6-i-j);

		AlgoritmoHanoi(m-1, 6-i-j, j);
	}
}

void rellenarVarillaInicial(std::vector<string> &v1, int numeroDiscos){
	for(unsigned int i = numeroDiscos; i>0; i--){
		string aux = "";
		for(unsigned int j = 0; j<i; j++){
			aux += "-";
		}
		v1.push_back(aux);
	}
}

void mostrarVarillas(std::vector<string> &v1, std::vector<string> &v2, std::vector<string> &v3){
	std::cout<<"VARILLA 1 \n";
	for(int i = v1.size(); i>0; i--){
		std::cout<<v1[i-1]<<"\n";
	}

	std::cout<<"VARILLA 2\n";
	for(int i = v2.size(); i>0; i--){
		std::cout<<v2[i-1]<<"\n";
	}

	std::cout<<"VARILLA 3\n";
	for(int i = v3.size(); i>0; i--){
		std::cout<<v3[i-1]<<"\n";
	}

	std::cin.ignore();
}


void mostrarPasosHanoi(int m, std::vector<string> &v1, std::vector<string> &v2, std::vector<string> &v3){
	if(m == 1){
		v3.push_back(v1.back());
		v1.pop_back();

		mostrarVarillas(v1, v2, v3);

	}else{
		mostrarPasosHanoi(m-1, v1,v3,v2);

		v3.push_back(v1.back());
		v1.pop_back();

		mostrarVarillas(v1, v2, v3);

		mostrarPasosHanoi(m-1,v2,v1,v3);
	}
}

void imprimirTiempo(double tiempo){		// fmod para restos

	double segundosTotal = tiempo*0.000001;
	double anyosResto = 0;
	double anyos = 0;
	double diasResto = 0;
	double dias = 0;
	double horasResto = 0;
	double horas = 0;
	double segundos = 0;
	double minutos = 0;

	if(segundosTotal<31536000){
		 anyosResto = std::fmod(segundosTotal, 31536000);
		 anyos = 0; // IMPRIME
	}
	else{
		 anyosResto = std::fmod(segundosTotal, 31536000);
		 anyos = (segundosTotal-anyosResto)/31536000; // IMPRIME
	}

	if(anyosResto<86400){
		 diasResto = std::fmod(anyosResto, 86400);
		 dias = 0;	//I
	}
	else{
		 diasResto = std::fmod(anyosResto, 86400);
		 dias = (anyosResto-diasResto)/86400;	//I
	}

	if(diasResto<3600){
		 horasResto = std::fmod(diasResto, 3600);
		 horas = 0;	//I
	}
	else{
		 horasResto = std::fmod(diasResto, 3600);
		 horas = (diasResto-horasResto)/3600;	//I
	}

	if(horasResto<60){
		 segundos = std::fmod(horasResto, 60);
		 minutos = 0;	//I
	}
	else{
		 segundos = std::fmod(horasResto, 60);
		 minutos = (horasResto-segundos)/60;	//I
	}

	std::cout<<"TIEMPO: "<<anyos<<" anyos, "<<dias<<" dias, "<<horas<<" horas, "<<minutos<<" minutos y "<<segundos<<" segundos.\n";

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
	std::cout<< "[1] Combinatoria iterativa";

	PLACE(posicion++,10);
	std::cout<< "[2] Combinatoria recursiva";

	PLACE(posicion++,10);
	std::cout<< "[3] Combinatoria recursiva con tabla";

	PLACE(posicion++,10);
	std::cout<< "[4] Calcular movimientos torres de Hanoi";

	PLACE(posicion++,10);
	std::cout<< "[5] Representar paso a paso en modo texto torres de Hanoi";

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

void realizarCombinatoria(int tipoMetodo){

	Data data;
	data = pedirValoresDatos();

	int tamVector = (data.max_n-data.min_n)/data.incremento;

	Clock reloj;																			// reloj que va a medir el tiempo que tarda el metodo en cada iteracion

	std::vector<double> tiempos(tamVector, 0);		// vector que guarda los tiempos medios que tarda para cada n
	std::vector<double> n(tamVector, 0);					// vector que guarda el tamaño de los vectores creados
	std::vector<double> exponente2(tamVector, 0);			// vector que guarda los valores tras calcular n*log(n)


	double tiempoPasado = 0.0;
	int posicionVector = 0;

	for(double i=data.min_n; i<=data.max_n; i = i + data.incremento){
		tiempoPasado = 0.0;

		for(int w = 0; w < data.num_repeticiones; w++){

			// RECURSIVA ITERATIVA
			if(tipoMetodo == 0){
				for (int k=0 ; k<=i; k++) {
					reloj.start();
					calcularCombinatoriaIterativa(i, k);  // i = n, j = k

					if (reloj.isStarted()){
						reloj.stop();
						tiempoPasado+=reloj.elapsed();
					}
				}
			}
			// RECURSIVA RECURSIVA SIN TABLA
			else  if(tipoMetodo == 1){
				for (int k=0 ; k<=i; k++) {
					reloj.start();
					calcularCombinatoriaRecursiva(i, k);

					if (reloj.isStarted()){
						reloj.stop();
						tiempoPasado+=reloj.elapsed();
					}
				}
			}
			// RECURSIVA RECURSIVA CON TABLA
			else  if(tipoMetodo == 2){
				for (int k=0 ; k<=i; k++) {
					std::vector< std::vector<double> > tabla( i+1,std::vector< double >(i+1) );

					for(int x=0; x<i+1; x++){
						for(int y=0; y<i+1; y++){
							if(x==y){
								tabla[x][y]=1; //si k == n --> combinatorio = 1
							}
							else{
								tabla[x][y]=-1;
							}
						}
					}

					reloj.start();
					calcularCombinatoriaRecursivaTabla(i, k, tabla);  // size = n, data.num_repeticiones = k

					if (reloj.isStarted()){
						reloj.stop();
						tiempoPasado+=reloj.elapsed();
					}

					tabla.clear();
				}
			}
		}

		tiempos[posicionVector] = tiempoPasado/data.num_repeticiones;		// guardamos el tiempo medio
		n[posicionVector] = i;																		// guardamos el tamaño del vector que hemos ordenado previamente
		exponente2[posicionVector] = pow(2, i);

		posicionVector++;
	}

	int ordenPolinomio = 0;

	if(tipoMetodo == 0){
		ordenPolinomio = 2;
	}	else if(tipoMetodo == 1){
		ordenPolinomio = 1;
	} else if(tipoMetodo == 2){
		ordenPolinomio = 2;
	}

	// Calculamos matrices A y B para poder obtener el valor de la matriz X y asi poder ajustar la curva
	// de manera correcta

	std::vector< std::vector<double> > A(ordenPolinomio+1, std::vector<double> (ordenPolinomio+1));
	std::vector< std::vector<double> > B(ordenPolinomio+1, std::vector<double> (1));
	std::vector< std::vector<double> > X(ordenPolinomio+1, std::vector<double> (1));

	// Combinatoria iterativa
	if(tipoMetodo == 0){
		calcularMatrizA(A, n, ordenPolinomio);
		calcularMatrizB(B, n, tiempos, ordenPolinomio);

		// Combinatoria recursiva SIN tabla
	}	else if(tipoMetodo == 1){
		calcularMatrizA(A, exponente2, ordenPolinomio);
		calcularMatrizB(B, exponente2, tiempos, ordenPolinomio);

		// Combinatoria recursiva CON tabla
	} else if(tipoMetodo == 2){
		calcularMatrizA(A, n, ordenPolinomio);
		calcularMatrizB(B, n, tiempos, ordenPolinomio);
	}

	resolverSistemaEcuaciones(A, B, ordenPolinomio+1, X);

	std::vector<double> tiemposMinimosCuadrados(tamVector, 0);


	// Rellenamos el vector que albergará los valores estimados del tiempo que tardaran los metodos
	// utilizados previamente, para despues compararlos con los que hemos recogido anteriormente en las
	// pruebas

	if(tipoMetodo == 0){
		calcularVectorTiemposEstimados(tiemposMinimosCuadrados, n, X);
	}	else if(tipoMetodo == 1){
		calcularVectorTiemposEstimados(tiemposMinimosCuadrados, exponente2, X);
	} else if(tipoMetodo == 2){
		calcularVectorTiemposEstimados(tiemposMinimosCuadrados, n, X);
	}

	double varianzaTiemposEstimados = calcularVarianza(tiemposMinimosCuadrados);
	double varianzaTiemposReales = calcularVarianza(tiempos);
	float coeficienteDeterminacion = varianzaTiemposEstimados/varianzaTiemposReales;

	std::cout<<"COEFICIENTE DETERMINACION: "<<coeficienteDeterminacion<<"\n\n";

	int valorEstimacion;

	std::cout<<"Repetiones a estimar (0 si no se desea hacer la estimacion): ";
	cin>>valorEstimacion;

	while(valorEstimacion!=0){

		if(valorEstimacion > 0){
			if(tipoMetodo == 0){

				double tiempo = 0.0;

				for(unsigned int i=0; i<X.size();i++){
					tiempo += X[i][0]*pow(valorEstimacion, i);
				}

				std::cout<<"TIEMPO INICIAL: "<<tiempo<<"\n";

				imprimirTiempo(tiempo);

			} else if(tipoMetodo == 1){

				double tiempo = 0.0;

				tiempo = X[0][0] + (X[1][0]*valorEstimacion*pow(2, valorEstimacion));


				imprimirTiempo(tiempo);
			}

			else if(tipoMetodo == 2){

				double tiempo = 0.0;

				for(unsigned int i=0; i<X.size();i++){
					tiempo += X[i][0]*pow(valorEstimacion, i);
				}

				imprimirTiempo(tiempo);
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
		escribirFichero("iterativo.txt", n, tiempos, tiemposMinimosCuadrados);
	}
	else if(tipoMetodo==1){
		escribirFichero("recursivo.txt", n, tiempos, tiemposMinimosCuadrados);
	}
	else if(tipoMetodo==2){
		escribirFichero("recursivocontabla.txt", n, tiempos, tiemposMinimosCuadrados);
	}

	std::cin.ignore();
}




void realizarCalculoMovimientosHanoi(){
	Data data;
	data = pedirValoresDatos();

	int tamVector = (data.max_n-data.min_n)/data.incremento;

	Clock reloj;																			// reloj que va a medir el tiempo que tarda el metodo en cada iteracion

	std::vector<double> tiempos(tamVector, 0);		// vector que guarda los tiempos medios que tarda para cada n
	std::vector<double> n(tamVector, 0);
	std::vector<double> exponente2(tamVector, 0);					// vector que guarda el tamaño de los vectores creados

	double tiempoPasado = 0.0;
	int posicionVector = 0;

	for(double i=data.min_n; i<=data.max_n; i = i + data.incremento){

		tiempoPasado = 0.0;

		for(int j=0 ; j<data.num_repeticiones; j++){

			reloj.start();
			AlgoritmoHanoi(i, 1, 2);
			if (reloj.isStarted()){
				reloj.stop();
				tiempoPasado+=reloj.elapsed();
			}
		}

		tiempos[posicionVector] = tiempoPasado/data.num_repeticiones;		// guardamos el tiempo medio
		n[posicionVector] = i;
		exponente2[posicionVector] = pow(2, i);																		// guardamos el tamaño del vector que hemos ordenado previamente

		posicionVector++;
	}

	int ordenPolinomio = 1;

	// Calculamos matrices A y B para poder obtener el valor de la matriz X y asi poder ajustar la curva
	// de manera correcta

	std::vector< std::vector<double> > A(ordenPolinomio+1, std::vector<double> (ordenPolinomio+1));
	std::vector< std::vector<double> > B(ordenPolinomio+1, std::vector<double> (1));
	std::vector< std::vector<double> > X(ordenPolinomio+1, std::vector<double> (1));

	calcularMatrizA(A, exponente2, ordenPolinomio);
	calcularMatrizB(B, exponente2, tiempos, ordenPolinomio);

	resolverSistemaEcuaciones(A, B, ordenPolinomio+1, X);

	std::vector<double> tiemposMinimosCuadrados(tamVector, 0);


	// Rellenamos el vector que albergará los valores estimados del tiempo que tardaran los metodos
	// utilizados previamente, para despues compararlos con los que hemos recogido anteriormente en las
	// pruebas

	calcularVectorTiemposEstimados(tiemposMinimosCuadrados, exponente2, X);

	double varianzaTiemposEstimados = calcularVarianza(tiemposMinimosCuadrados);
	double varianzaTiemposReales = calcularVarianza(tiempos);
	float coeficienteDeterminacion = varianzaTiemposEstimados/varianzaTiemposReales;

	std::cout<<"COEFICIENTE DETERMINACION: "<<coeficienteDeterminacion<<"\n\n";

	int valorEstimacion;

	std::cout<<"Repetiones a estimar (0 si no se desea hacer la estimacion): ";
	cin>>valorEstimacion;

	while(valorEstimacion!=0){

		if(valorEstimacion > 0){

			double tiempo = 0.0;

			tiempo = X[0][0] + (X[1][0]*valorEstimacion*pow(2, valorEstimacion));
			std::cout<<"TIEMPO: "<<tiempo<<"\n";

			imprimirTiempo(tiempo);

			std::cout<<"Introduzca otro valor (0 si no se desea hacer el calculo): ";
			cin>>valorEstimacion;
		}
		else{
			std::cout<<"El valor es negativo, solo valen valores positivos (0 si no se desea hacer el calculo): ";
			cin>>valorEstimacion;
		}
	}

	escribirFichero("hanoi.txt", n, tiempos, tiemposMinimosCuadrados);

	std::cin.ignore();
}

void mostrarPasosHanoi(){
	int numeroDiscos;

	std::cout<<"Introduzca un numero de discos (0 si no se desea hacer el calculo): ";
	std::cin>>numeroDiscos;

	while(numeroDiscos!=0){

		if(numeroDiscos > 0){

			std::vector<string> v1(numeroDiscos, "");
			std::vector<string> v2(numeroDiscos, "");
			std::vector<string> v3(numeroDiscos, "");

			rellenarVarillaInicial(v1, numeroDiscos);

			std::cin.ignore();
			mostrarVarillas(v1, v2, v3);

			mostrarPasosHanoi(numeroDiscos, v1, v3, v2);

			std::cout<<"\n\nIntroduzca otro numero de discos (0 si no se desea hacer el calculo): ";
			std::cin>>numeroDiscos;
		}
		else{
			std::cout<<"El valor es negativo, solo valen valores positivos (0 si no se desea hacer el calculo): ";
			std::cin>>numeroDiscos;
		}
	}
}
