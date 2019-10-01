/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// DIRECTIVES /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# include <sys/types.h>
# include <sys/wait.h>

# include "writing.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// MAIN ////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

int main(int argc, char** argv) {

    int i;
    char* number_images = argv[1];
    char* b = argv[2];
    if(b){
        printf("|   image   | nearly black |\n");
        printf("|-----------|--------------|\n");
    }

    for (i = 0; i < atoi(number_images); i++) {
        Image image;
        read(STDIN_FILENO, &image, sizeof(Image));
        printf("Largo: %d\n", image.height);
        printf("Ancho: %d\n", image.width);
        printf("%s\n", "Desde el writing");
        
        printImage (image);
        

        /*
        int number_image = i + 1;
        char output_file[20];
        strcpy(output_file, "out_");
        sprintf(output_file, "%d", number_image);

        // writing

        if(b){
            for(int i= 0; i<atoi(number_images); i++){
                Image image;
                read(STDIN_FILENO, &image, sizeof(Image));
                if(image.nearly_black==1){
                    printf("|  imagen_%d |     yes      |\n",i+1);
                }
                else if(image.nearly_black==0){
                    printf("|  imagen_%d |      no      |\n",i+1);
                }
            }
            writing(image, output_file);
        }
        else{
            writing(image, output_file);
        }
        */
    }


    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////