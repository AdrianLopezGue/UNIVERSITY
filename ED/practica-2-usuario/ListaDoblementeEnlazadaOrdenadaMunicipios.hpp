/*!
\file   ListaDoblementeEnlazadaOrdenadaMunicipios.hpp
\brief  Clase de una lista doblemente enlazada y ordenada de Municipios
\author Adrian Lopez Guerrero
\date 6/4/2017
\version 1.0

*/

#ifndef __ListaDoblementeEnlazadaOrdenadaMunicipios_HPP__
#define __ListaDoblementeEnlazadaOrdenadaMunicipios_HPP__

// Para comprobar las pre y post-condiciones
#include <cassert>

#include "ListaOrdenadaMunicipiosInterfaz.hpp"

#include "NodoDoblementeEnlazadoMunicipio.hpp"

#include "Municipio.hpp"

/*!
\namespace ed
\brief Espacio de nombres para la asignatura Estructuras de Datos

*/
namespace ed {

  /*!
  \class ListaDoblementeEnlazadaOrdenadaMunicipios
  \brief Definición de la clase ListaDoblementeEnlazadaOrdenadaMunicipios
  \n Lista doblemente enlazada de nodos de municipios ordenados alfabéticamente de forma ascendente
  */
  class ListaDoblementeEnlazadaOrdenadaMunicipios: public ed::ListaOrdenadaMunicipiosInterfaz
  {
    //! \name  Atributos y métodos privados

  private:

    ed::NodoDoblementeEnlazadoMunicipio *_head;    //!< \brief puntero al primer nodo de la lista
    ed::NodoDoblementeEnlazadoMunicipio *_current; //!< \brief puntero al nodo current de la lista

    // \name Observadores privados
    /*!
    \brief     Getter de la variable cabeza
    \note      Función inline
    \pre       Ninguna
    \post      Ninguna
    */
    inline ed::NodoDoblementeEnlazadoMunicipio * getHead() const{return this->_head;}

    /*!
    \brief     Getter de la variable current
    \note      Función inline
    \pre       Ninguna
    \post      Ninguna
    */
    inline ed::NodoDoblementeEnlazadoMunicipio * getCurrent() const{return this->_current;}

    //! \name Modificadores privados
    /*!
    \brief     Setter de la variable cabeza
    \note      Función inline
    \pre       Ninguna
    \post      getHead() == head
    \sa        getHead()
    */

    inline void setHead(ed::NodoDoblementeEnlazadoMunicipio *head){
      this->_head = head;

      #ifndef NDEBUG
      assert(this->getHead() == head);
      #endif //NDEBUG
    }

    /*!
    \brief     Setter de la variable current
    \note      Función inline
    \pre       Ninguna
    \post      getCurrent() == current
    \sa        getCurrent()
    */

    inline void setCurrent(ed::NodoDoblementeEnlazadoMunicipio *current){
      this->_current = current;

      #ifndef NDEBUG
      assert(this->getCurrent() == current);
      #endif //NDEBUG
    }


    //! \name  Métodos públicos

  public:

    //! \name Constructores

    /*!
    \brief Construye una lista vacía
    \note  Función inline
    \post  isEmpty() == true
    */
    inline ListaDoblementeEnlazadaOrdenadaMunicipios(){
      ed::NodoDoblementeEnlazadoMunicipio *aux=NULL;

      this->setHead(aux);
      this->setCurrent(aux);

      #ifndef NDEBUG
      assert(this->isEmpty() == true);
      #endif
    }

    //! \name Destructor

    /*!
    \brief Destruye una lista liberando la memoria de sus nodos
    \note Función codificada en el fichero cpp
    \post isEmpty() == true
    */

    ~ListaDoblementeEnlazadaOrdenadaMunicipios (){
      this->removeAll();

      #ifndef NDEBUG
      assert(this->isEmpty() == true);
      #endif
    }


    //! \name Observadores públicos

    /*!
    \brief  Comprueba si la lista está vacía
    \note   Función inline
    \note   Función de tipo "const": no puede modificar al objeto actual
    \return true, si la lista está vacía; false, en caso contrario
    */
    inline bool isEmpty() const{

      if((this->getHead() != NULL) &&
         (this->getCurrent() != NULL)){
        return false;
      }

      else{
        return true;
      }
    }

    /*!
    \brief  Devuelve el número de elementos o ítems de la lista
    \attention Función sobrecargada
    \note   Función de tipo "const": no puede modificar al objeto actual
    \return Número entero que representa el número de elementos o ítems de la lista
    \sa isEmpty(), getHead(), getNext()
    */

    int nItems() const;

    /*!
    \brief  Comprueba si el cursor está en el primer Municipio
    \attention Función sobrecargada
    \note   Función de tipo "const": no puede modificar al objeto actual
    \pre    La lista no está vacía
    \return Verdadero, si el cursor está situado en la cabeza; falso en caso contrario
    \sa isEmpty(), getCurrent(), getHead()
    */

    bool isFirstItem() const;

    /*!
    \brief  Comprueba si el cursor está en el último Municipio
    \attention Función sobrecargada
    \note   Función de tipo "const": no puede modificar al objeto actual
    \pre    La lista no está vacía
    \return true, si el cursor está situado al final de la lista; false, en caso contrario
    \sa isEmpty(), getCurrent(), getNext()
    */

    bool isLastItem() const;

