#!/bin/bash

# Comprobacion de los argumentos
if [ $# != 2 ]
then
	echo -e "ERROR: se debe de escribir asi: ./ejercicio4.sh IPS.txt (segundos)"
else

	# Comprobamos si podemos abrir el fichero pasado
	if [ ! -e $1 ]; then
		echo -e "No se ha podido abrir el fichero pasado por argumento"
	else
		while read x
		do
			# ping evalua $x en funcion de los comandos que le digamos. -c sirve para decir el numero de paquetes que queremos enviarle a $x y -w para el max de segundos que
			# vamos a esperar a la respuesta
			t=$(ping $x -c 1 -w $2)

			# $? Es una variable que guarda el resultado del ultimo comando de bash utilizado. En este caso $? evalua ping y ve si ha habido error o no.
			if [ $? -ne 0 ]
			then
				echo "La IP $x no respondió tras $2 segundos."
			else
				echo "La IP $x respondió en $(echo $t | sed 's/.*time=\(.*\) ms.*ms/\1/') milisegundos."
			fi

		done < $1 | sort -k 6
	fi
fi
