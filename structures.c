#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fonctions.h"
#include "fichier.h"

#define NB_VOLS 192 // Attention aussi dans main.c
#define MAX 1000

void importDataBase(FILE *fichier, struct Vol *listeVols) {
    char ligne[MAX] = "";
    int vol = 0;
    struct Vol *ptVol;

    scanFichier(fichier, '\n', ligne); //on passe la premiere ligne #flm

    do {
        char ligne[MAX] = "", infoVol[MAX] = "", listePassagers[MAX] = "";
        scanFichier(fichier, '\n', ligne); //on stock la ligne actuelle dans 'ligne'

        getCharTo(ligne, '"', infoVol); //recupere la chaine jusqu'a ", => infos vol

        getCharFromTo(ligne, '"', '"', listePassagers); // recupere de " a ", => liste passagers

        ptVol = &(listeVols[vol]);
        initVol(ptVol, infoVol); // init vol avec donnes du vol
        initPassagers(ptVol, listePassagers); // init liste passagers

        printf("|%c|", fgetc(fichier));

        vol++; //vol suivant
    }while(vol < NB_VOLS);
}

void afficheVol(struct Vol *vol) {
    printf("\n##========== VOL %d ==========##\n\nCompagnie : %s\nDestination : %s\nNumero de comptoir : %d\nHeure debut enregistrement : %d\nHeure fin enregistrement : %d\nSalle d'embarquement : %d\nHeure debut embarquement : %d\nHeure fin embarquement : %d\nHeure decollage : %d\nEtat vol : %s\n\nListe des passagers :\n",
    vol->numVol,
    vol->compagnie,
    vol->destination,
    vol->numComptoir,
    vol->h_debEnregistrement,
    vol->h_finEnregistrement,
    vol->salleEmbarquement,
    vol->h_debEmbarquement,
    vol->h_finEmbarquement,
    vol->h_decollage,
    vol->etatVol
    );
    long int nbPassagers = sizeof(vol->listePassagers) / sizeof(vol->listePassagers[0]);
    for(int i=0; i<nbPassagers; i++) {
        if(vol->listePassagers[i].numSiege != 0) {
            printf("\n%d : ", i+1);
            struct Passager *ptPassager = &(vol->listePassagers[i]);
            printf("\tNom : %s\n\tPrenom : %s\n\tDate de naissance : %s\n\tNumero de siege : %d\n\tPrix du billet : %.2f\n\n",
                ptPassager->nom,
                ptPassager->prenom,
                ptPassager->dateNaissance,
                ptPassager->numSiege,
                ptPassager->prixBillet
            );
        }
    }
}

void initVol(struct Vol *vol, char *infoVol)
{
    char info[300] = "";
    int i = 0, ind = 0, numElement = 0;
    while(i<strlen(infoVol)) {
        if(infoVol[i]!=',') {
            info[ind] = infoVol[i];
            ind++;
        }
        else {
            switch(numElement)
            {
                case 0: vol->numVol = atoi(info); break;
                case 1: copieChar(info, vol->compagnie); break;
                case 2: copieChar(info, vol->destination); break;
                case 3: vol->numComptoir = atoi(info); break;
                case 4: vol->h_debEnregistrement = atoi(info); break;
                case 5: vol->h_finEnregistrement = atoi(info); break;
                case 6: vol->salleEmbarquement = atoi(info); break;
                case 7: vol->h_debEmbarquement = atoi(info); break;
                case 8: vol->h_finEmbarquement = atoi(info); break;
                case 9: vol->h_decollage = atoi(info); break;
                case 10: copieChar(info, vol->etatVol); break;
            }
            numElement++;
            ind = 0;
            clearChar(info);
        }
        i++;
    }
}

void initPassagers(struct Vol *vol, const char *listePassagers)
{
    clearPassagers(vol);
    char info[100];
    int passager = 0;
    int i = 0, ind = 0, numElement = 0;
    while(i<strlen(listePassagers)) {
        if(listePassagers[i]!=';' && i<strlen(listePassagers)-1) {
            if(listePassagers[i]!=',') {
                info[ind] = listePassagers[i];
                //printf("\n|%s|", info);
                ind++;
            }else {
                switch(numElement)
                {
                    case 0: copieChar(info, vol->listePassagers[passager].nom); break;
                    case 1: copieChar(info, vol->listePassagers[passager].prenom); break;
                    case 2: copieChar(info, vol->listePassagers[passager].dateNaissance); break;
                    case 3: vol->listePassagers[passager].numSiege = atoi(info); break;
                }
                numElement++;
                ind=0;
                clearChar(info);
            }
        }else {
            vol->listePassagers[passager].prixBillet = atof(info);
            passager++;
            numElement=0;
            ind=0;
            clearChar(info);
            //printf("\n|-- %s --|\n", info);
        }
        i++;
    }
}

void clearPassagers(struct Vol *vol) {
    for(int i=0; i<10; ++i) {
        clearChar(vol->listePassagers[i].nom);
        clearChar(vol->listePassagers[i].prenom);
        clearChar(vol->listePassagers[i].dateNaissance);
        vol->listePassagers[i].numSiege = 0;
        vol->listePassagers[i].prixBillet = 0.;
    }
}