    /*!
    \brief  Devuelve el Municipio situado en el campo informativo indicado por el cursor
    \attention Función sobrecargada
    \note   Función de tipo "const": no puede modificar al objeto actual
    \pre    La lista no está vacía
    \return Una referencia constante al municipio indicado por el cursor
    \sa isEmpty(), getCurrent(), getItem()
    */

    inline Municipio const & getCurrentItem() const{

      #ifndef NDEBUG
      assert(this->isEmpty() == false);
      #endif

      return this->getCurrent()->getItem();
    }

    /*!
    \brief  Devuelve el Municipio situado en el campo informativo anterior
    \attention Función sobrecargada
    \note   Función de tipo "const": no puede modificar al objeto actual
    \pre    La lista no está vacía
    \pre    El cursor no está situado en el primer nodo
    \return Una referencia al municipio situado en el nodo previo al indicado por el cursor
    \sa isEmpty(), isFirstItem(),, getCurrent(), getPrevious(), getItem()
    */

    inline Municipio const & getPreviousItem() const{
      #ifndef NDEBUG
      assert((this->isEmpty() == false) &&
             (this->isFirstItem() == false));
      #endif

      ed::NodoDoblementeEnlazadoMunicipio *aux=NULL;
      aux = this->getCurrent()->getPrevious();

      return aux->getItem();
    }

    /*!
    \brief  Devuelve el Municipio situado en el campo informativo posterior
    \attention Función sobrecargada
    \note   Función de tipo "const": no puede modificar al objeto actual
    \pre    La lista no está vacía
    \pre 	El cursor no está situado en el último nodo
    \return Una referencia al municipio situado en el nodo siguiente al indicado por el cursor
    \sa isEmpty(), isLastItem(), getCurrent(), getNext(), getItem()
    */

    inline Municipio const & getNextItem() const{
      #ifndef NDEBUG
      assert((this->isEmpty() == false) &&
             (this->isLastItem() == false));
      #endif

      ed::NodoDoblementeEnlazadoMunicipio *aux=NULL;
      aux = this->getCurrent()->getNext();

      return aux->getItem();
    }

    //! \name Modificadores públicos

    /*!
    \brief  Coloca el cursor en la primera posición de la lista
    \attention Función sobrecargada
    \pre    La lista no está vacía
    \post   El ítem actual es el primero: isFirstItem() == true
    \return void
    \sa		gotoLast(), gotoPrevious(), gotoNext()
    */

    void gotoHead();

    /*!
    \brief  Coloca el cursor en la última posición de la lista
    \attention Función sobrecargada
    \pre    La lista no está vacía
    \post   El ítem actual es el último:  isLastItem() == true
    \return void
    \sa		gotoHead(), gotoPrevious(), gotoNext()
    */

    void gotoLast();

    /*!
    \brief  Coloca el cursor en la posición anterior de la lista
    \attention Función sobrecargada
    \pre    La lista no está vacía
    \pre    El ítem actual no es el primero: isFirstItem() == false
    \post   Ninguna
    \return void
    \sa		gotoHead(), gotoLast(), gotoNext()
    */

    void gotoPrevious();

    /*!
    \brief  Coloca el cursor en la posición siguiente de la lista
    \attention Función sobrecargada
    \pre    La lista no está vacía
    \pre    El ítem actual no es el último: isLastItem() == false
    \post   Ninguna
    \return void
    \sa		gotoHead(), gotoLast(), gotoPrevious()
    */

    void gotoNext();

    /*!
    \brief  Coloca el cursor en el nodo que contiene al municipio en su campo informativo, si existe;
    \attention Función sobrecargada
    \param  item: municipio buscado; referencia constante de la clase Municipio
    \post   retVal==true implica que getCurrentItem() == item
    \post   retVal==false implica que getCurrentItem > item o isLastItem() == true
    \return true, si el municipio está en la lista; false, en caso contrario
    */

    bool find(Municipio const & item);

    /*!
    \brief Inserta un Municipio de forma ordenada por apellidos y nombre
    \attention Función sobrecargada
    \param item: objeto de la clase Municipio que va a ser insertado; referencia constante de la clase Municipio
    \pre   find(item) == false
    \post  getCurrentItem() == item
    \sa    remove()
    */

    void insert(Municipio const & item);

    /*!
    \brief Borra el municipio indicado por el cursor
    \attention Función sobrecargada
    \pre   La lista no está vacía: isEmpty()== false
    \post  El número de municipios se reduce en uno
    \n nItems()==old.nItems()-1
    \post  Si old.isFirstItem()==falso y  old.isLastItem()==falso
    entonces old.getPreviousItem()== getPreviousItem() y old.getNextItem()==getCurrentItem()
    \post  Si old.lastItem()==verdadero entonces
    isEmpty()==verdadero
    o old.getPreviousItem()==getCurrentItem() y isLastItem()==verdadero
    \post  Si old.isFirstItem()==verdadero entonces
    isEmpty()==verdadero o old.getNextItem()==getCurrentItem() y isFirstItem()==verdadero
    \sa    insert()
    */

    void remove();

    /*!
    \brief     Borrar todos los municipios de la lista
    \pre       La lista debe de tener al menos una provincia.
    \post      La lista debe estar vacia.
    \sa        isEmpty(), getCurrent(), isEmpty()
    */

    void removeAll();

  }; // Fin de la clase ListaDoblementeEnlazadaOrdenadaMunicipios

} //namespace ed

#endif // __ListaDoblementeEnlazadaOrdenadaMunicipios_HPP__
