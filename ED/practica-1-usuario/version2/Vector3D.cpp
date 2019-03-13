/*!
\file Vector3D.cpp
\brief Fichero que contiene el código de las funciones de la clase Vector3D
\author   Adrian Lopez Guerrero
\date     2018-2-26
\version  1.0
*/


// Ficheros de cabecera
#include <iostream>

// Para usar sqrt, acos
#include <cmath>

// Para controlar las pre y post condiciones mediante asertos
#include <cassert>

#include "Vector3D.hpp"

// OBSERVADORES

double ed::Vector3D:: modulo() const{
	double valordevuelto;

	valordevuelto = sqrt((get1()*get1()) + (get2()*get2()) + (get3()*get3()));

	#ifndef NDEBUG
	assert(std::abs((sqrt((get1()*get1()) + (get2()*get2()) + (get3()*get3())))-valordevuelto)<COTA_ERROR);
	#endif

	return valordevuelto;
}

double ed::Vector3D::angulo(Vector3D v) const{
	#ifndef NDEBUG
	assert((modulo() * v.modulo()) > 0);
	#endif

	double angulo;
	double aux;

	if((dotProduct(v)/(modulo() * v.modulo()))<-1){
		angulo=acos(-1);
		aux=-1;
	}
	else if((dotProduct(v)/(modulo()*v.modulo()))>1){
		angulo=acos(1);
		aux=1;
	}
	else{
		angulo = acos(dotProduct(v)/(modulo() * v.modulo()));
		aux=dotProduct(v)/(modulo() * v.modulo());
	}

	#ifndef NDEBUG
	assert(std::abs(angulo-acos(aux)) <= COTA_ERROR);
	#endif

	return angulo;
}

double ed::Vector3D::alfa()const{
	#ifndef NDEBUG
	assert(modulo()>0);
	#endif

	double valordevuelto;
	Vector3D aux(1,0,0);

	valordevuelto = angulo(aux);

	#ifndef NDEBUG
	assert(std::abs(angulo(aux) - valordevuelto) < COTA_ERROR);
	#endif

	return valordevuelto;
}

double ed::Vector3D::beta()const{
	#ifndef NDEBUG
	assert(modulo()>0);
	#endif

	double valordevuelto;
	Vector3D aux(0,1,0);

	valordevuelto = angulo(aux);

	#ifndef NDEBUG
	assert(std::abs(angulo(aux) - valordevuelto) < COTA_ERROR);
	#endif

	return valordevuelto;
}

double ed::Vector3D::gamma()const{
	#ifndef NDEBUG
	assert(modulo()>0);
	#endif

	double valordevuelto;
	Vector3D aux(0,0,1);

	valordevuelto = angulo(aux);

	#ifndef NDEBUG
	assert(std::abs(angulo(aux) - valordevuelto) < COTA_ERROR);
	#endif

	return valordevuelto;
}

double ed::Vector3D::dotProduct(Vector3D v)const{
	double valordevuelto;

	valordevuelto = (get1()*v.get1()) + (get2()*v.get2()) + (get3()*v.get3());

	#ifndef NDEBUG
	assert(std::abs((get1()*v.get1()) + (get2()*v.get2()) + (get3()*v.get3()) - valordevuelto) < COTA_ERROR);
	#endif

	return valordevuelto;
}


ed::Vector3D ed::Vector3D::crossProduct(Vector3D v)const{

	#ifndef NDEBUG
	assert((angulo(v)) > 0);
	#endif

	ed::Vector3D valordevuelto;

	valordevuelto.set1((get2()*v.get3()) - (get3()*v.get2()));
	valordevuelto.set2(-(get1()*v.get3()) + (get3()*v.get1()));
	valordevuelto.set3((get1()*v.get2()) - (get2()*v.get1()));

	#ifndef NDEBUG
	assert((dotProduct(valordevuelto) == 0) && (v.dotProduct(valordevuelto) == 0) && (std::abs((modulo()*v.modulo()*sin(angulo(v))) - valordevuelto.modulo()) < COTA_ERROR));
	#endif

	return valordevuelto;
}

double ed::Vector3D::productoMixto(Vector3D v, Vector3D w)const{

	#ifndef NDEBUG
	assert((w.angulo(v)) > 0);
	#endif
	double valordevuelto;

	valordevuelto = dotProduct(v.crossProduct(w));

	#ifndef NDEBUG
	assert(std::abs((dotProduct(v.crossProduct(w))) - valordevuelto) < COTA_ERROR);
	#endif

	return valordevuelto;
}


////////////////////////////////////////////////////////////////

// MODIFICADORES

void ed::Vector3D::sumConst(double k){
	double antiguoX = get1();
	double antiguoY = get2();
	double antiguoZ = get3();

	set1(get1()+k);
	set2(get2()+k);
	set3(get3()+k);

	#ifndef NDEBUG
	assert((std::abs(antiguoX+k - get1()) < COTA_ERROR) && (std::abs(antiguoY+k - get2()) < COTA_ERROR) && (std::abs(antiguoZ+k - get3()) < COTA_ERROR));
	#endif

}

