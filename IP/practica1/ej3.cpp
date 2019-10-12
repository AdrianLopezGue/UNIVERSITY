#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;
int main(){

	float n;
	cout<<"Introduza el numero "<<endl;
	cin>>n;
	if (n>=0){
		n=sqrt(n);
		cout<<"La raiz es :"<<n<<endl;
	}
	else{ 
		cout<<"No se puede calcular la raiz"<<endl;
	}
	system("pause");
}
