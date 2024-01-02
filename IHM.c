#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fichier.h"
#include "fonctions.h"
#include "IHM.h"
#include "tri.h"

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

void afficheLigneVide(int nbColumns, int widthColumns) {
    printf("\n");
    for(int i=0; i<nbColumns; ++i) {
        printf("|");
        for(int j=0; j<widthColumns; ++j) {
            printf("_");
        }
    }
    printf("|");
}

void afficheCentre(const char *element, int widthColumn) {
    char affiche[widthColumn];
    int j=0;
    int nbEspaces = widthColumn-strlen(element);
    int nbEspacesGauche = nbEspaces/2;

    int i=0;
    while(i<nbEspacesGauche) {
        printf(" ");
        ++i;
    }
    printf("%s", element);
    i=i+strlen(element);
    while(i<widthColumn) {
        printf(" ");
        ++i;
    }
}

void afficheLigneInfo(struct Vol vol, int nbColumns, int widthColumns) {
    char element[100];
    printf("\n|");
    for(int i=0; i<nbColumns; ++i) {
        clearChar(element);
        switch(i) {
            case 0: sprintf(element, "%d", vol.numVol); break;
            case 1: copieChar(vol.compagnie, element); break;
            case 2: copieChar(vol.destination, element); break;
            case 3: sprintf(element, "%d", vol.numComptoir); break;
            case 4: sprintf(element, "%d:%d", vol.h_debEnregistrement.heure, vol.h_debEnregistrement.minute); break;
            case 5: sprintf(element, "%d:%d", vol.h_finEnregistrement.heure, vol.h_finEnregistrement.minute); break;
            case 6: sprintf(element, "%d", vol.salleEmbarquement); break;
            case 7: sprintf(element, "%d:%d", vol.h_debEmbarquement.heure, vol.h_debEmbarquement.minute); break;
            case 8: sprintf(element, "%d:%d", vol.h_finEmbarquement.heure, vol.h_finEmbarquement.minute); break;
            case 9: sprintf(element, "%d:%d", vol.h_decollage.heure, vol.h_decollage.minute); break;
            case 10: copieChar(vol.etatVol, element); break;
            default: printf("\nCas non traite par switch\n"); break;
        }
        afficheCentre(element, widthColumns);
        printf("|");
    }
}

void afficheLignePassager(struct Passager passager, int nbColumns, int widthColumns) {
    char element[100];
    printf("\n|");
    for(int i=0; i<nbColumns; ++i) {
        clearChar(element);
        switch(i) {
            case 0: copieChar(passager.nom, element); break;
            case 1: copieChar(passager.prenom, element); break;
            case 2:
                // pas très opti mais bon... flm
                if(passager.dateNaissance.jour < 10 && passager.dateNaissance.mois >= 10)
                    sprintf(element, "0%d/%d/%d", passager.dateNaissance.jour, passager.dateNaissance.mois, passager.dateNaissance.annee);
                else if(passager.dateNaissance.mois < 10 && passager.dateNaissance.jour >= 10)
                    sprintf(element, "%d/0%d/%d", passager.dateNaissance.jour, passager.dateNaissance.mois, passager.dateNaissance.annee);
                else if(passager.dateNaissance.jour < 10 && passager.dateNaissance.mois < 10)
                    sprintf(element, "0%d/0%d/%d", passager.dateNaissance.jour, passager.dateNaissance.mois, passager.dateNaissance.annee);
                else
                    sprintf(element, "%d/%d/%d", passager.dateNaissance.jour, passager.dateNaissance.mois, passager.dateNaissance.annee);

                break;
            case 3: sprintf(element, "%d", passager.numSiege); break;
            case 4: sprintf(element, "%f", passager.prixBillet); break;
            default: printf("\nCas non traite par switch\n"); break;
        }
        afficheCentre(element, widthColumns);
        printf("|");
    }
}

void afficheTableauVols(struct Vol *listeVols, int *tab, int taille) {
    /**
    Prend en argument un tableau(tab), qui contient les numeros des vols a afficher
    */

    int widthColumns = 17;
    int nbColumns = 11;

    // LIGNE DU HAUT DU TABLEAU
    printf(" ");
    for(int i=0; i<(nbColumns*widthColumns+nbColumns-1); ++i) {
        printf("_");
    }
    printf("\n");
    // AFFICHER ENTETE TABLO
    for(int i=0; i<nbColumns; ++i) {
            printf("|");
        switch(i) {
            case 0: afficheCentre("NumVol", widthColumns); break;
            case 1: afficheCentre("Compagnie", widthColumns); break;
            case 2: afficheCentre("Destination", widthColumns); break;
            case 3: afficheCentre("NumComptoir", widthColumns); break;
            case 4: afficheCentre("H debEnrg", widthColumns); break;
            case 5: afficheCentre("H finEnrg", widthColumns); break;
            case 6: afficheCentre("salleEmbarq", widthColumns); break;
            case 7: afficheCentre("H debEmbarq", widthColumns); break;
            case 8: afficheCentre("H finEmbarq", widthColumns); break;
            case 9: afficheCentre("H decollage", widthColumns); break;
            case 10: afficheCentre("EtatVol", widthColumns); break;
            default: printf("\nCas non traite par switch\n"); break;
        }
    }
    printf("|");
    afficheLigneVide(nbColumns, widthColumns);
    // AFFICHE INFOS
    int i=0;
    while(i<taille && tab[i] != -1) {
        afficheLigneInfo(listeVols[tab[i]], nbColumns, widthColumns);
        afficheLigneVide(nbColumns, widthColumns);
        ++i;
    }
}

void afficheTableauPassagers(struct Vol vol) {
    /**
    Affiche tous les passagers d'un vol passé en paramètre
    */

    int nbColumns = 5;
    int widthColumns = 20;

    // LIGNE DU HAUT DU TABLEAU
    printf(" ");
    for(int i=0; i<(nbColumns*widthColumns+nbColumns-1); ++i) {
        printf("_");
    }
    printf("\n");
    // AFFICHER ENTETE TABLO
    for(int i=0; i<nbColumns; ++i) {
            printf("|");
        switch(i) {
            case 0: afficheCentre("Nom", widthColumns); break;
            case 1: afficheCentre("Prenom", widthColumns); break;
            case 2: afficheCentre("DateNaissance", widthColumns); break;
            case 3: afficheCentre("NumSiege", widthColumns); break;
            case 4: afficheCentre("PrixBillet", widthColumns); break;
            default: printf("\nCas non traite par switch\n"); break;
        }
    }
    printf("|");
    afficheLigneVide(nbColumns, widthColumns);
    // AFFICHE INFOS
    for(int i=0; i<10; ++i) {
        if(vol.listePassagers[i].numSiege != 0) {
            afficheLignePassager(vol.listePassagers[i], nbColumns, widthColumns);
            afficheLigneVide(nbColumns, widthColumns);
        }
    }
}
