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
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

Image* reading (char fileName[]) {

    FILE *f = fopen(fileName, "rb");

    if (f != NULL) {

        int height, width;
        png_byte color_type, bit_depth;
        png_bytep* row = NULL;
        
        png_structp png_image = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        png_infop png_info = png_create_info_struct(png_image);

        png_init_io(png_image, f);
        png_read_info(png_image, png_info);

        height = png_get_image_height(png_image, png_info);
        width = png_get_image_width(png_image, png_info);
        color_type = png_get_color_type(png_image, png_info);
        bit_depth  = png_get_bit_depth(png_image, png_info);

        if(bit_depth == 16)
            png_set_strip_16(png_image);

        if( (color_type == PNG_COLOR_TYPE_PALETTE) )
            png_set_palette_to_rgb(png_image);

        if( (color_type == PNG_COLOR_TYPE_GRAY) && (bit_depth < 8) )
            png_set_expand_gray_1_2_4_to_8(png_image);

        if(png_get_valid(png_image, png_info, PNG_INFO_tRNS))
            png_set_tRNS_to_alpha(png_image);

        if( (color_type == PNG_COLOR_TYPE_RGB) || (color_type == PNG_COLOR_TYPE_GRAY) || (color_type == PNG_COLOR_TYPE_PALETTE) )
            png_set_filler(png_image, 0xFF, PNG_FILLER_AFTER);

        if( (color_type == PNG_COLOR_TYPE_GRAY) || (color_type == PNG_COLOR_TYPE_GRAY_ALPHA) )
            png_set_gray_to_rgb(png_image);

        png_read_update_info(png_image, png_info);

        row = (png_bytep*)malloc(sizeof(png_bytep) * height);

        if (row != NULL) {

            for(int y = 0; y < height; y++) {
                row[y] = (png_byte*)malloc(png_get_rowbytes(png_image, png_info));
                png_read_image(png_image, row);
            }
        } 

        else {

        }

        fclose(f);
        png_destroy_read_struct(&png_image, &png_info, NULL);
        return createStructImage (height, width, row);
    }

    else {

    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

Image* createStructImage (int height, int width, png_bytep* row) {

    Image* image = createPointerImage (height, width);
    int n, m;

    for (n = 0; n < height; n++) {
        png_bytep current_row = row[n];

        for (m = 0; m < width; m++) {
            png_bytep current_px = &(current_row[m * 4]);
            int red = current_px[0];
            int green = current_px[1];
            int blue = current_px[2];
            int gray = ( (54 * red) + (183 * green) + (19 * blue) ) / 256;

            image -> matrix[n][m] = gray;
        }
    }

    return image;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

Image* createPointerImage (int height, int width) {

    Image* image = (Image*)malloc(sizeof(Image));
    int n, m;

    if (image != NULL) {

        image -> height = height;
        image -> width = width;
        image -> matrix = (int**)malloc(sizeof(int*) * height);

        if ( (image -> matrix) != NULL) {

            for (n = 0; n < height; n++) {
                image -> matrix[n] = (int*)malloc(sizeof(int) * width);

                if ( (image -> matrix[n]) != NULL) {

                    for (m = 0; m < width; m++) {
                        image -> matrix[n][m] = 0;
                    }
                }
                else {

                }
            }
        }
        else {

        }
    }

    else {

    }

    return image;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

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

