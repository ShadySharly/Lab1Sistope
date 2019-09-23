#////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#/////////////////////////////////////////////////////////////////// VARIABLES //////////////////////////////////////////////////////////////////////////
#////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CC = gcc
CL = clean
BIN_DIR = ./bin
SRC_DIR = ./src
OBJ_DIR = ./obj
MAIN_OBJ = $(OBJ_DIR)/main.o
PIPE_OBJ = $(OBJ_DIR)/rectification.o
MAIN_SRC = $(SRC_DIR)/main.c
PIPE_SRC = $(SRC_DIR)/rectification.c
EXEC = $(BIN_DIR)/rectification
C_FLAGS = -g -Wall

#////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////////////////////////// TARGETS ///////////////////////////////////////////////////////////////////////////
#////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# Esta es la target que se ejecuta por defecto si se escribe "make" en la consola
.PHONY: all
all: inimsj $(EXEC) endmsj

# Compilación principal del ejecutable
$(EXEC): clean bin obj $(MAIN_OBJ) $(PIPE_OBJ)
	@echo '-------------------------------------------------------------------------'
	@echo ' => Compiling target "$(@F)"'
	$(CC) $(C_FLAGS) $(MAIN_OBJ) $(PIPE_OBJ) -o $@
	@echo ' => "$(@F)" compiled in the directory "$(@D)"'
	@echo ' => Enter the directory "$(@D)" by typing: cd $(@D)'
	@echo ' => Execute the program by typing: ./$(@F)'
	@echo ' => For any problem check the README file'
	@echo '-------------------------------------------------------------------------'

$(MAIN_OBJ): $(MAIN_SRC)
	@echo '-------------------------------------------------------------------------'
	@echo ' => Compiling target "$(@F)"'
	$(CC) $(C_FLAGS) -c $< -o $@
	@echo ' => "$(@F)" compiled in the directory "$(@D)"'
	@echo '-------------------------------------------------------------------------'

$(PIPE_OBJ): $(PIPE_SRC)
	@echo '-------------------------------------------------------------------------'
	@echo ' => Compiling target "$(@F)"'
	$(CC) $(C_FLAGS) -c $< -o $@
	@echo ' => "$(@F)" compiled in the directory "$(@D)"'
	@echo '-------------------------------------------------------------------------'

.PHONY: inimsj
inimsj:
	@echo '/////////////////////////////////////////////////////////////////////////'
	@echo ' => Compiling "rectification" program'
	@echo '-------------------------------------------------------------------------'

.PHONY: endmsj
endmsj:
	@echo '/////////////////////////////////////////////////////////////////////////'

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
	@echo ' => Deleting directory "$(BIN_DIR)" and directory "$(OBJ_DIR)" compilation contents'
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)
	@echo '-------------------------------------------------------------------------'

#////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////