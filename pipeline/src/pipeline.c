/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// DIRECTIVES /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# include <getopt.h>
# include <ctype.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../../structs.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// FUNCTIONS //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:

void getParams (int argc, char** argv, int* cValue, char* mValue, int* nValue, int* bValue) {

    int c;
    *bValue = 0;

    while ( (c = getopt (argc, argv, "c:m:n:b")) != -1) {

        switch (c) {
            case 'c':
                *cValue = atoi(optarg);
                printf("cValue: %d\n", *cValue);
                break;
            
            case 'm':
                strcpy(mValue, optarg);
                printf("mValue: %s\n", mValue);
                break;
            
            case 'n':
                *nValue = atoi(optarg);
                printf("nValue: %d\n", *nValue);
                break;
            
            case 'b':
                *bValue = 1;
                printf("bValue: %d\n", *bValue);
                break;
            
            case '?':

                if (optopt == 'c') {

                }

                if (optopt == 'm') {
                    
                }

                if (optopt == 'n') {           
                }

                if (optopt == 'b') {
                    
                }

            default:
                break;
            }

    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS:
// - OUTPUTS:
// - DESCRIPTION:


#define READ 0
#define WRITE 1

void pipeline(){
    pid_t pid1, pid2, pid3, pid4, pid5;
    int  status1, status2, status3, status4, status5;

    char * argvConvolution[] ={"convolution",NULL};
    char * argvRectification[] ={"rectification",NULL};
    char * argvPooling[] ={"pooling",NULL};
    char * argvClasificator[] ={"classifier",NULL};
    char * argvWriting[] ={"resultsWriter",NULL};

    int * pipe1 = (int *)malloc(2*sizeof(int));
    int * pipe2 = (int *)malloc(2*sizeof(int));
    int * pipe3 = (int *)malloc(2*sizeof(int));
    int * pipe4 = (int *)malloc(2*sizeof(int));
    int * pipe5 = (int *)malloc(2*sizeof(int));

    Image* image;
    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);
    pipe(pipe4);
    pipe(pipe5);

    if( (pid1=fork()) == 0 ){
        if( (pid2=fork()) == 0 ){
            if( (pid3=fork()) == 0 ){
                if( (pid4=fork()) == 0 ){
                    if( (pid5=fork()) == 0 ){
                        dup2(pipe5[READ],STDIN_FILENO);

                        close(pipe1[READ]);
                        close(pipe1[WRITE]);
                        close(pipe2[READ]);
                        close(pipe2[WRITE]);
                        close(pipe3[READ]);
                        close(pipe3[WRITE]);
                        close(pipe4[READ]);
                        close(pipe4[WRITE]);
                        close(pipe5[WRITE]);

                        //Writing
                        execvp(/*poner ruta*/"",argvWriting);
                    }
                    else{
                        dup2(pipe4[READ],STDIN_FILENO);
                        dup2(pipe5[WRITE],STDOUT_FILENO);

                        close(pipe1[READ]);
                        close(pipe1[WRITE]);
                        close(pipe2[READ]);
                        close(pipe2[WRITE]);
                        close(pipe3[READ]);
                        close(pipe3[WRITE]);
                        close(pipe4[WRITE]);
                        close(pipe5[READ]);

                        //Clasificator
                        execvp(/*poner ruta*/"",argvClasificator);
                    }
                }
                else{
                    dup2(pipe3[READ],STDIN_FILENO);
                    dup2(pipe4[WRITE],STDOUT_FILENO);

                    close(pipe1[READ]);
                    close(pipe1[WRITE]);
                    close(pipe2[READ]);
                    close(pipe2[WRITE]);
                    close(pipe3[WRITE]);
                    close(pipe4[READ]);
                    close(pipe5[READ]);
                    close(pipe5[WRITE]);
                    
                    //Pooling
                    execvp(/*poner ruta*/"",argvPooling);
                }
            }
            else{
                dup2(pipe2[READ],STDIN_FILENO);
                dup2(pipe3[WRITE],STDOUT_FILENO);

                close(pipe1[READ]);
                close(pipe1[WRITE]);
                close(pipe2[WRITE]);
                close(pipe3[READ]);
                close(pipe4[READ]);
                close(pipe4[WRITE]);
                close(pipe5[READ]);
                close(pipe5[WRITE]);

                //Rectification
                execvp(/*poner ruta*/"",argvRectification);
            }
        }
        else{
            dup2(pipe1[READ],STDIN_FILENO);
            dup2(pipe2[WRITE],STDOUT_FILENO);

            close(pipe1[WRITE]);
            close(pipe2[READ]);
            close(pipe3[READ]);
            close(pipe3[WRITE]);
            close(pipe4[READ]);
            close(pipe4[WRITE]);
            close(pipe5[READ]);
            close(pipe5[WRITE]);
            //Convolution
            execvp(/*poner ruta*/"",argvConvolution);
        }
    }
    else{     
        
        dup2(pipe1[WRITE],STDOUT_FILENO);

        close(pipe1[READ]);
        close(pipe2[READ]);
        close(pipe2[WRITE]);
        close(pipe3[READ]);
        close(pipe3[WRITE]);
        close(pipe4[READ]);
        close(pipe4[WRITE]);
        close(pipe5[READ]);
        close(pipe5[WRITE]);

        //Reading

        write(STDOUT_FILENO, &image, sizeof(Image));
        wait(&status1);
    }




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////