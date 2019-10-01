/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// DIRECTIVES /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# include <getopt.h>
# include <ctype.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# include "pipeline.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// FUNCTIONS //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - argc: Numero de argumentos introducidos por consola
//           - argv: Arreglo de punteros a caracteres correspondiente a los argumentos ingresados 
//           - cValue: Puntero que almacena la cantidad de imagenes a leer
//           - mValue: Puntero que almacena el nombre del archivo que contiene la matriz (mascara) para la convolucion 
//           - nValue: Puntero que almacena el umbral de "negrura" para la clasificacion "nearly black"
//           - bValue: Puntero que almacena la opcion de mostrar o no por consola los resultados obtenidos
// - OUTPUTS: -
// - DESCRIPTION: Obtiene los valores ingresados por consola verificando la validez de cada una de las banderas (flags) y los valores
//                por los que estan acompañadas, almacenandolas en las variables de entrada pasadas por referencia. Si no se cumplen algunas de 
//                las condiciones necesarias respetando la estructura de entrada y los tipos de datos el programa es abortado y no continua su ejecucion.

void getParams (int argc, char** argv, char* cValue, char* mValue, char* nValue, char* bValue) {

    int c;
    int int_n;
    strcpy(bValue, "0");

    // c: Cantidad de Imagenes (int)
    // m: Archivo con la mascara o kernel (string)
    // n: Umbral de negrura (nearly black) (porcentaje int)
    // b: Bandera (Mostrar resultados por pantalla (1) o no (0)) (binario)
    // Ejecutar como:
    //      ./pipeline -c (cValue) -m (mValue) -n (nValue) -b
    while ( (c = getopt (argc, argv, "c:m:n:b")) != -1) {

        switch (c) {
            case 'c':
                strcpy(cValue, optarg);
                // Verificacion de que se ingresa una cantidad de imagenes valida, osea un numero entero positivo
                if (!isInteger(cValue) || (strcmp(cValue, "0") == 0) ) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un ENTERO POSITIVO MAYOR A 0.\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }

                printf(" => Cantiad de imagenes (-c): %s\n", cValue);
                break;
            
            case 'm':
                strcpy(mValue, optarg);
                // Verificacion que el arcivo ingresado existe 
                if (!exist(mValue)) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un ARCHIVO EXISTENTE.\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }

                printf(" => Ruta de la mascara (-m): %s\n", mValue);
                break;
            
            case 'n':
                strcpy(nValue, optarg);
                int_n = atoi(optarg);
                // Verificacion de que se ingresa una cantidad de imagenes valida, osea un numero entero positivo
                if (!isInteger(nValue)) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un ENTERO POSITIVO.\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }

                // Verificacion de que se ingresa una cantidad de imagenes valida, osea un numero entero positivo entre 0 y 100
                if (!isPercentage(int_n)) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un ENTERO POSITIVO ENTRE 0 Y 100.\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }
            
                printf(" => Umbral (-n): %s\n", nValue);
                break;
            
            case 'b':
                strcpy(bValue, "1");

                printf(" => Opcion b (-b): %s\n", bValue);
                break;
            
            case '?':
                // Verificacion de existencia de argumentos
                if ( (optopt == 'c') || (optopt == 'm') || (optopt == 'n') ) { 
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => La opcion -%c requiere un argumento.\n", optopt);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }
                // VErificacion de la validez de las banderas
                else if (isprint (optopt)) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => Opcion -%c desconocida.\n", optopt);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }

            default:
                break;
            }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - fileName: Nombre del archivo a leer
// - OUTPUTS: Valor booleano 1 si el archivo existe, 0 en caso contrario
// - DESCRIPTION: Verifica que el archivo con el nombre "fileName" existe y devuelve la verificacion.

int exist (char* fileName) {

    FILE* f = fopen(fileName, "r");

    if (f != NULL) {
        fclose(f);
        return 1;
    }
      
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - input: Cadena de caracteres a evaluar si corresponde a un numero entero positivo o no
// - OUTPUTS: Valor booleano 1 si es entero positivo, 0 en caso contrario
// - DESCRIPTION: Verifica si una cadena de caracteres de entrada posee en cada una de sus posiciones un caracter que es
//                digito y es positivo

int isInteger (char* input) {

    int c;

    for (c = 0; c < strlen(input); c++) {

        if (!isdigit(input[c]))
            return 0;
    }

    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: input: Numero por determinar si es porcentaje o no
// - OUTPUTS: Valor booleano 1 si es un porcentaje valido, 0 en caso contrario
// - DESCRIPTION: Determina si la entrada es considerada como un porcentaje, es decir que su valor este entre el rango de 0 y 100 y que sea entero

int isPercentage (int input) {

    if ( (input >= 0) && (input <= 100) )
        return 1;

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////