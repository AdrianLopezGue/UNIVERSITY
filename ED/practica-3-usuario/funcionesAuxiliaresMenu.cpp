/*!
\file   funcionesAuxiliaresMenu.cpp
\brief  Funciones auxiliares para el programa principal de la práctica 3
\author Adrian Lopez Guerrero
\date 18/4/2017
\version 1.0
*/

#include "funcionesAuxiliaresMenu.hpp"
#include "macros.hpp"


// Para usar atoi


int ed::menu()
{
	int opcion;
	int posicion;

	// Se muestran las opciones del menú
	posicion=2;

	// Se borra la pantalla
	std::cout << CLEAR_SCREEN;

	PLACE(1,10);
	std::cout << BIBLUE;
	std::cout << "Programa secundario | Opciones del menú";
	std::cout << RESET;

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout<< "[1] Mostrar informacion acerca del monticulo";

	PLACE(posicion++,10);
	std::cout <<  "[2] Comprobar si el monticulo tiene mediciones";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[3] Cargar monticulo desde un fichero";

	PLACE(posicion++,10);
	std::cout << "[4] Grabar el monticulo en un fichero";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[5] Mostrar mediciones del monticulo";

	posicion++;

	PLACE(posicion++,10);
	std::cout <<  "[6] Borrar todas las mediciones del monticulo";

	PLACE(posicion++,10);
	std::cout << "[7] Consultar una medicion";

	PLACE(posicion++,10);
	std::cout << "[8] Insertar una medicion";

	PLACE(posicion++,10);
	std::cout << "[9] Borrar una medicion";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << BIRED << "[0] Salir";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << BIGREEN;
	std::cout << "Opción: ";
	std::cout << RESET;

	// Se lee el número de opción
	std::cin >> opcion;

	// Se elimina el salto de línea del flujo de entrada
	std::cin.ignore();

	return opcion;
}


//////////////////////////////////////////////////////////////////////////////

void ed::mostrarInformacionMonticulo(ed::MonticuloMediciones &monticulo){
	if(monticulo.isEmpty() == true){
		mostrarMonticuloEstaVacio();
		return;
	}
	else{

		int NumeroNiveles = log2 (monticulo.size());
		int posicion = 4;

		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,60);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,32);
		std::cout << IBLUE <<"INFORMACIÓN DEL MONTICULO"<<RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,60);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,28);
		std::cout << IBLUE <<"NUMERO DE ELEMENTOS: "<<RESET;
		std::cout << IGREEN << monticulo.size();
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,28);
		std::cout << IBLUE <<"NIVELES: "<<RESET;
		std::cout << IGREEN << NumeroNiveles+1;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;
	}
}

// OPCION 1
void ed::comprobarMonticuloVacio(ed::MonticuloMediciones &monticulo)
{
	if(monticulo.isEmpty() == true){
		mostrarMonticuloEstaVacio();
		return;
	}
	else{
		int posicion = 4;

		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,60);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,30);
		std::cout << IBLUE <<"EL MONTICULO "<<UNDERLINE<<"NO ESTA VACIO"<<RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,60);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,32);
		std::cout << IGREEN <<"	( "<<monticulo.size()<<" mediciones )  "<<RESET;
		PLACE(posicion,60);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;
	}
	return;
}

//////////////////////////////////////////////////////////////////////////////

// OPCION 2
void ed::cargarMonticulo(ed::MonticuloMediciones &monticulo, std::string nombrefichero)
{

	std::ifstream fichero(nombrefichero.c_str());
	int posicion = 4;

	if(fichero){

		char cadenaaux[256];

		double precipitacionaux;
		ed::Fecha fechaaux;

		monticulo.removeAll();

		while(fichero.getline(cadenaaux, 256, '-') != NULL){
			fechaaux.setDia(atoi(cadenaaux));

			fichero.getline(cadenaaux, 256, '-');
			fechaaux.setMes(atoi(cadenaaux));

			fichero.getline(cadenaaux, 256, ' ');
			fechaaux.setAgno(atoi(cadenaaux));

			fichero.getline(cadenaaux, 256, '\n');
			precipitacionaux = atof(cadenaaux);

			ed::Medicion medicionaux(fechaaux, precipitacionaux);

			monticulo.insert(medicionaux);
		}

		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"______________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,65);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,30);
		std::cout << IBLUE <<"MONTICULO CARGADO CORRECTAMENTE"<<RESET;
		PLACE(posicion,65);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,35);
		std::cout << IBLUE <<"MEDIANTE EL FICHERO: "<<RESET;
		PLACE(posicion,65);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,38);
		std::cout << IGREEN <<UNDERLINE<<nombrefichero<<RESET;
		PLACE(posicion,65);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,65);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|______________________________________|\n"<<RESET;

		fichero.close();
	}
	else{

		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,60);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,33);
		std::cout << IBLUE <<"EL FICHERO "<<UNDERLINE<<nombrefichero<<"\n"RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,33);
		std::cout << IBLUE <<"NO SE HA PODIDO ABRIR"<<RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;
	}

	return;
}

