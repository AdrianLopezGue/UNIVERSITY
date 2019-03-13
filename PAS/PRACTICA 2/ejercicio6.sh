#!/bin/bash

# Comprobacion de los argumentos
if [ $# -ne 1 ]
	then
	echo "ERROR: Tienes que introducir la ruta de la shell"
	exit 1
fi

# Modificamos el fichero passwd para que sea mas facil de manipular y lo guardamos a un fichero auxiliar.
cat /etc/passwd | sed 's/::/: :/' > aux.txt

while read i
do
	if [ $1 == $(echo -e -n $i | sed -r -e 's/^(.*):(.*):(.*):(.*):(.*):(.*):(.*).*$/\7/') ]
	then

echo '=========='
echo -e -n $i | sed -r -e 's/^(.*):(.*):(.*):(.*):(.*):(.*):(.*).*$/Logname: \1\n->UID: \3\n->Grupo: \1\n->GID: \4\n->gecos: \5\n->Home: \6\n->Shell por defecto: \7\n/'

	# Guardamos el usuario para comprobarlo posteriormente
	usuario=$(echo -e -n $i | sed -r -e 's/^(.*):(.*):(.*):(.*):(.*):(.*):(.*).*$/\1/')

		# Comprobamos si al utilizar el comando who, el elemento usuario aparece alguna vez. Si es mas grande que 0, significa que el usuario esta logueado.
		if [ $(who | grep $usuario | wc -l) -gt 0 ]
			then
		 		echo '->Logueado: 1'
			else
		 		echo '->Logueado: 0'
		fi
	fi

done < aux.txt

rm aux.txt
