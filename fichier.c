#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fichier.h"


void scanFichier(FILE* fichier, char stop, char *chaine)
{
    int i=0;

    /*
    char carac;
    do {
        carac = fgetc(fichier);
        chaine[i] = carac;
        i++;
    }while(carac != stop && carac != EOF);
    */


    char carac;
    carac = fgetc(fichier);
    while(carac != EOF && carac != stop) {
        chaine[i] = carac;
        i++;

        carac = fgetc(fichier);
    }
}