// OPCION 3
void ed::grabarMonticulo(ed::MonticuloMediciones &monticulo, std::string nombrefichero)
{

	if(monticulo.isEmpty() == true){
		mostrarMonticuloEstaVacio();
		return;
	}

	std::ofstream fichero(nombrefichero.c_str());
	int posicion = 4;

	if(fichero){

		ed::MonticuloMediciones monticuloaux = monticulo;

		while(monticuloaux.size() != 0){

			fichero<<monticuloaux.top();

			monticuloaux.remove();
		}

		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"______________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,65);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,30);
		std::cout << IBLUE <<"MONTICULO CARGADO CORRECTAMENTE"<<RESET;
		PLACE(posicion,65);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,35);
		std::cout << IBLUE <<"EN EL FICHERO: "<<RESET;
		PLACE(posicion,65);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,38);
		std::cout << IGREEN <<UNDERLINE<<nombrefichero<<RESET;
		PLACE(posicion,65);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,65);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|______________________________________|\n"<<RESET;

		fichero.close();
	}
	else{
		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,60);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,33);
		std::cout << IBLUE <<"EL FICHERO "<<UNDERLINE<<nombrefichero<<"\n"RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,33);
		std::cout << IBLUE <<"NO SE HA PODIDO ABRIR"<<RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;
	}

	return;
}

//////////////////////////////////////////////////////////////////////

// OPCION 4
void ed::mostrarMedicionesdeMonticulo(ed::MonticuloMediciones &monticulo)
{
	if(monticulo.isEmpty() == true){
		mostrarMonticuloEstaVacio();
		return;
	}
	else{
		monticulo.print();

		return;
	}
}

//

// OPCION 5
void ed::borrarTodosLasMedicionesdeMonticulo(ed::MonticuloMediciones &monticulo)
{

	if(monticulo.isEmpty() == true){
		mostrarMonticuloEstaVacio();
		return;
	}
	else{
		monticulo.removeAll();

		int posicion = 4;

		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"_____________________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,72);
		std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,30);
		std::cout << IBLUE <<"EL MONTICULO SE HA BORRADO CORRECTAMENTE"<<RESET;
		PLACE(posicion,72);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|_____________________________________________|\n"<<RESET;

		return;
	}
}


////////////////////////////////////////////////////////////////////////

