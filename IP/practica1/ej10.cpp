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
 
if ( (a>=b) and  (a>=c)){
	cout<<"El mayor es "<<a<<endl;
}
else if ( (b>=a) and  (b>=c)){
	cout<<"El mayor es "<<b<<endl;
}
else if ( (c>=a) and  (c>=b)){
	cout<<"El mayor es "<<c<<endl;
}
  system("pause");


}
