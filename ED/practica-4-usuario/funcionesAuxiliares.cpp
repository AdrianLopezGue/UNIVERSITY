#include "funcionesAuxiliares.hpp"
#include "macros.hpp"

int ed::menu()
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
	std::cout<< "[1] Cargar grafo de fichero";

	PLACE(posicion++,10);
	std::cout << "[2] Grabar grafo en un fichero";

	posicion++;

	PLACE(posicion++,10);
	std::cout <<  "[3] Realizar prim";

	PLACE(posicion++,10);
	std::cout <<  "[4] Realizar kruskal";

	posicion++;

	PLACE(posicion++,10);
	std::cout <<  "[5] Mostrar grafo principal";

	PLACE(posicion++,10);
	std::cout <<  "[6] Mostrar arbol abarcador de coste minimo";

	PLACE(posicion++,10);
	std::cout <<  "[7] Mostrar vertices grafo principal";

	PLACE(posicion++,10);
	std::cout <<  "[8] Mostrar vertices grafo abarcador de coste minimo";

	PLACE(posicion++,10);
	std::cout <<  "[9] Mostrar lados grafo principal";

	PLACE(posicion++,10);
	std::cout <<  "[10] Mostrar lados grafo abarcador de coste minimo";

	posicion++;

	PLACE(posicion++,10);
	std::cout <<  "[11] Añadir vertice";

	PLACE(posicion++,10);
	std::cout <<  "[12] Borrar todos los vertices";

	PLACE(posicion++,10);
	std::cout <<  "[13] Longitud total del arbol abarcador de coste minimo";
	//////////////////////////////////////////////////////////////////////////////
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

void ed::cargarVerticesFichero(ed::Grafo &grafo){

	std::string nombreFichero;
	int posicion = 4;

	PLACE(posicion,27);
	std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,60);
	std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,28);
	std::cout << IBLUE << "NOMBRE FICHERO: "<<RESET;
	PLACE(posicion,60);
	std::cout << BIYELLOW<<"|\n"<<RESET;

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;

	std::cout << PLACE(posicion-1, 44) << "\b";
	std::cout << " \b";
	std::cin >> nombreFichero;

	std::ifstream fichero(nombreFichero.c_str());


	if(fichero){

		grafo.removeAll();

		char cadenaaux[256];
		float x;
		float y;

		while(fichero.getline(cadenaaux, 256, ' ') != NULL){
			x = atof(cadenaaux);

			fichero.getline(cadenaaux, 256, '\n');
			y = atof(cadenaaux);

			ed::Vertice verticeaux(x, y);

			grafo.addVertex(verticeaux);
		}

		posicion++;

		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"______________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,65);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,30);
		std::cout << IBLUE <<"GRAFO CARGADO CORRECTAMENTE"<<RESET;
		PLACE(posicion,65);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,35);
		std::cout << IBLUE <<"MEDIANTE EL FICHERO: "<<RESET;
		PLACE(posicion,65);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,38);
		std::cout << IGREEN <<UNDERLINE<<nombreFichero<<RESET;
		PLACE(posicion,65);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,65);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|______________________________________|\n"<<RESET;

		fichero.close();
	}
	else{

		posicion++;

		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,60);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,33);
		std::cout << IBLUE <<"EL FICHERO "<<UNDERLINE<<nombreFichero<<"\n"RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,33);
		std::cout << IBLUE <<"NO SE HA PODIDO ABRIR"<<RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;
	}

	std::cin.ignore();
}

void ed::grabarVerticesFichero(ed::Grafo &grafo){
	if(grafo.isEmpty() == true){
		mostrarGrafoEstaVacio();
		return;
	}

	std::string nombrefichero;
	int posicion = 4;

	PLACE(posicion,27);
	std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,60);
	std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,28);
	std::cout << IBLUE << "NOMBRE FICHERO: "<<RESET;
	PLACE(posicion,60);
	std::cout << BIYELLOW<<"|\n"<<RESET;

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;

	std::cout << PLACE(posicion-1, 44) << "\b";
	std::cout << " \b";
	std::cin >> nombrefichero;


	std::ofstream fichero(nombrefichero.c_str());

	if(fichero){

		for(int i = 0; i < grafo.sizeLados(); i++){
			fichero << grafo.getLadoVectorLados(i);
		}

		posicion++;

		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"______________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,65);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,30);
		std::cout << IBLUE <<"GRAFO CARGADO CORRECTAMENTE"<<RESET;
		PLACE(posicion,65);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,35);
		std::cout << IBLUE <<"EN EL FICHERO: "<<RESET;
		PLACE(posicion,65);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,38);
		std::cout << IGREEN <<UNDERLINE<<nombrefichero<<RESET;
		PLACE(posicion,65);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,65);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|______________________________________|\n"<<RESET;

		fichero.close();
	}
	else{
		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,60);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,33);
		std::cout << IBLUE <<"EL FICHERO "<<UNDERLINE<<nombrefichero<<"\n"RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,33);
		std::cout << IBLUE <<"NO SE HA PODIDO ABRIR"<<RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;
	}

	std::cin.ignore();
}

