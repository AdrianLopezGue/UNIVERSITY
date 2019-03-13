//dados.cc

#include "dados.h"
#include <ctime>
#include <cstdlib>
#include <cstdio>

Dados::Dados()
{
	d1_=1;
	d2_=1;
	numlanzamientos1 = 0;
	numlanzamientos2 = 0;
	suma1 = 0;
	suma2 = 0;

	for(int i = 0; i<5;i++){
		lanzamientos1[i] = 0;
		lanzamientos2[i] = 0;
	}

	srand(time(NULL));
}

void Dados:: lanzamiento()
{
	int dado1, dado2;

	dado1 = rand()%6+1;
	setDado1(dado1);
	numlanzamientos1++;
	suma1 += getDado1();

	dado2 = rand()%6+1;
	setDado2(dado2);
	numlanzamientos2++;
	suma2 += getDado2();
}


bool Dados:: setDado1(int x)
{
	if(x<1||x>6)
	{
		return false;
	}

	d1_=x;
	addlanzamiento1(x);
	suma1 += getDado1();

	numlanzamientos1++;
	return true;
}

bool Dados:: setDado2(int x)
{
	if(x<1||x>6)
	{
		return false;
	}

	d2_=x;
	addlanzamiento2(x);
	suma2 += getDado2();
	numlanzamientos2++;

	return true;
}

int Dados:: getDiferencia(){
	if(d1_ == d2_){
		return 0;
	}

	else{
		if(d1_ > d2_){
			return d1_ - d2_;
		}
		else{
			return d2_ - d1_;
		}
	}
}


float Dados:: getMedia1(){
float resultado;
	if(numlanzamientos1 == 0){
		return 0;
	}
	else{
		resultado = (float)suma1/(float)numlanzamientos1;

		return resultado;
	}
}

float Dados:: getMedia2(){
float resultado;
	if(numlanzamientos2 == 0){
		return 0;
	}
	else{
		resultado = (float)suma2/(float)numlanzamientos2;

		return resultado;
	}
}

void Dados:: addlanzamiento1(int num){

	for(int i=4;i>=1;i--){
		lanzamientos1[i] = lanzamientos1[i-1];
	}

	lanzamientos1[0] = num;
}

void Dados:: addlanzamiento2(int num){

	for(int i=4;i>=1;i--){
		lanzamientos2[i] = lanzamientos2[i-1];
	}

	lanzamientos2[0] = num;
}