void ed::Vector3D::sumVect(Vector3D v){
	double antiguoX = get1();
	double antiguoY = get2();
	double antiguoZ = get3();

	set1(get1()+v.get1());
	set2(get2()+v.get2());
	set3(get3()+v.get3());

	#ifndef NDEBUG
	assert((std::abs(antiguoX+v.get1() - get1()) < COTA_ERROR) && (std::abs(antiguoY+v.get2() - get2()) < COTA_ERROR) && (std::abs(antiguoZ+v.get3() - get3()) < COTA_ERROR));
	#endif

}

void ed::Vector3D::multConst(double k){
	double antiguoX = get1();
	double antiguoY = get2();
	double antiguoZ = get3();

	set1(get1()*k);
	set2(get2()*k);
	set3(get3()*k);

	#ifndef NDEBUG
	assert((std::abs(antiguoX*k - get1()) < COTA_ERROR) && (std::abs(antiguoY*k - get2()) < COTA_ERROR) && (std::abs(antiguoZ*k - get3()) < COTA_ERROR));
	#endif

}

void ed::Vector3D::multVect(Vector3D v){
	double antiguoX = get1();
	double antiguoY = get2();
	double antiguoZ = get3();

	set1(get1()*v.get1());
	set2(get2()*v.get2());
	set3(get3()*v.get3());


	#ifndef NDEBUG
	assert((std::abs(antiguoX*v.get1() - get1()) < COTA_ERROR) && (std::abs(antiguoY*v.get2() - get2()) < COTA_ERROR) && (std::abs(antiguoZ*v.get3() - get3()) < COTA_ERROR));
	#endif

}
////////////////////////////////////////////////////////////////////////////////

// OPERADORES

ed::Vector3D & ed::Vector3D::operator=(Vector3D const &objeto){

	set1(objeto.get1());
	set2(objeto.get2());
	set3(objeto.get3());

	#ifndef NDEBUG
	assert((get1() == objeto.get1()) && (get2() == objeto.get2()) && (get3() == objeto.get3()));
	#endif

	return *this;
}

bool ed::Vector3D::operator == ( ed::Vector3D const &objeto) const{

	if((std::abs(get1()-objeto.get1())<COTA_ERROR) && (std::abs(get2()-objeto.get2())<COTA_ERROR) && (std::abs(get3()-objeto.get3())<COTA_ERROR)){
		#ifndef NDEBUG
		assert((std::abs(get1()-objeto.get1())<COTA_ERROR) && (std::abs(get2()-objeto.get2())<COTA_ERROR) && (std::abs(get3()-objeto.get3())<COTA_ERROR));
		#endif

		return true;
	}
	else{
		#ifndef NDEBUG
		assert((std::abs(get1()-objeto.get1())>=COTA_ERROR) || (std::abs(get2()-objeto.get2())>=COTA_ERROR) || (std::abs(get3()-objeto.get3())>=COTA_ERROR));
		#endif

		return false;
	}
}

ed::Vector3D ed::Vector3D::operator+(ed::Vector3D v)const{
	ed::Vector3D valordevuelto;

	valordevuelto.set1(get1() + v.get1());
	valordevuelto.set2(get2() + v.get2());
	valordevuelto.set3(get3() + v.get3());

	#ifndef NDEBUG
	assert((std::abs((get1() + v.get1()) - valordevuelto.get1()) < COTA_ERROR) && (std::abs((get2() + v.get2())  - valordevuelto.get2()) < COTA_ERROR) && (std::abs((get3() + v.get3())  - valordevuelto.get3()) < COTA_ERROR));
	#endif

	return valordevuelto;
}

ed::Vector3D ed::Vector3D::operator+()const{
	ed::Vector3D valordevuelto;

	valordevuelto.set1(get1());
	valordevuelto.set2(get2());
	valordevuelto.set3(get3());

	#ifndef NDEBUG
	assert((std::abs(get1() - valordevuelto.get1()) < COTA_ERROR) && (std::abs(get2() - valordevuelto.get2()) < COTA_ERROR) && (std::abs(get3() - valordevuelto.get3()) < COTA_ERROR));
	#endif

	return valordevuelto;

}

ed::Vector3D ed::Vector3D::operator-(ed::Vector3D v)const{
	ed::Vector3D valordevuelto;

	valordevuelto.set1(get1() - v.get1());
	valordevuelto.set2(get2() - v.get2());
	valordevuelto.set3(get3() - v.get3());

	#ifndef NDEBUG
	assert((std::abs((get1() - v.get1()) - valordevuelto.get1()) < COTA_ERROR) && (std::abs((get2() - v.get2())  - valordevuelto.get2()) < COTA_ERROR) && (std::abs((get3() - v.get3())  - valordevuelto.get3()) < COTA_ERROR));
	#endif

	return valordevuelto;
}

