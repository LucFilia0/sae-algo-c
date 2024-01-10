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
        indices[ind] = listeVols[indicesTri[trouve]].numVol - 1;
        prec = trouve-1;
        suiv = trouve+1;
        ++ind;

        char compagniePrec[50] = "", compagnieSuiv[50] = "";
        copyCharToLower(listeVols[indicesTri[prec]].compagnie, compagniePrec);
        copyCharToLower(listeVols[indicesTri[suiv]].compagnie, compagnieSuiv);
        while(strcmp(entryLowered, compagniePrec)==0 || strcmp(entryLowered, compagnieSuiv)==0) {
            if(strcmp(compagniePrec, entryLowered)==0) {
                indices[ind] = listeVols[indicesTri[prec]].numVol - 1;
                --prec;
                ++ind;
                copyCharToLower(listeVols[indicesTri[prec]].compagnie, compagniePrec);
            }
            if(strcmp(compagnieSuiv, entryLowered)==0) {
                indices[ind] = listeVols[indicesTri[suiv]].numVol - 1;
                ++suiv;
                ++ind;
                copyCharToLower(listeVols[indicesTri[suiv]].compagnie, compagnieSuiv);
            }
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
        indices[ind] = listeVols[indicesTri[trouve]].numVol - 1;
        prec = trouve-1;
        suiv = trouve+1;
        ++ind;

        char destinationPrec[50] = "", destinationSuiv[50] = "";
        copyCharToLower(listeVols[indicesTri[prec]].destination, destinationPrec);
        copyCharToLower(listeVols[indicesTri[suiv]].destination, destinationSuiv);
        while(strcmp(entryLowered, destinationPrec)==0 || strcmp(entryLowered, destinationSuiv)==0) {
            if(strcmp(destinationPrec, entryLowered)==0) {
                indices[ind] = listeVols[indicesTri[prec]].numVol - 1;
                --prec;
                ++ind;
                copyCharToLower(listeVols[indicesTri[prec]].destination, destinationPrec);
            }
            if(strcmp(destinationSuiv, entryLowered)==0) {
                indices[ind] = listeVols[indicesTri[suiv]].numVol - 1;
                ++suiv;
                ++ind;
                copyCharToLower(listeVols[indicesTri[suiv]].destination, destinationSuiv);
            }
        }
    }
    if(ind<nbVols)
        indices[ind] = -1;
}

