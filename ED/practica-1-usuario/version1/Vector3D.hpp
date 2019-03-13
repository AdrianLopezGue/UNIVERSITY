/*!
\file Vector3D.hpp
\brief Fichero de definición de la clase Vector3D: vector libre de tres dimensiones
\author   Adrian Lopez Guerrero
\date     2018-2-26
\version  2.0
*/

#ifndef _VECTOR3D_HPP_
#define _VECTOR3D_HPP_

// Entrada y salida
#include <iostream>

// Para usar abs
#include <cmath>

// Para controlar las pre y post condiciones mediante asertos
#include <cassert>

// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

#define COTA_ERROR   1.0e-6 //!< Cota de error para la comparación números reales


// Se incluye la clase Vector3D dentro del espacio de nombre de la asigantura: ed
namespace ed {

  //!  Definición de la clase Vector3D:  \f$ \vec{v} = (v_1, v_2, v_3) = v_1 \vec{i} + v_2 \vec{j} + v_3 \vec{k} \f$
  class Vector3D
  {
    //! \name Atributos privados de la clase Vector3D
  private:

    double v1; //<! Componente v1
    double v2; //<! Componente v2
    double v3; //<! Componente v3
    //! \name Funciones o métodos públicos de la clase Vector3D
  public:

    //! \name Constructores de la clase Vector3D
    /*!
    \brief     Constructor que crea un Vector3D sin necesidad de introducir parametros.
    \attention Funcion sobrecargada
    \warning   No existen parametros por defecto (no hay argumentos)
    \param     Ninguno
    \post      get1()==0 && get2()==0 && get3()==0
    \sa        get1(), get2(), get3() de la clase Vector3D
    */

    Vector3D(){
      v1 = 0;
      v2 = 0;
      v3 = 0;

      #ifndef NDEBUG
      assert(get1()==0 && get2()==0 && get3()==0);
      #endif
    }

    /*!
    \brief     Constructor que crea un Vector3D a partir de unos parametros pasados como argumentos.
    \attention Funcion sobrecargada
    \warning   Los parametros no tienen valores por defecto
    \param     v1arg: Coordenada X deL Vector3D;
    \param     v2arg: Coordenada Y deL Vector3D;
    \param     v3arg: Coordenada Z deL Vector3D;
    \pre       Ninguno
    \post      (get1()==v1) && (get2()==v2) && (get3()==v3)
    \sa        get1(), get2(), get3() de la clase Vector3D
    */

    Vector3D(double v1arg, double v2arg, double v3arg){

      v1 = v1arg;
      v2 = v2arg;
      v3 = v3arg;

      #ifndef NDEBUG
      assert((std::abs((v1) - (get1())) < COTA_ERROR) && (std::abs((v2) - (get2())) < COTA_ERROR) && (std::abs((v3) - (get3())) < COTA_ERROR));
      #endif
    };

    /*!
    \brief     Constructor de "copia" que crea un Vector3D a partir de otro Vector3D
    \attention Funcion sobrecargada
    \warning   Se requiere que las funciones de acceso getX y getY tengan el modificador const
    \param     v: Vector3D utilizado para proporcionar los valores iniciales del nuevo Vector3D
    \pre       Ninguna
    \post 	   (get1()==v.get1()) && (get2()==v.get2()) && (get3()==v.get3())
    \sa        get1(), get2(), get3() de la clase Vector3D
    */

    Vector3D(Vector3D const &v) {
      v1 = v.get1();
      v2 = v.get2();
      v3 = v.get3();

      #ifndef NDEBUG
      assert((std::abs((v.get1()) - (get1())) < COTA_ERROR) && (std::abs((v.get2()) - (get2())) < COTA_ERROR) && (std::abs((v.get3()) - (get3())) < COTA_ERROR));
      #endif
    };

    //! \name Observadores: funciones de consulta de Vector3D

    //! \name Observadores: funciones de consulta de Vector3D

    /*!
    \brief   Funcion que devuelve la Coordenada X del Vector3D
    \warning Se utiliza el modificador const en la definicion de la funcion para poder definir el constructor de copia y el operador de asignacion "="
    \return  Coordenada X del Vector3D (tipo double)
    \pre     Ninguna
    \post    Ninguna
    \sa      get2(), get3() de la clase Vector3D
    */