// OPCION 6
void ed::consultarMedicionenMonticulo(ed::MonticuloMediciones &monticulo)
{

	if(monticulo.isEmpty() == true){
		mostrarMonticuloEstaVacio();
		return;
	}
	else{
		ed::MonticuloMediciones monticuloaux = monticulo;
		ed::Fecha fechaaux;
		int posicion = 11;

		fechaaux.leerFecha();

		if(fechaaux.esCorrecta() == true){
			while(monticuloaux.isEmpty() == false){
				if(monticuloaux.top().getFecha() == fechaaux){

					PLACE(posicion,27);
					std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

					posicion++;

					PLACE(posicion,26);
					std::cout<<BIYELLOW<<"|"<<RESET;
					PLACE(posicion,60);
					std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

					posicion++;

					PLACE(posicion,26);
					std::cout<<BIYELLOW<<"|"<<RESET;
					PLACE(posicion,32);
					std::cout << IBLUE <<"INFORMACIÓN DE LA MEDICION"<<RESET;
					PLACE(posicion,60);
					std::cout << BIYELLOW<<"|\n"<<RESET;

					posicion++;

					PLACE(posicion,26);
					std::cout<<BIYELLOW<<"|"<<RESET;
					PLACE(posicion,60);
					std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

					posicion++;

					PLACE(posicion,26);
					std::cout<<BIYELLOW<<"|"<<RESET;
					PLACE(posicion,28);
					std::cout << IBLUE << "DATOS DEL DIA : "<<RESET;
					std::cout << IGREEN << fechaaux.getDia()<<"-"<<fechaaux.getMes()<<"-"<<fechaaux.getAgno()<<RESET;
					PLACE(posicion,60);
					std::cout << BIYELLOW<<"|\n"<<RESET;

					posicion++;

					PLACE(posicion,26);
					std::cout<<BIYELLOW<<"|"<<RESET;
					PLACE(posicion,28);
					std::cout << IBLUE << "PRECIPITACION : "<<RESET;
					std::cout << IGREEN << monticuloaux.top().getPrecipitacion() <<RESET;
					PLACE(posicion,60);
					std::cout << BIYELLOW<<"|\n"<<RESET;

					posicion++;

					PLACE(posicion,26);
					std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;

					std::cin.ignore();

					return;
				}
				else{
					monticuloaux.remove();
				}
			}

			PLACE(posicion,27);
			std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

			posicion++;

			PLACE(posicion,26);
			std::cout<<BIYELLOW<<"|"<<RESET;
			PLACE(posicion,60);
			std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

			posicion++;

			PLACE(posicion,26);
			std::cout<<BIYELLOW<<"|"<<RESET;
			PLACE(posicion,33);
			std::cout << IBLUE <<"FECHA: "<<RESET;
			std::cout << IGREEN << fechaaux.getDia()<<"-"<<fechaaux.getMes()<<"-"<<fechaaux.getAgno()<<RESET;
			PLACE(posicion,60);
			std::cout << BIYELLOW<<"|\n"<<RESET;

			posicion++;

			PLACE(posicion,26);
			std::cout<<BIYELLOW<<"|"<<RESET;
			PLACE(posicion,60);
			std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

			posicion++;

			PLACE(posicion,26);
			std::cout<<BIYELLOW<<"|"<<RESET;
			PLACE(posicion,33);
			std::cout << IRED <<"NO SE ENCUENTRA EN"<<RESET;
			PLACE(posicion,60);
			std::cout << BIYELLOW<<"|\n"<<RESET;

			posicion++;

			PLACE(posicion,26);
			std::cout<<BIYELLOW<<"|"<<RESET;
			PLACE(posicion,36);
			std::cout << IRED <<"EL MONTICULO"<<RESET;
			PLACE(posicion,60);
			std::cout << BIYELLOW<<"|\n"<<RESET;

			posicion++;

			PLACE(posicion,26);
			std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;

			std::cin.ignore();

			return;
		}
		else{
			std::cin.ignore();

			return;
		}
	}
}

// OPCION 7
void ed::insertarMedicionenMonticulo(ed::MonticuloMediciones &monticulo)
{

	double dia, mes, agno;
	int posicion = 4;

	PLACE(posicion,27);
	std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,60);
	std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,28);
	std::cout << IBLUE << "DIA: "<<RESET;
	PLACE(posicion,60);
	std::cout << BIYELLOW<<"|\n"<<RESET;

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,28);
	std::cout << IBLUE << "MES:  "<<RESET;
	PLACE(posicion,60);
	std::cout << BIYELLOW<<"|\n"<<RESET;

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,28);
	std::cout << IBLUE << "AÑO: "<<RESET;
	PLACE(posicion,60);
	std::cout << BIYELLOW<<"|\n"<<RESET;

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;

	std::cout << PLACE(posicion-3, 33) << "\b";
	std::cout << " \b";
	std::cin >> dia;
	std::cout << PLACE(posicion-2, 33) << "\b";
	std::cout << " \b";
	std::cin >> mes;
	std::cout << PLACE(posicion-1, 33) << "\b";
	std::cout << " \b";
	std::cin >> agno;


	ed::Fecha fechaaux(dia, mes, agno);

	if(fechaaux.esCorrecta() == false){
		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,33);
		std::cout << IBLUE << "LA FECHA INTRODUCIDA"<<RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,36);
		std::cout << IBLUE << "NO ES CORRECTA"<<RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;

		std::cin.ignore();

		return;
	}
	else{

		float precipitacionaux;

		PLACE(posicion,27);
		std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|"<<RESET;
		PLACE(posicion,28);
		std::cout << IBLUE << "PRECIPITACION: "<<RESET;
		PLACE(posicion,60);
		std::cout << BIYELLOW<<"|\n"<<RESET;

		posicion++;

		PLACE(posicion,26);
		std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;

		std::cout << PLACE(posicion-1, 43) << "\b";
		std::cout << " \b";
		std::cin >> precipitacionaux;

		ed::Medicion medicionaux(fechaaux, precipitacionaux);

		PLACE(13,27);

		monticulo.insert(medicionaux);

		std::cin.ignore();

		return;
	}
}

