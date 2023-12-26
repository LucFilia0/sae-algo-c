#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fichier.h"
#include "fonctions.h"
#include "IHM.h"

void verifAlpha(char *chaine) {
    /**
    Verifie si caracteres alphanumériques respectés
    */
    for(int i=0; i<strlen(chaine); ++i) {
        if ( ((chaine[i] >= 48) && (chaine[i] <= 58)) || ((chaine[i] >= 65) && (chaine[i] <= 90)) || ((chaine[i] >= 97) && (chaine[i] <= 122)) ) {}
        else {
            chaine[i] = ' ';
        }
    }
}

void copieChar(const char* copie, char *colle) {
    strcpy(colle, copie);
    verifAlpha(colle);
}

void getCharTo(const char *chaine, char stop, char *sortie) {
    int i = 0;
    while(i<strlen(chaine) && chaine[i]!=stop) {
        sortie[i] = chaine[i];
        i++;
    }
}

void getCharFromTo(const char *chaine, char start, char stop, char *sortie) {
    int i=0, statut = 0, iSortie = 0;
    while(i<strlen(chaine)) {
        if(chaine[i]==start && statut==0) {
            statut = 1;
        }else {
            if(chaine[i]==stop && statut==1) {
                statut = 0;
            }else {
                if(statut==1) {
                    sortie[iSortie] = chaine[i];

                    iSortie++;
                }
            }
        }
        i++;
    }
}

void clearChar(char *chaine) {
    memset(chaine, 0, strlen(chaine));
}

/* GRAPHICS */

void showTitle() {
    printf("\n>> GESTION'AIR\n\n");
}

void userEntryInt(const char *message, int *data, int nbMin, int nbMax) {
    *data = 0;
    char entry[100] = "";
    char verified[100] = "";


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
            printf("\n|-- Veuillez saisir une valeur entre %d et %d --|\n", nbMin, nbMax);
        }
    }while(*data<nbMin || *data>nbMax);
}

void waitPress() {
    printf("\nAppuyez sur [entree]...");
    getchar();
    system("cls");
}
