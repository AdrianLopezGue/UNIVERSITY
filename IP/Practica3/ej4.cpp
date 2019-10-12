#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(){
int i=0,x,y,z; 
cin>>x; y=x, z=x; 
while(i<4){
cin>>x;
if(x<z){	z=x;} if(x>y){ 	y=x; }i++;}
z = z+y;
cout<<z<<endl;
system("pause"); }

