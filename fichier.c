#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fichier.h"

/** ##---- DEFINITIONS FONCTIONS FICHIERS ----## */

void scanFichier(FILE* fichier, char stop, char *chaine)
{
    /*
        :entree:
            'fichier' -> le fichier � lire
            'stop' -> le caract�re qui stoppe le scan de 'fichier'
            'chaine' -> la chaine de caract�res dans laquelle sera stock�e le scan du fichier
        :type:
            'stop' est un char, donc '\n' et '\0' sont acc�pt�s
        :fonction:
            scan le fichier et copie progressivement dans 'chaine' jusqu'� rencontrer 'stop' ou EOF
    */
    int i=0;
    char carac;
    do {
        carac = fgetc(fichier);
        chaine[i] = carac;
        i++;
    }while(carac != stop && carac != EOF);
}
