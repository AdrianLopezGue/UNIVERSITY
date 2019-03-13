NAME=principalmenu

#
OBJECTS = $(NAME).o funcionespractica1.o funcionespractica2.o sistemaEcuaciones.o

#
CPPFLAGS = -c -g -Wall -ansi -O2 -lrt -std=c++11 -lm

INCLUDES = macros.hpp ClaseTiempo.hpp sistemaEcuaciones.hpp funcionespractica1.hpp funcionespractica2.hpp

INCLUDES = funcionespractica1.hpp funcionespractica2.hpp macros.hpp ClaseTiempo.hpp sistemaEcuaciones.hpp

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

#
funcionesAuxiliares.o: funcionesAuxiliares.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

funcionespractica1.o: funcionespractica1.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

funcionespractica2.o: funcionespractica2.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

sistemaEcuaciones.o: sistemaEcuaciones.cpp $(INCLUDES)
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
