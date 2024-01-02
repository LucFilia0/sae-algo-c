#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fonctions.h"
#include "fichier.h"
#include "IHM.h"
#include "tri.h"


//=================================================

void afficheTab(int taille, int tab[taille]) {
    int i=0;
    printf("[");
    while(i<taille-1) {
        printf("%d ", tab[i]);
        ++i;
    }
    printf("%d]\n", tab[i]);
}
/*
void tableauVols(int taille, int indices[taille], struct Vol listeVols[taille]) {
    int i=0;
    while(i<taille && indices[i] != -1) {
        struct Vol *v = &(listeVols[indices[i]]);
        afficheVol(v);
        ++i;
    }
}
*/
//=================================================

void rechercheCompagnie(const char *nomCompagnie, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]) {
    int ind=0;
    char chaine1[50];
    char chaine2[50];

    copyCharToLower(nomCompagnie, chaine1);

    for(int i=0; i<nbVols; ++i) {
        clearChar(chaine2);
        copyCharToLower(listeVols[i].compagnie, chaine2);

        if(strcmp(chaine1, chaine2) == 0) {
            indices[ind] = i;
            ++ind;
        }
    }
    indices[ind] = -1;
}

void rechercheDestination(const char *nomDestination, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]) {
    int ind=0;
    char chaine1[50];
    char chaine2[50];

    copyCharToLower(nomDestination, chaine1);

    for(int i=0; i<nbVols; ++i) {
        clearChar(chaine2);
        copyCharToLower(listeVols[i].destination, chaine2);

        if(strcmp(chaine1, chaine2) == 0) {
            indices[ind] = i;
            ++ind;
        }
    }
    indices[ind] = -1;
}

void rechercheHeureDecollage(const char *horaire, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]) {
    int ind=0;

    struct Heure horaireRecherchee;
    setHeure(horaire, &horaireRecherchee);

    for(int i=0; i<nbVols; ++i) {
        if(listeVols[i].h_decollage.heure == horaireRecherchee.heure && listeVols[i].h_decollage.minute == horaireRecherchee.minute) {
            indices[ind] = i;
            ++ind;
        }
    }
    indices[ind] = -1;
}








