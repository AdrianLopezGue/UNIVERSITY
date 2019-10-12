#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;
int main(){
	int dia;
	cout<<"Indique el dia"<<endl;
	cin>>dia;
	if ( (dia>=1) && (dia<=7) ){
		
			if (dia==1){
				cout<<"LUNES"<<endl;
			}
			if (dia==2){
				cout<<"MARTES"<<endl;
			}
			if (dia==3){
				cout<<"MIERCOLES"<<endl;
			}
			if (dia==4){
				cout<<"JUEVES"<<endl;
			}
			if (dia==5){
				cout<<"VIERNES"<<endl;
			}
			if (dia==6){
				cout<<"SABADO"<<endl;
			}
			if (dia==7){
				cout<<"DOMINGO"<<endl;
			}
			
	}
	else{
			cout<<"Dia incorrecto"<<endl;
	}
	system("pause");
		
 
}
