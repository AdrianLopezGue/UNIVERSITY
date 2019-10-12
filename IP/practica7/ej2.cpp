#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

void copia(char cad1[],char cad2[]){
	
for (int i = 0; i<100; i++){
	cad2[i] = cad1[i];
}
}

int main(){

char cad1[100], cad2[100];

cin.getline(cad1,100);



copia(cad1,cad2);
cout<<"Cad 2 es : "<<cad2<<endl;
    system("pause");
}

