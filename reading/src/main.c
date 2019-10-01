/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// DIRECTIVES /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <png.h>

# include "reading.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// MAIN ////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - argv[1]: Cantidad de imagenes de entrada
//           - argv[2]: Nombre o ruta del archivo que contiene la mascara
// - OUTPUTS: -
// - DESCRIPTION: Ejecuta la etapa de "reading" del pipeline, leyendo las imagenes de entrada, y ejecutando el pipeline.

int main(int argc, char** argv) {

    char* number_images = argv[1];
    char* mask_file_name = argv[2];
    char* threshold = argv[3];
    char* b = argv[4];

    pipeline (mask_file_name, number_images, threshold, b);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


