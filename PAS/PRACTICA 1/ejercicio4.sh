#!/bin/bash

# La variable contador muestra el numero de veces que aparece un archivo que no sea una carpeta dentro de la ruta que le indiquemos
contador=0

for i in $(find)
do
	if [ ! -d $i ] # Si no es un fichero, aumenta el contador
	then
		let contador=$contador+1
	fi
done


echo "El numero de archivos en la carpeta actual es $contador"
echo "-------------------"


echo "Esta seria la lista de usuario conectados en este momento: "

# Guarda los nombres de usuarios en la variable Nombreusuarios
Nombreusuarios=$(who -q)

# Esto empieza a leer de derecha a izquierda (desde el numero total de usuarios). El comando borra todo hasta la primera N, por lo que borrara "Nº de usuarios: x", dejando solo los
# nombres de usuarios en una linea
Nombreusuarios="${Nombreusuarios%N*}"

# Como los nombres de usuarios vienen en una linea, los espacios que separan los nombres los sustituimos por saltos de linea con tr, y con uniq -u borramos los usuarios que aparezcan
# a la vez

Nombreusuarios=$(echo "$Nombreusuarios" | tr ' ' '\n' | uniq -u)
echo "$Nombreusuarios"
echo "-------------------"


read -t5 -p "¿Que caracter quieres contar? " caracter

# Si en 5 segundos no introduce el caracter pone como predeterminado el caracter "a"
if [ -z $caracter ]
then
	caracter="a"
fi


# Lee el numero de veces que aparece los elementos en el nombre de los ficheros.
numerodeveces=0

for i in $(find -name "*$caracter*")
do

	echo "$i" > fich.txt
	# wc recibe el nombre del fichero con lineas separadas con un solo caracter. El numero de lineas es el numero de veces que ha aparecido el caracter.
	let numerodeveces=$numerodeveces+$(grep o -o fich.txt | wc -l)

done

echo "El caracter $caracter aparece $numerodeveces en nombres de ficheros o carpetas contenidos en la carpeta actual"
rm fich.txt
