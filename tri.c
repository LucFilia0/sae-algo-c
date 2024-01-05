#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fonctions.h"
#include "fichier.h"
#include "IHM.h"
#include "tri.h"


//=================================================

void indexFill(int n, int tabIndices[n], int nbVols)
{
    for (int i = 0 ; i < nbVols ; i++) {
        tabIndices[i] = i ;
    }
    for (int i = nbVols ; i < n ; i++) {
        tabIndices[i] = -1 ;
    }
}

void printTab(int n, int tab[n])
{
    printf("\n");
    for (int i = 0 ; i < n ; i++) {
        printf("%d ",tab[i]);
    }
    printf("\n");
}

void echange(int a, int b, int *tab)
{
    int temp = tab[a] ;
    tab[a] = tab[b] ;
    tab[b] = temp ;
}

void lowerCase(char *strIn, char *strOut)
{
    int i = 0 ;
    while (strIn[i] !='\0') {
        if (strIn[i] >= 'A' && strIn[i] <= 'Z') {
            strOut[i] = strIn[i] + 32 ;
        }
        else {
            strOut[i] = strIn[i] ;
        }
        i++ ;
    }
    strOut[i] = '\0' ;
}

int minCompagnieFrom(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols, int iDeb)
{
    int comp, indMin = iDeb ;
    char lowerStrMin[30], lowerStr[30] ;
    lowerCase(listeVols[tabIndices[indMin]].compagnie, lowerStrMin);

    for (int i = iDeb + 1 ; i < nbVols ; i++) {
        lowerCase(listeVols[tabIndices[i]].compagnie, lowerStr);
        comp = strcmp(lowerStrMin, lowerStr);

        if (comp > 0) {
            indMin = i ;
            lowerCase(listeVols[tabIndices[i]].compagnie, lowerStrMin);
        }
    }

    return indMin ;
}

void triCompagnie(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols)
{
    int indMin ;
    for (int i = 0 ; i < nbVols ; i++) {
        indMin = minCompagnieFrom(n, tabIndices, listeVols, nbVols, i) ;
        if (indMin != i) {
            echange(indMin, i, tabIndices);
        }
    }
}

int minDestinationFrom(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols, int iDeb)
{
    int comp, indMin = iDeb ;
    char lowerStrMin[30], lowerStr[30] ;
    lowerCase(listeVols[tabIndices[indMin]].destination, lowerStrMin);

    for (int i = iDeb + 1 ; i < nbVols ; i++) {
        lowerCase(listeVols[tabIndices[i]].destination, lowerStr);
        comp = strcmp(lowerStrMin, lowerStr);

        if (comp > 0) {
            indMin = i ;
            lowerCase(listeVols[tabIndices[i]].destination, lowerStrMin);
        }
    }

    return indMin ;
}

void triDestination(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols)
{
    int indMin ;
    for (int i = 0 ; i < nbVols ; i++) {
        indMin = minDestinationFrom(n, tabIndices, listeVols, nbVols, i) ;
        if (indMin != i) {
            echange(indMin, i, tabIndices);
        }
    }
}

int minH_DecollageFrom(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols, int iDeb)
{
    int comp, indMin = iDeb ;
    struct Heure heureMin, heureActuelle ;
    heureMin.heure = listeVols[tabIndices[indMin]].h_decollage.heure ;
    heureMin.minute = listeVols[tabIndices[indMin]].h_decollage.minute ;

    for (int i = iDeb + 1 ; i < nbVols ; i++) {
        heureActuelle.heure = listeVols[tabIndices[i]].h_decollage.heure ;
        heureActuelle.minute = listeVols[tabIndices[i]].h_decollage.minute ;

        comp = ecartHeures(heureActuelle,heureMin) ;

        if (comp < 0) {
            indMin = i ;
            heureMin.heure = listeVols[tabIndices[indMin]].h_decollage.heure ;
            heureMin.minute = listeVols[tabIndices[indMin]].h_decollage.minute ;
        }
    }

    return indMin ;
}

void triH_Decollage(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols)
{
    int indMin ;
    for (int i = 0 ; i < nbVols ; i++) {
        indMin = minH_DecollageFrom(n, tabIndices, listeVols, nbVols, i) ;
        if (indMin != i) {
            echange(indMin, i, tabIndices);
        }
    }
}

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

int rechercheIndiceAvecNumVol(int n, int nbVols, int tabIndices[n], struct Vol listeVols[n], int numVol)
{
    int i = 0 ;
    while (i < nbVols) {
        if (listeVols[tabIndices[i]].numVol == numVol) {
           return i ;
        }
        i++ ;
    }
    return -1 ;
}









