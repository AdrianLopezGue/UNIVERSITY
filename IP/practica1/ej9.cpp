 #include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
int main(){
  int a,b,c;
  cout<<"Introduzca el valor a"<<endl;
  cin>>a;
  cout<<"Introduzca el valor b"<<endl;
  cin>>b;
  cout<<"Introduzca el valor c"<<endl;
  cin>>c;

 //Hay dos opciones, que a<b o que a>b,
 //En cada caso las evaluaciones a realizar cambian
 if (a<b){
	if (  ( a<c) and (c<b)){
		cout<<"C SI esta entre a y b"<<endl;
	}
	else{
		cout<<"C NO esta entre a y b"<<endl;
	}
 }
else{ //es el caso a>=b, cambiamos los roles de a y b
	if (  ( b<c) and (c<a)){
		cout<<"C SI esta entre a y b"<<endl;
	}
	else{
		cout<<"C NO esta entre a y b"<<endl;
	}
}
   system("pause");
}
