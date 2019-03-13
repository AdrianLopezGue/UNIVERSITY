//dados.h
//we create the class "Dados"
#ifndef DADOS_H
#define DADOS_H

class Dados
{
private:
	int d1_;
	int d2_;
	int numlanzamientos1;
	int numlanzamientos2;
	int suma1;
	int suma2;

	int lanzamientos1[5];
	int lanzamientos2[5];
public:
	Dados();
	void lanzamiento();

	int getDado1(){return d1;};
	bool setDado1(int x);

	int getDado2(){return d2_;};
	bool setDado2(int x);

	int getSuma(){return d1_+d2_;};
	int getSuma1(){return suma1;}
	int getSuma2(){return suma2;}

	int getDiferencia();

	int getLanzamientos1(){return numlanzamientos1;};
	void addlanzamiento1(int num);

	int getLanzamientos2(){return numlanzamientos2;};
	void addlanzamiento2(int num);

	float getMedia1();
	float getMedia2();

	void getUltimos1(int v[]){for(int i=0; i<5;i++)v[i] = lanzamientos1[i];};
	void getUltimos2(int v[]){for(int i=0; i<5;i++)v[i] = lanzamientos2[i];};

};


#endif
