#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

int vocales(string cad){
int s = cad.size(), j = 0;

	for(int i = 0; i<s; i++){
		char z =cad[i];	
		if(islower(z)==true){
				j++;
			}
	}
return j;
}
int main(){
string cad;
getline(cin, cad);

cout<<"Vocales: "<<vocales(cad)<<endl;

    system("pause");
}

