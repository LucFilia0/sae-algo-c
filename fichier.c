#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fichier.h"

/** ##---- DEFINITIONS FONCTIONS FICHIERS ----## */

void scanFichier(FILE* fichier, char stop, char *chaine)
{
    /*
        :entree:
            'fichier' -> le fichier à lire
            'stop' -> le caractère qui stoppe le scan de 'fichier'
            'chaine' -> la chaine de caractères dans laquelle sera stockée le scan du fichier
        :type:
            'stop' est un char, donc '\n' et '\0' sont accéptés
        :fonction:
            scan le fichier et copie progressivement dans 'chaine' jusqu'à rencontrer 'stop' ou EOF
    */
    int i=0;
    char carac;
    do {
        carac = fgetc(fichier);
        chaine[i] = carac;
        i++;
    }while(carac != stop && carac != EOF);
}
