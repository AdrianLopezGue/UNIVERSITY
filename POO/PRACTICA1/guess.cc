#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{

	srand(time(NULL));
	int i =  rand() % 10+1;

	int x; // Variable que guardara el numero que introduce el usuario

	cout<<"Introduce el numero a adivinar: ";
	cin>>x;

	while(x!=i){


		if(x>i){
			cout<<"\nEl numero introducido es mayor\n";
		}
		else{
			cout<<"\nEl numero introducido es menor\n";
			}

			cout<<"Introduce el numero a adivinar: ";
			cin>>x;
		}
	

	
		cout<<"\nEl numero introducido es el mismo que el generado\n";
	

	
	
	return 0;
}