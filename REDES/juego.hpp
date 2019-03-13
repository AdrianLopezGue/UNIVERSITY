#ifndef JUEGO_HPP_
#define JUEGO_HPP_

#include "Jugador.hpp"
#include "tablero.hpp"

#include <string>
#include <cstdlib>
#include <sstream> //for using ostringstream

class juego{

private:
  Jugador _jugador1;
  Jugador _jugador2;
  int _banderasJ1;
  int _banderasJ2;

  int _turno;  // turno=1 ----> juega jugador 1; turno=2 ----> juega jugador 2

  Tablero _tablero;

public:

  juego(Jugador j1, Jugador j2, Tablero tablero): _jugador1(j1), _jugador2(j2), _tablero(tablero){

    _turno = 1;
    _banderasJ1 = 0;
    _banderasJ2 = 0;


  };

  char* getBoard(){

    char *cadena=new char[500];
    char *cadenaAux=new char[15];
    int contador = 0;

    cadena[0]=' ';
    cadena[1]=' ';
    cadena[2]='1';
    cadena[3]=' ';
    cadena[4]='2';
    cadena[5]=' ';
    cadena[6]='3';
    cadena[7]=' ';
    cadena[8]='4';
    cadena[9]=' ';
    cadena[10]='5';
    cadena[11]=' ';
    cadena[12]='6';
    cadena[13]=' ';
    cadena[14]='7';
    cadena[15]=' ';
    cadena[16]='8';
    cadena[17]=' ';
    cadena[18]='9';
    cadena[19]=' ';
    cadena[20]='1';
    cadena[21]='0';
    cadena[22]='\n';
    contador=23;

    cadenaAux[0]='A';
    cadenaAux[1]='B';
    cadenaAux[2]='C';
    cadenaAux[3]='D';
    cadenaAux[4]='E';
    cadenaAux[5]='F';
    cadenaAux[6]='G';
    cadenaAux[7]='H';
    cadenaAux[8]='I';
    cadenaAux[9]='J';

    for(unsigned int i=0; i<_tablero.getPCBoard().size(); i++){

      cadena[contador]=cadenaAux[i];
      contador++;
      cadena[contador]=' ';
      contador++;
      for(unsigned int j=0; j<_tablero.getPCBoard().size(); j++){
        cadena[contador]=_tablero.getPCBoard()[i][j];
        contador++;
        cadena[contador]=' ';
        contador++;
      }
      cadena[contador]='\n';
      contador++;
    }

    return cadena;
  }

  Jugador getJugador1()const{
    return _jugador1;
  }

  Jugador getJugador2()const{
    return _jugador2;
  }

  int getBanderas1()const{
    return _banderasJ1;
  }

  int getBanderas2()const{
    return _banderasJ2;
  }

  int getTurno()const{
    return _turno;
  }

  void setTurno(int turno){
    _turno = turno;
  }

  Tablero getTablero()const{
    return _tablero;
  }

  void setTablero(Tablero tablero){
    _tablero = tablero;
  }

  void aumentarBandera(int turno){
    if(turno == 1){
      _banderasJ1++;
    }
    else{
      _banderasJ2++;
    }
  }

  void decrementarBandera(int turno){
    if(turno == 1){
      _banderasJ1--;
    }
    else{
      _banderasJ2--;
    }
  }

  void cambiarTurno(){
    if( getTurno() == 1 ){
      _turno = 2;
      return;
    }
    if( getTurno() == 2 ){
      _turno = 1;
      return;
    }
    return;
  }

};

#endif
