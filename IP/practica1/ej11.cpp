 
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
int main(){
  int mes;
  cout<<"Introduzca el  mes"<<endl;
  cin>>mes;

//Dejamos el a, el menor de a y b. Para ello, intercambiamos los valores a por b si a es mayor que b
if ( (mes==1) or (mes==3 ) or (mes==5) or (mes==8)or (mes==10) or (mes==12) ){
	cout<<"El mes tiene 31 dias"<<endl;
} 

else if ( (mes==4) or (mes==6 ) or (mes==9) or (mes==11)){
	cout<<"El mes tiene 30 dias"<<endl;
} 
else {
	cout<<"El mes tiene 28 dias"<<endl;
}
system("pause");
}
