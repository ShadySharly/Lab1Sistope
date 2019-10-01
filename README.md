# Lab1Sistope

# ORGANIZACION ###################################################################################################################
# El programa se encuentra dividido en 7 programas, cada uno con su respectivo directorio cada uno con los siguientes contenidos:

# -> src: Carpeta donde se encuentra el codigo fuente del programa (.c y .h)
# -> Makefile

# Ademas de los 7 directorios el programa cuenta con un archivo .h de estructuras compartidas para los 7 programas, una carpeta
# de imagenes que se utilizaron de prueba para evaluar el desempeño del programa y una carpeta con los archivos
# de "mascaras" para la etapa de convolucion

# COMPILACION ####################################################################################################################
# Cada programa en su respectivo directorio posee su makefile respectivo lo que permite compilar por separado cada uno de estos
# abriendo la consola y ejecutando el comando "make", lo que genera instantaneamente dos carpetas en eldirectorio del programa
# actual:

# -> obj: Contiene los objetos generados por la compilacion de cada archivo .c de la carpeta src, y que corresponde al "main", y 
#         al archivo de funciones que utiliza el main llamado con el nombre de cada programa.

# -> bin: Contiene el archivo ejecutable generado de la compilacion del programa utilizando los archivos obj anteriores, el cual
#         se genera con el nombre del programa respectivo y es el que es ejecutado.

# Asi como cada "sub-programa" puede ser ejecutado por separado, el programa tambien posee un propio makefile con los mismos
# comandos de cada sub-programa y que permite compilar todos los programas, y al igual generando las mismas carpetas anteriores.
# Para ejecutar el programa utilizando todos los demas ejecutables de cada sub-programa se va a la carpeta bin del directorio
# raiz del programa y se ejecuta el archivo con nombre "pipeline".
# La compilacion cuenta con el paso a paso de cada sub-programa y de sus .c respectivos por consola, permitiendo ver que archivo
# se compila, el comando utilizado y donde es almacenado.

# El makefile "maestro" cuenta con los mismos comandos de cada sub-programa, "make" para compilar el programa completo, compilando
# cada makefile de cada sub-programa, y "make clean" para limpiar cada carpeta generada por el makefile de cada sub-programa
# (elimina bin y obj)

# EJECUCION ####################################################################################################################
# AL compilar el programa:

# - Compilar el programa con: make
# - Dirigirse a la carpeta bin del directorio raiz: cd bin
# . Ejecutar el comando: ./pipeline -c (cantidad de imagenes) -m (ruta del archivo con la mascara) -n (umbral de negrura) -b (bandera)

# Al ejecutar dependiendo de si se especifica la bandera "b", se muestran los resultados por pantalla, en caso contrario solo se
# generan las imagenes de salida en la misma carpeta bin donde esta ubicado el ejecutable.

# ###############################################################################################################################