void ed::imprimirMatrizGrafoPrincipal(ed::Grafo &grafo){
	if(grafo.isEmpty() == true){
		mostrarGrafoEstaVacio();
		return;
	}
	int posicion = 5;

	PLACE(posicion,27);

	std::cout<<BIBLUE<<"["<<RESET;
	std::cout<<BIYELLOW<<" MATRIZ DE ADYACENCIA "<<RESET;
	std::cout<<BIBLUE<<"]\n"<<RESET;

	posicion++;
	posicion++;

	PLACE(posicion,27);

	for(int i = 0; i < grafo.sizeVertices(); i++){
		for(int j = 0; j < grafo.sizeVertices(); j++ ){
			if(grafo.getValorMatrizAdyacencia(i, j) == std::numeric_limits<int>::max()){
				std::cout<<BIBLUE<<"["<<RESET;
				std::cout<<BIYELLOW<<"INF"<<RESET;
				std::cout<<BIBLUE<<"]"<<RESET;
			}
			else{
				std::cout<<BIBLUE<<"[ "<<RESET;
				std::cout<<BIYELLOW<<grafo.getValorMatrizAdyacencia(i, j)<<RESET;
				std::cout<<BIBLUE<<" ]"<<RESET;
			}
		}
		posicion++;
		PLACE(posicion,27);
	}
	return;
}

void ed::imprimirMatrizArbol(ed::Grafo &grafo){
	if(grafo.isEmpty() == true){
		mostrarGrafoEstaVacio();
		return;
	}
	int posicion = 5;

	PLACE(posicion,27);

	std::cout<<BIBLUE<<"["<<RESET;
	std::cout<<BIYELLOW<<" ARBOL ABARCADOR MINIMO "<<RESET;
	std::cout<<BIBLUE<<"]\n"<<RESET;

	posicion++;
	posicion++;

	PLACE(posicion,27);

	for(int i = 0; i < grafo.sizeVertices(); i++){
		for(int j = 0; j < grafo.sizeVertices(); j++ ){
			if((grafo.getValorMatrizAdyacencia(i, j) == std::numeric_limits<int>::max()) ||
			(grafo.getValorMatrizAdyacencia(i, j) == 0)){
				std::cout<<BIBLUE<<"["<<RESET;
				std::cout<<BIYELLOW<<"INF"<<RESET;
				std::cout<<BIBLUE<<"]"<<RESET;
			}
			else{
				std::cout<<BIBLUE<<"[ "<<RESET;
				std::cout<<BIYELLOW<<grafo.getValorMatrizAdyacencia(i, j)<<RESET;
				std::cout<<BIBLUE<<" ]"<<RESET;
			}
		}
		posicion++;
		PLACE(posicion,27);
	}
	return;
}