ed::Vector3D ed::Vector3D::operator-()const{
	ed::Vector3D valordevuelto;

	valordevuelto.set1(-get1());
	valordevuelto.set2(-get2());
	valordevuelto.set3(-get3());

	#ifndef NDEBUG
	assert((std::abs(-get1() - valordevuelto.get1()) < COTA_ERROR) && ((std::abs(-get2() - valordevuelto.get2())) < COTA_ERROR) && (std::abs(-get3() - valordevuelto.get3()) < COTA_ERROR));

	#endif

	return valordevuelto;

}


ed::Vector3D ed::Vector3D::operator*(double k)const{
	ed::Vector3D valordevuelto;

	valordevuelto.set1(k * get1());
	valordevuelto.set2(k * get2());
	valordevuelto.set3(k * get3());

	#ifndef NDEBUG
	assert((std::abs(get1() * k - valordevuelto.get1()) < COTA_ERROR) && (std::abs(get2() * k - valordevuelto.get2()) < COTA_ERROR) && (std::abs(get3() * k - valordevuelto.get3()) < COTA_ERROR));
	#endif

	return valordevuelto;
}


double ed::Vector3D::operator*(ed::Vector3D v)const{
	double valordevuelto;

	valordevuelto = (get1()*v.get1()) + (get2()*v.get2()) + (get3()*v.get3());

	#ifndef NDEBUG
	assert(std::abs((get1()*v.get1()) + (get2()*v.get2()) + (get3()*v.get3()) - valordevuelto) < COTA_ERROR);
	#endif

	return valordevuelto;
}


ed::Vector3D ed::Vector3D::operator^(ed::Vector3D v)const{
	#ifndef NDEBUG
	assert((angulo(v)) > 0);
	#endif

	ed::Vector3D valordevuelto;

	valordevuelto.set1((get2()*v.get3()) - (get3()*v.get2()));
	valordevuelto.set2(-(get1()*v.get3()) + (get3()*v.get1()));
	valordevuelto.set3((get1()*v.get2()) - (get2()*v.get1()));

	#ifndef NDEBUG
	assert((dotProduct(valordevuelto) == 0) && (v.dotProduct(valordevuelto) == 0) && (std::abs((modulo()*v.modulo()*sin(angulo(v))) - valordevuelto.modulo()) - COTA_ERROR));
	#endif

	return valordevuelto;
}

////////////////////////////////////////////////////////////////////////////////

// FUNCIONES DE LECTURA Y ESCRITURA

void ed::Vector3D::leerVector3D(){
	double valoraux;

	std::cout<<"Introduzca el valor X: ";
	std::cin>>valoraux;

	set1(valoraux);

	std::cout<<"Introduzca el valor Y: ";
	std::cin>>valoraux;

	set2(valoraux);

	std::cout<<"Introduzca el valor Z: ";
	std::cin>>valoraux;

	set3(valoraux);
}

void ed::Vector3D::escribirVector3D() const{
	std::cout<<"("<<get1()<<", "<<get2()<<", "<<get3()<<")\n";
}


////////////////////////////////////////////////////////////////////////////////


// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{


	// Producto "por un" escalar (prefijo): k * v
	ed::Vector3D & operator* (double k, ed::Vector3D const & objeto)
	{
		ed::Vector3D *vectorResultado = new ed::Vector3D();


		vectorResultado->set1(objeto.get1() * k);
		vectorResultado->set2(objeto.get2() * k);
		vectorResultado->set3(objeto.get3() * k);

		#ifndef NDEBUG
		assert((std::abs((objeto.get1()*k)-(vectorResultado->get1())) < COTA_ERROR) && (std::abs((objeto.get2()*k)-(vectorResultado->get2())) < COTA_ERROR) && (std::abs((objeto.get3()*k)-(vectorResultado->get3())) < COTA_ERROR));
		#endif

		return *vectorResultado;
	}


	// Sobrecarga del operador de salida
	// Se escriben por pantalla las coordenadas del vector 3D  de la forma (v1, v2, v3)
	ostream &operator<<(ostream &stream, ed::Vector3D const &objeto)
	{

		stream<<"("<<objeto.get1()<<", "<<objeto.get2()<<", "<<objeto.get3()<<")\n";
		return stream;
	}

	// Sobrecarga del operador de entrada
	istream &operator>>(istream &stream, ed::Vector3D &objeto)
	{

		double valoraux;

		std::cout<<"Introduzca el valor X: ";
		stream>>valoraux;

		objeto.set1(valoraux);

		std::cout<<"Introduzca el valor Y: ";
		stream>>valoraux;

		objeto.set2(valoraux);

		std::cout<<"Introduzca el valor Z: ";
		stream>>valoraux;

		objeto.set3(valoraux);
		return stream;
	}

} // Fin del espacio de nombres ed
