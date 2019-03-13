/*!
\file grafo.hpp
\brief Fichero de la clase Grafo
\author Adrian Lopez Guerrero
\date 26/5/2018
\version 1.0
*/

#ifndef _GRAFO_HPP
#define _GRAFO_HPP

#include <vector>
#include <limits>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "vertice.hpp"
#include "lado.hpp"

/*!
\namespace ed
\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed{

  /*!
  \class Grafo
  \brief Definición de la clase Grafo
  \n  Grafo creado con un conjunto de lados
  */

  class Grafo
  {

  private:

    //! \name Atributos privados de la clase Grafo

    std::vector< std::vector<int> > _MatrizAdyacencia;  //!< Matrix de adyacencia
    std::vector <ed::Vertice> _VerticesGrafo; //!< Vector de vertices del grafo
    std::vector <ed::Lado> _LadosGrafo; //!< Vector de lados del grafo




    //! \name Métodos públicos de la clase MonticuloMediciones

  public:

    //! \name Constructor

    /*!
    \brief     Constructor de la clase Grafo
    \attention Función sobrecargada
    \note      Función inline
    \note      Función inline
    \pre       Ninguna
    \post      Todos los elementos de la parte privada estan vacios
    */

    inline Grafo(){

      #ifndef NDEBUG
      assert(isEmpty() == true);
      #endif //NDEBUG
    };

    /*!
    \brief Construye un grafo estableciendo valores por defecto a los elementos de la matriz de adyacencia a infinito
    \attention Función sobrecargada
    \note      Función inline
    \warning   Se requiere que las funciones de acceso tengan el modificador const
    \param     numeronodos: int que indica que dimension queremos que sea la matriz cuadrada de adyacencia
    \post  getFecha() == fecha
    \post  La matriz no esta vacia pero el vector de lados y vertices si (no se han introducido todavia)
    */

    inline Grafo(int numeronodos){

      _MatrizAdyacencia = std::vector< std::vector<int> > (numeronodos);

      for(int i = 0; i<numeronodos ; i++){
        this->_MatrizAdyacencia[i] = std::vector<int> (numeronodos, std::numeric_limits<int>::max());
      }

      #ifndef NDEBUG
      assert((isEmptyMatriz() == true));
      #endif //NDEBUG
      #ifndef NDEBUG
      assert((isEmptyLados() == true));
      #endif //NDEBUG
      #ifndef NDEBUG
      assert((isEmptyVertices() == true));
      #endif //NDEBUG
    }

    //! \name Observadores: funciones de consulta de la clase Medicion

    /*!
    \brief     Getter de un elemento  de la matriz de adyacencia indicando su index
    \note      Función inline
    \note   Función de tipo "const": no puede modificar al objeto actual
    \param 		 i: entero que indica el indice del elemento
    \param 		 j: entero que indica el indice del elemento
    \pre       Ninguna
    \post      Ninguna
    */

    inline int getValorMatrizAdyacencia(int i, int j) const{
      return _MatrizAdyacencia[i][j];
    }

    /*!
    \brief     Getter de un elemento  del vector de vertices indicando su index
    \note      Función inline
    \note      Función de tipo "const": no puede modificar al objeto actual
    \param 		 index: entero que indica el indice del elemento
    \pre       Ninguna
    \post      Ninguna
    */

    inline ed::Vertice getVerticeVectorVertices(int index) const{
      return getVerticesGrafo()[index];
    }

    /*!
    \brief     Getter de un elemento  del vector de lados indicando su index
    \note      Función inline
    \note      Función de tipo "const": no puede modificar al objeto actual
    \param 		 index: entero que indica el indice del elemento
    \pre       Ninguna
    \post      Ninguna
    */

    inline ed::Lado getLadoVectorLados(int index) const{
      return getLadosGrafo()[index];
    }

    /*!
    \brief     Getter de la matriz de adyacencia
    \note      Función inline
    \note      Función de tipo "const": no puede modificar al objeto actual
    \pre       Ninguna
    \post      Ninguna
    */

    inline std::vector< std::vector<int> > getMatrizIncidencia()const{
      return _MatrizAdyacencia;
    }

    /*!
    \brief     Getter de vector de vertices
    \note      Función inline
    \note      Función de tipo "const": no puede modificar al objeto actual
    \pre       Ninguna
    \post      Ninguna
    */

    inline std::vector <ed::Vertice>  getVerticesGrafo()const{
      return _VerticesGrafo;
    }

    /*!
    \brief     Getter de vector de lados
    \note      Función inline
    \note      Función de tipo "const": no puede modificar al objeto actual
    \pre       Ninguna
    \post      Ninguna
    */

    inline std::vector <ed::Lado> getLadosGrafo()const{
      return _LadosGrafo;
    }

    //! \name Observadores publicos

    /*!
    \brief  Comprueba si todos los elementos de la parte privada estan vacios
    \note      Función inline
    \post 	Devuelve verdadero si todos estan vacios; falso, en el caso de que alguno de ellos este vacio.
    \return true, si todos los elementos estan vacios; false, en el caso de que alguno de ellos este vacio.
    */

    inline bool isEmpty() {

      bool valorDevuelto;

      if(isEmptyMatriz() && isEmptyLados() && isEmptyVertices()){
        valorDevuelto =  true;
      }
      else{
        valorDevuelto =  false;
      }

      #ifndef NDEBUG
      assert(valorDevuelto == (isEmptyMatriz() && isEmptyLados() && isEmptyVertices()));
      #endif //NDEBUG

      return valorDevuelto;
    }

    /*!
    \brief  Comprueba si la matriz de adyacencia esta vacia
    \note      Función inline
    \post 	Devuelve verdadero si esta vacia; falso, en el caso de que no lo este.
    \return Devuelve true si esta vacia; falso, en el caso de que no lo este.
    */

    inline bool isEmptyMatriz() {

      bool valorDevuelto;

      if(sizeAdyacencia() == 0){
        valorDevuelto = true;
      }
      else{
        valorDevuelto = false;
      }

      #ifndef NDEBUG
      assert(valorDevuelto == (sizeAdyacencia() == 0));
      #endif //NDEBUG

      return valorDevuelto;
    }

    /*!
    \brief  Comprueba si la matriz de adyacencia esta vacia
    \note      Función inline
    \post 	Devuelve verdadero si esta vacia; falso, en el caso de que no lo este.
    \return Devuelve true si esta vacia; falso, en el caso de que no lo este.
    */

    inline bool isEmptyVertices() {
      bool valorDevuelto;

      if(sizeVertices() == 0){
        valorDevuelto = true;
      }
      else{
        valorDevuelto = false;
      }

      #ifndef NDEBUG
      assert(valorDevuelto == (sizeVertices() == 0));
      #endif //NDEBUG

      return valorDevuelto;
    }

    /*!
    \brief  Comprueba si el vector de lados esta vacio
    \note      Función inline
    \post 	Devuelve verdadero si esta vacio; falso, en el caso de que no lo este.
    \return Devuelve true si esta vacio; falso, en el caso de que no lo este.
    */

    inline bool isEmptyLados() {
      bool valorDevuelto;

      if(sizeLados() == 0){
        valorDevuelto = true;
      }
      else{
        valorDevuelto = false;
      }

      #ifndef NDEBUG
      assert(valorDevuelto == (sizeLados() == 0));
      #endif //NDEBUG

      return valorDevuelto;
    }

    /*!
    \brief  Devuelve el número de vertices del vector de vertices
    \note   Función de tipo "const": no puede modificar al objeto actual
    \return Número entero que representa el número de elementos o ítems del vector de vertices
    */

    inline int sizeVertices() const{
      return getVerticesGrafo().size();
    }

    /*!
    \brief  Devuelve el número de vertices de la matriz de adyacencia
    \note   Función de tipo "const": no puede modificar al objeto actual
    \return Número entero que representa el número de elementos o ítems de la matriz de adyacencia
    */

    inline int sizeAdyacencia() const{
      return getMatrizIncidencia().size();
    }

    /*!
    \brief  Devuelve el número de lados del vector de lados
    \note   Función de tipo "const": no puede modificar al objeto actual
    \return Número entero que representa el número de elementos o ítems del vector de lados
    */

    inline int sizeLados() const{
      return getLadosGrafo().size();
    }

    ////////////////////////////////////////////////////////////

    //! \name Operaciones de modificación

    /*!
    \brief  Inserta un nuevo vertice en el grafo
    \param 		vertice: Objeto de tipo medicion pasado por referencia
    \post 	  isEmpty() == falso
    \post 		has(medicion) == true)
    */

    void addVertex(Vertice &vertice);

    /*!
    \brief     Añade un nuevo lado al grafo
    \note      Función inline
    \param 		 u: vertice pasado como referencia constante
    \param 		 v: vertice pasado como referencia constante
    \pre       Ninguna
    \post      El lado se encuentra en el vector de lados
    */

    inline void addEdge(ed::Vertice const &u, ed::Vertice const &v){
      ed::Lado ladoaux(u, v);
      if(hasLado(ladoaux) == false){
        _LadosGrafo.push_back(ladoaux);

        #ifndef NDEBUG
        assert(hasLado(getLadoVectorLados(sizeLados()-1)));
        #endif //NDEBUG
      }

    }

    /*!
    \brief     Setter del vector de vertices pasado como argumento
    \note      Función inline
    \param 		 VerticesGrafo: vector de vertices de la clase vertice
    \pre       Ninguna
    \post      Ninguna
    */

    inline void setVectorVertices(std::vector <ed::Vertice> VerticesGrafo){
      _VerticesGrafo = VerticesGrafo;
    }

    /*!
    \brief     Setter del vector de lados pasado como argumento
    \note      Función inline
    \param 		 LadosGrafo: vector de lados de la clase lado
    \pre       Ninguna
    \post      Ninguna
    */

    inline void setVectorLados(std::vector <ed::Lado> LadosGrafo){
      _LadosGrafo = LadosGrafo;
    }

    /*!
    \brief     Setter de la matriz de adyacencia pasado como argumento
    \note      Función inline
    \param 		 MatrizAdyacencia: vector de vectores de int de la clase std
    \pre       Ninguna
    \post      Ninguna
    */

    inline void setMatriz(std::vector< std::vector<int> > MatrizAdyacencia){
      _MatrizAdyacencia = MatrizAdyacencia;
    }

    /*!
    \brief  Borra todos los elementos del grafo (matriz de adyacencia, vector de vertices y vector de lados)
    \note      Función inline
    \post 	  isEmpty() == true
    */

    inline void removeAll(){
      _VerticesGrafo.clear();
      _MatrizAdyacencia.clear();
      _LadosGrafo.clear();


      #ifndef NDEBUG
      // Se comprueba la postcondición
      assert(isEmpty() == true);
      #endif //NDEBUG
    }

    Grafo prim();
    Grafo kruskal();

    void setVerticesGrafo(std::vector <ed::Vertice> VerticesGrafo);

    /*!
    \brief     Operador de asignación
    \attention Se sobrecarga el operador de asignación "="
    \note      Función inline
    \warning   Se requiere que las funciones de acceso tengan el modificador const
    \param     m: objeto de la clase Grafo pasado como referencia constante
    \pre       El grafo "m" debe ser diferente al grafo actual
    \post      Ninguna
    */

    inline Grafo & operator=(Grafo const &m){

      #ifndef NDEBUG
      assert(this != &m);
      #endif //NDEBUG

      setMatriz(m.getMatrizIncidencia());
      setVectorVertices(m.getVerticesGrafo());
      setVectorLados(m.getLadosGrafo());

      return *this;
    }

    /*!
    \brief     Calcula la longitud del grafo (suma de los elementos distintos de cero de la matriz de adyacencia)
    \note      Función inline
    \pre 			 Ninguna
    \post      Ninguna
    \return 	entero que la longitud calculada
    */

    inline int longitudGrafo(){

      int longitud = 0;

      for(int i = 0; i < sizeVertices(); i++){
        for(int j = 0; (j < sizeVertices()) && (i>j); j++ ){
          if((getValorMatrizAdyacencia(i, j) != std::numeric_limits<int>::max()) && (getValorMatrizAdyacencia(i, j) > 0)){
            longitud += getValorMatrizAdyacencia(i, j);
          }
        }
      }

      return longitud;
    }

    /*!
    \brief     Se comprueba si el lado está incluido dentro del vector de vertices.
    \note      Función inline
    \param 		 vertice: Objeto de tipo Vertice "vertice"
    \pre 			 Ninguna
    \post      Ninguna
    \return 	true: si se encuentra dentro de vector de vertices; false: si no se encuentra dentro de este
    */

    inline bool hasVertice(ed::Vertice vertice){
      for(int i = 0; i<sizeVertices(); i++){
        if(vertice == getVerticeVectorVertices(i)){
          return true;
        }
      }
      return false;
    }

    /*!
    \brief     Se comprueba si el lado está incluido dentro del vector de lados.
    \note      Función inline
    \param 		 lado: Objeto de tipo Lado "lado"
    \pre 			 Ninguna
    \post      Ninguna
    \return 	true: si se encuentra dentro de vector de lados; false: si no se encuentra dentro de este
    */

    inline bool hasLado(ed::Lado lado){
      for(int i = 0; i<sizeLados(); i++){
        if(lado == getLadoVectorLados(i)){
          return true;
        }
      }
      return false;
    }

    //! \name Función de escritura

    /*!
    \brief  Muestra por pantalla la matriz de adyacencia
    \note      Función inline
    */

    inline void imprimirMatrizAdyacencia(){
      for(int i = 0; i < sizeVertices(); i++){
        for(int j = 0; j < sizeVertices(); j++ ){
          if(getValorMatrizAdyacencia(i, j) == std::numeric_limits<int>::max()){
            std::cout<<"[INF]";
          }
          else{
            std::cout<<"["<< getValorMatrizAdyacencia(i, j) << "]";
          }
        }
        std::cout<<"\n";
      }
    }

    /*!
    \brief  Muestra por pantalla el vector de lados
    \note      Función inline
    */

    inline void imprimirVectorLados(){
      for(int i = 0; i<sizeLados(); i++){
        std::cout<<getLadoVectorLados(i)<<"\n";
      }
    }

    /*!
    \brief  Muestra por pantalla el vector de vertices
    \note      Función inline
    */

    inline void imprimirVectorVertices(){
      for(int i = 0; i<sizeVertices(); i++){
        std::cout<<getVerticeVectorVertices(i)<<"\n";
      }
    }

  };


}

#endif
