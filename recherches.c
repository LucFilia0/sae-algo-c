#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fichier.h"
#include "fonctions.h"
#include "IHM.h"
#include "tri.h"
#include "recherches.h"

#define NB_VOLS_MAX 192

/** ##---- DEFINITIONS FONCTIONS RECHERCHE ----## */

int rechercheIntDansTab(int val, int taille, int tab[taille]) {
    /*
        :entree;
            'val' -> la valeur à rechercher
            'taille' -> taille du tableau
            'tab' -> le tableau en question
        :fonction:
            renvoie 1 si 'val' est trouvé dans 'tab', sinon 0.
            recherche linéaire, s'arrête quand '-1' rencontré.
            utilisé dans 'rechercheAvancee'
    */
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

void rechercheCompagnie(const char *nomCompagnie, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]) {
    /*
        :entree:
            'nomCompagnie' -> la compagnie à rechercher
            'nbVols' -> le nombre de vols
            'listeVols' -> liste contenant tous les vols
            'indices' -> tableau contenant les vols correspondant à 'nomCompagnie'
        :fonction:
            recherche tous les vols ayant pour compagnie 'nomCompagnie'.
            les indices des vols sont stockés dans indices.
    */
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
    /*
        :entree:
            'nomDestination' -> la destination recherchee
            'nbVols' -> le nombre de vols
            'listeVols' -> liste contenant tous les vols
            'indices' -> tableau stockant tous les indices des vols correspondant à la recherche
        :fonction:
            recherche dans tous les vols de 'listeVols' ceux dont la destination correspond à 'nomDestination'.
            stock les indices des vols dans 'indices'
    */
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
    /*
        :entree:
            'heureDecollage' -> l'heure recherchee
            'nbVols' -> le nombre de vols
            'listeVols' -> liste contenant tous les vols
            'indices' -> tableau stockant tous les indices des vols correspondant à la recherche
        :fonction:
            recherche dans tous les vols de 'listeVols' ceux dont l'heure correspond à 'heureDecollage'.
            stock les indices des vols dans 'indices'
    */
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

/** ##---- RECHERCHE AVANCEE ----## */

void rechercheAvancee(const char *compagnie, const char *destination, const char *heureDecollage, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]) {
    /*
        :entree:
            'compagnie' -> le nom de la compagnie
            'destination' -> la destination
            'heureDecollage' -> l'heure de decollage
            'nbVols' -> le nombre de vols
            'listeVols' -> la liste contenant tous les vols
            'indices' -> le tableau contenant tous les indices des vols correspondants aux critères
        :fonction:
            recherche les vols correspondant aux critères qui ne sont pas laissés vides par l'utilisateur.
            stock les indices des vols trouvés dans 'indices'
    */
    int indicesCompagnie[NB_VOLS_MAX] = {0};
    int indicesDestination[NB_VOLS_MAX] = {0};
    int indicesHeureDecollage[NB_VOLS_MAX] = {0};

    rechercheCompagnie(compagnie, nbVols, listeVols, indicesCompagnie);
    rechercheDestination(destination, nbVols, listeVols, indicesDestination);
    rechercheHeureDecollage(heureDecollage, nbVols, listeVols, indicesHeureDecollage);

    int indicesReference[NB_VOLS_MAX] = {0};

    // recherche le tableau à prendre pour référence
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