int rechercheDichotomieH_Decollage(int nbVols, struct Vol listeVols[], int indices[], struct Heure heure) {
    int deb = 0, fin = nbVols-1, mid = 0;
    int exit = -1;

    do {
        mid=(deb+fin)/2;
        if(compareHeures(listeVols[indices[mid]].h_decollage, heure)==0) {
            exit = mid;
        }
        else if(compareHeures(listeVols[indices[mid]].h_decollage, heure)==1) {
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

    trouve = rechercheDichotomieH_Decollage(nbVols, listeVols, indicesTri, heure);

    if(trouve != -1) {
        indices[ind] = listeVols[indicesTri[trouve]].numVol - 1;
        prec = trouve-1;
        suiv = trouve+1;
        ++ind;

        //char destinationPrec[50] = "", destinationSuiv[50] = "";
        //copyCharToLower(listeVols[indicesTri[prec]].destination, destinationPrec);
        //copyCharToLower(listeVols[indicesTri[suiv]].destination, destinationSuiv);
        while(compareHeures(listeVols[indicesTri[prec]].h_decollage, heure)==0 || compareHeures(listeVols[indicesTri[prec]].h_decollage, heure)==0) {
            if(compareHeures(listeVols[indicesTri[prec]].h_decollage, heure)==0) {
                indices[ind] = listeVols[indicesTri[prec]].numVol - 1;
                --prec;
                ++ind;
            }
            if(compareHeures(listeVols[indicesTri[prec]].h_decollage, heure)==0) {
                indices[ind] = listeVols[indicesTri[suiv]].numVol - 1;
                ++suiv;
                ++ind;
            }
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

int recherchePrixMaxFrom(int nbPassagers, struct Passager listePassagers[nbPassagers], int indices[nbPassagers], int deb) {
    /*
        :entree:
            'nbPassagers' -> le nombre de passagers max dans la liste
            'listePassagers' -> la liste de passagers
            'indices' -> tableau contenant l'ordre d'affichage des passagers
            'deb' -> indices à partir duquel on commence la recherche
        :fonction:
            recherche le prix du billet le plus cher dans une liste de passagers, à partir d'un indice
    */
    int max = deb;
    int i = deb+1;
    int ordreAlpha = 0;

    while(i<nbPassagers && indices[i] != -1) {
        if(listePassagers[indices[i]].prixBillet >= listePassagers[indices[max]].prixBillet) {
            // Si prix egal, ordre alphabétique en fonction du nom
            if(listePassagers[indices[i]].prixBillet == listePassagers[indices[max]].prixBillet) {
                ordreAlpha = compareOrdreAlpha(listePassagers[indices[i]].nom, listePassagers[indices[max]].nom);
                if(ordreAlpha == 1)
                    max = i;
            }else {
                max = i;
            }
        }
        ++i;
    }
    return max;
}

int rechercheHeureDecollageMinFrom(int nbVols, struct Vol listeVols[], int indices[], int deb) {
    int min = deb;
    int i = deb+1;

    while(i<nbVols) {
        if(compareHeures(listeVols[indices[i]].h_decollage, listeVols[indices[min]].h_decollage) == 2) {
            min = i;
        }
        ++i;
    }
    return min;
}

void rechercheCompagnie(const char *nomCompagnie, int nbVols, struct Vol listeVols[], int indices[]) {
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

void rechercheDestination(const char *nomDestination, int nbVols, struct Vol listeVols[], int indices[]) {
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

void rechercheHeureDecollage(const char *heureDecollage, int nbVols, struct Vol listeVols[], int indices[]) {
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

void rechercheAvancee(const char *compagnie, const char *destination, const char *heureDecollage, int nbVols, struct Vol listeVols[], int indicesTriCompagnie[], int indicesTriDestination[], int indicesTriH_Decollage[], int indices[]) {
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

    /*
    rechercheCompagnie(compagnie, nbVols, listeVols, indicesCompagnie);
    rechercheDestination(destination, nbVols, listeVols, indicesDestination);
    rechercheHeureDecollage(heureDecollage, nbVols, listeVols, indicesHeureDecollage);
    */

    rechercheCompagnieD(compagnie, nbVols, listeVols, indicesTriCompagnie, indicesCompagnie);
    rechercheDestinationD(destination, nbVols, listeVols, indicesTriDestination, indicesDestination);
    rechercheH_DecollageD(heureDecollage, nbVols, listeVols, indicesTriH_Decollage, indicesHeureDecollage);

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
    int h_decollageVol = 0;

    int heureAct = castHeureEnMinute(mtn);

    trouve = rechercheDichotomieSalleEmb(nbVols, listeVols, indicesTri, salleEmb);

    if(trouve != -1) {
        if((h_decollageVol = castHeureEnMinute(listeVols[indicesTri[trouve]].h_decollage)) < heureAct+30)
            indices[ind] = listeVols[indicesTri[trouve]].numVol - 1;
        prec = trouve-1;
        suiv = trouve+1;
        ++ind;

        while(listeVols[indicesTri[prec]].salleEmbarquement == salleEmb || listeVols[indicesTri[suiv]].salleEmbarquement == salleEmb) {
            if(listeVols[indicesTri[prec]].salleEmbarquement == salleEmb) {
                if((h_decollageVol = castHeureEnMinute(listeVols[indicesTri[prec]].h_decollage)) < heureAct+30)
                    indices[ind] = listeVols[indicesTri[prec]].numVol - 1;
                --prec;
                ++ind;
            }
            if(listeVols[indicesTri[suiv]].salleEmbarquement == salleEmb) {
                if((h_decollageVol = castHeureEnMinute(listeVols[indicesTri[suiv]].h_decollage)) < heureAct+30)
                    indices[ind] = listeVols[indicesTri[suiv]].numVol - 1;
                ++suiv;
                ++ind;
            }
        }
    }
    if(ind<nbVols)
        indices[ind] = -1;
}








