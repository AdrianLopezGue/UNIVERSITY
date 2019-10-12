#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
int x,j=0;
cin>>x;
for(int i=1; i<=x; i++){
if((x%i)==0){
	j++;
	}
}
if(j==2){
	cout<<"Primo"<<endl;
}
else{
	cout<<"No primo"<<endl;
}
    system("pause");
}

