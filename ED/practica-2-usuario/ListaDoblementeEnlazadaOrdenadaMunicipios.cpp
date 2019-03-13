/*!
\file   ListaDoblementeEnlazadaOrdenadaMunicipios.cpp
\brief  Clase de una lista doblemente enlazada y ordenada de Municipios
\author Adrian Lopez Guerrero
\date 6/4/2017
\version 1.0
*/

// Para comprobar las pre y post-condiciones
#include <cassert>

#include "ListaDoblementeEnlazadaOrdenadaMunicipios.hpp"
#include "NodoMunicipioInterfaz.hpp"
#include "Municipio.hpp"

int ed::ListaDoblementeEnlazadaOrdenadaMunicipios::nItems() const{

  if(this->isEmpty() == true){
    return 0;
  }
  else{
    int contador = 1;
    ed::NodoDoblementeEnlazadoMunicipio *aux=NULL;

    aux = this->getHead();

    while(aux->getNext() != NULL){
      contador++;
      aux = aux->getNext();
    }

    return contador;
  }
}

bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::isFirstItem() const{

  #ifndef NDEBUG
  assert(this->isEmpty() == false);
  #endif

  if(this->getCurrent() == this->getHead()){
    return true;
  }
  else{
    return false;
  }
}

bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::isLastItem() const{

  #ifndef NDEBUG
  assert(this->isEmpty() == false);
  #endif

  if(this->getCurrent()->getNext() == NULL){
    return true;
  }
  else{

    return false;
  }
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoHead(){
  #ifndef NDEBUG
  assert(this->isEmpty() == false);
  #endif

  this->setCurrent(this->getHead());

  #ifndef NDEBUG
  assert(this->isFirstItem() == true);
  #endif
}


void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoLast(){
  #ifndef NDEBUG
  assert(this->isEmpty() == false);
  #endif

  while(this->isLastItem() == false){
    this->setCurrent(this->getCurrent()->getNext());
  }

  #ifndef NDEBUG
  assert(this->isLastItem() == true);
  #endif
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoPrevious(){
  #ifndef NDEBUG
  assert((this->isEmpty() == false) &&
         (this->isFirstItem() == false));
  #endif

  this->setCurrent(this->getCurrent()->getPrevious());
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoNext(){
  #ifndef NDEBUG
  assert((this->isEmpty() == false));
  #endif

  #ifndef NDEBUG
  assert((this->isLastItem() == false));
  #endif

  this->setCurrent(this->getCurrent()->getNext());
}


bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::find(ed::Municipio const & item){

  bool valorDevuelto=false;

  if(this->isEmpty() == true){
    return false;
  }
  else{
    this->gotoHead();

    if(this->nItems() == 1){
      if(this->getCurrentItem()==item){
        valorDevuelto=true;
      }
      else{
        valorDevuelto=false;
      }
    }

    else{

      this->gotoHead();

      // ESTE BUCLE WHILE NO RECORRE EL ULTIMO ELEMENTO,
      while(this->isLastItem() == false){
        if(this->getCurrentItem()==item){
          valorDevuelto=true;
          break;
        }
        else{
          if(item < this->getCurrentItem()){
            break;
          }
          this->gotoNext();
        }
      }

      // COMPARA CON EL ULTIMO
      if(this->getCurrentItem()==item){
        valorDevuelto=true;
      }
    }
  }

  if(valorDevuelto == true){
    #ifndef NDEBUG
    // Se comprueba la postcondicion
    assert(this->getCurrentItem() == item);
    #endif //NDEBUG

    return valorDevuelto;
  }

  else{

    #ifndef NDEBUG
    // Se comprueba la postcondicion
    assert(item < this->getCurrentItem() ||
          (this->isLastItem() == true));
    #endif //NDEBUG

    return valorDevuelto;
  }

}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::insert(ed::Municipio const & item){
  #ifndef NDEBUG
  assert(this->find(item) == false);
  #endif

  int oldnumeromunicipios=this->nItems();

  ed::NodoDoblementeEnlazadoMunicipio *aux;
  aux = new NodoDoblementeEnlazadoMunicipio(item,NULL,NULL);

  if(this->isEmpty() == true){  // CASO 0: No hay ningun elemento en la lista

    aux->setPrevious(NULL);
    aux->setNext(NULL);
    this->setHead(aux);
    this->setCurrent(aux);

  }
  else if(this->nItems() == 1){ // CASO 1: Solo hay un elemento en la lista.
    if(item < this->getCurrentItem()){    // CASO 1.1: item es menor que el elemento que esta en cabeza.
      this->setHead(aux);
      this->getHead()->setNext(this->getCurrent());
      this->getHead()->setPrevious(NULL);
      this->getCurrent()->setPrevious(this->getHead());

      this->setCurrent(this->getHead());

    }
    else{ // CASO 1.2: item es mayor que el elemento que esta en cabeza.
      this->getCurrent()->setNext(aux);
      aux->setNext(NULL);
      aux->setPrevious(this->getHead());

      this->setCurrent(aux);

    }
  }
  else{ // CASO 2: Hay dos o mas elementos.

    this->gotoHead();

    while(this->isLastItem() == false){

      if(item < this->getCurrentItem()){
        if(this->isFirstItem() == true){  // CASO 2.1: item es menor que el current y el current es la cabeza.

          aux->setPrevious(NULL);
          aux->setNext(this->getHead());
          this->setHead(aux);
          this->getCurrent()->setPrevious(this->getHead());

          this->setCurrent(this->getHead());

          #ifndef NDEBUG
          assert((this->getCurrentItem() == item));
          #endif

          #ifndef NDEBUG
          assert((this->nItems() == oldnumeromunicipios+1));
          #endif

          return;
        }
        else{   // CASO 2.2: item es menor que el current y current se encuentra en cualquier posicion de la fila
          aux->setPrevious(this->getCurrent()->getPrevious());
          aux->setNext(this->getCurrent());

          this->getCurrent()->getPrevious()->setNext(aux);
          this->getCurrent()->setPrevious(aux);

          this->setCurrent(aux);

          #ifndef NDEBUG
          assert((this->getCurrentItem() == item));
          #endif

          #ifndef NDEBUG
          assert((this->nItems() == oldnumeromunicipios+1));
          #endif

          return;
        }
      }

      this->gotoNext();
    }

    if(item < this->getCurrentItem()){    // CASO 2.3
      aux->setPrevious(this->getCurrent()->getPrevious());
      aux->setNext(this->getCurrent());

      this->getCurrent()->getPrevious()->setNext(aux);
      this->getCurrent()->setPrevious(aux);

      this->setCurrent(aux);

    }
    else{ // CASO 3: item es mayor que todos los elementos de la lista (se pone al final de la lista)
      this->getCurrent()->setNext(aux);

      aux->setPrevious(this->getCurrent());
      aux->setNext(NULL);

      this->setCurrent(aux);

    }
  }

  #ifndef NDEBUG
  assert((this->getCurrentItem() == item));
  #endif

  #ifndef NDEBUG
  assert((this->nItems() == oldnumeromunicipios+1));
  #endif
}



void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::remove(){
  #ifndef NDEBUG
  assert(this->isEmpty() == false);
  #endif

  int oldnumeromunicipios=this->nItems();

  if(this->nItems() == 1){ // CASO 0: Solo hay un nodo.
    delete this->getCurrent();
    this->setCurrent(NULL);
    this->setHead(NULL);


    #ifndef NDEBUG
    assert((this->nItems() == oldnumeromunicipios-1) &&
           (this->isEmpty() == true));
    #endif
  }

  else if(this->nItems() == 2){ // CASO 1: Existen dos municipios dentro de la lista.
    if(this->isFirstItem() == true){  // CASO 1.1: El current esta en la primera posicion (se borra el head)

      ed::NodoDoblementeEnlazadoMunicipio *aux;
      aux = new NodoDoblementeEnlazadoMunicipio(this->getCurrentItem(),this->getCurrent()->getPrevious(),this->getCurrent()->getNext());

      this->setHead(this->getCurrent()->getNext());
      this->getHead()->setPrevious(NULL);
      delete this->getCurrent();

      this->setCurrent(this->getHead());

      #ifndef NDEBUG
      assert((this->nItems() == oldnumeromunicipios-1) &&
             (this->isFirstItem() == true) &&
             (aux->getNext()->getItem() == this->getCurrentItem()));
      #endif
    }
    else{ // CASO 1.2: El current estaba al final (se borra el ultimo elemento, no se toca la cabeza)

      ed::NodoDoblementeEnlazadoMunicipio *aux;
      aux = new NodoDoblementeEnlazadoMunicipio(this->getCurrentItem(),this->getCurrent()->getPrevious(),this->getCurrent()->getNext());

      this->getHead()->setNext(NULL);
      delete this->getCurrent();

      this->setCurrent(this->getHead());



      #ifndef NDEBUG
      assert((this->nItems() == oldnumeromunicipios-1) &&
             (this->isLastItem() == true) &&
             (aux->getPrevious()->getItem() == this->getCurrentItem()));
      #endif


    }
  }
  else{ // CASO 2: Existen mas de dos nodos dentro de la lista.
    if(this->isFirstItem() == true){  // CASO 2.1: El current esta en la cabeza
      ed::NodoDoblementeEnlazadoMunicipio *aux;
      aux = new NodoDoblementeEnlazadoMunicipio(this->getCurrentItem(),this->getCurrent()->getPrevious(),this->getCurrent()->getNext());


      this->setHead(this->getCurrent()->getNext());
      this->getHead()->setPrevious(NULL);
      delete this->getCurrent();

      this->setCurrent(this->getHead());



      #ifndef NDEBUG
      assert((this->nItems() == oldnumeromunicipios-1) &&
             (this->isFirstItem() == true) &&
             (aux->getNext()->getItem() == this->getCurrentItem()));
      #endif
    }
    else if(this->isLastItem() == true){  // CASO 2.2: El current esta al final
      ed::NodoDoblementeEnlazadoMunicipio *aux;
      aux = new NodoDoblementeEnlazadoMunicipio(this->getCurrentItem(),this->getCurrent()->getPrevious(),this->getCurrent()->getNext());


      this->setCurrent(this->getCurrent()->getPrevious());
      delete this->getCurrent()->getNext();
      this->getCurrent()->setNext(NULL);



      #ifndef NDEBUG
      assert((this->nItems() == oldnumeromunicipios-1) &&
             (this->isLastItem() == true) &&
             (aux->getPrevious()->getItem() == this->getCurrentItem()));
      #endif
    }
    else{ // CASO 2.3: El current esta en cualquier posicion.
      ed::NodoDoblementeEnlazadoMunicipio *aux;
      aux = new NodoDoblementeEnlazadoMunicipio(this->getCurrentItem(),this->getCurrent()->getPrevious(),this->getCurrent()->getNext());

      this->getCurrent()->getPrevious()->setNext(aux->getNext());

      this->getCurrent()->getNext()->setPrevious(aux->getPrevious());

      this->setCurrent(aux->getNext());

      #ifndef NDEBUG
      assert((this->nItems() == oldnumeromunicipios-1));
      #endif

      #ifndef NDEBUG
      assert((aux->getPrevious()->getItem() == this->getPreviousItem()));
      #endif

      #ifndef NDEBUG
      assert((aux->getNext()->getItem() == this->getCurrentItem()));
      #endif
    }
  }
}


void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::removeAll(){

  if(this->isEmpty() == true){
    return;
  }

  while(this->getCurrent() != NULL){
    this->remove();
  }

  #ifndef NDEBUG
  assert(this->isEmpty() == true);
  #endif
}
