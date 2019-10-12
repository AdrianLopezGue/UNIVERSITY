#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){

int suma = 0, n;
cin>>n;

for(int i  = 1; i<=n; i++){
	if(i%2 != 0){
		suma += i;
	}
}    
cout<<suma<<endl;
system("pause");
}