    double get1()const{return v1;};

    /*!
    \brief   Funcion que devuelve la Coordenada Y del Vector3D
    \warning Se utiliza el modificador const en la definicion de la funcion para poder definir el constructor de copia y el operador de asignacion "="
    \return  Coordenada Y del Vector3D (tipo double)
    \pre     Ninguna
    \post    Ninguna
    \sa      get1(), get3() de la clase Vector3D
    */

    double get2()const{return v2;};

    /*!
    \brief   Funcion que devuelve la Coordenada Z del Vector3D
    \warning Se utiliza el modificador const en la definicion de la funcion para poder definir el constructor de copia y el operador de asignacion "="
    \return  Coordenada Z del Vector3D (tipo double)
    \pre     Ninguna
    \post    Ninguna
    \sa      get2(), get3() de la clase Vector3D
    */

    double get3()const{return v3;};

    /*!
    \brief  Calcula el modulo del vector
    \n \f$ modulo(\vec{v}) = mod(\vec{v}) = \sqrt{ (v1*v1) + (v2*v2) + (v3*v3) } \f$
    \param  Ninguno
    \return sqrt( (v1*v1) + (v2*v2) + (v3*v3) )
    \pre    Ninguna
    \post   valordevuelto == sqrt((get1()*get1()) + (get2()*get2()) + (get3()*get3()))
    \sa     get1(), get2(), get3() de la clase Vector3D
    */

    double modulo() const;

    /*!
    \brief  Devuelve el ángulo en radianes entre el vector actual y vector pasado como argumento.
    \n \f$ \arccos(\vec{u}*\vec{v} / (modulo(\vec{u}) * modulo(\vec{v}))) ) \f$
    \param  v Vector3D
    \return acos(dotProduct(v)/(modulo() * v.modulo()))
    \pre    (modulo() * v.modulo()) > 0
    \post   angulo+COTA_ERROR >= acos(dotProduct(v)/(modulo() * v.modulo()))
    */

    double angulo(Vector3D v) const;

    /*!
    \brief  Calcula el ángulo del vector con el eje X
    \param  Ninguno
    \return angulo del vector respecto al eje X
    \pre    modulo()>0
    \post   valordevuelto == angulo(aux)
    */

    double alfa()const;

    /*!
    \brief  Calcula el ángulo del vector con el eje Y
    \param  Ninguno
    \return angulo del vector respecto al eje Y
    \pre    modulo()>0
    \post   valordevuelto == angulo(aux)
    */

    double beta()const;

    /*!
    \brief  Calcula el ángulo del vector con el eje Z
    \param  Ninguno
    \return angulo del vector respecto al eje Z
    \pre    modulo()>0
    \post   valordevuelto == angulo(aux)
    */

    double gamma()const;

    /*!
    \brief  Calcula el producto escalar.
    \n \f$ \vec{u} * \vec{v} = u_1*v_1 + u_2*v_2 + u_3*v_3  \f$
    \param  v Vector3D
    \return get1()*v.get1()) + (get2()*v.get2()) + (get3()*v.get3()
    \pre    Ninguna
    \post   valordevuelto == (get1()*v.get1()) + (get2()*v.get2()) + (get3()*v.get3())
    \sa     get1(), get2(), get3() de la clase Vector3D
    */

    double dotProduct(Vector3D v)const;

    /*!
    \brief  Devuelve un Vector3D que es el resultado del producto vectorial de dos vectores.
    \n \f$ \vec{u} \wedge \vec{v} = \vec{w} = w_1*\vec{i} + w_2*\vec{j} + w_3*\vec{k} \f$
    \param  v Vector3D
    \return Vector3D con los parametros del resultado del producto vectorial.
    \pre    (angulo(v)) > 0
    \post   (dotProduct(valordevuelto) == 0) && (v.dotProduct(valordevuelto) == 0) && (valordevuelto.modulo() == modulo()*v.modulo()*sin(angulo(v)))
    \sa     get1(), get2(), get3(), set1(), set2(), set3() de la clase Vector3D
    */

    Vector3D crossProduct(Vector3D v)const;

