/*!
\file MonticuloMediciones.cpp
\brief Fichero que contiene el código de las funciones de la clase MonticuloMediciones.
\author Adrian Lopez Guerrero
\date 18/4/2017
\version 1.0
*/

//#include <vector>

#include <cassert>

#include "Medicion.hpp"

#include "MonticuloMediciones.hpp"

////////////////////////////////////////////////////////////////////

// Métodos privados de la clase MonticuloMediciones

void ed::MonticuloMediciones::shiftUp(int i){
  #ifndef NDEBUG
  assert((i >= 0) &&
  (i < size()));
  #endif //NDEBUG

  int index = i;

  if(index == 0){
    return;
  }

  while((getElement(index).getPrecipitacion() > getElement(getParent(index)).getPrecipitacion())){

    ed::Medicion medicionaux = getElement(index);
    setElement(index, getElement(getParent(index)));
    setElement((index-1)/2, medicionaux);

    index = (index-1)/2;

    if(index == 0){
      break;
    }
  }

  if(index != 0){

    #ifndef NDEBUG
    assert(getElement(index).getPrecipitacion() <= getElement(getParent(index)).getPrecipitacion());
    #endif //NDEBUG

    if(getLeftChild(index) != -1){
      #ifndef NDEBUG
      assert(getElement(index).getPrecipitacion() > getElement(getLeftChild(index)).getPrecipitacion());
      #endif //NDEBUG

      if(getRightChild(index) != -1){
        #ifndef NDEBUG
        assert(getElement(index).getPrecipitacion() > getElement(getRightChild(index)).getPrecipitacion());
        #endif //NDEBUG
      }
    }


  }
  else{
    if(getLeftChild(index) != -1){
      #ifndef NDEBUG
      assert(getElement(index).getPrecipitacion() > getElement(getLeftChild(index)).getPrecipitacion());
      #endif //NDEBUG

      if(getRightChild(index) != -1){
        #ifndef NDEBUG
        assert(getElement(index).getPrecipitacion() > getElement(getRightChild(index)).getPrecipitacion());
        #endif //NDEBUG
      }
    }
  }
}

void ed::MonticuloMediciones::shiftDown(int i){

  #ifndef NDEBUG
  assert((i >= 0) &&
  (i < size()));
  #endif //NDEBUG

  int index = 0;

  while(getLeftChild(index) != -1){
    int indexpequeno = getLeftChild(index);

    if((getRightChild(index) != -1) && (getElement(getRightChild(index)).getPrecipitacion() > getElement(getLeftChild(index)).getPrecipitacion())){
      indexpequeno = getRightChild(index);
    }

    if(getElement(index).getPrecipitacion() > getElement(indexpequeno).getPrecipitacion()){
      break;
    }
    else{
      ed::Medicion medicionaux = getElement(index);
      setElement(index, getElement(indexpequeno));
      setElement(indexpequeno, medicionaux);
    }

    index = indexpequeno;
  }

  if(index != 0){

    #ifndef NDEBUG
    assert(getElement(index).getPrecipitacion() <= getElement(getParent(index)).getPrecipitacion());
    #endif //NDEBUG

    if(getLeftChild(index) != -1){
      #ifndef NDEBUG
      assert(getElement(index).getPrecipitacion() > getElement(getLeftChild(index)).getPrecipitacion());
      #endif //NDEBUG

      if(getRightChild(index) != -1){
        #ifndef NDEBUG
        assert(getElement(index).getPrecipitacion() > getElement(getRightChild(index)).getPrecipitacion());
        #endif //NDEBUG
      }
    }


  }
  else{
    if(getLeftChild(index) != -1){
      #ifndef NDEBUG
      assert(getElement(index).getPrecipitacion() > getElement(getLeftChild(index)).getPrecipitacion());
      #endif //NDEBUG

      if(getRightChild(index) != -1){
        #ifndef NDEBUG
        assert(getElement(index).getPrecipitacion() > getElement(getRightChild(index)).getPrecipitacion());
        #endif //NDEBUG
      }
    }
  }
}
