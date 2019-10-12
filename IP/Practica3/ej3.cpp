#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(){
float x,z=0,i=0;
cin>>x;
if(x>0){
while(x>0){
	cin>>x;	
	z += x;
	i++;
  }
 }
z = z/i;
cout<<"El resultado es: "<<z<<endl;
    system("pause");
}

