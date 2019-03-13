/*!
\file  grafo.cpp
\brief Fichero que contiene el código de las funciones de la clase grafo
*/

#include "grafo.hpp"

void ed::Grafo::addVertex(ed::Vertice &vertice){
  if(hasVertice(vertice) == false){
    vertice.setLabel(sizeVertices()+1);
    _VerticesGrafo.push_back(vertice);

    _MatrizAdyacencia.resize(sizeVertices());

    for(int i=0; i<sizeVertices(); i++){
      _MatrizAdyacencia[i].resize(sizeVertices());
    }

    for(int i = 0; i<sizeVertices(); i++){
      if(i == sizeVertices()-1){
        _MatrizAdyacencia[i][i] = 0;
      }
      else{

        addEdge(getVerticeVectorVertices(i), getVerticeVectorVertices(sizeVertices()-1));

        _MatrizAdyacencia[i][sizeVertices()-1] = getLadoVectorLados(sizeLados()-1).getData();
        _MatrizAdyacencia[sizeVertices()-1][i] = getLadoVectorLados(sizeLados()-1).getData();
      }
    }
    #ifndef NDEBUG
    assert(getVerticesGrafo().back() == vertice);
    #endif //NDEBUG
  }
}

ed::Grafo ed::Grafo::prim(){

  std::vector< std::vector<int> > MatrixAdyacenciaAux = getMatrizIncidencia();
  std::vector< std::vector<int> > MatrixArbol(sizeVertices());
  std::vector<int> LineasVistas;
  std::vector<int> :: iterator it;

  ed::Grafo GrafoAux;

  // Inicializo las distancias del arbol en INF.
  for(int i = 0; i < sizeVertices(); i++)
  MatrixArbol[i] = std::vector<int> (sizeVertices(), std::numeric_limits<int>::max());

  int nodoorigen = 0;
  int nododestino = 0;

  while(LineasVistas.size() + 1 < _VerticesGrafo.size()){
    nodoorigen = nododestino;

    // Marco la fila y elimino la columna del nodo padre.
    LineasVistas.push_back(nodoorigen);
    for(int i = 0; i < sizeVertices(); i++)
    MatrixAdyacenciaAux[i][nodoorigen] = std::numeric_limits<int>::max();

    // Encuentro la menor distancia entre las filas marcadas.
    // El nodo padre es la linea marcada y el nodo hijo es la columna del minimo.
    int minimo = std::numeric_limits<int>::max();
    for(it = LineasVistas.begin(); it != LineasVistas.end(); it++){
      for(int i = 0; i < sizeVertices(); i++){
        if(minimo > MatrixAdyacenciaAux[*it][i]){
          minimo = MatrixAdyacenciaAux[*it][i];
          nodoorigen = *it;
          nododestino = i;
        }
      }
    }

    MatrixArbol[nodoorigen][nododestino] = minimo;
    MatrixArbol[nododestino][nodoorigen] = minimo;

    GrafoAux.addEdge(getVerticeVectorVertices(nodoorigen), getVerticeVectorVertices(nododestino));
  }

  GrafoAux.setMatriz(MatrixArbol);
  GrafoAux.setVectorVertices(getVerticesGrafo());

  return GrafoAux;

}


ed::Grafo ed::Grafo::kruskal(){

  std::vector< std::vector<int> > MatrixAdyacenciaAux = getMatrizIncidencia();
  std::vector< std::vector<int> > MatrixArbol(sizeVertices());
  std::vector<int> ArbolDelNodo(sizeVertices()); // indica a que árbol pertenece el nodo

  ed::Grafo GrafoAux;

  for(int i = 0; i < sizeVertices(); i++){
    MatrixArbol[i] = std::vector<int> (sizeVertices(), 0);
    ArbolDelNodo[i] = i;
  }

  int nodoOrigen = 0;
  int nodoFinal = 0;
  int contador = 1;

  while(contador < sizeVertices()){
    // Encontrar  el arco mínimo que no forma ciclo y guardar los nodos y la distancia.
    int minimo = std::numeric_limits<int>::max();
    for(int i = 0; i < sizeVertices(); i++)
    for(int j = 0; j < sizeVertices(); j++)
    if(minimo > MatrixAdyacenciaAux[i][j] && MatrixAdyacenciaAux[i][j]!=0 && ArbolDelNodo[i] != ArbolDelNodo[j]){
      minimo = MatrixAdyacenciaAux[i][j];
      nodoOrigen = i;
      nodoFinal = j;
    }

    // Si los nodos no pertenecen al mismo árbol agrego el arco al árbol mínimo.
    if(ArbolDelNodo[nodoOrigen] != ArbolDelNodo[nodoFinal]){
      MatrixArbol[nodoOrigen][nodoFinal] = minimo;
      MatrixArbol[nodoFinal][nodoOrigen] = minimo;

      GrafoAux.addEdge(getVerticeVectorVertices(nodoOrigen), getVerticeVectorVertices(nodoFinal));

      // Todos los nodos del árbol del nodoB ahora pertenecen al árbol del nodoA.
      int aux = ArbolDelNodo[nodoFinal];
      ArbolDelNodo[nodoFinal] = ArbolDelNodo[nodoOrigen];
      for(int k = 0; k < sizeVertices(); k++)
      if(ArbolDelNodo[k] == aux)
      ArbolDelNodo[k] = ArbolDelNodo[nodoOrigen];

      contador++;
    }
  }

  GrafoAux.setMatriz(MatrixArbol);
  GrafoAux.setVectorVertices(getVerticesGrafo());

  return GrafoAux;
}


void ed::Grafo::setVerticesGrafo(std::vector <ed::Vertice> VerticesGrafo){

  removeAll();

  std::vector<ed::Vertice> :: iterator it;

  for(it = VerticesGrafo.begin(); it != VerticesGrafo.end(); it++){
    addVertex(*it);
  }
}