ed::Grafo ed::AlgoritmoPrim(ed::Grafo &grafo){
	if(grafo.isEmpty() == true){
		mostrarGrafoEstaVacio();
		return 0;
	}

	std::vector< std::vector<int> > MatrixAdyacenciaAux = grafo.getMatrizIncidencia();
	std::vector< std::vector<int> > MatrixArbol(grafo.sizeVertices());
	std::vector<int> LineasVistas;
	std::vector<int> :: iterator it;

	ed::Grafo GrafoAux;

	// Inicializo las distancias del arbol en INF.
	for(int i = 0; i < grafo.sizeVertices(); i++)
	MatrixArbol[i] = std::vector<int> (grafo.sizeVertices(), std::numeric_limits<int>::max());

	int nodoorigen = 0;
	int nododestino = 0;

	while(LineasVistas.size() + 1 < grafo.getVerticesGrafo().size()){
		nodoorigen = nododestino;

		// Marco la fila y elimino la columna del nodo padre.
		LineasVistas.push_back(nodoorigen);
		for(int i = 0; i < grafo.sizeVertices(); i++)
		MatrixAdyacenciaAux[i][nodoorigen] = std::numeric_limits<int>::max();

		// Encuentro la menor distancia entre las filas marcadas.
		// El nodo padre es la linea marcada y el nodo hijo es la columna del minimo.
		int minimo = std::numeric_limits<int>::max();
		for(it = LineasVistas.begin(); it != LineasVistas.end(); it++){
			for(int i = 0; i < grafo.sizeVertices(); i++){
				if(minimo > MatrixAdyacenciaAux[*it][i]){
					minimo = MatrixAdyacenciaAux[*it][i];
					nodoorigen = *it;
					nododestino = i;
				}
			}
		}

		MatrixArbol[nodoorigen][nododestino] = minimo;
		MatrixArbol[nododestino][nodoorigen] = minimo;

		GrafoAux.addEdge(grafo.getVerticeVectorVertices(nodoorigen), grafo.getVerticeVectorVertices(nododestino));
	}

	GrafoAux.setMatriz(MatrixArbol);
	GrafoAux.setVectorVertices(grafo.getVerticesGrafo());

	int posicion = 4;

	PLACE(posicion,27);
	std::cout<<BIYELLOW<<"____________________________________________"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,71);
	std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,30);
	std::cout << IBLUE <<"¡SE HA REALIZADO PRIM CORRECTAMENTE!"<<RESET;
	PLACE(posicion,71);
	std::cout << BIYELLOW<<"|\n"<<RESET;

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|____________________________________________|\n"<<RESET;

	posicion++;
	posicion++;

	PLACE(posicion,35);

	std::cout<<BIBLUE<<"["<<RESET;
	std::cout<<BIYELLOW<<" MATRIZ DEL ARBOL"<<RESET;
	std::cout<<BIBLUE<<"]\n"<<RESET;

	posicion++;
	posicion++;

	PLACE(posicion,32);

	for(int i = 0; i < GrafoAux.sizeVertices(); i++){
		for(int j = 0; j < GrafoAux.sizeVertices(); j++ ){
			if(GrafoAux.getValorMatrizAdyacencia(i, j) == std::numeric_limits<int>::max()){
				std::cout<<BIBLUE<<"["<<RESET;
				std::cout<<BIYELLOW<<"INF"<<RESET;
				std::cout<<BIBLUE<<"]"<<RESET;
			}
			else{
				std::cout<<BIBLUE<<"[ "<<RESET;
				std::cout<<BIYELLOW<<GrafoAux.getValorMatrizAdyacencia(i, j)<<RESET;
				std::cout<<BIBLUE<<" ]"<<RESET;
			}
		}
		posicion++;
		PLACE(posicion,32);
	}

	return GrafoAux;

	std::cin.ignore();
}

