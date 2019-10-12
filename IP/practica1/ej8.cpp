#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
int main(){
  float x0,y0,x1,y1;
  
  cin>>x0;
  cin>>y0;
  cin>>x1;
  cin>>y1;
  float dist= sqrt( (x0-x1)*(x0-x1) + (y0-y1)*(y0-y1));
  cout<<"La distancia es :"<<dist<<endl;
  system("pause");
}
