/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// DIRECTIVES /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# ifndef _PIPELINE_H_
# define _PIPELINE_H_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////// DEFINITIONS /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getParams (int argc, char** argv, char* cValue, char* mValue, char* nValue, char* bValue);

int isPercentage (int input);

int isInteger (char* input);

int exist (char* fileName);

int main(int argc, char** argv);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# endif