    /*!
    \brief  Devuelve el resultado de calcular el producto escalar del vector actual con el vector obtenido al calcular el producto vectorial de otros dos vectores.
    \n \f$ productoMixto(\vec{u}, \vec{v}, \vec{w}) = \vec{u} * (\vec{v} \wedge \vec{w})  \f$
    \param  v primer Vector3D
    \param  w segundo Vector3D
    \return dotProduct(v.crossProduct(w))
    \pre    (w.angulo(v)) > 0
    \post   valordevuelto == dotProduct(v.crossProduct(w))
    */

    double productoMixto(Vector3D v, Vector3D w)const;


    //! \name Modificadores: funciones de modificación de Vector3D

    /*!
    \brief Funcion que asigna un valor "v" a la Coordenada X de un Vector3D
    \param v: nuevo valor de Coordenada X del Vector3D (tipo double)
    \pre   Ninguma
    \post  get1() == v
    \sa get1() de la clase Vector3D
    */

    void set1(double  v){
      v1 = v;

      #ifndef NDEBUG
        assert((std::abs((v) - (get1())) < COTA_ERROR));
      #endif
    };

    /*!
    \brief Funcion que asigna un valor "v" a la Coordenada Y de un Vector3D
    \param v: nuevo valor de Coordenada Y del Vector3D (tipo double)
    \pre   Ninguma
    \post  get2() == v
    \sa get2() de la clase Vector3D
    */

    void set2(double  v){
      v2 = v;

      #ifndef NDEBUG
      assert((std::abs((v) - (get2())) < COTA_ERROR));
      #endif
    };

    /*!
    \brief Funcion que asigna un valor "v" a la Coordenada Z de un Vector3D
    \param v: nuevo valor de Coordenada Z del Vector3D (tipo double)
    \pre   Ninguma
    \post  get3() == v
    \sa get3() de la clase Vector3D
    */

    void set3(double  v){
      v3 = v;

      #ifndef NDEBUG
      assert((std::abs((v) - (get3())) < COTA_ERROR));
      #endif
    };

    /*!
    \brief  Modifica el vector sumando una constante a cada componente
    \param  k elemento double
    \return Ninguna
    \pre    Ninguna
    \post   (get1() == antiguoX+k) && (get2() == antiguoY+k) && (get3() == antiguoZ+k) )
    \sa     get1(), get2(), get3(), set1(), set2(), set3() de la clase Vector3D
    */

    void sumConst(double k);

    /*!
    \brief  Modifica el vector sumando a cada componente la componente equivalente de otro vector.
    \param  v Vector3D
    \return Ninguna
    \pre    Ninguna
    \post   (get1() == antiguoX*k) && (get2() == antiguoY*k) && (get3() == antiguoZ*k)
    \sa     get1(), get2(), get3(), set1(), set2(), set3() de la clase Vector3D
    */

    void sumVect(Vector3D v);

    /*!
    \brief  Modifica el vector multiplicando cada componente por una constante: escala el vector
    \param  k elemento double
    \return Ninguna
    \pre    Ninguna
    \post   (get1() == antiguoX*k) && (get2() == antiguoY*k) && (get3() == antiguoZ*k)
    \sa     get1(), get2(), get3(), set1(), set2(), set3() de la clase Vector3D
    */

    void multConst(double k);

    /*!
    \brief  Modifica el vector multiplicando, por separado, cada componente por la componente de otro vector.
    \param  v Vector3D
    \return Ninguna
    \pre    Ninguna
    \post   (get1() == antiguoX*v.get1()) && (get2() == antiguoY*v.get2()) && (get3() == antiguoZ*v.get3())
    \sa     get1(), get2(), get3(), set1(), set2(), set3() de la clase Vector3D
    */

    void multVect(Vector3D v);


    //! \name Operadores de la clase

    /*!
    \brief     Operador de asignacion: operador que "copia" un Vector3D en otro Vector3D
    \attention Se sobrecarga el operador de asignacion "="
    \warning   Se requiere que las funciones de acceso getX y getY tengan el modificador const
    \param     objeto: objeto de tipo Vector3D pasado como referencia constante
    \return    Vector3D con los mismos parametros de igualdad al vector pasado como argumento.
    \pre       Ninguna
    \post      El vector actual debe ser igual al vector pasado como argumento
    \n (get1() == objeto.get1()) && (get2() == objeto.get2()) && (get3() == objeto.get3())
    \sa        get1(), get2(), get3(), set1(), set2(), set3(), operator==() de la clase Vector3D
    */

