/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// DIRECTIVES /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# include "../../structs.h"
# include "convolution.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// FUNCTIONS //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - image: Estructura Image con la informacion de una imagen en particular, proveniente de la lectura
//           - mask_file_name: Ruta del archivo que contiene la mascara para la convolucion, tambien llamada como "kernel"
// - OUTPUTS: Estructura imagen anterior convolcionada
// - DESCRIPTION: La convolucion consiste en tomar una mascara en forma de matriz, en este caso de dimensiones 3 x 3, y sobreponerla por cada pixel de
//                la imagen, multiplicando las posiciones adyacentes de la mascara y la imagen, uncluyendo el pixel actual con la posicion
//                correspondiente de la mascara, finalmente estos valores (pixel * mask) se promedian y el valor final es reemplazado en el pixel actual
//                de la matriz de la imagen.

Image* convolution (Image* image, char* mask_file_name) {
    
    // Para emplear la convolucion en los bordes de la matriz de la imagen, se agrega un borde de 0 a la matriz, con lo que la matriz
    // resulta de la altura y ancho originales mas dos respectivamente.
    Image* new_image = addZeroes (image);
    Image* convolved_image = createPointerImage ( (image -> height), (image -> width) );
    // Se almacena la matriz de la mascara en un arreglo de enteros
    int** mask = readMask (mask_file_name);
    // Se definen las variables que almacenaran las multiplicaciones de cada pixel de cada posicion respecto a un pixel central (mid)
    int n, m, up_left, up_mid, up_right, left, mid, right, down_left, down_mid, down_right, new_pixel;

    if ( (new_image != NULL) && (convolved_image != NULL) ) {

        for (n = 1; n < ( (new_image -> height) - 1); n++) {

            for (m = 1; m < ( (new_image -> width) - 1); m++) {
                // Se multiplica la matriz con la mascara respecto al pixel en la posicion (n, m)
                up_left = (new_image -> matrix[n - 1][m - 1]) * mask[0][0];
                up_mid = (new_image -> matrix[n - 1][m]) * mask[0][1];
                up_right = (new_image -> matrix[n - 1][m + 1]) * mask[0][2];
                left = (new_image -> matrix[n][m - 1]) * mask[1][0];
                mid = (new_image -> matrix[n][m]) * mask[1][1];
                right = (new_image -> matrix[n][m + 1]) * mask[1][2];
                down_left = (new_image -> matrix[n + 1][m - 1]) * mask[2][0];
                down_mid = (new_image -> matrix[n + 1][m]) * mask[2][1];
                down_right = (new_image -> matrix[n + 1][m + 1]) * mask[2][2];

                // Se suman los valores y se saca el promedio
                new_pixel = (up_left + up_mid + up_right + left + mid + right + down_left + down_mid + down_right);
                new_pixel = new_pixel / 9;

                // Se asigna el valor anterior a la matriz de la imagen resultante
                convolved_image -> matrix[n - 1][m - 1] = new_pixel;
            }
        }
    }

    else {

    }

    return convolved_image;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - mask_file_name: Ruta del archivo que contiene la mascara para la convolucion, tambien llamada como "kernel"
// - OUTPUTS: Matriz de enteros con los valores de la mascara del archivo de entrada "mask_file_name"
// - DESCRIPTION: Lectura y almacenamiento de los valores del archivo de entrada, almacenados en un doble puntero entero

int** readMask (char* mask_file_name) {

    FILE* f = fopen (mask_file_name, "r");
    int** mask = NULL;
    int n, m, value;

    if (f != NULL) {
        mask = (int**)malloc(sizeof(int*) * 3);

        if (mask != NULL) {

            for (n = 0; n < 3; n++) {
                mask[n] = (int*)malloc(sizeof(int) * 3);

                if (mask[n] != NULL) {
                    
                    for (m = 0; m < 3; m++) {
                        fscanf(f, "%d", &value);
                        mask[n][m] = value;
                    }
                }
                else {

                }
            }
        }
        else{

        }
    }
    
    return mask;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - image: Estructura Image con la informacion de una imagen en particular
// - OUTPUTS: Estructura Image con los bordes en 0
// - DESCRIPTION: Toma una imagen y a su matriz se le agrega un borde de 0

Image* addZeroes (Image* image) {

    int n, m;
    Image* new_image = createPointerImage ( (image -> height) + 2, (image -> width) + 2);

    if (new_image != NULL) {

        for (n = 0; n < (image -> height); n++) {

            for (m = 0; m < (image -> width); m++) {
                new_image -> matrix[n + 1][m + 1] = image -> matrix[n][m];
            }
        }    
    }

    else {

    }

    return new_image;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - height: Altura de la imagen
//           - width: Anchura de la image
// - OUTPUTS: - image: Estructura Image inicializada en memoria, y con puros 0 en cada posicion (n, m) de la matriz de dimensiones "height" y "width"
// - DESCRIPTION: Toma las dimensiones de una imagen cualquiera e inicializa una estructura Image cuya matriz tiene las dimensiones anteriores y contiene
//                solo 0 (Se define por defecto los valores MAX_HEIGHT y MAX_WIDTH como la resolucion maxima de cada imagen, por lo que al recorrer
//                la matriz se consideran los valores "height" y "width" en vez de los anteriores.

Image* createPointerImage (int height, int width) {

    Image* image = (Image*)malloc(sizeof(Image));
    int n, m;

    if (image != NULL) {

        image -> height = height;
        image -> width = width;

        for (n = 0; n < MAX_HEIGHT; n++) {

            for (m = 0; m < MAX_WIDTH; m++) {
                image -> matrix[n][m] = 0;
            }
        }
    }

    else {

    }

    return image;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////