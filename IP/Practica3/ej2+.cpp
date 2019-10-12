#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
int x,z;
cin>>x;
z=x;
if(x>0){
while(x>0){
	cin>>x;
	if(x>z){
		z=x;
	}
}
cout<<z<<endl;
    system("pause");
}
}

