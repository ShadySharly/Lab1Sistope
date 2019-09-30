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
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

Image* convolution (Image* image, char* maskFileName) {

    Image* new_image = addZeroes (image);
    Image* convolved_image = createPointerImage ( (image -> height), (image -> width) );
    int n, m, up_left, up_mid, up_right, left, mid, right, down_left, down_mid, down_right, new_pixel;

    if ( (new_image != NULL) && (convolved_image != NULL) ) {

        for (n = 1; n < ( (new_image -> height) - 1); n++) {

            for (m = 1; m < ( (new_image -> width) - 1); m++) {
                up_left = (new_image -> matrix[n - 1][m - 1]) * mask[0][0];
                up_mid = (new_image -> matrix[n - 1][m]) * mask[0][1];
                up_right = (new_image -> matrix[n - 1][m + 1]) * mask[0][2];
                left = (new_image -> matrix[n][m - 1]) * mask[1][0];
                mid = (new_image -> matrix[n][m]) * mask[1][1];
                right = (new_image -> matrix[n][m + 1]) * mask[1][2];
                down_left = (new_image -> matrix[n + 1][m - 1]) * mask[2][0];
                down_mid = (new_image -> matrix[n + 1][m]) * mask[2][1];
                down_right = (new_image -> matrix[n + 1][m + 1]) * mask[2][2];

                new_pixel = (up_left + up_mid + up_right + left + mid + right + down_left + down_mid + down_right);
                new_pixel = new_pixel / 9;

                convolved_image -> matrix[n - 1][m - 1] = new_pixel;
            }
        }
    }

    else {

    }

    return convolved_image;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

int** readMask (char* maskFileName) {

    FILE* f = fopen (maskFileName, "r");
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
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

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