#!/bin/bash

echo "*******"
echo "1) Líneas con la duracion de las peliculas: "
cat peliculas.txt | grep -E '.hr ..min'

echo "*******"
echo "2) Líneas con el país de las peliculas: "
cat peliculas.txt | grep -E '(../../..)'

echo "*******"
echo "3) Solo el país de las peliculas: "
cat peliculas.txt | grep -o -E '\-.*\-' | sed -r -e 's/-$//' | sed -r -e 's/-//'

echo "*******"

peliculas2016=$(cat peliculas.txt | grep -E '(../../2016)' | wc -l)
peliculas2017=$(cat peliculas.txt | grep -E '(../../2017)' | wc -l)

echo "4) Hay $peliculas2016 peliculas del 2016 y $peliculas2017 peliculas del 2017: "


echo "*******"
echo "5) Eliminar lineas vacias: "
cat peliculas.txt | grep -E '.'

echo "*******"
echo "6) Líneas que empiezan la letra E (con o sin espacios antes): "
cat peliculas.txt | grep -E '^ *E'

echo "*******"
echo "7) Líneas que contienen d,l o t, una vocal y la misma letra: "
cat peliculas.txt | grep -E '([dlt])[aeiou]\1'

echo "*******"
echo "8) Líneas que contienen ocho aes o más: "
cat peliculas.txt | grep -E '(.*a){8,8}'

echo "*******"
echo "9) Líneas que terminan con tres puntos y no empiezan por espacio: "
cat peliculas.txt | grep -E '\.\.\.$' | grep -v -E '^ '

echo "*******"
echo "10) Mostrar entre comillas las vocales con tilde: "
cat peliculas.txt | sed -r -e 's/([áéíóú])/"\1"/'
