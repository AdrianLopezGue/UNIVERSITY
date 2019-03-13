NAME=principalmenu

#
OBJECTS = $(NAME).o funcionespractica4.o Moneda.o SistemaMonetario.o Material.o SistemaMateriales.o

#
CPPFLAGS = -c -g -Wall -ansi -O2 -lrt -std=c++11 -lm

INCLUDES = macros.hpp funcionespractica4.hpp Moneda.hpp SistemaMonetario.hpp Material.hpp SistemaMateriales.hpp

INCLUDES = funcionespractica4.hpp macros.hpp Moneda.hpp SistemaMonetario.hpp Material.hpp SistemaMateriales.hpp

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

funcionespractica4.o: funcionespractica4.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

SistemaMonetario.o: SistemaMonetario.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

Moneda.o: Moneda.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

SistemaMateriales.o: SistemaMateriales.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

Material.o: Material.cpp $(INCLUDES)
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
