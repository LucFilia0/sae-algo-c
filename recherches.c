#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fichier.h"
#include "fonctions.h"
#include "IHM.h"
#include "tri.h"
#include "recherches.h"
#include "retard.h"

#define NB_VOLS_MAX 192

/** ##---- RECHERCHE DICHOTOMIE ----## */

int rechercheDichotomieCompagnie(int nbVols, struct Vol listeVols[], int indices[], const char *entryLowered) {
    int deb = 0, fin = nbVols-1, mid = 0;
    int exit = -1;
    char compagnieLowered[50];

    do {
        mid=(deb+fin)/2;
        copyCharToLower(listeVols[indices[mid]].compagnie, compagnieLowered);
        if(compareOrdreAlpha(compagnieLowered, entryLowered)==0) {
            exit = mid;
        }
        else if(compareOrdreAlpha(compagnieLowered, entryLowered)==1) {
            deb = mid+1;
        }else {
            fin = mid-1;
        }
    }while(exit == -1 && deb<fin);
    return exit;
}

void rechercheCompagnieD(const char *entry, int nbVols, struct Vol listeVols[], int indicesTri[], int indices[]) {
    int trouve = 0, ind = 0;
    int prec = 0, suiv = 0;
    char entryLowered[50] = "";

    copyCharToLower(entry, entryLowered);

    trouve = rechercheDichotomieCompagnie(nbVols, listeVols, indicesTri, entryLowered);

    if(trouve != -1) {
        indices[ind] = indicesTri[trouve];
        prec = trouve-1;
        suiv = trouve+1;
        ++ind;

        char compagniePrec[50] = "", compagnieSuiv[50] = "";
        copyCharToLower(listeVols[indicesTri[prec]].compagnie, compagniePrec);
        copyCharToLower(listeVols[indicesTri[suiv]].compagnie, compagnieSuiv);
        while(strcmp(entryLowered, compagniePrec)==0 && prec>=0) {
            indices[ind] = indicesTri[prec];
            --prec;
            ++ind;
            copyCharToLower(listeVols[indicesTri[prec]].compagnie, compagniePrec);
        }
        while(strcmp(compagnieSuiv, entryLowered)==0 && indicesTri[suiv]<nbVols) {
            indices[ind] = indicesTri[suiv];
            ++suiv;
            ++ind;
            copyCharToLower(listeVols[indicesTri[suiv]].compagnie, compagnieSuiv);
        }
    }
    if(ind<nbVols)
        indices[ind] = -1;
}

int rechercheDichotomieDestination(int nbVols, struct Vol listeVols[], int indices[], const char *entryLowered) {
    int deb = 0, fin = nbVols-1, mid = 0;
    int exit = -1;
    char destinationLowered[50];

    do {
        mid=(deb+fin)/2;
        copyCharToLower(listeVols[indices[mid]].destination, destinationLowered);
        if(compareOrdreAlpha(destinationLowered, entryLowered)==0) {
            exit = mid;
        }
        else if(compareOrdreAlpha(destinationLowered, entryLowered)==1) {
            deb = mid+1;
        }else {
            fin = mid-1;
        }
    }while(exit == -1 && deb<fin);
    return exit;
}

void rechercheDestinationD(const char *entry, int nbVols, struct Vol listeVols[], int indicesTri[], int indices[]) {
    int trouve = 0, ind = 0;
    int prec = 0, suiv = 0;
    char entryLowered[50] = "";

    copyCharToLower(entry, entryLowered);

    trouve = rechercheDichotomieDestination(nbVols, listeVols, indicesTri, entryLowered);

    if(trouve != -1) {
        indices[ind] = indicesTri[trouve];
        prec = trouve-1;
        suiv = trouve+1;
        ++ind;

        char destinationPrec[50] = "", destinationSuiv[50] = "";
        copyCharToLower(listeVols[indicesTri[prec]].destination, destinationPrec);
        copyCharToLower(listeVols[indicesTri[suiv]].destination, destinationSuiv);
        while(strcmp(entryLowered, destinationPrec)==0 && prec>=0) {
            indices[ind] = indicesTri[prec];
            --prec;
            ++ind;
            copyCharToLower(listeVols[indicesTri[prec]].destination, destinationPrec);
        }
        while(strcmp(destinationSuiv, entryLowered)==0 && suiv<nbVols) {
            indices[ind] = indicesTri[suiv];
            ++suiv;
            ++ind;
            copyCharToLower(listeVols[indicesTri[suiv]].destination, destinationSuiv);
        }
    }
    if(ind<nbVols)
        indices[ind] = -1;
}

