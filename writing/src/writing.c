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
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:
void writing (Image image, char* name) {
    FILE* file;
    png_structp png = NULL;
    png_infop infoPtr = NULL;
    int i, j;
    png_byte** rowPointers = NULL;

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
    
    infoPtr = png_create_info_struct (png);
    
    if (!infoPtr) {
        fprintf(stderr, "No se pudo crear \"infoPtr\".\n");
    }
    
    if (setjmp(png_jmpbuf(png))) {
        fprintf(stderr, "Error durante png_read_image.\n");
    }
    
    // put the atributes
    png_set_IHDR (png,
                  infoPtr,
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
    /*
    png_write_info(png, infoPtr);
    png_write_image(png, rowPointers);
    png_write_end(png, NULL);
    */
    
    png_init_io (png, file);
    png_set_rows (png, infoPtr, rowPointers);
    png_write_png (png, infoPtr, PNG_TRANSFORM_IDENTITY, NULL);
    
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