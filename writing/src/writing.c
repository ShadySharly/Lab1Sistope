/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// DIRECTIVES /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include "../../structs.h"
# include <png.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "writing.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// FUNCTIONS //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: Estructura imagen, que contiene la matriz con los datos de la imagen y el string que tiene el nombre del archivo de salida para la escritura de la nueva imagen png
// - OUTPUTS: Ninguna (es un procedimiento)
// - DESCRIPTION: Se crea el archivo de salida, para luego definir los parametros que se escribiran en la imagen png. Luego de analizar si se crearon los datos
//                se definen los parametros de la imagen dejando la mayoria como los valores por deferto, y se le atribuyen los particulares de la imagen.
//                Finalmente se reconstruye el row  para ir escribiendolo uno a uno en el archivo. Finalmente se ciera el archivo.
// - INPUTS: Estructura imagen, que contiene la matriz con los datos de la imagen y el string que tiene el nombre del archivo de salida para la escritura de la nueva imagen png
// - OUTPUTS: Ninguna (es un procedimiento)
// - DESCRIPTION: Se crea el archivo de salida, para luego definir los parametros que se escribiran en la imagen png. Luego de analizar si se crearon los datos
//                se definen los parametros de la imagen dejando la mayoria como los valores por deferto, y se le atribuyen los particulares de la imagen.
//                Finalmente se reconstruye el row  para ir escribiendolo uno a uno en el archivo. Finalmente se ciera el archivo.

void writing (Image image, char* name) {
    FILE* file;
    png_structp png = NULL;
    png_infop p_info = NULL;
    png_byte** rowPointers = NULL;
    int i, j;
    int pixel_size = 1;
    int depth = 8;
    
    file = fopen (name, "wb");
    if (!file) {
        fprintf(stderr, "No se encontro el archivo con nombre \"%s\".\n", name);
    }

    png = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fprintf(stderr, "No se pudo crear \"png\".\n");
    }
    p_info = png_create_info_struct (png);
    if (!p_info) {
        fprintf(stderr, "No se pudo crear \"p_info\".\n");
    }
    if (setjmp(png_jmpbuf(png))) {
        fprintf(stderr, "Error durante png_read_image.\n");
    }
    
    // put the atributes
    png_set_IHDR (png,
                  p_info,
                  image.width,
                  image.height,
                  depth,
                  PNG_COLOR_TYPE_GRAY,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);

    rowPointers = png_malloc (png, sizeof(png_byte*) * image.height);
    for (j = 0; j < image.height; j++) {
        png_byte *row = png_malloc (png, sizeof(u_int8_t) * image.width * pixel_size);
        rowPointers[j] = row;
        for (i = 0; i < image.width; i++) {
            *row++ = image.matrix[j][i];
        }
    }
    
    png_init_io (png, file);
    png_set_rows (png, p_info, rowPointers);
    png_write_png (png, p_info, PNG_TRANSFORM_IDENTITY, NULL);
    
    //releasing memory 
    for (j = 0; j < image.height; j++) {
        png_free (png, rowPointers[j]);
    }
    png_free (png, rowPointers);
    //Closing png
    fclose(file);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - image: Estructura Image con la informacion de una imagen en particular
// - OUTPUTS: -
// - DESCRIPTION: Muestra por consola la matriz de "image" donde cada posicion de esta corresponde al valor gris de cada pixel

void printImage (Image image) {

    int n, m;
    for(n = 0; n < (image.height); n++) {

        for (m = 0; m < (image.width); m++) {
            printf("%5d", image.matrix[n][m]);
        }
        printf("\n");
    }
    printf("\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////