int rechercheDichotomieH_Decollage(int nbVols, struct Vol listeVols[], int indices[], struct Heure heure) {
    int deb = 0, fin = nbVols-1, mid = 0;
    int exit = -1;
    int heureAct = castHeureEnMinute(heure);
    int h_mid = 0;

    do {
        mid=(deb+fin)/2;
        h_mid = castHeureEnMinute(listeVols[indices[mid]].h_decollage);
        if(h_mid >= heureAct && h_mid <= heureAct+180) {
            exit = mid;
        }
        else if(h_mid > heureAct+180) {
            fin = mid-1;
        }else {
            deb = mid+1;
        }
    }while(exit == -1 && deb<fin);

    return exit;
}

void rechercheH_DecollageD(const char *entry, int nbVols, struct Vol listeVols[], int indicesTri[], int indices[]) {
    int trouve = 0, ind = 0;
    int prec = 0, suiv = 0;

    struct Heure heure;
    setHeure(entry, &heure);
    int heureAct = castHeureEnMinute(heure);

    trouve = rechercheDichotomieH_Decollage(nbVols, listeVols, indicesTri, heure);

    if(trouve != -1) {
        int h_trouve = castHeureEnMinute(listeVols[indicesTri[trouve]].h_decollage);
        if(h_trouve >= heureAct && h_trouve <= heureAct+180) {
            indices[ind] = indicesTri[trouve];
            ++ind;
        }
        prec = trouve-1;
        suiv = trouve+1;

        int h_prec = castHeureEnMinute(listeVols[indicesTri[prec]].h_decollage);
        int h_suiv = castHeureEnMinute(listeVols[indicesTri[suiv]].h_decollage);
        while(h_prec >= heureAct && h_prec <= heureAct+180 && prec>=0) {
            indices[ind] = indicesTri[prec];
            ++ind;
            --prec;
            h_prec = castHeureEnMinute(listeVols[indicesTri[prec]].h_decollage);
        }
        while(h_suiv >= heureAct && h_suiv <= heureAct+180 && indicesTri[suiv]!=-1) {
            indices[ind] = indicesTri[suiv];
            ++ind;
            ++suiv;
            h_suiv = castHeureEnMinute(listeVols[indicesTri[suiv]].h_decollage);
        }
    }
    if(ind<nbVols)
        indices[ind] = -1;
}

/** ##---- DEFINITIONS FONCTIONS RECHERCHE ----## */

int rechercheIndiceAvecNumVol(int nbVols, int tabIndices[], struct Vol listeVols[], int numVol)
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

