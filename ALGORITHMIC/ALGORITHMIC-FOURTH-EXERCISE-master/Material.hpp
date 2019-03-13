#ifndef _MATERIAL_HPP
#define _MATERIAL_HPP


class Material
{
	private:
		int _etiqueta;
		int _volumen;
    int _precio;

	public:

		Material( int etiqueta=0, int volumen=0, int precio=0 ){
      _etiqueta = etiqueta;
      _volumen = volumen;
      _precio = precio;
    }

		int getEtiqueta(){
      return _etiqueta;
    }

		int getVolumen(){
      return _volumen;
    }

    int getPrecio(){
      return _precio;
    }

    void setEtiqueta(int etiqueta){
      _etiqueta = etiqueta;
    }

    void setVolumen(int volumen){
      _volumen = volumen;
    }

		void setPrecio(int precio){
      _precio = precio;
    }

};

#endif
