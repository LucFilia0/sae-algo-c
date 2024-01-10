#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fichier.h"
#include "fonctions.h"
#include "IHM.h"
#include "tri.h"
#include "retard.h"

/** ##---- DECLARATION DES FONCTIONS D'INTERACTION AVEC L'UTILISATEUR ----## */

void userEntryInt(const char *message, int *data, int nbMin, int nbMax) {
    /*
        :entree:
            'message' -> message affiché à l'utilisateur. L'affichage de la flèche est pris en compte par la fonction
            'data' -> la variable qui va stocker l'entrée de l'utilisateur
            'nbMin' -> nombre minimal accepté
            'nbMax' -> nombre maximal accepté
        :types:
            'data' est un pointeur
        :fonction:
            Permet une saisie sécurisée de l'utilisateur.
            Va scanner la réponse de l'utilisateur et en extirper les chiffres
            Ensuite, cast cette chaine de chiffre en nombre, dans 'data'
            Vérifie que nbMin <= 'data' <= nbMax (boucle tant que pas correct, message d'erreur géré par la fonction)
    */
    *data = 0;
    char entry[100] = ""; //entrée de l'utilisateur
    char verified[100] = ""; //chaine contenant les chiffres, pour ensuite etre caster en int


    do {
        int v = 0;
        clearChar(entry);
        clearChar(verified);

        printf("\n%s\n => ", message);
        fgets(entry, 100, stdin);// pas touche au 100

        for(int i=0; i<strlen(entry); i++) {
            if(entry[i]=='0'||entry[i]=='1'||entry[i]=='2'||entry[i]=='3'||entry[i]=='4'||entry[i]=='5'||entry[i]=='6'||entry[i]=='7'||entry[i]=='8'||entry[i]=='9') {
                verified[v] = entry[i];
                v++;
            }
        }

        system("cls");
        *data = atoi(verified);
        if(*data<nbMin || *data>nbMax) {
            printf("\n---- Veuillez saisir une valeur entre %d et %d ----\n", nbMin, nbMax);
        }
    }while(*data<nbMin || *data>nbMax);
}

void userEntryChar(const char *message, char *data, int length, int clearChaine) {
    /*
        :entree:
            'message' -> message affiché à l'utilisateur (les ':' sont gérés pas la fonction
            'data' -> la chaine contenant l'entrée de l'utilisateur
            'length' -> le nombre de caractères acceptés par le 'fgets'
            'clearChaine' -> pour vider la mémoire avant d'écrire dedans (conseillé)
                            0 pour ne pas vider, sinon vide
        :fonction:
            Permet à l'utilisateur d'entrer du texte, stocké dans 'data'
    */
    if(clearChaine != 0)
        clearChar(data);
    printf("%s : ", message);
    fgets(data, length, stdin);
    setCharClean(data);
    system("cls");
}

void waitPress() {
    /*
        :fonction:
            Attend que l'utilisateur appuie sur [entrée] pour effacer l'écran
    */
    printf("\n\nAppuyez sur [entree]...");
    getchar();
    system("cls");
}

/** ##---- DECLARATIONS FONCTIONS AFFICHAGE ----## */

void showTitle(const char *title) {
    /*
        :fonction:
            Affiche le titre le l'application (ceci est provisoire)
    */
    printf(" ________________________________________________________"
           "\n/\t\t\t\t\t\t\t \\\n|\t\t\tGESTION'AIR\t\t\t |\n\\"
           "________________________________________________________/"
           "\n\n>> %s\n____________________________________________________________\n", title);
}

void returnMenu(int *menu) {
    /*
        :entree:
            'menu' -> variable 'menu', dans le main, qui doit être modifié
        :types:
            'menu' est un pointeur
        :fonction:
            modifie menu, automatise l'affichage du message
    */
    showTitle("RETOUR ?");
    userEntryInt("1 - Nouvelle Recherche\n2 - Menu", menu, 1, 2);
}

void showTime(struct Date ajd, struct Heure mtn) {
    printf(" \n-<[ ");
    if(ajd.mois < 10)
        printf("%d/0%d/%d", ajd.jour, ajd.mois, ajd.annee);
    else
        printf("%d/%d/%d", ajd.jour, ajd.mois, ajd.annee);
    char heureChar[5] = "";
    afficherHeureDans(mtn, heureChar);
    printf(" | %s ]>-\n\n", heureChar);
}

void afficheLigneVide(int nbColumns, int widthColumns) {
    printf("\n");
    for(int i=0; i<nbColumns; ++i) {
        printf("|");
        for(int j=0; j<widthColumns; ++j) {
            printf("_");
        }
    }
    printf("|");
}

void afficheCentre(const char *element, int widthColumn) {
    char affiche[widthColumn];
    int j=0;
    int nbEspaces = widthColumn-strlen(element);
    int nbEspacesGauche = nbEspaces/2;

    int i=0;
    while(i<nbEspacesGauche) {
        printf(" ");
        ++i;
    }
    printf("%s", element);
    i=i+strlen(element);
    while(i<widthColumn) {
        printf(" ");
        ++i;
    }
}

