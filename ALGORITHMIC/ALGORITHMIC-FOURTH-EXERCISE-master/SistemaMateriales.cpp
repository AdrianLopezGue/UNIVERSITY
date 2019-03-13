#include "SistemaMateriales.hpp"

bool SistemaMateriales::leerFichero(string nombreFichero){
	std::ifstream ficheroin(nombreFichero.c_str());

	if(ficheroin){
		Material materialaux;

		int etiqueta;
		int volumen;
		int precio;

		while(ficheroin >> etiqueta >> volumen >> precio){

			materialaux.setEtiqueta(etiqueta);
			materialaux.setVolumen(volumen);
			materialaux.setPrecio(precio);

			insertarMaterial(materialaux);
		}

		ficheroin.close();
		return true;
	}

	else{
		return false;
	}
}

void SistemaMateriales::printMateriales(){
	std::cout << "\n";
	for (unsigned int i=0; i < getSizeMateriales(); i++){
		std::cout << BPURPLE;
		std::cerr << "Material: " << getMaterial(i).getEtiqueta() << "\n\tVolumen -> " << getMaterial(i).getVolumen() << "\n\tPrecio -> " << getMaterial(i).getPrecio() << "\n\n";
		std::cout << RESET;
	}
}
