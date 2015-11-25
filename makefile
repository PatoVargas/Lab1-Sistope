
DIR_OUTPUT = ./bin
DIR_SRC = ./src
NOMBRE_EJECUTABLE = lab1

# Esta es la target que se ejecuta por defecto si se escribe "make" en la consola
all: release

# Compilación principal del ejecutable
release:
	@echo 'Compilando target: $@'
	mkdir -p $(DIR_OUTPUT)
	gcc $(DIR_SRC)/lab1.c -o $(DIR_OUTPUT)/$(NOMBRE_EJECUTABLE) 
	@echo ' '
	@echo $@ compilado en el directorio $(DIR_OUTPUT)
	@echo "Ingrese al directorio '"$(DIR_OUTPUT)"' haciendo: cd "$(DIR_OUTPUT)
	@echo "Ejecute el programa haciendo: ./"$(NOMBRE_EJECUTABLE)""
	@echo ' '
	@echo "Si tiene problemas, en el fichero README blablabla"

#Compilación con opciones de debugueo y sin optimizaciones
debug:
	@echo 'Compilando target: $@'
	mkdir -p $(DIR_OUTPUT)
	gcc $(DIR_SRC)/lab1.c -o $(DIR_OUTPUT)/$(NOMBRE_EJECUTABLE) -g3 -Wall -pedantic -DDEBUG
	@echo ' '
	@echo $@ compilado en el directorio $(DIR_OUTPUT)
	@echo "Ingrese al directorio '"$(DIR_OUTPUT)"' haciendo: cd "$(DIR_OUTPUT)
	@echo "Ejecute el programa haciendo: ./"$(NOMBRE_EJECUTABLE)"
	@echo ' '
	@echo "Si tiene problemas, en el fichero README blablabla"


# Other Targets
clean:
	#Borro el contenido del directorio de compilación
	rm -rf $(DIR_OUTPUT)/*
	-@echo ' ' 
