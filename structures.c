#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "structures.h"
#include "fichier.h"
#include "fonctions.h"
#include "IHM.h"
#include "tri.h"

#define NB_VOLS_MAX 192 // Attention aussi dans main.c
#define MAX 1000

/** ##---- DEFINITIONS FONCTIONS DATES ----## */

void setDate(struct Date *date,const char *chaine) {
    /*
        :entree:
            'date' -> la date à initialiser
            'chaine' -> la chaine de caractères de forme 'JJ/MM/AAAA'
        :fonction:
            Découpe 'chaine' et stock les valeurs de la dates en int dans la structure
    */
    int element = 0, ind = 0;
    char info[7] = "";
    clearChar(info);

    for(int i=0; i<11; ++i) { //pas touche au 11 ou wallah je te nik
        if(chaine[i] == '/' || i == strlen(chaine)) {
            switch(element) {
                case 0: date->jour = atoi(info); break;
                case 1: date->mois = atoi(info); break;
                case 2: date->annee = atoi(info); break;
                default: printf("Cas non gere par switch");
            }
            element++;
            ind = 0;
            clearChar(info);
        }else {
            info[ind] = chaine[i];
            ++ind;
        }
    }
}

/** ##---- DEFINITION FONCTIONS HEURES ----## */

void setHeure(const char *chaine, struct Heure *heure) {
    /*
        :entree:
            'chaine' -> la chaine de caractères de la forme 'HH:MM'
            'heure' -> l'heure à initialiser
        :types:
            'heure' est un pointeur
        :fonction:
            découpe 'chaine', et stock les valeurs en int dans la structure int
    */
    char heureChar[3] = "";
    char minuteChar[3] = "";
    int heureInt = 0;
    int minuteInt = 0;

    heureChar[0] = chaine[0];
    heureChar[1] = chaine[1];

    minuteChar[0] = chaine[2];
    minuteChar[1] = chaine[3];

    heureInt = atoi(heureChar);
    minuteInt = atoi(minuteChar);

    if((heureInt<24 && heureInt>=0) && (minuteInt<60 && minuteInt>=0)) {
        heure->heure = atoi(heureChar);
        heure->minute = atoi(minuteChar);
    }else {
        printf("\n---- Heure invalide ----\n");
    }
}

void ajouterHeure(struct Heure *heure, int val) {
    /*
        :entree:
            'heure' -> l'heure à modifier
            'val' -> la valeur, en minutes, à ajouter (peut être négatif)
        :types:
            'heure' est un pointeur
        :fonction:
            ajoute la valeur 'val' à 'heure', en vérifiant toutes les contraintes liées aux bases 60 et 24
    */
    int nbHeure = heure->heure;
    int nbMinute = heure->minute;

    nbMinute = nbMinute + val;

    if(nbMinute>=0 && nbMinute<60) {
        heure->minute = nbMinute;
    }else if(nbMinute>=60) {
        do {
            heure->heure = heure->heure + 1;
            nbMinute = nbMinute - 60;
            if(heure->heure >= 24)
                heure->heure = 0;
        }while(nbMinute>=60);
        heure->minute = nbMinute;
    }else {
        // dans le cas ou val est négatif
        do {
            heure->heure = heure->heure - 1;
            nbMinute = 60 + nbMinute;
            if(heure->heure < 0)
                heure->heure = 23;
        }while(nbMinute<0);
        heure->minute = nbMinute;
    }
}

int compareHeures(struct Heure h1, struct Heure h2) {
    int exit = 0;
    if(h1.heure == h2.heure) {
        if(h1.minute == h2.minute) {
            exit = 0;
        }
        else if(h1.minute > h2.minute) {
            exit = 1;
        }
        else {
            exit = 2;
        }
    }else {
        if(h1.heure > h2.heure) {
            exit = 1;
        }else {
            exit = 2;
        }
    }
    return exit;
}

int castHeureEnMinute(struct Heure heure) {
    int exit = heure.heure * 60 + heure.minute;
    return exit;
}

void afficherHeureDans(struct Heure heure, char *chaine) {
    /*
        :entree:
            'heure' -> l'heure à afficher
            'chaine' -> la chaine de caractères qui contient la valeur texte de 'heure'
        :fonction:
            affiche un '0' devant les minutes, si elles sont inférieures à 10,
            prcq c'est joli :)
    */
    if(heure.minute < 10) {
        sprintf(chaine, "%d:0%d", heure.heure, heure.minute);
    }else {
        sprintf(chaine, "%d:%d", heure.heure, heure.minute);
    }
}

/** ##---- DEFINITION FONCTIONS IMPORTATION DONNEES ----## */

