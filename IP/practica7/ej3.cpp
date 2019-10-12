#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

bool iguales(char cad1[], char cad2[]){
int s = strlen(cad1);
	for(int i = 0; i<s; i++){
		if(cad1[i]!=cad2[i]){
			return false;	
		}
	}
return true;
}
 
int main(){
char cad1[100],cad2[100];

cin.getline(cad1, 100);
cin.getline(cad2, 100);

if(iguales(cad1, cad2)== true){
	cout<<"iguales"<<endl;
}
else{
cout<<"no jeje"<<endl;
}


    system("pause");
}

