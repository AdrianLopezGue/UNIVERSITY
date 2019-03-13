#!/bin/bash

# FUNCION RECURSIVA

function recursiva(){
for fichero in "$1"/*
do
	if [ ! -d $fichero ]
	then
		echo "<li>$(dirname $fichero)/$(basename $fichero)</li>" >> $nombrefichero.html
	else
		echo "<ul><li><strong>$fichero</strong></li>" >> $nombrefichero.html
		recursiva $fichero
		echo "</ul>" >> $nombrefichero.html
	fi
done
}

if [ $# -ne 1 ]
then
	echo "Debes introducir la ruta"
	exit 1
fi

nombrefichero=$1
nombrefichero=${nombrefichero##*/}

echo "$nombrefichero"

# Pasamos mediante ">>" los elementos necesarios para crear el archivo html necesario
# Remarcar que el primer echo que se hace (el de abajo) utiliza ">" para que vuelva a crear el fichero html en caso de que exista un fichero con el mismo nombre
# que el que se va a crear

echo "<html>" > $nombrefichero.html
echo "<head>" >> $nombrefichero.html
echo "<title>Listado del directorio $nombrefichero</title>" >> $nombrefichero.html
echo "</head>" >> $nombrefichero.html
echo "<body>" >> $nombrefichero.html
echo "<style type="text/css">" >> $nombrefichero.html
echo "	body { font-family: sans-serif;}" >> $nombrefichero.html
echo "</style>" >> $nombrefichero.html
echo "<h1>Listado del directorio $nombrefichero</h1>" >> $nombrefichero.html

#Llamamos a la funcion recursiva
recursiva "$1"


echo "</body>" >> $nombrefichero.html
echo "</html>" >> $nombrefichero.html
