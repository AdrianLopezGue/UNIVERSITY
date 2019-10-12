#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
int min, max,x,i = 0;

cin>>x;
min = x;
max  = x;

while(i<4) {
    cin>>x;
    if(x>max) {
        max = x;
    }
    if(x<min) {
        min = x;
    }
i++;
}
max = max+min;
cout<<max<<endl;

system("pause");
}

