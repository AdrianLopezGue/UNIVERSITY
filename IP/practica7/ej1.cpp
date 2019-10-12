#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int longitud(char cad[]){
char s= '\0';
int j = 0;
	for(int i = 0;	cad[i] != s; i++){
		j++;
		}
	return j;
}
		
int main(){
char nombre[100];
cin>>nombre;

cout<<longitud(nombre)<<endl;
    system("pause");
}

