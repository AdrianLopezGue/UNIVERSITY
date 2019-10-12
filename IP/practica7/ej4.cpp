#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;
void replace(char cad[], char a, char b){
int s = strlen(cad);	
for(int i = 0; i<s; i++){
	if(cad[i]==a){
		cad[i]=b;
	}
}
}
int main(){
char cad[100] ;
char a = 'a';
char b = 'b';

cin.getline(cad,100);
replace(cad, a , b);

cout<<"Ahora la frase es: "<< cad<<endl;
    system("pause");
}

