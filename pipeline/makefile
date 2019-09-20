#////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#/////////////////////////////////////////////////////////////////// VARIABLES //////////////////////////////////////////////////////////////////////////
#////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CC = gcc
CL = clean
BIN_DIR = ./bin
SRC_DIR = ./src
OBJ_DIR = ./obj
MAIN_OBJ = $(OBJ_DIR)/main.o
PIPE_OBJ = $(OBJ_DIR)/pipeline.o
MAIN_SRC = $(SRC_DIR)/main.c
PIPE_SRC = $(SRC_DIR)/pipeline.c
EXEC = $(BIN_DIR)/pipeline
C_FLAGS = -g -Wall

#////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////////////////////////// TARGETS ///////////////////////////////////////////////////////////////////////////
#////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# Esta es la target que se ejecuta por defecto si se escribe "make" en la consola
.PHONY: all
all: $(EXEC)

# Compilación principal del ejecutable
$(EXEC): clean bin obj $(MAIN_OBJ) $(PIPE_OBJ)
	@echo '-------------------------------------------------------------------------'
	@echo ' => Compiling target "$(@F)"'
	$(CC) $(C_FLAGS) $(MAIN_OBJ) $(PIPE_OBJ) -o $@
	#@echo 'Compilando target: $@'
	#gcc $(SRC_DIR)/ejemPunteros.c -o $(DIR_OUTPUT)/$(NOMBRE_EJECUTABLE)-O2
	#@echo ' '
	#@echo $@ compilado en el directorio $(DIR_OUTPUT)
	#@echo "Ingrese al directorio '"$(DIR_OUTPUT)"' haciendo: cd "$(DIR_OUTPUT)
	#@echo "Ejecute el programa haciendo: ./"$(NOMBRE_EJECUTABLE)""
	#@echo ' '
	#@echo "Si tiene problemas, en el fichero README blablabla"
	@echo '-------------------------------------------------------------------------'

$(MAIN_OBJ): $(MAIN_SRC)
	@echo '-------------------------------------------------------------------------'
	@echo ' => Compiling target "$(@F)"'
	@echo '    "$(@F)" compiled in the directory "$(@D)"'
	$(CC) $(C_FLAGS) -c $< -o $@
	@echo '-------------------------------------------------------------------------'

$(PIPE_OBJ): $(PIPE_SRC)
	@echo '-------------------------------------------------------------------------'
	@echo ' => Compiling target "$(@F)"'
	@echo '    "$(@F)" compiled in the directory "$(@D)"'
	$(CC) $(C_FLAGS) -c $< -o $@
	@echo '-------------------------------------------------------------------------'

.PHONY: bin
bin: 
	@echo '-------------------------------------------------------------------------'
	@echo ' => Creating direcotry "$@"'
	mkdir $(BIN_DIR)
	@echo '-------------------------------------------------------------------------'

.PHONY: obj
obj: 
	@echo '-------------------------------------------------------------------------'
	@echo ' => Creating direcotry "$@"'
	mkdir $(OBJ_DIR)
	@echo '-------------------------------------------------------------------------'

#////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#Compilación con opciones de debugueo y sin optimizaciones
.PHONY: debug
debug:
	@echo 'Compilando target: $@'
	mkdir -p $(BIN_DIR)
	gcc $(SRC_DIR)/main.c -o $(BIN_DIR)/$(EXE_NAME) -g3 -Wall -pedantic -DDEBUG
	@echo ' '
	@echo $@ compilado en el directorio $(BIN_DIR)
	@echo "Ingrese al directorio '"$(BIN_DIR)"' haciendo: cd "$(BIN_DIR)
	@echo "Ejecute el programa haciendo: ./"$(EXE_NAME)"
	@echo ' '
	@echo "Si tiene problemas, en el fichero README blablabla"

#////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
.PHONY: clean
clean: 
	@echo '-------------------------------------------------------------------------'
	@echo ' => Deleting "$(BIN_DIR)" directory and "$(OBJ_DIR)" directory compilation contents'
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)
	@echo '-------------------------------------------------------------------------'