ed::Grafo ed::AlgoritmoKruskal(ed::Grafo &grafo){
	if(grafo.isEmpty() == true){
		mostrarGrafoEstaVacio();
		return 0;
	}


	std::vector< std::vector<int> > MatrixAdyacenciaAux = grafo.getMatrizIncidencia();
	std::vector< std::vector<int> > MatrixArbol(grafo.sizeVertices());
	std::vector<int> ArbolDelNodo(grafo.sizeVertices()); // indica a que árbol pertenece el nodo

	ed::Grafo GrafoAux;

	for(int i = 0; i < grafo.sizeVertices(); i++){
		MatrixArbol[i] = std::vector<int> (grafo.sizeVertices(), 0);
		ArbolDelNodo[i] = i;
	}

	int nodoOrigen = 0;
	int nodoFinal = 0;
	int contador = 1;

	while(contador < grafo.sizeVertices()){
		// Encontrar  el arco mínimo que no forma ciclo y guardar los nodos y la distancia.
		int minimo = std::numeric_limits<int>::max();
		for(int i = 0; i < grafo.sizeVertices(); i++)
		for(int j = 0; j < grafo.sizeVertices(); j++)
		if(minimo > MatrixAdyacenciaAux[i][j] && MatrixAdyacenciaAux[i][j]!=0 && ArbolDelNodo[i] != ArbolDelNodo[j]){
			minimo = MatrixAdyacenciaAux[i][j];
			nodoOrigen = i;
			nodoFinal = j;
		}

		// Si los nodos no pertenecen al mismo árbol agrego el arco al árbol mínimo.
		if(ArbolDelNodo[nodoOrigen] != ArbolDelNodo[nodoFinal]){
			MatrixArbol[nodoOrigen][nodoFinal] = minimo;
			MatrixArbol[nodoFinal][nodoOrigen] = minimo;

			GrafoAux.addEdge(grafo.getVerticeVectorVertices(nodoOrigen), grafo.getVerticeVectorVertices(nodoFinal));

			// Todos los nodos del árbol del nodoB ahora pertenecen al árbol del nodoA.
			int aux = ArbolDelNodo[nodoFinal];
			ArbolDelNodo[nodoFinal] = ArbolDelNodo[nodoOrigen];
			for(int k = 0; k < grafo.sizeVertices(); k++)
			if(ArbolDelNodo[k] == aux)
			ArbolDelNodo[k] = ArbolDelNodo[nodoOrigen];

			contador++;
		}
	}

	for(int i = 0; i<GrafoAux.sizeAdyacencia(); i++){
		for(int j = 0; i<GrafoAux.sizeAdyacencia(); j++){
			if(MatrixArbol[i][j] == 0){
				MatrixArbol[i][j] = std::numeric_limits<int>::max();
			}
		}
	}

	GrafoAux.setMatriz(MatrixArbol);
	GrafoAux.setVectorVertices(grafo.getVerticesGrafo());

	int posicion = 4;

	PLACE(posicion,27);
	std::cout<<BIYELLOW<<"____________________________________________"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,71);
	std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,30);
	std::cout << IBLUE <<"¡SE HA REALIZADO KRUSKAL CORRECTAMENTE!"<<RESET;
	PLACE(posicion,71);
	std::cout << BIYELLOW<<"|\n"<<RESET;

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|____________________________________________|\n"<<RESET;

	posicion++;
	posicion++;

	PLACE(posicion,35);

	std::cout<<BIBLUE<<"["<<RESET;
	std::cout<<BIYELLOW<<" MATRIZ DEL ARBOL"<<RESET;
	std::cout<<BIBLUE<<"]\n"<<RESET;

	posicion++;
	posicion++;

	PLACE(posicion,32);

	for(int i = 0; i < GrafoAux.sizeVertices(); i++){
		for(int j = 0; j < GrafoAux.sizeVertices(); j++ ){
			if((GrafoAux.getValorMatrizAdyacencia(i, j) == std::numeric_limits<int>::max()) ||
			(GrafoAux.getValorMatrizAdyacencia(i, j) == 0)){
				std::cout<<BIBLUE<<"["<<RESET;
				std::cout<<BIYELLOW<<"INF"<<RESET;
				std::cout<<BIBLUE<<"]"<<RESET;
			}
			else{
				std::cout<<BIBLUE<<"[ "<<RESET;
				std::cout<<BIYELLOW<<GrafoAux.getValorMatrizAdyacencia(i, j)<<RESET;
				std::cout<<BIBLUE<<" ]"<<RESET;
			}
		}
		posicion++;
		PLACE(posicion,32);
	}

	return GrafoAux;

	std::cin.ignore();
}

void ed::anadirVertice(ed::Grafo &grafo){

	float x, y;
	int posicion = 4;

	PLACE(posicion,27);
	std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,60);
	std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,28);
	std::cout << IBLUE << "COORDENADA X: "<<RESET;
	PLACE(posicion,60);
	std::cout << BIYELLOW<<"|\n"<<RESET;

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,28);
	std::cout << IBLUE << "COORDENADA Y:  "<<RESET;
	PLACE(posicion,60);
	std::cout << BIYELLOW<<"|\n"<<RESET;

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;


	std::cout << PLACE(posicion-2, 43) << "\b";
	std::cout << " \b";
	std::cin >> x;
	std::cout << PLACE(posicion-1, 43) << "\b";
	std::cout << " \b";
	std::cin >> y;

	ed::Vertice VerticeAux(x,y);

	posicion++;
	posicion++;

	if(grafo.hasVertice(VerticeAux) == true){
		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"____________________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,71);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,30);
		std::cout << IRED <<"NODO EXISTENTE EN EL GRAFO"<<RESET;
		PLACE(posicion,71);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|____________________________________________|\n"<<RESET;
	}
	else{

		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"____________________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,71);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,30);
		std::cout << IGREEN <<"¡NODO INSERTADO CORRECTAMENTE!"<<RESET;
		PLACE(posicion,71);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|____________________________________________|\n"<<RESET;

		grafo.addVertex(VerticeAux);
	}

	std::cin.ignore();
	return;
}

