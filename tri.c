#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fonctions.h"
#include "fichier.h"
#include "IHM.h"
#include "tri.h"
#include "recherches.h"

#define NB_VOLS_MAX 192 // attention aussi dans main.c

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


// TRI PASSAGERS

void concatenerTableaux(int taille1, int tab1[taille1], int taille2, int tab2[taille2], int taille3, int tab3[taille3]) {
    int ind3 = 0;
    int ind1 = 0;
    int ind2 = 0;
    while(ind1<taille1 && tab1[ind1] != -1) {
        tab3[ind3] = tab1[ind1];
        ++ind1;
        ++ind3;
    }
    while(ind2<taille2 && tab2[ind2] != -1) {
        tab3[ind3] = tab2[ind2];
        ++ind2;
        ++ind3;
    }
    if(ind3<taille3)
        tab3[ind3] = -1;
}


void trierPrixBilletsPassagers(int nbPassagers, struct Passager listePassagers[nbPassagers], int indices[nbPassagers]) {
    int i=0;
    int max = 0;
    while(i<nbPassagers && indices[i] != -1) {
        max = recherchePrixMaxFrom(nbPassagers, listePassagers, indices, i);
        echangeIndicesTab(nbPassagers, indices, i, max);
        ++i;
    }
}

void trierPassagers(int nbPassagers, struct Passager listePassagers[nbPassagers], int indices[nbPassagers]) {
    struct Date ajd = {11, 1, 2024}; // 11 janvier 2024
    int agePassager = 0;

    int listePassagersMoinsDouze[10] = {0}, indMD = 0;
    int listePassagersPlusDouze[10] = {0}, indPD = 0;
    for(int passager=0; passager<nbPassagers; ++passager) {
        agePassager = ajd.annee - listePassagers[passager].dateNaissance.annee;
        if(listePassagers[passager].numSiege != 0) {
            if(agePassager<=12) {
                listePassagersMoinsDouze[indMD] = passager;
                ++indMD;
            }else {
                listePassagersPlusDouze[indPD] = passager;
                ++indPD;
            }
        }
    }
    if(indMD<10) {
        listePassagersMoinsDouze[indMD] = -1;
    }
    if(indPD<10) {
        listePassagersPlusDouze[indPD] = -1;
    }

    trierPrixBilletsPassagers(10, listePassagers, listePassagersMoinsDouze);
    trierPrixBilletsPassagers(10, listePassagers, listePassagersPlusDouze);

    concatenerTableaux(10, listePassagersMoinsDouze, 10, listePassagersPlusDouze, nbPassagers, indices);
}








