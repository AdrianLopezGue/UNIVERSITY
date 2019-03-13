#!/bin/bash

#Comprobacion de argumentos

if [ $# -eq 0 ]
then
	echo "Tienes que introducir al menos una carpeta a la que hacer la copia de seguridad."
	exit 1
fi

#Creando la carpeta copia (en el caso de que no exista)

if [ ! -d Copia ]
then
	echo "Creando la carpeta copia"
	mkdir -p Copia
fi

#Fecha en segundos

fecha="$(date +%s)"

nombrearchivos=""

#Guardamos el nombre de los ficheros que vamos a guardar dentro de la variable nombrearchivos
for i
do
	nombrearchivos=$nombrearchivos" "$i
done


tar czf $(pwd)/Copia/copia-$LOGNAME-$fecha.tar.gz $nombrearchivos
echo "La copia de seguridad se ha creado correctamente"

for i in $(find $(pwd)/Copia/ -mmin +3,33333 -name "*.tar.gz")
do
	echo "Borrando $(dirname $i)$(basename $i) de $(stat -c %w $i) segundos..."
	rm -r $i
done
