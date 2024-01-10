#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fonctions.h"
#include "fichier.h"
#include "IHM.h"
#include "tri.h"
#include "recherches.h"
#include "retard.h"

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

void trierPassagers(int nbPassagers, struct Passager listePassagers[nbPassagers], int indices[nbPassagers], int temp[], struct Date ajd) {
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

    triFusionPrixBillet(listePassagersMoinsDouze, temp, listePassagers, 0, indMD-1) ;
    triFusionPrixBillet(listePassagersPlusDouze, temp, listePassagers, 0, indPD-1);

    concatenerTableaux(100, listePassagersMoinsDouze, 100, listePassagersPlusDouze, nbPassagers, indices);
}

void trierPiste(int nbVols, struct Vol listeVols[], int indices[]) {
    int i=0;
    int min = 0;
    while(i<nbVols) {
        min = rechercheHeureDecollageMinFrom(nbVols, listeVols, indices, i);
        echangeIndicesTab(nbVols, indices, i, min);
        ++i;
    }
}

//====================================================================================

void fusion(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin, int  typeTri)
{
    int iMilieu = (iDeb + iFin)/2 ;
    int i = iDeb, j = iMilieu + 1, k = 0, comp;
    double compPrix ;
    char chaine1[30], chaine2[30] ;

    while (i <= iMilieu && j <= iFin) {
        switch(typeTri){
        case 1:
            comp = ecartHeures(listeVols[tabIndices[i]].h_decollage, listeVols[tabIndices[j]].h_decollage) ; break ;
            break ;
        case 2:
            copyCharToLower(listeVols[tabIndices[i]].destination, chaine1) ;
            copyCharToLower(listeVols[tabIndices[j]].destination,chaine2) ;
            comp = strcmp(chaine1, chaine2) ;
            break ;
        case 3:
            copyCharToLower(listeVols[tabIndices[i]].compagnie, chaine1) ;
            copyCharToLower(listeVols[tabIndices[j]].compagnie,chaine2) ;
            comp = strcmp(chaine1, chaine2) ;
            break ;
        case 4:
            comp = listeVols[tabIndices[i]].salleEmbarquement - listeVols[tabIndices[j]].salleEmbarquement ;
            break ;
        }

        if (comp < 0) {
            temp[k] = tabIndices[i] ;
            i++ ;
        }

        else {
            temp[k] = tabIndices[j] ;
            j++ ;
        }
        k++ ;
    }

    while (i <= iMilieu) {
        temp[k] = tabIndices[i] ;
        i++ ; k++ ;
    }

    while (j <= iFin) {
        temp[k] = tabIndices[j] ;
        j++ ; k++ ;
    }

    k = 0 ;
    while (k <= iFin - iDeb) {
        tabIndices[iDeb + k] = temp[k] ;
        temp[k] = 0 ;
        k++ ;
    }
}

void triFusionH_Decollage(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin)
{
    if (iDeb < iFin) {
        int iMilieu = (iDeb + iFin)/2 ;
        triFusionH_Decollage(tabIndices, temp, listeVols, iDeb, iMilieu) ;
        triFusionH_Decollage(tabIndices, temp, listeVols, iMilieu + 1, iFin) ;
        fusion(tabIndices, temp, listeVols, iDeb, iFin, 1) ;
    }
}

void triFusionDestination(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin)
{
    if (iDeb < iFin) {
        int iMilieu = (iDeb + iFin)/2 ;
        triFusionDestination(tabIndices, temp, listeVols, iDeb, iMilieu) ;
        triFusionDestination(tabIndices, temp, listeVols, iMilieu + 1, iFin) ;
        fusion(tabIndices, temp, listeVols, iDeb, iFin, 2) ;
    }
}

void triFusionCompagnie(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin)
{
    if (iDeb < iFin) {
        int iMilieu = (iDeb + iFin)/2 ;
        triFusionCompagnie(tabIndices, temp, listeVols, iDeb, iMilieu) ;
        triFusionCompagnie(tabIndices, temp, listeVols, iMilieu + 1, iFin) ;
        fusion(tabIndices, temp, listeVols, iDeb, iFin, 3) ;
    }
}

void triFusionSalleEmbarquement(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin)
{
    if (iDeb < iFin) {
        int iMilieu = (iDeb + iFin)/2 ;
        triFusionSalleEmbarquement(tabIndices, temp, listeVols, iDeb, iMilieu) ;
        triFusionSalleEmbarquement(tabIndices, temp, listeVols, iMilieu + 1, iFin) ;
        fusion(tabIndices, temp, listeVols, iDeb, iFin, 4) ;
    }
}

void triFusion(int nbVols, int tabIndices[], int temp[], struct Vol listeVols[], int typeTri)
{
    int iDeb = 0, iFin = nbVols - 1 ;
    switch(typeTri) {
        case 1:
            triFusionH_Decollage(tabIndices, temp, listeVols, iDeb, iFin) ; break ;
        case 2:
            triFusionDestination(tabIndices, temp, listeVols, iDeb, iFin) ; break ;
        case 3:
            triFusionCompagnie(tabIndices, temp, listeVols, iDeb, iFin) ; break ;
        case 4:
            triFusionSalleEmbarquement(tabIndices, temp, listeVols, iDeb, iFin) ; break ;
        default:
            printf("\nTri invalide\n") ;
    }
}

void fusionPrixBillet(int tabIndices[], int temp[], struct Passager listePassagers[], int iDeb, int iFin)
{
    int iMilieu = (iDeb + iFin)/2 ;
    int i = iDeb, j = iMilieu + 1, k = 0 ;
    double comp ;
    char chaine1[30], chaine2[30] ;

    while (i <= iMilieu && j <= iFin) {
        comp = listePassagers[tabIndices[i]].prixBillet - listePassagers[tabIndices[j]].prixBillet ;
        if(comp == 0) {
            int alpha = compareOrdreAlpha(listePassagers[tabIndices[i]].nom, listePassagers[tabIndices[j]].nom);
            if(alpha == 1) {
                temp[k] = tabIndices[i];
                ++i;
            }else {
                temp[k] = tabIndices[j];
                ++j;
            }
        }
        if (comp > 0) {
            temp[k] = tabIndices[i] ;
            i++ ;
        }

        else {
            temp[k] = tabIndices[j] ;
            j++ ;
        }
        k++ ;
    }

    while (i <= iMilieu) {
        temp[k] = tabIndices[i] ;
        i++ ; k++ ;
    }

    while (j <= iFin) {
        temp[k] = tabIndices[j] ;
        j++ ; k++ ;
    }

    k = 0 ;
    while (k <= iFin - iDeb) {
        tabIndices[iDeb + k] = temp[k] ;
        temp[k] = 0 ;
        k++ ;
    }
}

void triFusionPrixBillet(int tabIndices[], int temp[], struct Passager listePassagers[], int iDeb, int iFin)
{
    if (iDeb < iFin) {
        int iMilieu = (iDeb + iFin)/2 ;
        triFusionPrixBillet(tabIndices, temp, listePassagers, iDeb, iMilieu) ;
        triFusionPrixBillet(tabIndices, temp, listePassagers, iMilieu + 1, iFin) ;
        fusionPrixBillet(tabIndices, temp, listePassagers, iDeb, iFin) ;
    }
}