int rechercheIntDansTab(int val, int taille, int tab[taille]) {
    /*
        :entree;
            'val' -> la valeur � rechercher
            'taille' -> taille du tableau
            'tab' -> le tableau en question
        :fonction:
            renvoie 1 si 'val' est trouv� dans 'tab', sinon 0.
            recherche lin�aire, s'arr�te quand '-1' rencontr�.
            utilis� dans 'rechercheAvancee'
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

/** ##---- RECHERCHE AVANCEE ----## */

void rechercheAvancee(const char *compagnie, const char *destination, const char *heureDecollage, int nbVols, struct Vol listeVols[], int temp[], int indicesTriCompagnie[], int indicesTriDestination[], int indicesTriH_Decollage[], int indices[]) {
    /*
        :entree:
            'compagnie' -> le nom de la compagnie
            'destination' -> la destination
            'heureDecollage' -> l'heure de decollage
            'nbVols' -> le nombre de vols
            'listeVols' -> la liste contenant tous les vols
            'indices' -> le tableau contenant tous les indices des vols correspondants aux crit�res
        :fonction:
            recherche les vols correspondant aux crit�res qui ne sont pas laiss�s vides par l'utilisateur.
            stock les indices des vols trouv�s dans 'indices'
    */
    int indicesCompagnie[NB_VOLS_MAX] = {0};
    int indicesDestination[NB_VOLS_MAX] = {0};
    int indicesHeureDecollage[NB_VOLS_MAX] = {0};

    rechercheCompagnieD(compagnie, nbVols, listeVols, indicesTriCompagnie, indicesCompagnie);
    rechercheDestinationD(destination, nbVols, listeVols, indicesTriDestination, indicesDestination);
    rechercheH_DecollageD(heureDecollage, nbVols, listeVols, indicesTriH_Decollage, indicesHeureDecollage);

    int indicesReference[NB_VOLS_MAX] = {0};

    // recherche le tableau � prendre pour r�f�rence
    if(indicesCompagnie[0] != -1) {
        copieTabDansTab(NB_VOLS_MAX, indicesCompagnie, indicesReference);
    }
    else if(indicesDestination[0] != -1) {
        copieTabDansTab(NB_VOLS_MAX, indicesDestination, indicesReference);
    }
    else {
        copieTabDansTab(NB_VOLS_MAX, indicesHeureDecollage, indicesReference);
    }

    int n = compterElmntTab(nbVols, indicesReference);
    triFusion(n, indicesReference, temp, listeVols, 1);

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


/** ##---- AFFICHAGE ACCUEIL DES VOLS ----## **/

void rechercheVolsAccueil(int nbVols, struct Vol listeVols[nbVols], int indicesTri[nbVols], int indices[nbVols], struct Heure heureActuelle) {
    int deb = 0;
    int fin = nbVols-1;
    int mid = 0, ind = 0;

    int trouve = -1;
    int now = castHeureEnMinute(heureActuelle);

    do {
        mid = (deb+fin)/2;
        int heurePointee = castHeureEnMinute(listeVols[indicesTri[mid]].h_decollage);
        if(now <= heurePointee && heurePointee <= now + 180) {
            trouve = mid;
        }
        else {
            if(heurePointee > now+180) {
                fin = mid-1;
            }
            if(heurePointee < now) {
                deb = mid+1;
            }
        }
    }while(deb < fin && trouve == -1);

    if(trouve != -1) {
        int h_prec = 0, h_suiv = 0;
        if(etatVol(nbVols, indicesTri, listeVols, trouve)!=-1) {
            indices[ind] = listeVols[indicesTri[trouve]].numVol - 1;
            ++ind;
        }
        int prec = trouve-1;
        h_prec = castHeureEnMinute(listeVols[indicesTri[prec]].h_decollage);
        int suiv = trouve+1;
        h_suiv = castHeureEnMinute(listeVols[indicesTri[suiv]].h_decollage);
        do {
            if(now <= h_prec && h_prec <= now + 180) {
                if(etatVol(nbVols, indicesTri, listeVols, prec)!=-1) {
                    indices[ind] = listeVols[indicesTri[prec]].numVol - 1;
                    ++ind;
                }
                --prec;
                h_prec = castHeureEnMinute(listeVols[indicesTri[prec]].h_decollage);
            }
            if(now <= h_suiv && h_suiv <= now + 180) {
                if(etatVol(nbVols, indicesTri, listeVols, suiv)!=-1) {
                    indices[ind] = listeVols[indicesTri[suiv]].numVol - 1;
                    ++ind;
                }
                ++suiv;
                h_suiv = castHeureEnMinute(listeVols[indicesTri[suiv]].h_decollage);
            }
        }while((now <= h_prec && h_prec <= now + 180) || (now <= h_suiv && h_suiv <= now + 180));
    }
    if(ind < nbVols) {
        indices[ind] = -1;
    }
}

/** ##---- RECHERCHE VOL A VENIR DANS SALLE EMBARQUEMENT ----## */

int rechercheDichotomieSalleEmb(int nbVols, struct Vol listeVols[nbVols], int indices[nbVols], int salleEmb) {
    int deb = 0, fin = nbVols-1, mid = 0;
    int exit = -1;

    do {
        mid=(deb+fin)/2;
        if(listeVols[indices[mid]].salleEmbarquement == salleEmb) {
            exit = mid;
        }
        else if(listeVols[indices[mid]].salleEmbarquement > salleEmb) {
            fin = mid-1;
        }else {
            deb = mid+1;
        }
    }while(exit == -1 && deb<fin);
    return exit;
}

void rechercheVolActuelDansSalleEmb(int nbVols, struct Vol listeVols[nbVols], int indicesTri[nbVols], int indices[nbVols], int salleEmb, struct Heure mtn) {
    int trouve = 0, ind = 0;
    int prec = 0, suiv = 0;

    int heureAct = castHeureEnMinute(mtn);

    trouve = rechercheDichotomieSalleEmb(nbVols, listeVols, indicesTri, salleEmb);

    if(trouve != -1) {
        int h_trouveD=castHeureEnMinute(listeVols[indicesTri[trouve]].h_debEmbarquement);
        int h_trouveF=castHeureEnMinute(listeVols[indicesTri[trouve]].h_finEmbarquement);

        if(h_trouveD >= heureAct-30 && h_trouveD <= heureAct+10 || h_trouveF >= heureAct-30 && h_trouveF <= heureAct+10 || h_trouveD < heureAct && heureAct < h_trouveF) {
            indices[ind] = indicesTri[trouve];
            ++ind;
        }
        prec = trouve-1;
        suiv = trouve+1;

        int h_precD = 0, h_precF = 0;
        int h_suivD = 0, h_suivF = 0;

        while(listeVols[indicesTri[prec]].salleEmbarquement == salleEmb || listeVols[indicesTri[suiv]].salleEmbarquement == salleEmb) {
            if(listeVols[indicesTri[prec]].salleEmbarquement == salleEmb) {
                h_precD = castHeureEnMinute(listeVols[indicesTri[prec]].h_debEmbarquement);
                h_precF = castHeureEnMinute(listeVols[indicesTri[prec]].h_finEmbarquement);
                if(h_precD >= heureAct-30 && h_precD <= heureAct+10 || h_precF >= heureAct-30 && h_precF <= heureAct+10 || h_precD < heureAct && heureAct < h_precF) {
                    indices[ind] = indicesTri[prec];
                    ++ind;
                }
                --prec;
            }
            if(listeVols[indicesTri[suiv]].salleEmbarquement == salleEmb) {
                h_suivD = castHeureEnMinute(listeVols[indicesTri[suiv]].h_debEmbarquement);
                h_suivF = castHeureEnMinute(listeVols[indicesTri[suiv]].h_finEmbarquement);
                if(h_suivD >= heureAct-30 && h_suivD <= heureAct+10 || h_suivF >= heureAct-30 && h_suivF <= heureAct+10 || h_suivD < heureAct && heureAct < h_suivF) {
                    indices[ind] = indicesTri[suiv];
                    ++ind;
                }
                ++suiv;
            }
        }
    }
    if(ind<nbVols)
        indices[ind] = -1;
}

/** ##---- RECHERCHE VOLS AU NUM DE COMPTOIR ----## */

int rechercheDichotomieComptoir(int nbVols, struct Vol listeVols[nbVols], int indices[nbVols], int comptoir) {
    int deb = 0, fin = nbVols-1, mid = 0;
    int exit = -1;

    do {
        mid=(deb+fin)/2;
        if(listeVols[indices[mid]].numComptoir == comptoir) {
            exit = mid;
        }
        else if(listeVols[indices[mid]].numComptoir > comptoir) {
            fin = mid-1;
        }else {
            deb = mid+1;
        }
    }while(exit == -1 && deb<fin);
    return exit;
}

void rechercheVolAuNumComptoir(int nbVols, struct Vol listeVols[nbVols], int indicesTri[nbVols], int indices[nbVols], int comptoir, struct Heure mtn) {
    int trouve = 0, ind = 0;
    int prec = 0, suiv = 0;

    int heureAct = castHeureEnMinute(mtn);

    trouve = rechercheDichotomieComptoir(nbVols, listeVols, indicesTri, comptoir);

    if(trouve != -1) {
        int h_trouveD=castHeureEnMinute(listeVols[indicesTri[trouve]].h_debEnregistrement);
        int h_trouveF=castHeureEnMinute(listeVols[indicesTri[trouve]].h_finEnregistrement);

        if(h_trouveD >= heureAct-30 && h_trouveD <= heureAct+10 || h_trouveF >= heureAct-30 && h_trouveF <= heureAct+10 || h_trouveD < heureAct && heureAct < h_trouveF) {
            indices[ind] = indicesTri[trouve];
            ++ind;
        }
        prec = trouve-1;
        suiv = trouve+1;

        int h_precD = 0, h_precF = 0;
        int h_suivD = 0, h_suivF = 0;

        while(listeVols[indicesTri[prec]].numComptoir == comptoir || listeVols[indicesTri[suiv]].numComptoir == comptoir) {
            if(listeVols[indicesTri[prec]].numComptoir == comptoir) {
                h_precD = castHeureEnMinute(listeVols[indicesTri[prec]].h_debEnregistrement);
                h_precF = castHeureEnMinute(listeVols[indicesTri[prec]].h_finEnregistrement);
                if(h_precD >= heureAct-30 && h_precD <= heureAct+10 || h_precF >= heureAct-30 && h_precF <= heureAct+10 || h_precD < heureAct && heureAct < h_precF) {
                    indices[ind] = indicesTri[prec];
                    ++ind;
                }
                --prec;
            }
            if(listeVols[indicesTri[suiv]].numComptoir == comptoir) {
                h_suivD = castHeureEnMinute(listeVols[indicesTri[suiv]].h_debEnregistrement);
                h_suivF = castHeureEnMinute(listeVols[indicesTri[suiv]].h_finEnregistrement);
                if(h_suivD >= heureAct-30 && h_suivD <= heureAct+10 || h_suivF >= heureAct-30 && h_suivF <= heureAct+10 || h_suivD < heureAct && heureAct < h_suivF) {
                    indices[ind] = indicesTri[suiv];
                    ++ind;
                }
                ++suiv;
            }
        }
    }
    if(ind<nbVols)
        indices[ind] = -1;
}





