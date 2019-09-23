/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// DIRECTIVES /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# include "structs.h"
# include "convolution.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// FUNCTIONS //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

void convolution (Image* image, int mask[3][3]) {

    int n;
    int m;
    Image* convolved_image = reserveImage (image ->height, image -> width);

    for (n = 1; n < (image -> height - 1); n++) {

        for (m = 1; m < (image -> width - 1); m++) {

            int new_pixel;
            int up_left = (image -> matrix[n - 1][m - 1]) * mask[0][0];
            int up_mid = (image -> matrix[n - 1][m]) * mask[0][1];
            int up_right = (image -> matrix[n - 1][m + 1]) * mask[0][2];
            int left = (image -> matrix[n][m - 1]) * mask[1][0];
            int mid = (image -> matrix[n][m]) * mask[1][1];
            int right = (image -> matrix[n][m + 1]) * mask[1][2];
            int down_left = (image -> matrix[n + 1][m - 1]) * mask[2][0];
            int down_mid = (image -> matrix[n + 1][m]) * mask[2][1];
            int down_right = (image -> matrix[n + 1][m + 1]) * mask[2][2];

            new_pixel = (up_left + up_mid + up_right + left + mid + right + down_left + down_mid + down_right);
            new_pixel = new_pixel / 9;
            convolved_image -> matrix[n][m] = new_pixel;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

Image* reserveImage (int height, int width) {

    int n;
    int m;
    Image* new_image = (Image*)malloc(sizeof(Image)); 

    if (new_image != NULL) {
        new_image -> matrix = (int**)malloc(sizeof(int*) * height);
        new_image -> height = height;
        new_image -> width = width;

        if (new_image -> matrix != NULL) {

            for (n = 0; n < height; n++) {
                new_image -> matrix[n] = (int*)malloc(sizeof(int) * width);

                if ( (new_image -> matrix[n]) != NULL ) {

                    for (m = 0; m < width; m++) {
                        new_image -> matrix[n] = 0;

                    }
                }  

                else{

                }
            }
        }

        else{

        }
    }

    else {

    }

    return new_image;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////