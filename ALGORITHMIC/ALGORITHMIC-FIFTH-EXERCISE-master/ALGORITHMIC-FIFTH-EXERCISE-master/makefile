NAME=principalmenu

#
OBJECTS = $(NAME).o funcionespractica5.o Moneda.o SistemaMonetario.o

#
CPPFLAGS = -c -g -Wall -ansi -O2 -lrt -std=c++11 -lm

INCLUDES = macros.hpp funcionespractica5.hpp Moneda.hpp SistemaMonetario.hpp

INCLUDES = funcionespractica5.hpp macros.hpp Moneda.hpp SistemaMonetario.hpp

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

funcionespractica4.o: funcionespractica5.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

SistemaMonetario.o: SistemaMonetario.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

Moneda.o: Moneda.cpp $(INCLUDES)
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
