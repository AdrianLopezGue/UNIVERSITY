#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

bool palindromo(char cad[]){
int s = strlen(cad), j;
j = s-1;
	for(int i  = 0; i<(s/2); i++,j--){
		if(cad[i]!=cad[j]){
			return false;
		}
	}
return true;
}

int main(){
char cad[100];

cin.getline(cad, 100);
if( palindromo(cad) == true){
	cout<<"Palindromo"<<endl;
}
else{
	cout<<"No"<<endl;
}

    system("pause");
}

