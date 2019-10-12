#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
int main(){
   float nota1,nota2,nota3;
   cout<<"Introduzca la primera nota"<<endl;
   cin>>nota1;
   cout<<"Introduzca la segunda nota"<<endl;
   cin>>nota2;
   cout<<"Introduzca el tercera nota"<<endl;
   cin>>nota3;
   float nota_final= nota1*0.25+nota2*0.25+nota3*0.5;
	
  cout<<"La nota final es "<<nota_final<<endl;
   	system("pause");

}


