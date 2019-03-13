NAME=principalmenu

#
OBJECTS = $(NAME).o funcionespractica6.o estructura.o

#
CPPFLAGS = -c -g -Wall -ansi -O2 -lrt -std=c++11 -lm

INCLUDES = funcionespractica6.hpp macros.hpp estructura.hpp

# Macros predefinidas
#
# $@: nombre del objetivo
# $^: todas las dependencias
# $<: primera dependencia
#

objetivo: $(NAME).exe

#Opciones para NO depurar los asertos
ndebug: CPPFLAGS += -DNDEBUG
ndebug: objetivo

# Primer objetivo
$(NAME).exe: $(OBJECTS)
			@echo "Generando " $@
			@g++ $^ -o $@
#
$(NAME).o: $(NAME).cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

funcionespractica6.o: funcionespractica6.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

estructura.o: estructura.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

# Generación de la documentación
doc: Doxyfile
	@echo "Generando la documentación con doxygen"
	@doxygen

# Borrado
.PHONY: clean
clean:
	@echo "Borrando los ficheros superfluos"
	@rm -f $(OBJECTS) *~
