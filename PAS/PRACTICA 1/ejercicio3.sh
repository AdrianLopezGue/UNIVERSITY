#!/bin/bash

# COMPROBACION DE LOS ARGUMENTOS PASADOS

if [ $# -eq 0 ]
then
	echo "Debe de haber al menos un argumento"
	exit 1
else
	if [ $# -lt 4 ]
	then
		case $# in
			1)
			ruta=$1
			umbral1=10000
			umbral2=100000
			;;
			2)
			ruta=$1
			umbral1=$2
			umbral2=100000
			;;
			3)
			ruta=$1
			umbral1=$2
			umbral2=$3
			;;
		esac
	else
		echo "Se han introducido demasiados argumentos"
		exit
	fi
fi

ruta=$(pwd)
rutapequenos=$(echo "$ruta/pequenos")
rutamedianos=$(echo "$ruta/medianos")
rutagrandes=$(echo "$ruta/grandes")

if [ -d pequenos ]
then
	echo "Borrando carpeta pequenos"
	rm -r pequenos
fi

if [ -d medianos ]
then
	echo "Borrando carpeta medianos"
	rm -r medianos
fi

if [ -d grandes ]
then
	echo "Borrando carpeta grandes"
	rm -r grandes
fi


echo "Creando carpetas pequenos medianos grandes"
mkdir pequenos medianos grandes



# Busca los archivos cuyo tamano sea menor que el indicado en el umbral1 y los guarda en la carpeta pequenos
for archivo in $(find $ruta -size -"$umbral1"c)
do

if [ -f $archivo ]
then
	rutaarchivo=$(echo "$(dirname $archivo)/$(basename $archivo)")
	cp $rutaarchivo $rutapequenos
fi
done


# Busca los archivos cuyo tamano sea mayor que el indicado en el umbral1 y menor que el indicado en el umbral2 y los guarda en la carpeta meidanos
for archivo in $(find $ruta -size +"$umbral1"c -and -size -"$umbral2"c)
do

if [ -f $archivo ]
then
	rutaarchivo=$(echo "$(dirname $archivo)/$(basename $archivo)")
	cp $rutaarchivo $rutamedianos
fi
done


# Busca los archivos cuyo tamano sea mayor que el indicado en el umbral2 y los guarda en la carpeta grandes
for archivo in $(find $ruta -size +"$umbral2"c)
do

if [ -f $archivo ]
then
	rutaarchivo=$(echo "$(dirname $archivo)/$(basename $archivo)")
	cp $rutaarchivo $rutagrandes
fi
done