void afficheLigneVol(struct Vol vol, int nbColumns, int widthColumns) {
    char element[100];
    printf("\n|");
    for(int i=0; i<nbColumns; ++i) {
        clearChar(element);
        switch(i) {
            case 0: sprintf(element, "%d", vol.numVol); break;
            case 1: copieChar(vol.compagnie, element, 1); break;
            case 2: copieChar(vol.destination, element, 1); break;
            case 3: sprintf(element, "%d", vol.numComptoir); break;
            case 4: afficherHeureDans(vol.h_debEnregistrement, element); break;
            case 5: afficherHeureDans(vol.h_finEnregistrement, element); break;
            case 6: sprintf(element, "%d", vol.salleEmbarquement); break;
            case 7: afficherHeureDans(vol.h_debEmbarquement, element); break;
            case 8: afficherHeureDans(vol.h_finEmbarquement, element); break;
            case 9: afficherHeureDans(vol.h_decollage, element); break;
            case 10: copieChar(vol.etatVol, element, 0); break;
            default: printf("\nCas non traite par switch\n"); break;
        }
        afficheCentre(element, widthColumns);
        printf("|");
    }
}

void afficheLignePassager(struct Passager passager, int nbColumns, int widthColumns) {
    char element[100];
    printf("\n|");
    for(int i=0; i<nbColumns; ++i) {
        clearChar(element);
        switch(i) {
            case 0: copieChar(passager.nom, element, 1); break;
            case 1: copieChar(passager.prenom, element, 1); break;
            case 2:
                // pas très opti mais bon... flm
                if(passager.dateNaissance.jour < 10 && passager.dateNaissance.mois >= 10)
                    sprintf(element, "0%d/%d/%d", passager.dateNaissance.jour, passager.dateNaissance.mois, passager.dateNaissance.annee);
                else if(passager.dateNaissance.mois < 10 && passager.dateNaissance.jour >= 10)
                    sprintf(element, "%d/0%d/%d", passager.dateNaissance.jour, passager.dateNaissance.mois, passager.dateNaissance.annee);
                else if(passager.dateNaissance.jour < 10 && passager.dateNaissance.mois < 10)
                    sprintf(element, "0%d/0%d/%d", passager.dateNaissance.jour, passager.dateNaissance.mois, passager.dateNaissance.annee);
                else
                    sprintf(element, "%d/%d/%d", passager.dateNaissance.jour, passager.dateNaissance.mois, passager.dateNaissance.annee);

                break;
            case 3: sprintf(element, "%d", passager.numSiege); break;
            case 4: sprintf(element, "%.2f", passager.prixBillet); break;
            default: printf("\nCas non traite par switch\n"); break;
        }
        afficheCentre(element, widthColumns);
        printf("|");
    }
}

void afficheTableauVols(struct Vol *listeVols, int nbVols, int indices[nbVols]) {
    /*
        :entree:
    */

    int widthColumns = 17;
    int nbColumns = 11;

    // LIGNE DU HAUT DU TABLO
    printf(" ");
    for(int i=0; i<(nbColumns*widthColumns+nbColumns-1); ++i) {
        printf("_");
    }
    printf("\n");
    // AFFICHER ENTETE TABLO
    for(int i=0; i<nbColumns; ++i) {
            printf("|");
        switch(i) {
            case 0: afficheCentre("NumVol", widthColumns); break;
            case 1: afficheCentre("Compagnie", widthColumns); break;
            case 2: afficheCentre("Destination", widthColumns); break;
            case 3: afficheCentre("NumComptoir", widthColumns); break;
            case 4: afficheCentre("H debEnrg", widthColumns); break;
            case 5: afficheCentre("H finEnrg", widthColumns); break;
            case 6: afficheCentre("salleEmbarq", widthColumns); break;
            case 7: afficheCentre("H debEmbarq", widthColumns); break;
            case 8: afficheCentre("H finEmbarq", widthColumns); break;
            case 9: afficheCentre("H decollage", widthColumns); break;
            case 10: afficheCentre("EtatVol", widthColumns); break;
            default: printf("\nCas non traite par switch\n"); break;
        }
    }
    printf("|");
    afficheLigneVide(nbColumns, widthColumns);
    // AFFICHE INFOS
    int i=0;

    while(i<nbVols && indices[i] != -1) {
        afficheLigneVol(listeVols[indices[i]], nbColumns, widthColumns);
        afficheLigneVide(nbColumns, widthColumns);
        ++i;
    }
}

void afficheTableauPassagers(struct Vol vol, int nbPassagers, int indices[nbPassagers]) {
    /**
    Affiche tous les passagers d'un vol passé en paramètre
    */

    int nbColumns = 5;
    int widthColumns = 20;

    // LIGNE DU HAUT DU TABLEAU
    printf(" ");
    for(int i=0; i<(nbColumns*widthColumns+nbColumns-1); ++i) {
        printf("_");
    }
    printf("\n");
    // AFFICHER ENTETE TABLO
    for(int i=0; i<nbColumns; ++i) {
            printf("|");
        switch(i) {
            case 0: afficheCentre("Nom", widthColumns); break;
            case 1: afficheCentre("Prenom", widthColumns); break;
            case 2: afficheCentre("DateNaissance", widthColumns); break;
            case 3: afficheCentre("NumSiege", widthColumns); break;
            case 4: afficheCentre("PrixBillet", widthColumns); break;
            default: printf("\nCas non traite par switch\n"); break;
        }
    }
    printf("|");
    afficheLigneVide(nbColumns, widthColumns);
    // AFFICHE INFOS
    for(int i=0; i<10; ++i) {
        if(vol.listePassagers[i].numSiege != 0) {
            afficheLignePassager(vol.listePassagers[indices[i]], nbColumns, widthColumns);
            afficheLigneVide(nbColumns, widthColumns);
        }
    }
}
