/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// DIRECTIVES /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
#include "../../structs.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// MAIN ////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

int main(int argc, char** argv) {
    Image* image;
    read(STDIN_FILENO, &image, sizeof(Image));//lectura de la imagen
    //Tirar clasification
    write(STDOUT_FILENO, &image, sizeof(Image));//Escribir en el pipe
    wait(NULL);
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////