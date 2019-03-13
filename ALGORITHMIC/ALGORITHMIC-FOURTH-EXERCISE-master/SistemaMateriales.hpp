#ifndef _SISTEMAMATERIALES_HPP_
#define _SISTEMAMATERIALES_HPP_

#include <cstdlib>
#include <fstream>
#include <ctime>

#include <string>
#include <vector>
#include <iostream>

#include "Material.hpp"
#include "macros.hpp"

using namespace std;

class SistemaMateriales{

	private:
		std::vector<Material> _materiales;

	public:

		SistemaMateriales(){
			 _materiales.resize(0);
		 }

		Material getMaterial(int index) {
			return _materiales[index];
		}

		void setMaterial(int index, Material material){
			_materiales[index] = material;
		}

		unsigned int getSizeMateriales(){
			return _materiales.size();
		}

		void insertarMaterial(Material material){
			_materiales.push_back(material);
		}

		void printMateriales();
		bool leerFichero(string nombreFichero);

};

#endif
