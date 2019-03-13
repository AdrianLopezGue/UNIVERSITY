//juego.cc
//a program that simulates the throw of two dices 
#include <iostream>
#include <cstdlib>
#include "dados.h"
using namespace std;

int main(void)
{
	Dados d;
	int x,d1,d2;
	cout<<"Se efectuará el lanzamiento de dos dados"<<endl;
	cout<<"Dado 1: "<<d.getDado1()<<endl;
	cout<<"Dado 2: "<<d.getDado2()<<endl;
	cout<<"Suma de los dados: "<<d.getSuma()<<endl;
	cout<<"\nSi desea cambiar el valor de los dados pulse 1, sino cualquier tecla."<<endl;
	cin>>x;
	if(confirmar(x)==false)
	{
		exit(-1);
	}
	else
	{
		cout<<"Introduzca el nuevo valor del dado 1: ";
		cin>>d1;
		d.setDado1(d1);
		cout<<"Introduzca el nuevo valor del dado 2: ";
		cin>>d2;
		d.setDado2(d2);
		cout<<"Nuevo valor dado 1: "<<d.getDado1()<<endl;
		cout<<"Nuevo valor dado 2: "<<d.getDado2()<<endl;
		cout<<"Suma de los dados: "<<d.getSuma()<<endl;

	}

}	