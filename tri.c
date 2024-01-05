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

/** ##---- DEFINITIONS FONCTIONS TRI */

void trierPrixBilletsPassagers(int nbPassagers, struct Passager listePassagers[nbPassagers], int indices[nbPassagers]) {
    /*
        :fonction:
            tri par sélection, tri les passagers selon leur prix de billet. Ordre décroissant.
            L'ordre est stocké dans 'indices'
    */
    int i=0;
    int max = 0;
    while(i<nbPassagers && indices[i] != -1) {
        max = recherchePrixMaxFrom(nbPassagers, listePassagers, indices, i);
        echangeIndicesTab(nbPassagers, indices, i, max);
        ++i;
    }
}

void trierPassagers(int nbPassagers, struct Passager listePassagers[nbPassagers], int indices[nbPassagers]) {
    /*
        :entree:
            'nbPassagers' -> le nombre de passagers / la taille de la liste
            'listePassagers' -> la liste de tous les passagers, contenant toutes les infos
            'indices' -> le tableau contenant l'ordre dans lequel afficher les passagers
        :fonction:
            Ordonne l'affichage des passagers selon les contraintes suivantes :
                - Les passagers de 12 ans et moins devant
                - Les passagers sont affichés selon leur prix de billet, par ordre décroissant
    */
    struct Date ajd = {11, 1, 2024}; // 11 janvier 2024
    int agePassager = 0;

    int listePassagersMoinsDouze[100] = {0}, indMD = 0;
    int listePassagersPlusDouze[100] = {0}, indPD = 0;
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
    if(indMD<100) {
        listePassagersMoinsDouze[indMD] = -1;
    }
    if(indPD<100) {
        listePassagersPlusDouze[indPD] = -1;
    }

    trierPrixBilletsPassagers(100, listePassagers, listePassagersMoinsDouze);
    trierPrixBilletsPassagers(100, listePassagers, listePassagersPlusDouze);

    concatenerTableaux(100, listePassagersMoinsDouze, 100, listePassagersPlusDouze, nbPassagers, indices);
}

void trierPiste(int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]) {
    int i=0;
    int min = 0;
    while(i<nbVols) {
        min = rechercheHeureDecollageMinFrom(nbVols, listeVols, indices, i);
        echangeIndicesTab(nbVols, indices, i, min);
        ++i;
    }
}

//=================================================

void trierCompagnie(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols)
{
    int indMin ;
    for (int i = 0 ; i < nbVols ; i++) {
        indMin = rechercheCompagnieMinFrom(n, tabIndices, listeVols, nbVols, i) ;
        if (indMin != i) {
            echangeIndicesTab(n, tabIndices, indMin, i);
        }
    }
}

void trierDestination(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols)
{
    int indMin ;
    for (int i = 0 ; i < nbVols ; i++) {
        indMin = rechercheDestinationMinFrom(n, tabIndices, listeVols, nbVols, i) ;
        if (indMin != i) {
            echangeIndicesTab(n, tabIndices, indMin, i);
        }
    }
}

void trierHeureDecollage(int n, int tabIndices[n], struct Vol listeVols[n], int nbVols)
{
    int indMin ;
    for (int i = 0 ; i < nbVols ; i++) {
        indMin = rechercheHeureDecollageMinFrom(nbVols, listeVols, tabIndices, i) ;
        if (indMin != i) {
            echangeIndicesTab(n, tabIndices, indMin, i);
        }
    }
}
