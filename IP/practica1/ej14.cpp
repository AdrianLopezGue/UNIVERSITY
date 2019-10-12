#include <iostream>
#include <cmath>
using namespace std;
int main(){
  int a,b,c;
  cin>>a;
  cin>>b;
  cout<<a<<" "<<b<<endl;
  if (a>b){
	c=a;
	a=b;
	b=c;
  }
  cout<<a<<" "<<b<<endl;
}