void importDataBase(FILE *fichier, struct Vol *listeVols, int *nbVols) {
    /*
        :paramètres:
            'fichier' -> le fichier à lire
            'listeVols' -> le tableau stockant tous les vols que l'on va importer
            'nbVols' -> la compteur qui dénombre les vols existant (différent de nombre de vols max)
        :pre-cond:
            'nbVols' est un pointeur
        :fonction:
            importe tous les vols aux bons emplacements
    */
    char ligne[MAX] = "";
    struct Vol *ptVol;
    char verif = ' ';

    scanFichier(fichier, '\n', ligne); //on passe la premiere ligne #flm

    do {
        char ligne[MAX] = "", infoVol[MAX] = "", listePassagers[MAX] = "";
        scanFichier(fichier, '\n', ligne); //on stock la ligne actuelle dans 'ligne'

        getCharTo(ligne, '"', infoVol); //recupere la chaine jusqu'a ", => infos vol

        getCharFromTo(ligne, '"', '"', listePassagers); // recupere de " a ", => liste passagers

        ptVol = &(listeVols[*nbVols]);
        initVol(ptVol, infoVol); // init vol avec donnes du vol
        initPassagers(ptVol, listePassagers); // init liste passagers

        verif = fgetc(fichier); // on vérifie le carac suivant
        fseek(fichier, -1, SEEK_CUR); // on se replace bien

        *nbVols = *nbVols + 1; //vol suivant (pas de ++)
    }while(*nbVols < NB_VOLS_MAX && verif != EOF);
}


void initVol(struct Vol *vol, char *infoVol)
{
    /*
        :entree:
            'vol' -> le vol à implémenter
            'infoVol' -> la chaine de caractère contenant toutes les infos sur le vol
        :types:
            'vol' est un pointeur, car on veut modifier le vol, pas juste le lire, donc on écrit sur son emplacement mémoire
        :fonction:
            initialise les données du vol
    */
    char info[50] = "";
    int i = 0, ind = 0, numElement = 0;
    while(i<strlen(infoVol)) {
        if(infoVol[i]!=',') {
            info[ind] = infoVol[i];
            ind++;
        }
        else {
            switch(numElement)
            {
                case 0: vol->numVol = atoi(info); break;
                case 1: copieChar(info, vol->compagnie, 1); break;
                case 2: copieChar(info, vol->destination, 1); break;
                case 3: vol->numComptoir = atoi(info); break;
                case 4: setHeure(info, &(vol->h_debEnregistrement)); break;
                case 5: setHeure(info, &(vol->h_finEnregistrement)); break;
                case 6: setHeure(info, &(vol->salleEmbarquement)); break;
                case 7: setHeure(info, &(vol->h_debEmbarquement)); break;
                case 8: setHeure(info, &(vol->h_finEmbarquement)); break;
                case 9: setHeure(info, &(vol->h_decollage)); break;
                case 10: copieChar(info, vol->etatVol, 0); break;
                default: printf("\nCas non traite par switch\n"); break;
            }
            numElement++;
            ind = 0;
            clearChar(info);
        }
        i++;
    }
}

void clearPassagers(struct Vol *vol) {
    /*
        :entree:
            'vol' -> le vol dont on va nettoyer la liste de passagers
        :fonction:
            met tous les paramètres de tous les passagers de 'vol' à leur valeur nulle,
            afin de ne pas avoir de valeur bizarres qui apparaissent lors de l'affichage
    */
    for(int i=0; i<100; ++i) {
        clearChar(vol->listePassagers[i].nom);
        clearChar(vol->listePassagers[i].prenom);
        vol->listePassagers[i].dateNaissance.jour = 0;
        vol->listePassagers[i].dateNaissance.mois = 0;
        vol->listePassagers[i].dateNaissance.annee = 0;
        vol->listePassagers[i].numSiege = 0;
        vol->listePassagers[i].prixBillet = 0.;
    }
}

void initPassagers(struct Vol *vol, const char *listePassagers)
{
    /*
        :entree:
            'vol' -> le vol dont on va modifier la liste de passagers
            'listePassagers' -> la chaine de caractères contenant toutes les infos des passagers
        :types:
            'vol' -> pointeur, car on veut modifier
        :fonction:
            initialise la liste de passagers du vol
    */
    clearPassagers(vol);
    char info[100];
    int passager = 0;
    int i = 0, ind = 0, numElement = 0;

    char jour[3] = "";
    char mois[3] = "";
    char annee[5] = "";

    while(i<strlen(listePassagers)) {
        if(listePassagers[i]!=';' && i<strlen(listePassagers)-1) {
            if(listePassagers[i]!=',') {
                info[ind] = listePassagers[i];
                ++ind;
            }else {
                switch(numElement)
                {
                    case 0: copieChar(info, vol->listePassagers[passager].nom, 1); break;
                    case 1: copieChar(info, vol->listePassagers[passager].prenom, 1); break;
                    case 2: setDate(&(vol->listePassagers[passager].dateNaissance), info); break;
                    case 3: vol->listePassagers[passager].numSiege = atoi(info); break;
                    default: printf("\nCas non traite par switch\n"); break;
                }
                numElement++;
                ind=0;
                clearChar(info);
            }
        }else {
            vol->listePassagers[passager].prixBillet = atof(info);
            passager++;
            numElement=0;
            ind=0;
            clearChar(info);
        }
        ++i;
    }
}

/** ##---- FONCTIONS TIME.H ----## */

void getHeureSystemInto(struct Heure *heure) {
    time_t now;
    time(&now);
    struct tm *heureActuelle = localtime(&now);

    heure->heure = heureActuelle->tm_hour;
    heure->minute = heureActuelle->tm_min;
}

void getDateSystemInto(struct Date *date) {
    time_t now;
    time(&now);
    struct tm *heureActuelle = localtime(&now);

    date->jour = heureActuelle->tm_mday;
    date->mois = heureActuelle->tm_mon + 1;
    date->annee = heureActuelle->tm_year + 1900;
}
