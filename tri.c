#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fonctions.h"
#include "fichier.h"
#include "IHM.h"
#include "tri.h"

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
    if(ind<nbVols)
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
    if(ind<nbVols)
        indices[ind] = -1;
}

void rechercheHeureDecollage(const char *heureDecollage, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]) {
    int ind=0;

    // elever le ':'
    char heureClean[5];
    int h = 0;
    for(int i=0; i<5; ++i) {
        if(heureDecollage[i] != ':' || i != 2) {
            heureClean[h] = heureDecollage[i];
            ++h;
        }
    }

    struct Heure horaireRecherchee;
    setHeure(heureClean, &horaireRecherchee);

    for(int i=0; i<nbVols; ++i) {
        if(listeVols[i].h_decollage.heure == horaireRecherchee.heure && listeVols[i].h_decollage.minute == horaireRecherchee.minute) {
            indices[ind] = i;
            ++ind;
        }
    }
    if(ind<nbVols)
        indices[ind] = -1;
}

int rechercheIntDansTab(int val, int taille, int tab[taille]) {
    int exist = 0, i = 0;
    if(tab[0] != -1) {
        while(i<taille && tab[i] != -1) {
            if(tab[i] == val) {
                exist = 1;
                break;
            }
            ++i;
        }
    }

    return exist;
}

int copieTabDansTab(int taille, int copie[taille], int colle[taille]) {
    int i = -1;
    do {
        ++i;
        colle[i] = copie[i];
    }while(copie[i] != -1 && i<taille);
}

void rechercheMultiple(const char *compagnie, const char *destination, const char *heureDecollage, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]) {
    int indicesCompagnie[NB_VOLS_MAX] = {0};
    int indicesDestination[NB_VOLS_MAX] = {0};
    int indicesHeureDecollage[NB_VOLS_MAX] = {0};

    rechercheCompagnie(compagnie, nbVols, listeVols, indicesCompagnie);
    rechercheDestination(destination, nbVols, listeVols, indicesDestination);
    rechercheHeureDecollage(heureDecollage, nbVols, listeVols, indicesHeureDecollage);

    int indicesReference[NB_VOLS_MAX] = {0};

    if(indicesCompagnie[0] != -1) {
        copieTabDansTab(NB_VOLS_MAX, indicesCompagnie, indicesReference);
    }
    else if(indicesDestination[0] != -1) {
        copieTabDansTab(NB_VOLS_MAX, indicesDestination, indicesReference);
    }
    else {
        copieTabDansTab(NB_VOLS_MAX, indicesHeureDecollage, indicesReference);
    }

    int existInCompagnie = 0;
    int existInDestination = 0;
    int existInHeureDecollage = 0;
    int ind = 0, i = 0;
    while(i<nbVols && indicesReference[i] != -1) {
        existInCompagnie = rechercheIntDansTab(indicesReference[i], nbVols, indicesCompagnie);
        existInDestination = rechercheIntDansTab(indicesReference[i], nbVols, indicesDestination);
        existInHeureDecollage = rechercheIntDansTab(indicesReference[i], nbVols, indicesHeureDecollage);

        if((existInCompagnie == 1 || strcmp(compagnie, "") == 0) && (existInDestination == 1 || strcmp(destination, "") == 0) && (existInHeureDecollage == 1 || strcmp(heureDecollage, "") == 0)) {
            indices[ind] = indicesReference[i];
            ++ind;
        }
        ++i;
    }
    if(ind<nbVols)
        indices[ind] = -1;
}


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








