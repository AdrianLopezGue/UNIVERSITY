#!/bin/bash

# COMPROBACION DE LOS ARGUMENTOS PASADOS

if [ $# -ne 1 ]
then
  echo "Debe de introducirse por argumento"
  exit 1
fi

numeroarchivosc=$(find $1 -name "*.c" | wc -l)
numeroarchivosh=$(find $1 -name "*.h" | wc -l)

echo "Tenemos $numeroarchivosc ficheros con extension .c y $numeroarchivosh ficheros con extension .h"

for i in $(find $1 -name "*.c" -or -name "*.h")
do
  echo "El fichero $i tiene $(wc -l < $i) lineas y $(wc -c < $i) caracteres"

done | sort -nrk 8
