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
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

void getParams (int argc, char** argv, int* cValue, char* mValue, int* nValue, int* bValue) {

    int c;
    char* m_string = (char*)malloc(sizeof(char));
    char* n_string = (char*)malloc(sizeof(char));
    *bValue = 0;

    // c: Cantidad de Imagenes (int)
    // m: Archivo con la mascara o kernel (string)
    // n: Umbral de negrura (nearly black) (porcentaje int)
    // b: Bandera (Mostrar resultados por pantalla (1) o no (0)) (binario)
    // Ejecutar como:
    //      ./pipeline -c (cValue) -m (mValue) -n (nValue) -b
    while ( (c = getopt (argc, argv, "c:m:n:b")) != -1) {

        switch (c) {
            case 'c':
                strcpy(m_string, optarg);
                // Verificacion de que se ingresa una cantidad de imagenes valida, osea un numero entero positivo
                if (!isInteger(m_string) || (strcmp(m_string, "0") == 0) ) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un ENTERO POSITIVO MAYOR A 0.\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }

                *cValue = atoi(optarg);
                break;
            
            case 'm':
                strcpy(mValue, optarg);
                
                if (!exist(mValue)) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un ARCHIVO EXISTENTE.\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }

                printf("mValue: %s\n", mValue);

                break;
            
            case 'n':
                strcpy(n_string, optarg);

                if (!isInteger(n_string)) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un ENTERO POSITIVO.\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }

                *nValue = atoi(optarg);

                if (!isPercentage(*nValue)) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un ENTERO POSITIVO entre 0 y 100.\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }
            
                printf("nValue: %d\n", *nValue);
                break;
            
            case 'b':
                *bValue = 1;
                printf("bValue: %d\n", *bValue);
                break;
            
            case '?':

                if ( (optopt == 'c') || (optopt == 'm') || (optopt == 'n') ) { 
                    fprintf (stderr, " => La opcion -%c requiere un argumento.\n", optopt);
                }

            default:
                break;
            }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

int exist (char* fileName) {

    FILE* f = fopen(fileName, "r");

    if (f != NULL) {
        fclose(f);
        return 1;
    }
        
    fclose(f);
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

int isInteger (char* input) {

    int c;

    for (c = 0; c < strlen(input); c++) {

        if (!isdigit(input[c]))
            return 0;
    }

    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

int isPercentage (int input) {

    if ( (input >= 0) && (input <= 100) )
        return 1;

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

void pipeline () {
    
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////