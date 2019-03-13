#!/bin/bash

#COMPROBAMOS EL FICHERO

if [ $# -ne 1 ]
then
	echo "Se debe de introducir el nombre del fichero"
	exit 1
fi

echo "===="
echo "Listado de archivos ocultos del directorio /home/$USER"

# i guarda los nombres de los ficheros que empiecen por . (archivos ocultos)
for i in $(ls -a /home/$USER | grep -E '^\.')
do

# expr permite almacenar en la variable tamano la longitud del nombre del fichero
tamano=$(expr length $i)
echo $tamano $i

# en el done ordenamos por el tamano y con el sed eliminamos el tamano (no lo necesitamos)
done | sort -n | sed -r -e 's/^[0-9]*//'

echo "===="
echo "El fichero a procesar es $1"

cat $1 | sed -e '/^ *$/d' > $1.sinLineasVacias

echo "El fichero sin lineas vacías se ha guardado en $1.sinLineasVacias"

echo "===="
echo "Listado de los procesos ejecutados por el usuario $USER:"

# ps eo permite mostrar todos los procesos (e) y especificar el formato (elementos) que queramos  tomar del ps (o). Con el primer sed
# eliminamos la primera linea que no es util y con el segundo sed lo ponemos en el formato pedido.
ps eo pid,start_time,fname | sed '1d' | sed -r -e 's/(.*) (.*) (.*)/PID: "\1" Hora: "\2" Ejecutable: "\3"/'
