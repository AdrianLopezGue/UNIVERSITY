#ifndef JUGADOR_HPP_
#define JUGADOR_HPP_

#include <string>

class Jugador{
private:
  std::string _nombre;
  int _estado;
  //estado == -1 --> Estado error
  //estado == 0 --> Acaba de hacer USUARIO %s y va a introducir la contraseña
  //estado == 1 --> (logueado)Esta esperando a otro jugador para iniciar partida
  //estado == 2 --> Dentro de una partida

  int _identificador;   // identificador del usuario en el servidor

public:

  //Jugador();

  Jugador(int i, std::string nombre){
    _identificador=i;
    _nombre = nombre;
    setEstado(0);
  }

  void setEstado(int estado){
    _estado = estado;
  }

  int getEstado()const{
    return _estado;
  }

  int getIdentificador()const{
  	return _identificador;
  }

  std::string getNombre()const{
  	return _nombre;
  }

  void setIdentificador(int identificador){
  	_identificador = identificador;
  }

  void operator=(const Jugador &aux){
  	_nombre = aux.getNombre();
  	_estado = aux.getEstado();
  	_identificador = aux.getIdentificador();
  }


};

#endif
