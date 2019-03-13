#!/bin/bash

var=$(lscpu | grep -E '^CPU\(s\):' | sed 's/ //g' | sed 's/^.*:\(.*\)/\1/')

cat /proc/cpuinfo | sed 's/^model name.*: \(.*\)/Modelo de procesador: \1/' | sed 's/^cpu MHz.*: \(.*\)/Megahercios: \1/' | sed 's/^siblings.*: \(.*\)/Número de hilos máximo de ejecución: '$var'/' | sed 's/^cache size.*: \(.*\)/Tamaño de la caché: \1/' | sed 's/vendor_id.*: \(.*\)/ID vendedor: \1/' | sed -e 's/^[^NMIT].*//' -e '/^$/d'

echo "Puntos de montaje: "

cat /proc/mounts | sed -e 's/^\(.*\) \(.*\) \(.*\) \(.*\) \(.*\) \(.*\)/--> Punto de montaje: \2, Dispositivo: \1, Tipo de dispositivo: \3/'

echo "Particiones y número de bloques: "

cat /proc/partitions | sed -n -e '1,2!p' | sed -e 's/^\(.*\) \(.*\) \(.*\) \(.*\)/--> Partición: \4, Número de bloques: \3/'
