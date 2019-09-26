/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// DIRECTIVES /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# ifndef READING_H
# define READING_H

# include "../../structs.h"
# include <png.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////// DEFINITIONS /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Image* reading (char fileName[]);

Image* createStructImage (int height, int width, png_bytep* row);

Image* createPointerImage (int height, int width);

void printImage (Image* image);

int main(int argc, char** argv);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# endif