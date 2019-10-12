#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
int n,suma=0;
cin>>n;
for(int i = 1; i<=n; i++){	
	if(i%2 != 0){	
	suma += i;
	}	
}
cout<<"res = "<<suma<<endl;
    system("pause");
}