void ed::mostrarLados(ed::Grafo &grafo){
	if(grafo.isEmpty() == true){
		mostrarGrafoEstaVacio();
		return;
	}

	int posicion = 4;

	PLACE(posicion,27);
	std::cout<<BIYELLOW<<"______________________"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,49);
	std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,30);
	std::cout << IGREEN <<"LADOS GRAFO"<<RESET;
	PLACE(posicion,49);
	std::cout << BIYELLOW<<"|\n"<<RESET;

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|______________________|\n"<<RESET;

	posicion++;
	posicion++;
	
	PLACE(posicion,16);  //32
	std::cout<<ICYAN<<"| PRIMER VERTICE |"<<RESET;

	PLACE(posicion,36); //52
	std::cout<<ICYAN<<"| SEGUNDO VERTICE |"<<RESET;

	posicion++;

	PLACE(posicion,16); //31
	std::cout<<ICYAN<<"------------------------------------------------------"<<RESET;

	posicion++;

	PLACE(posicion,18);  //34
	std::cout<<ICYAN<<"LABEL   X - Y"<<RESET;

	PLACE(posicion,38); //54
	std::cout<<ICYAN<<"LABEL   X - Y"<<RESET;

	PLACE(posicion,56); //72
	std::cout<<ICYAN<<"DISTANCIA"<<RESET;

	posicion++;
	posicion++;


	for(int i = 0; i<grafo.sizeLados(); i++){
		PLACE(posicion,20); //36
		std::cout<<BIYELLOW<<grafo.getLadoVectorLados(i).first().getLabel()<<RESET;

		PLACE(posicion,26); //42
		std::cout<<BIYELLOW<<grafo.getLadoVectorLados(i).first().getX()<<RESET;

		PLACE(posicion,29); //45
		std::cout<<BIYELLOW<<grafo.getLadoVectorLados(i).first().getY()<<RESET;

		PLACE(posicion,40); //56
		std::cout<<BIYELLOW<<grafo.getLadoVectorLados(i).second().getLabel()<<RESET;

		PLACE(posicion,46); //62
		std::cout<<BIYELLOW<<grafo.getLadoVectorLados(i).second().getX()<<RESET;

		PLACE(posicion,49); //65
		std::cout<<BIYELLOW<<grafo.getLadoVectorLados(i).second().getY()<<RESET;

		PLACE(posicion,62); //70
		std::cout<<BIYELLOW<<grafo.getLadoVectorLados(i).getData()<<RESET;

		posicion++;
	}

	//grafo.imprimirVectorLados();
}


void ed::mostrarVertices(ed::Grafo &grafo){
	if(grafo.isEmpty() == true){
		mostrarGrafoEstaVacio();
		return;
	}

	int posicion = 4;

	PLACE(posicion,27);
	std::cout<<BIYELLOW<<"______________________"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,49);
	std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,30);
	std::cout << IGREEN <<"VERTICES GRAFO"<<RESET;
	PLACE(posicion,49);
	std::cout << BIYELLOW<<"|\n"<<RESET;

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|______________________|\n"<<RESET;

	posicion++;
	posicion++;

	PLACE(posicion,32);
	std::cout<<ICYAN<<"LABEL   X    Y"<<RESET;

	posicion++;

	PLACE(posicion,31);
	std::cout<<ICYAN<<"------------------"<<RESET;

	posicion++;


	for(int i = 0; i<grafo.sizeVertices(); i++){
		PLACE(posicion,34);
		std::cout<<BIYELLOW<<grafo.getVerticeVectorVertices(i).getLabel()<<RESET;

		PLACE(posicion,40);
		std::cout<<BIYELLOW<<grafo.getVerticeVectorVertices(i).getX()<<RESET;

		PLACE(posicion,45);
		std::cout<<BIYELLOW<<grafo.getVerticeVectorVertices(i).getY()<<RESET;

		posicion++;
	}
}

void ed::borrarVertices(ed::Grafo &grafo){
	if(grafo.isEmpty() == true){
		mostrarGrafoEstaVacio();
		return;
	}
	else{
		grafo.removeAll();

		int posicion = 4;

		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"__________________________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,77);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,30);
		std::cout << IBLUE <<" LOS VERTICES SE HAN BORRADO CORRECTAMENTE"<<RESET;
		PLACE(posicion,77);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|__________________________________________________|\n"<<RESET;

		return;
	}
}

void ed::longitudArbolAbarcador(ed::Grafo &grafo){
	if(grafo.isEmpty() == true){
		mostrarGrafoEstaVacio();
		return;
	}
	else{
		int longitud = grafo.longitudGrafo();

		int posicion = 4;

		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,60);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,30);
		std::cout << IBLUE <<"LONGITUD:"<<longitud<<RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;
	}
}

void ed::mostrarGrafoEstaVacio(){

	int posicion = 4;

	PLACE(posicion,27);
	std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,60);
	std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,30);
	std::cout << IBLUE <<"EL GRAFO ESTA "<<UNDERLINE<<"VACIO"<<RESET;
	PLACE(posicion,60);
	std::cout << BIYELLOW<<"|\n"<<RESET;

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;
}