    Vector3D & operator=(Vector3D const &objeto);

    /*!
    \brief     Operador de igualdad: compara si un Vector3D es igual a otro Vector3D
    \attention Se sobrecarga el operador de asignacion "=="
    \param     objeto: objeto de tipo Vector3D pasado como referencia constante
    \return   Valor booleano (true o false) que dependera de si el Vector3D pasado como argumento es igual al Vector3D que ha llamado a la funcion
    \pre       Ninguna
    \post      (std::abs(get1()-objeto.get1())<COTA_ERROR) && (std::abs(get2()-objeto.get2())<COTA_ERROR) && (std::abs(get3()-objeto.get3())<COTA_ERROR)
    \n Se debe utilizar una cota de error para tener en cuenta la precision de los numeros reales
    \sa         get1(), get2(), get3(), set1(), set2(), set3(),  operator=() de la clase Vector3D
    */

    bool operator == (const Vector3D  &objeto) const;

    /*!
		\brief     Devuelve otro vector que es la suma del vector actual y el vector pasado como parámetro.
		\attention Se sobrecarga el operador suma "+"
		\param     v: objeto de tipo Vector3D pasado como variable constante.
    \return    Vector3D con los parametros sumados.
		\pre       Ninguna
		\post      (valordevuelto.get1() == get1() + v.get1()) && (valordevuelto.get2() == get2() + v.get2()) && (valordevuelto.get3() == get3() + v.get3())
		\sa        get1(), get2(), get3(), set1(), set2(), set3(),  operator+() de la clase Vector3D
	*/

    Vector3D operator+(Vector3D const v)const;

    /*!
    \brief     Devuelve otro vector con los parametros en positivo.
    \attention Se sobrecarga el operador suma "+"
    \param     Ninguna.
    \return    Vector3D con los parametros en positivo.
    \pre       Ninguna
    \post      (valordevuelto.get1() == get1()) && (valordevuelto.get2() == get2()) && (valordevuelto.get3() == get3())
    \sa        get1(), get2(), get3(), set1(), set2(), set3(),  operator+() de la clase Vector3D
    */

    Vector3D operator+()const;

    /*!
    \brief     Devuelve otro vector que es la resta del vector actual y el vector pasado como parámetro.
    \attention Se sobrecarga el operador resta "-"
    \param     v: objeto de tipo Vector3D pasado como variable constante.
    \return    Vector3D con los parametros restados.
    \pre       Ninguna
    \post      (valordevuelto.get1() == get1() - v.get1()) && (valordevuelto.get2() == get2() - v.get2()) && (valordevuelto.get3() == get3() - v.get3())
    \sa        get1(), get2(), get3(), set1(), set2(), set3(),  operator-() de la clase Vector3D
    */

    Vector3D operator-(Vector3D  v)const;

    /*!
    \brief     Devuelve otro vector con los parametros en negativo.
    \attention Se sobrecarga el operador resta "-"
    \param     Ninguna.
    \return    Vector3D con los parametros en negativo.
    \pre       Ninguna
    \post      (valordevuelto.get1() == -get1()) && (valordevuelto.get2() == -get2()) && (valordevuelto.get3() == -get3())
    \sa        get1(), get2(), get3(), set1(), set2(), set3(),  operator-() de la clase Vector3D
    */

    Vector3D operator-()const;

    /*!
    \brief     Operador asterisco: Devuelve otro vector cuyas componentes se obtienen multiplicando por “k” las componentes del vector actual
    \attention Se sobrecarga el operador de asignacion "*"
    \param     k: constante de tipo double
    \return    Vector3D cuyos parametros estan multiplicados por la constante k pasado por argumento.
    \pre       Ninguna
    \post      (valordevuelto.get1() == get1() * k) && (valordevuelto.get2() == get2() * k) && (valordevuelto.get2() == get2() * k)
    \sa        get1(), get2(), get3(), set1(), set2(), set3(),  operator*() de la clase Vector3D
    */

