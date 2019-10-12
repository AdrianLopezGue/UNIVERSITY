#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
bool palindromo(string cad){
	int s = cad.size(),j;
	j = s-1;
	for(int i= 0; i< (s/2); i++,j--){
		if(cad[i]!=cad[j]){
			return false;
		}
	}
return true;
}

int main(){
string cad;

getline(cin, cad);

if(palindromo(cad) == true){
	cout<<"Pal"<<endl;
}
else{
	cout<<"no"<<endl;
}

    system("pause");
}

