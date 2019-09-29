/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// DIRECTIVES /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <png.h>

# include "../../structs.h"
# include "reading.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// FUNCTIONS //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - fileName: Nombre del archivo que contiene la imagen a leer
// - OUTPUTS: Estructura "Image" que contiene la imagen en representacion matricial de enteros en escala de grises "matrix", y sus dimensiones
//            respectivas "height" y "width"
// - DESCRIPTION: Toma el nombre del archivo de entrada y lee la imagen con el nombre correspondiente, utilizando estructuras predifinidas en la
//                directiva "png.g" se extrae la informacion de la imagen como los valores RGB de cada pixel y se aplica una formula entre estos valores
//                para determinar el unico valor en escala de grises para cada uno de estos y se almacena en la matriz de la estructura de salida.

Image* reading (char fileName[]) {

    Image* image = NULL;
    FILE* f = fopen(fileName, "rb");

    if (f != NULL) {

        int n, width, height;
        png_byte color_type;
        png_byte bit_depth;
        png_bytep* row = NULL;

        // Se crean las estructuras para manejar la informacion proveniente de "f"
        png_structp png_image = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if(!png_image)
            abort();

        png_infop info_image = png_create_info_struct(png_image);

        if(!info_image) 
            abort();

        if(setjmp(png_jmpbuf(png_image))) 
            abort();

        png_init_io(png_image, f);
        png_read_info(png_image, info_image);

        // Se obtiene la informacion contenida en "png_image" e "info_image" para obtener las dimensiones, la profundidad de bit y el tipo de 
        // color de la imagen y se almacenan en variables respectivas
        width = png_get_image_width(png_image, info_image);
        height = png_get_image_height(png_image, info_image);
        color_type = png_get_color_type(png_image, info_image);
        bit_depth = png_get_bit_depth(png_image, info_image);

        // Tomando en cuenta la informacion de la imagen anterior se modifican ciertos parametros de la imagen "png_image", tales como
        // tipo de color en que viene esta de entrada Ej: RGB, escala de grises, etc.
        if(bit_depth == 16)
            png_set_strip_16(png_image);

        if(color_type == PNG_COLOR_TYPE_PALETTE)
            png_set_palette_to_rgb(png_image);

        if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
            png_set_expand_gray_1_2_4_to_8(png_image);

        if(png_get_valid(png_image, info_image, PNG_INFO_tRNS))
            png_set_tRNS_to_alpha(png_image);

        if( (color_type == PNG_COLOR_TYPE_RGB) || (color_type == PNG_COLOR_TYPE_GRAY) || (color_type == PNG_COLOR_TYPE_PALETTE) )
            png_set_filler(png_image, 0xFF, PNG_FILLER_AFTER);

        if( (color_type == PNG_COLOR_TYPE_GRAY) || (color_type == PNG_COLOR_TYPE_GRAY_ALPHA) )
            png_set_gray_to_rgb(png_image);

        png_read_update_info(png_image, info_image);

        if (row)
            abort();

        // Se almacena memoria para "row" y se almacenan los bytes de cada fila n de la imagen en esta
        row = (png_bytep*)malloc(sizeof(png_bytep) * height);

        for(n = 0; n < height; n++) {
            row[n] = (png_byte*)malloc(png_get_rowbytes(png_image, info_image));
        }

        png_read_image(png_image, row);
        png_destroy_read_struct(&png_image, &info_image, NULL);
        fclose(f);

        // Se traspasa la informacion de "row" a la estructura "image"
        image = createStructImage(height, width, row);
    } 

    return image;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - height: Altura de la imagen 
//           - width: Anchura de la imagen
//           - row: Puntero que contiene los valores de cada pixel(cada uno es un arreglo) en su representacion RGB
//                 (R = pixel[0], G = pixel[1], B = pixel[2])
// - OUTPUTS: Estructura Image con los valores de "row" cargadas en la matriz de "image" con los valores de cada pixel en su represeentacion en escala de
//            grises obtenida a traves de una formula 
// - DESCRIPTION: Toma los valores RGB de cada pixel contenidas en "row" aplicando una transformacion utilizando la formula:
//                (grey = (R * 54 + G * 183 * B * 19) / 256 ), y los traspasa a la matriz de enteros de "image"

Image* createStructImage (int height, int width, png_bytep* row) {

    Image* image = createPointerImage (height, width);
    int n, m;

    for (n = 0; n < height; n++) {
        png_bytep current_row = row[n];

        for (m = 0; m < width; m++) {
            // Se asigna a una variable el pixel (byte) actual de la iteracion
            png_bytep current_px = &(current_row[m * 4]);
            // Se obtiene el RGB del pixel anterior
            int red = current_px[0];
            int green = current_px[1];
            int blue = current_px[2];
            // Se aplica la formula multiplicando por una constante cada valor del RGB para obtener el valor en escala de grises
            int gray = ( (54 * red) + (183 * green) + (19 * blue) ) / 256;

            // Se almacena el valor anterior en la matriz
            image -> matrix[n][m] = gray;
        }
    }

    return image;
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
// - OUTPUTS: -
// - DESCRIPTION: Muestra por consola la matriz de "image" donde cada posicion de esta corresponde al valor gris de cada pixel

void printImage (Image* image) {

    int n, m;
    for(n = 0; n < (image -> height); n++) {

        for (m = 0; m < (image -> width); m++) {
            printf("%3d", image -> matrix[n][m]);
        }
        printf("\n");
    }
    printf("\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

