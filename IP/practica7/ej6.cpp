#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

void convierte(char cad[]){
int s = strlen(cad);
	for(int i=0 ; i<s; i++){
	cad[i] = toupper(cad[i]);
	}
}

int main(){
char cad[100];
cin.getline(cad,100);

convierte(cad);
cout<<"Ahora la frase es: "<<cad<<endl;
    system("pause");
}

