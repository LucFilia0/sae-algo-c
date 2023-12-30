#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fichier.h"
#include "fonctions.h"

#define NB_VOLS_MAX 192 //attention aussi dans structures.c

int main(int argc, char *argv[])
{
    struct Vol listeVols[NB_VOLS_MAX];

    const char* nomFichier = "data_vols.csv";
    FILE *fichier;
    fichier = fopen(nomFichier, "r");

    if(fichier==NULL) {
        perror(nomFichier);
    }
    else
    {
        int nb_vols = 0;

        importDataBase(fichier, listeVols, &nb_vols);

        printf("Nombre de vols : %d", nb_vols);

        struct Vol *v;
        int entry, numVol, quit = 0;

        do {
            userEntryInt("Voir un vol (1) / Quitter (2)", &entry, 1, 2);
            if(entry==1) {
                userEntryInt("Numero du vol", &numVol, 1, nb_vols);
                v = &(listeVols[numVol-1]);
                afficheVol(v);
            }else {
                quit=1;
            }
        }while(quit==0);




        fclose(fichier);
    }
    return 0;
}
