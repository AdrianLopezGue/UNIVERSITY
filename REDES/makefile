NAME=Servidor-minas

NAME2=Cliente-minas

#
OBJECTS = $(NAME).o juego.o tablero.o Jugador.o

OBJECTS2 = $(NAME2).o juego.o tablero.o Jugador.o

#
CPPFLAGS = -c -g -Wall -ansi -O2 -lrt

INCLUDES = juego.hpp tablero.hpp Jugador.hpp

# Macros predefinidas
#
# $@: nombre del objetivo
# $^: todas las dependencias
# $<: primera dependencia
#

objetivo: $(NAME).exe

objetivo: $(NAME2).exe

#Opciones para NO depurar los asertos
#ndebug: CPPFLAGS += -DNDEBUG
#ndebug: objetivo

# Primer objetivo
$(NAME).exe: $(OBJECTS)
			@echo "Generando " $@
			@g++ $^ -o $@


$(NAME2).exe: $(OBJECTS2)
			@echo "Generando " $@
			@g++ $^ -o $@


#
$(NAME).o: $(NAME).cc $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<


$(NAME2).o: $(NAME2).cc $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
juego.o: juego.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

tablero.o: tablero.cc $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

Jugador.o: Jugador.cc $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#




# Borrado
.PHONY: clean
clean:
	@echo "Borrando los ficheros superfluos"
	@rm -f $(OBJECTS) *~
	@rm -f $(OBJECTS2) *~
