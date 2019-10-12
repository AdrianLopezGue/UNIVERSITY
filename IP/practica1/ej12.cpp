#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int main(){
   int cantidad,n500,n200,n100,n50,n20,n10,n5;
   cout<<"Introduzca la cantidad"<<endl;
   cin>>cantidad;
   n500= cantidad / 500;
   cantidad=cantidad % 500;
   n200= cantidad / 200;
   cantidad=cantidad % 200;
   n100= cantidad / 100;
   cantidad=cantidad % 100;
   n50= cantidad / 50;
   cantidad=cantidad % 50;
   n20= cantidad / 20;
   cantidad=cantidad % 20;
   n10= cantidad / 10;
   cantidad=cantidad % 10;
   n5= cantidad / 5;
   cantidad=cantidad % 5;

   cout<<"Su cambio es "<<endl;
   cout<< n500<<" billetes de 500"<<endl;
   cout<< n200<<" billetes de 200"<<endl;
   cout<< n100<<" billetes de 100"<<endl;
   cout<< n50<<" billetes de 50"<<endl;
   cout<< n20<<" billetes de 20"<<endl;
   cout<< n10<<" billetes de 10"<<endl;
   cout<< " Y le sobran "<<cantidad<<" euros" <<endl;
	
}


