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
void writing (Image* image, char* name) {
    FILE* filePtr;
    png_structp pngPtr = NULL;
    png_infop infoPtr = NULL;
    int i, j;
    png_byte** rowPointers = NULL;

    int pixel_size = 1;
    int depth = 8;
    
    filePtr = fopen (name, "wb");
    if (!filePtr) {
        fprintf(stderr, "No se encontro el archivo con nombre \"%s\".\n", name);
    }

    pngPtr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    
    if (!pngPtr) {
        fprintf(stderr, "No se pudo crear \"pngPtr\".\n");
    }
    
    infoPtr = png_create_info_struct (pngPtr);
    
    if (!infoPtr) {
        fprintf(stderr, "No se pudo crear \"infoPtr\".\n");
    }
    

    // Si existe un problema con el archivo posterior a su metadata
    if (setjmp(png_jmpbuf(pngPtr))) {
        fprintf(stderr, "Error durante png_read_image.\n");
    }
    
    // Se dejan los atributos por defecto al guardar la imagen

    png_set_IHDR (pngPtr,
                  infoPtr,
                  image->width,
                  image->height,
                  depth,
                  PNG_COLOR_TYPE_GRAY,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);

    rowPointers = png_malloc (pngPtr, sizeof(png_byte*) * image->height);
    for (j = 0; j < image->height; j++) {
        png_byte *row = png_malloc (pngPtr, sizeof(u_int8_t) * image->width * pixel_size);
        rowPointers[j] = row;
        for (i = 0; i < image->width; i++) {
            *row++ = image->matrix[j][i];
        }
    }

    png_init_io (pngPtr, filePtr);
    png_set_rows (pngPtr, infoPtr, rowPointers);
    png_write_png (pngPtr, infoPtr, PNG_TRANSFORM_IDENTITY, NULL);

    for (j = 0; j < image->height; j++) {
        png_free (pngPtr, rowPointers[j]);
    }
    png_free (pngPtr, rowPointers);

    fclose(filePtr);

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