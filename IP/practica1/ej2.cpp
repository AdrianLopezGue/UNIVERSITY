#include <iostream>
#include <cstdio>

#include <cstdlib>
using namespace std;
int main(){

	float angulo_grados,angulo_radianes;
	cout<<"Introduza el angulo en grados"<<endl;
	cin>>angulo_grados;
	angulo_radianes= (3.14159*angulo_grados) / 360.;
	cout<<"El angulo en radianes es "<<angulo_radianes<<endl;
	system("pause");
}
