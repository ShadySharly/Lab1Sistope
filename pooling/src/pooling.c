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
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

Image* pooling (Image* image) {

    int n, m;
    int new_n = 0; 
    int new_m = 0;

    Image* image_with_zeroes = addZeroes (image);
    int new_height = (image_with_zeroes -> height) / 3;
    int new_width = (image_with_zeroes -> width) / 3;
    Image* pooled_image = createPointerImage (new_height, new_width);

    for (n = 0; n < (image_with_zeroes -> height); n+=3) {

        for (m = 0; m < (image_with_zeroes -> width); m+=3) {
            int current_n = n;
            int current_m = m;
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
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

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
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

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
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

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
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

void copyImage (Image* source_image, Image* destiny_image) {

    int n, m;

    for (n = 0; n < (source_image -> height); n++) {

        for (m = 0; m < (source_image -> width); m++) {
            destiny_image -> matrix[n][m] = source_image -> matrix[n][m];
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////