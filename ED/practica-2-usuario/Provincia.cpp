/*!

\file  Provincia.cpp
\brief Definición de la clase Provincia
\author Adrian Lopez Guerrero
\date 6/4/2017
\version 1.0

*/
//Para los flujos de entrada/salida en ficheros.
#include <fstream>
#include <iostream>
#include <stdlib.h>

// Para comprobar las pre y post condiciones
#include <cassert>

#include "Provincia.hpp"


///////////////////////////////////////////////////////////////////////////////

// OSBSERVADORES

int ed::Provincia::getTotalHombres(){
  if(this->getNumeroMunicipios() == 0){
    return 0;
  }
  else{
    int numerohombres = 0;
    int i = 0;

    this->_listaMunicipios.gotoHead();

    while(i < this->getNumeroMunicipios()){
      numerohombres += this->_listaMunicipios.getCurrentItem().getHombres();

      i++;
      this->_listaMunicipios.gotoNext();
    }

    return numerohombres;
  }
}

int ed::Provincia::getTotalMujeres(){
  if(this->getNumeroMunicipios() == 0){
    return 0;
  }
  else{
    int numeromujeres = 0;
    int i = 0;

    this->_listaMunicipios.gotoHead();

    while(i < this->_listaMunicipios.nItems()){
      numeromujeres += this->_listaMunicipios.getCurrentItem().getMujeres();

      i++;
      this->_listaMunicipios.gotoNext();
    }

    return numeromujeres;
  }
}

int ed::Provincia::getTotalHabitantes(){
  int valorDevuelto = this->getTotalHombres() + this->getTotalMujeres();

  #ifndef NDEBUG
  assert(valorDevuelto == this->getTotalHombres() + this->getTotalMujeres());
  #endif

  return valorDevuelto;
}

/////////////////////////////////////////////////////////////////////////////////////////

// MODIFICADORES

void ed::Provincia::insertarMunicipio(Municipio municipio){

  #ifndef NDEBUG
  assert(this->existeMunicipio(municipio.getNombre()) == false);
  #endif

  int oldnumeromunicipios = this->getNumeroMunicipios();
  this->_listaMunicipios.insert(municipio);

  #ifndef NDEBUG
  assert((this->existeMunicipio(municipio.getNombre()) == true));
  #endif

  #ifndef NDEBUG
  assert((this->getNumeroMunicipios() == oldnumeromunicipios+1));
  #endif
}

void ed::Provincia::borrarMunicipio(std::string nombre){
  #ifndef NDEBUG
  assert(this->existeMunicipio(nombre) == true);
  #endif

  if(this->existeMunicipio(nombre) == true){

    int oldnumeromunicipios = this->getNumeroMunicipios();
    this->_listaMunicipios.remove();

    #ifndef NDEBUG
    assert((this->existeMunicipio(nombre) == false) &&
           (this->getNumeroMunicipios() == oldnumeromunicipios-1));
    #endif
  }
}

void ed::Provincia::borrarTodosLosMunicipios(){

  if(this->_listaMunicipios.isEmpty()){
    std::cout<<"La lista esta vacia, no se puede borrar.\n";
  }
  else{
    this->_listaMunicipios.removeAll();
  }

  #ifndef NDEBUG
  assert(this->hayMunicipios() == false);
  #endif
}

///////////////////////////////////////////////////////////////////////////////////

// FUNCIÓN DE ESCRITURA

void ed::Provincia::escribirMunicipios(){


  if(this->_listaMunicipios.isEmpty() == true){
    std::cout<<"La lista esta vacia, no se puede recorrer\n";

    return;
  }

  this->_listaMunicipios.gotoHead();

  for(int i=0; i < this->getNumeroMunicipios(); i++){

    this->_listaMunicipios.getCurrentItem().escribirMunicipio();

    if(this->_listaMunicipios.isLastItem() == false){
      this->_listaMunicipios.gotoNext();
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////

// OPERACIONES CON FICHEROS

bool ed::Provincia::cargarFichero(std::string nombre){

  std::ifstream fichero(nombre.c_str());
  char cadenaaux[256];

  ed::Municipio municipioaux("", -1, -1, -1);

  if(fichero){

    this->borrarTodosLosMunicipios();

    // CODIGO
    fichero.getline(cadenaaux, 256, ' ');
    this->setCodigo(atoi(cadenaaux));

    // NOMBRE DE LA PROVINCIA
    fichero.getline(cadenaaux, 256, '\n');
    std::string str(cadenaaux);
    this->setNombre(str);

    while(fichero>>municipioaux){

      this->insertarMunicipio(municipioaux);
    }

    fichero.close();

    return true;
  }

  else{
    std::cout<<"ERROR: No se ha podido abrir el fichero correctamente.\n";

    return false;
  }
}


bool ed::Provincia::grabarFichero(std::string nombre){

  if(_listaMunicipios.isEmpty() == true){
    std::cout<<"La lista esta vacia, no se puede grabar.\n";
    return false;
  }

  std::ofstream fichero(nombre.c_str());

  if(fichero){

    fichero<<this->getCodigo()<<" "<<this->getNombre()<<"\n";

    this->_listaMunicipios.gotoHead();
    int i = 0;

    while(i < this->getNumeroMunicipios()){

      fichero<<this->_listaMunicipios.getCurrentItem()<<"\n";
      i++;

      if(this->_listaMunicipios.isLastItem() == false){
        this->_listaMunicipios.gotoNext();
      }
    }
    return true;
  }

  else{
    std::cout<<"ERROR: No se ha podido abrir el fichero correctamente.\n";

    return false;
  }

}
