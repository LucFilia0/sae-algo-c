#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fichier.h"
#include "fonctions.h"
#include "IHM.h"
#include "tri.h"

/** ##-- DEFINITIONS FONCTIONS SUR LES CHAINES DE CARACTERES --## */

void verifAlpha(char *chaine) {
    /*
        :entree;
            'chaine' -> la chaine a vérifier
        :fonction:
            vérifie si 'chaine' respecte les caractères alphanumériques.
            Sinon, elle remplace par un espace
    */
    for(int i=0; i<strlen(chaine); ++i) {
        if ( ((chaine[i] >= 48) && (chaine[i] <= 58)) || ((chaine[i] >= 65) && (chaine[i] <= 90)) || ((chaine[i] >= 97) && (chaine[i] <= 122)) ) {}
        else {
            chaine[i] = ' ';
        }
    }
}

void copieChar(const char* copie, char *colle, int alpha) {
    /*
        :entree:
            'copie' -> la chaine à copier
            'colle' -> la chaine dans laquelle on colle
            'aplha' -> si 0, la vérification alphanumérique n'est pas effectuée.
                        Pour toute autre valeur que 0, les caractères seront remplacés par des espaces
        :fonction:
            copie une chaine de caractères dans une autre, en vérifiant les caractères alphanuméiques, ou pas.
    */
    strcpy(colle, copie);
    if(alpha != 0)
        verifAlpha(colle);
}

void getCharTo(const char *chaine, char stop, char *sortie) {
    /*
        :entree:
            'chaine' -> chaine que l'on scan
            'stop' -> le caractère qui arrête le scan
            'sortie' -> la chaine dans laquelle est copiée le scan
        :fonction:
            scan 'chaine', jusqu'à renconter 'stop'. Copie le scan dans 'sortie'
    */
    int i = 0;
    while(i<strlen(chaine) && chaine[i]!=stop) {
        sortie[i] = chaine[i];
        i++;
    }
}

void getCharFromTo(const char *chaine, char start, char stop, char *sortie) {
    /*
        :entree:
            'chaine' -> chaine a scanner
            'start' -> caractère qui commence le scan
            'stop' -> caractère qui arrête le scan
            'sortie' -> chaine qui accueille le scan
        :fonction:
            scan 'chaine', en commencant à 'start', et en s'arrêtant à 'stop', copie dans 'sortie'
    */
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
    /*
        :fonction:
            supprime tous les éléments d'une chaine ou d'un tableau
    */
    memset(chaine, 0, strlen(chaine));
}

void setCharClean(char *chaine) {
    /*
        :fonction:
            Suite à un 'fgets', enleve le caractère '\n' de chaine quand l'utilisateur tape entrée,
            sinon bousille toutes les comparations de chaine
    */
    chaine[strlen(chaine)-1] = '\0';
}

void copyCharToLower(const char *copie, char *colle) {
    /*
        :entree:
            'copie' -> chaine à copier
            'colle' -> chaine accueillant la version minuscule de 'copie'
        :fonction:
            'colle' est la version de 'copie' en lettres minuscules. Les autres caractères ne sont pas affectés
    */
    for(int i=0; i<strlen(copie); ++i) {
        if(copie[i]>=65 && copie[i]<=90) {
            colle[i] = copie[i] + 32;
        }else {
            colle[i] = copie[i];
        }
    }
    colle[strlen(copie)] = '\0'; // evite les erreurs
}

int compareOrdreAlpha(const char *chaine1, const char *chaine2) {
    /*
        :fontion:
            renvoie 1 si 'chaine1' est avant 'chaine2' dans l'ordre alphabétique
            renvoie 2 si 'chaine2' est avant
            renvoie 0 si elles sont égales

            La casse est gérée
    */
    int alpha = 0;
    int taille = 0;

    if(strlen(chaine1)>strlen(chaine2))
        taille = strlen(chaine1);
    else
        taille = strlen(chaine2);

    char *c1;
    char *c2;

    copyCharToLower(chaine1, c1);
    copyCharToLower(chaine2, c2);

    for(int i=0; i<taille; ++i) {
        if(c1[i] == '\0') {
            alpha = 2;
            break;
        }
        else if(c2[i] == '\0') {
            alpha = 1;
            break;
        }
        else if(c1[i]>c2[i]) {
            alpha = 1;
            break;
        }
        else if(c1[i]<c2[i]) {
            alpha = 2;
            break;
        }
    }

    return alpha;
}

/** ##---- DEFINITIONS DES FONCTIONS SUR LES TABLEAUX ----## */

void echangeIndicesTab(int taille, int tab[taille], int ind1, int ind2) {
    /*
        :fonction:
            échange les valeurs des indices 'ind1' et 'ind2' dans 'tab'
    */
    int temp = tab[ind1];
    tab[ind1] = tab[ind2];
    tab[ind2] = temp;
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
