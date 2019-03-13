#include "ruleta.h"

using namespace std;


bool Ruleta::setBanca(const int valor){
	if(valor>=0){
		banca_ = valor;
		return true;
	}
	else{
		return false;
	}
}

bool Ruleta::setBola(const int valor){
	if(valor>= 0 && valor<=36){
		bola_=valor;
		return true;
	}
	else{
		return false;
	}
}

bool Ruleta::addJugador(Jugador aux){

	string dnijugador;

	dnijugador = aux.getDNI();

	list<Jugador>::iterator it;

	for(it = jugadores_.begin(); it!=jugadores_.end(); it++){
		if((*it).getDNI() == dnijugador){
			return false;
		}
	}

	jugadores_.push_back(aux);

	string nombrefichero;
	nombrefichero = dnijugador + ".txt";
	ifstream fichero(nombrefichero.c_str());


	if(!fichero){

		ofstream fichero(nombrefichero.c_str());

	}

	fichero.close();
	return true;
}

int Ruleta::deleteJugador(const string aux){

	if(jugadores_.empty()){
		return -1;
	}

	list<Jugador>::iterator it;

	for(it = jugadores_.begin(); it!=jugadores_.end(); it++){
		if((*it).getDNI() == aux){
			jugadores_.erase(it);
			return 1;
		}
	}

	return -2;
}

int Ruleta::deleteJugador(Jugador aux){

	if(jugadores_.empty()){
		return -1;
	}

	string dnijugador;
	dnijugador = aux.getDNI();
	list<Jugador>::iterator it;

	for(it = jugadores_.begin(); it!=jugadores_.end(); it++){
		if((*it).getDNI() == dnijugador){
			jugadores_.erase(it);
			return 1;
		}
	}

	return -2;
}

void Ruleta::escribeJugadores(){

	ofstream fichero("jugadores.txt");
	//fichero.open("jugadores.txt", ios::out);

	if(fichero){
		list<Jugador>::iterator it;

		for(it = jugadores_.begin(); it!=jugadores_.end(); it++){
				fichero << (*it).getDNI()<<","<<(*it).getCodigo()<<","<<(*it).getNombre()<<","<<(*it).getApellidos()<<","<<(*it).getDireccion()<<","<<(*it).getLocalidad()<<","<<(*it).getProvincia()<<","<<(*it).getPais()<<","<<(*it).getDinero()<<"\n";
			}
		}
	fichero.close();
	}


void Ruleta::leeJugadores(){

	fstream fichero;
	fichero.open("jugadores.txt", ios:: in);
	char cadena1[10], cadena2[10], cadena3[10], cadena4[10], cadena5[10], cadena6[10], cadena7[10], cadena8[10], cadena9[10];

	if(fichero){
		jugadores_.clear();



		while(fichero.getline(cadena1, 256, ',')){


			fichero.getline(cadena2, 256, ',');

			Jugador aux(cadena1, cadena2);


			fichero.getline(cadena3, 256, ',');
			aux.setNombre(cadena3);

			fichero.getline(cadena4, 256, ',');
			aux.setApellidos(cadena4);

			fichero.getline(cadena5, 256, ',');
			aux.setDireccion(cadena5);

			fichero.getline(cadena6, 256, ',');
			aux.setLocalidad(cadena6);

			fichero.getline(cadena7, 256, ',');
			aux.setProvincia(cadena7);

			fichero.getline(cadena8, 256, ',');
			aux.setPais(cadena8);

			fichero.getline(cadena9, 256, '\n');
			aux.setDinero(atoi(cadena9));

			jugadores_.push_back(aux);
		}
		fichero.close();
	}
}

void Ruleta::giraRuleta(){

	bola_ = rand() % 37;
	numerotiradas_ ++;
}

void Ruleta::getPremios(){

	list<Jugador>::iterator it;
	string dniaux;
	char tipo[10], valor[10], cantidad[10];

	for(it = jugadores_.begin(); it!= jugadores_.end(); it++){

		dniaux = (*it).getDNI() + ".txt";
		fstream fichero(dniaux.c_str());

		if(fichero){

		Apuesta aux;

			while(fichero.getline(tipo, 256, ',')){
				aux.tipo = atoi(tipo);

				fichero.getline(valor, 256, ',');
				aux.valor = valor;

				fichero.getline(cantidad, 256, '\n');
				aux.cantidad = atoi(cantidad);

				(*it).setDinero((*it).getDinero() + validacion(aux));

			}
		}
	}
}

