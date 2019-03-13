#!/bin/bash

# COMPROBACION DE LOS ARGUMENTOS PASADOS

if [ $# -gt 0 ] && [ $# -lt 3 ]
then
	if [ $# -eq 1 ]
	then
		numerobytes=0
	else
		numerobytes=$2
	fi
else
	echo "Tienes que introducir al menos un argumento"
	exit 1
fi

nombredirectorio=$1

echo "Nombre, LongitudUsuario, FechaModificacion, FechaAcceso, Tamano, Bloques, Permisos, Ejecutable"

for i in $(find $nombredirectorio -size +$numerobytes)
do

	echo -n "$(basename $i); $(echo -n $LOGNAME | wc -c); $(stat -c %w $i) $(stat -c %x $i); $(stat -c %s $i); $(stat -c %b $i); $(stat -c %A $i);"

	if [ -x $i ]
	then
		echo 1
	else
		echo 0
	fi

done | sort -nk 5
