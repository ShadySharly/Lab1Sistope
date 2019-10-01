/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// DIRECTIVES /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# include "../../structs.h"
# include "pooling.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// FUNCTIONS //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - image: Estructura Image con la informacion de una imagen en particular, proveniente desde la rectificacion
// - OUTPUTS: Imagen con su matriz aplicado el pooling
// - DESCRIPTION: El pooling consiste en tomar la matriz de la imagen de entrada y evaluar cada 9 pixeles, es decir, evaluar cada submatriz de 3 x 3 y 
//                encontrar el maximo valor de estos pixeles, el mayor de estos se reemplaza en una nueva matriz en la posicion (n, m), como se evaluan
//                conjuntos de submatrices de 3 x 3, la matriz resultante resulta con dimensiones divididas por 3 de la matriz original.

Image* pooling (Image* image) {

    int n, m;
    int new_n = 0; 
    int new_m = 0;

    // Como no es seguro que la imagen de entrada tenga dimensiones multiplo de 3, se agregan filas y columnas de 0 para que esto se cumpla
    // Como no existen valores mayores que 0, no influyen en la resolucion del maximo de cada submatriz
    Image* image_with_zeroes = addZeroes (image);
    // Se almacenan las dimensiones de la nueva matriz
    int new_height = (image_with_zeroes -> height) / 3;
    int new_width = (image_with_zeroes -> width) / 3;
    // Se crea la nueva imagen con la matriz de las dimensiones anteriores
    Image* pooled_image = createPointerImage (new_height, new_width);

    for (n = 0; n < (image_with_zeroes -> height); n+=3) {

        for (m = 0; m < (image_with_zeroes -> width); m+=3) {
            int current_n = n;
            int current_m = m;
            // Se obitne el maximo pixel
            int max = maxPixel (image_with_zeroes, current_n, current_m);
            pooled_image -> matrix[new_n][new_m] = max;
            new_m++;
        }
        new_m = 0;
        new_n++;
    }
    return pooled_image;
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - image: Estructura Image con la informacion de una imagen en particular
//           - current_n: Indice de la fila actual de la matriz de la imagen "image"
//           - current_m: Indice de la columna actual de la matriz de la imagen "image"
// - OUTPUTS: Valor del maximo pixel de una submnatriz especifica
// - DESCRIPTION: Determina el pixel con el valor maximo en la submatriz de 3 x 3 con pixel inicial en la pisicion current_n x current_m

int maxPixel (Image* image, int current_n, int current_m) {

    int n, m;
    int max = 0;

    for (n = current_n; n < (current_n + 3); n++) {

        for (m = current_m; m < (current_m + 3); m++) {
            
            if ( (image -> matrix[n][m]) > max ) {
                max = (image -> matrix[n][m]);
            }
        }
    }

    return max;
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
// - INPUTS: - image: Estructura Image con la informacion de una imagen en particular
// - OUTPUTS: Imagen con las columnas y filas de 0 agregadas
// - DESCRIPTION: Si las dimensiones de la matriz de la imagen de entrada no es multiplo de 3, se le agregan filas y columnas de 0 para
//                que se cumpla dicha condicion

Image* addZeroes (Image* image) {

    int remaining_height = (image -> height) % 3;
    int remaining_width = (image -> width) % 3;
    

    if ( (remaining_height != 0) || (remaining_width != 0) ) {
        int zeroes_height = 3 - remaining_height;
        int zeroes_width = 3 - remaining_width;

        if (remaining_height == 0) {
            zeroes_height = 0;
        }

        if (remaining_width == 0) {
            zeroes_width = 0;
        }
        
        Image* new_image = createPointerImage ( (image -> height) + zeroes_height, (image -> width) + zeroes_width);
        copyImage (image, new_image);
        return new_image;
    }  

    return image;    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - source_image: Imagen fuente cuyos datos desean ser replicados
//           - destiny_image: Imagen de destino que se desea replicar datos de una imagen fuente
// - OUTPUTS: -
// - DESCRIPTION: Replica los datos desde una imagen fuente hacia una de destino

void copyImage (Image* source_image, Image* destiny_image) {

    int n, m;

    for (n = 0; n < (source_image -> height); n++) {

        for (m = 0; m < (source_image -> width); m++) {
            destiny_image -> matrix[n][m] = source_image -> matrix[n][m];
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////