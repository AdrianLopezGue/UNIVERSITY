#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
int n,j=0;
cin>>n;
for(int i = 1; i<=n ; i++){
	if(n%i == 0){	
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