// OPCION 9
void ed::borrarMediciondeMonticulo(ed::MonticuloMediciones &monticulo)
{
	if(monticulo.isEmpty() == true){
		mostrarMonticuloEstaVacio();
		return;
	}
	else{
		ed::MonticuloMediciones monticulorecorrer = monticulo;
		ed::MonticuloMediciones monticuloaux;

		ed::Fecha fechaaux;
		int posicion = 11;

		fechaaux.leerFecha();

		if(fechaaux.esCorrecta() == true){

					bool ComprobarBorrado = false;

					while(monticulorecorrer.isEmpty() == false){
						if(monticulorecorrer.top().getFecha() == fechaaux){
							monticulorecorrer.remove();

							ComprobarBorrado = true;
						}
						else{
							monticuloaux.insert(monticulorecorrer.top());
							monticulorecorrer.remove();
						}
					}

					monticulo = monticuloaux;

					if(ComprobarBorrado == true){

						PLACE(posicion,27);
						std::cout<<BIYELLOW<<"________________________________________"<<RESET<<"\n";

						posicion++;

						PLACE(posicion,26);
						std::cout<<BIYELLOW<<"|"<<RESET;
						PLACE(posicion,67);
						std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

						posicion++;

						PLACE(posicion,26);
						std::cout<<BIYELLOW<<"|"<<RESET;
						PLACE(posicion,33);
						std::cout << IBLUE <<"MEDICION CON FECHA: "<<RESET;
						std::cout << IGREEN << fechaaux.getDia()<<"-"<<fechaaux.getMes()<<"-"<<fechaaux.getAgno()<<RESET;
						PLACE(posicion,67);
						std::cout << BIYELLOW<<"|\n"<<RESET;

						posicion++;

						PLACE(posicion,26);
						std::cout<<BIYELLOW<<"|"<<RESET;
						PLACE(posicion,67);
						std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

						posicion++;

						PLACE(posicion,26);
						std::cout<<BIYELLOW<<"|"<<RESET;
						PLACE(posicion,33);
						std::cout << IGREEN <<"BORRADA CORRECTAMENTE"<<RESET;
						PLACE(posicion,67);
						std::cout << BIYELLOW<<"|\n"<<RESET;

						posicion++;

						PLACE(posicion,26);
						std::cout<<BIYELLOW<<"|________________________________________|\n"<<RESET;

					}
					else{
						PLACE(posicion,27);
						std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

						posicion++;

						PLACE(posicion,26);
						std::cout<<BIYELLOW<<"|"<<RESET;
						PLACE(posicion,60);
						std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

						posicion++;

						PLACE(posicion,26);
						std::cout<<BIYELLOW<<"|"<<RESET;
						PLACE(posicion,33);
						std::cout << IBLUE <<"FECHA: "<<RESET;
						std::cout << IGREEN << fechaaux.getDia()<<"-"<<fechaaux.getMes()<<"-"<<fechaaux.getAgno()<<RESET;
						PLACE(posicion,60);
						std::cout << BIYELLOW<<"|\n"<<RESET;

						posicion++;

						PLACE(posicion,26);
						std::cout<<BIYELLOW<<"|"<<RESET;
						PLACE(posicion,60);
						std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

						posicion++;

						PLACE(posicion,26);
						std::cout<<BIYELLOW<<"|"<<RESET;
						PLACE(posicion,33);
						std::cout << IRED <<"NO SE ENCUENTRA EN"<<RESET;
						PLACE(posicion,60);
						std::cout << BIYELLOW<<"|\n"<<RESET;

						posicion++;

						PLACE(posicion,26);
						std::cout<<BIYELLOW<<"|"<<RESET;
						PLACE(posicion,36);
						std::cout << IRED <<"EL MONTICULO"<<RESET;
						PLACE(posicion,60);
						std::cout << BIYELLOW<<"|\n"<<RESET;

						posicion++;

						PLACE(posicion,26);
						std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;
					}

					std::cin.ignore();
					return;
		}
		else{
			std::cin.ignore();
			return;
		}
	}
}

void ed::mostrarMonticuloEstaVacio(){

	int posicion = 4;

	PLACE(posicion,27);
	std::cout<<BIYELLOW<<"_________________________________"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,60);
	std::cout<<BIYELLOW<<"|"<<RESET<<"\n";

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|"<<RESET;
	PLACE(posicion,30);
	std::cout << IBLUE <<"EL MONTICULO ESTA "<<UNDERLINE<<"VACIO"<<RESET;
	PLACE(posicion,60);
	std::cout << BIYELLOW<<"|\n"<<RESET;

	posicion++;

	PLACE(posicion,26);
	std::cout<<BIYELLOW<<"|_________________________________|\n"<<RESET;
}
