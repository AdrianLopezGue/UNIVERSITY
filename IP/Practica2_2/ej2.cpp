#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
int x,fact = 1;
cin>>x;
for(int i = 1; i<=x; i++){	
	fact *= i;
	}
cout<<fact<<endl;
    system("pause");
}

