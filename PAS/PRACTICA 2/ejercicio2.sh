#!/bin/bash

# sed -r -e '/^=*$/d' - sirve para eliminar las lineas "========"
# sed -r -e 's/^([^|])/Título: \1/' - una vez que todo el fichero esta con el formato |-> (...), los titulos son los unicos que quedan sin ese formato, por lo que podemos modificarlos.

cat peliculas.txt | sed -r -e 's/\((.*)\).*/|-> Fecha de estreno: \1/' | sed -r -e 's/Dirigida por (.*)/|-> Director: \1/' | sed -r -e 's/Reparto: (.*)/|-> Reparto: \1/' | sed -r -e 's/(.hr ..min)/|-> Duración: \1/' | sed -r -e '/^=*$/d' |  grep -E '^ ' -v | sed -r -e 's/^([^|])/Título: \1/'