int Ruleta::validacion(const Apuesta aux){

	int ganado = 0;

	switch(aux.tipo){
		case 1:


		if(atoi((aux.valor).c_str()) == bola_){
			ganado += (aux.cantidad)*35;
			banca_-=(aux.cantidad)*35;
			return ganado;
		}
		else{
			ganado -= aux.cantidad;
			banca_ += aux.cantidad;
			return ganado;
		}
		 break;

		case 2:
		if(bola_ == 0){
			ganado-= aux.cantidad;
			banca_ += aux.cantidad;
			return ganado;
		}
		else{
			string numerotransformado = transformarbolaencolor();

			if(numerotransformado == aux.valor){
				ganado+=(aux.cantidad)*2;
				banca_-=(aux.cantidad)*2;
				return ganado;
			}
			else{
				ganado-=aux.cantidad;
				banca_ += aux.cantidad;
				return ganado;
			}
		}
		 break;

		 case 3:

		 if(bola_ == 0){
			ganado-= aux.cantidad;
			banca_ += aux.cantidad;
			return ganado;
		}

		 if(bola_%2 == 0){
		 	if(aux.valor == "par"){
		 		ganado += (aux.cantidad);
		 		banca_-=(aux.cantidad);
		 		return ganado;
		 	}
		 	else{
		 		ganado -= aux.cantidad;
		 		banca_ += aux.cantidad;
		 		return ganado;
		 	}
		 }

		 else{
		 	if(aux.valor=="impar"){
		 		ganado+=(aux.cantidad);
		 		banca_-=(aux.cantidad);
		 		return ganado;
		 	}
		 	else{
		 		ganado-= aux.cantidad;
		 		banca_ += aux.cantidad;
		 		return ganado;
		 	}
		 }
		 break;

		 case 4:

		 if(bola_ == 0){
		 	ganado-=aux.cantidad;
		 	banca_ += aux.cantidad;
		 	return ganado;
		 }

		 else{
		 	if(bola_>=1 && bola_<=18){
		 		if(aux.valor == "bajo"){
		 			ganado+=(aux.cantidad);
		 			banca_-=(aux.cantidad);
		 			return ganado;
		 		}
		 		else{
		 			ganado-=aux.cantidad;
		 			banca_ += aux.cantidad;
		 			return ganado;
		 		}
		 	}
		 	else{
		 		if(aux.valor == "alto"){
		 			ganado+=(aux.cantidad);
		 			banca_-=(aux.cantidad);
		 			return ganado;
		 		}
		 		else{
		 			ganado-=aux.cantidad;
		 			banca_ += aux.cantidad;
		 			return ganado;
		 		}
		 	}
		 }
		 break;

		 default: return ganado; break;
	}
}

string Ruleta::transformarbolaencolor(){

	string rojo = "rojo";
	string negro = "negro";

	switch(bola_){
		case 1: return rojo; break;
		case 2: return negro; break;
		case 3: return rojo; break;
		case 4: return negro; break;
		case 5: return rojo; break;
		case 6: return negro; break;
		case 7: return negro; break;
		case 8: return negro; break;
		case 9: return rojo; break;
		case 10: return negro; break;
		case 11: return negro; break;
		case 12: return rojo; break;
		case 13: return negro; break;
		case 14: return rojo; break;
		case 15: return negro; break;
		case 16: return rojo; break;
		case 17: return negro; break;
		case 18: return rojo; break;
		case 19: return rojo; break;
		case 20: return negro; break;
		case 21: return rojo; break;
		case 22: return negro; break;
		case 23: return rojo; break;
		case 24: return negro; break;
		case 25: return rojo; break;
		case 26: return negro; break;
		case 27: return rojo; break;
		case 28: return negro; break;
		case 29: return negro; break;
		case 30: return rojo; break;
		case 31: return negro; break;
		case 32: return rojo; break;
		case 33: return negro; break;
		case 34: return rojo; break;
		case 35: return negro; break;
		case 36: return rojo; break;
		default: return negro; break;
	}

}

void Ruleta::getEstadoRuleta(int &njugadores, int &dinero, int &lanzamientos, int &ganancia, Ruleta aux){

	list<Jugador>::iterator it;

	lanzamientos = numerotiradas_;

	njugadores = 0;
	dinero = banca_;

	for(it = jugadores_.begin(); it!=jugadores_.end(); it++){
		njugadores++;
		dinero+= (*it).getDinero();
	}

	ganancia = aux.getBanca() - 1000000;
}
