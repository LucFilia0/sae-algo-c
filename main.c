#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fichier.h"
#include "fonctions.h"

#define NB_VOLS 40 //attention aussi dans structures.c

int main(int argc, char *argv[])
{
    struct Vol listeVols[NB_VOLS];

    const char* nomFichier = "data_vols.csv";
    FILE *fichier;
    fichier = fopen(nomFichier, "r");

    if(fichier==NULL) {
        perror(nomFichier);
    }
    else
    {
        importeDataBase(fichier, listeVols);

        struct Vol *v;
        int entry, numVol, quit = 0;

        do {
            do {
                printf("Rechercher Vol (1) / Quitter (2) : ");
                scanf("%d", &entry);
            }while(entry<1 || entry>2);
            if(entry==1) {
                do {
                    printf("Numero du vol : ");
                    scanf("%d", &numVol);
                }while(numVol<0 || numVol>NB_VOLS);
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
