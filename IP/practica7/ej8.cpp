#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

int espacios(string cad){
int s=cad.size(), j=0;	
	for(int i = 0; i<s; i++){
		if(cad[i]==32){	
			j++;	
		}	
	}
return j;
}
int main(){
string nombre;

getline(cin, nombre);

cout<<"Numero: "<<espacios(nombre)<<endl;

    system("pause");
}

