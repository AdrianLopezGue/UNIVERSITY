#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	int i = 0,x,z;
cin>>x;
z=x;
while(i<4){
	cin>>x;
	if(x<z){
	z=x;
	}
i++;
}
cout<<z<<endl;
    system("pause");
}

