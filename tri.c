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

void tableauVols(int taille, int indices[taille], struct Vol listeVols[taille]) {
    int i=0;
    while(i<taille && indices[i] != -1) {
        struct Vol *v = &(listeVols[indices[i]]);
        afficheVol(v);
        ++i;
    }
}

//=================================================

void rechercheCompagnie(const char *nomCompagnie, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]) {
    int ind=0;
    for(int i=0; i<nbVols; ++i) {
        if(strcmp(nomCompagnie, listeVols[i].compagnie) == 0) {
            indices[ind] = i;
            ++ind;
        }
    }
    indices[ind] = -1;
}

void rechercheDestination(const char *nomDestination, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]) {
    int ind=0;
    for(int i=0; i<nbVols; ++i) {
        if(strcmp(nomDestination, listeVols[i].destination) == 0) {
            indices[ind] = i;
            ++ind;
        }
    }
    indices[ind] = -1;
}