    Vector3D operator*(double k)const;

    /*!
    \brief     Operador asterisco: Devuelve el producto escalar de dos vectores.
    \attention Se sobrecarga el operador de asignacion "*"
    \param     v: Vector3D al que se multiplicaran sus componentes y se guardara el resultado en una variable.
    \return    variable double con el resultado de la multiplicacion de los parametros de un Vector3D.
    \pre       Ninguna
    \post      valordevuelto == (get1()*v.get1()) + (get2()*v.get2()) + (get3()*v.get3())
    \sa        get1(), get2(), get3(), operator*() de la clase Vector3D
    */

    double operator*(Vector3D v)const;

    /*!
    \brief     Operador ^: Devuelve un Vector3D que es el resultado del producto vectorial de dos vectores.
    \attention Se sobrecarga el operador de asignacion "^"
    \param     v: Vector3D al que se hara el producto vectorial.
    \return    Vector3D en el que se guardaran el resultado del producto vectorial.
    \pre       (angulo(v)) > 0
    \post      (dotProduct(valordevuelto) == 0) && (v.dotProduct(valordevuelto) == 0) && (valordevuelto.modulo() == modulo()*v.modulo()*sin(angulo(v)))
    \sa        get1(), get2(), get3(), set1(), set2(), set3(),  operator^() de la clase Vector3D
    */

    Vector3D operator^(Vector3D v)const;


    //! \name Funciones lectura y escritura de la clase Vector3D

    /*!
    \brief   Asigna a un Vector3D las coordenadas X,Y y Z lei­das desde el teclado
    \warning Se deben teclear numeros
    \return  Ninguna
    \pre     Ninguna
    \post    Ninguna
    \sa      set1(), set2(), set3() de la clase Vector3D
    */

    void leerVector3D();

    /*!
    \brief Escribe por pantalla las coordenadas de un Vector3D de la forma (x,y,z)
    \return  Ninguna
    \pre   Ninguna
    \post  Ninguna
    \sa     get1(), get2(), get3() de la clase Vector3D
    */

    void escribirVector3D() const;

  }; // Fin de la definición de la clase Vector3D


  //////////////////////////////////////////////////////////////////////////////////////

  //! \name Funciones que utilizan un objetos de la clase Vector3D, pero que no pertenecen a la clase Vector3D

  /*!
  \brief     Operador asterisco: Devuelve otro vector cuyas componentes se obtienen multiplicando por “k” las componentes del vector actual.
  \attention Se sobrecarga el operador de asignacion "*"
  \param     k: constante de tipo double
  \param     objeto: objeto de tipo Vector3D pasado como referencia constante
  \return    Vector3D cuyos parametros estan multiplicados por la constante k pasado por argumento.
  \pre       Ninguna
  \post      (vectorResultado->get1() == objeto.get1()*k) && (vectorResultado->get2() == objeto.get2()*k) && (vectorResultado->get3() == objeto.get3()*k)
  \sa         get1(), get2(), get3(), set1(), set2(), set3(),  operator*() de la clase Vector3D
  */

  Vector3D & operator* (double k, Vector3D const & objeto);

  /*!
  \brief      Sobrecarga del operador de entrada o lectura ">>"
  \n Lee las coordenadas del vertice separadas por espacios
  \attention  Funcion amiga de la clase Vector3D
  \param      istream: flujo de entrada
  \param      objeto Vector3D al que se le van a asignar nuevos valores.
  \return     flujo "stream"
  \pre        Ninguna
  \post       Ninguna
  \sa         operator>>
  */

  istream &operator>>(istream &stream, Vector3D &objeto);

  /*!
  \brief      Sobrecarga del operador de entrada o lectura "<<"
  \n Escribe las coordenadas del vertice separadas por espacios
  \attention  Funcion amiga de la clase Vector3D
  \param      ostream: flujo de salida
  \param      objeto Vector3D al que se le van a escribir sus valores.
  \return     flujo "stream"
  \pre        Ninguna
  \post       Ninguna
  \sa         operator<<
  */

  ostream &operator<<(ostream &stream, Vector3D const &objeto);


} // \brief Fin de namespace ed.

//  _VECTOR3D_HPP_
#endif
