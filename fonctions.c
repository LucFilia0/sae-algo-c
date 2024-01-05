#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fichier.h"
#include "fonctions.h"
#include "IHM.h"
#include "tri.h"

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

void setCharClean(char *chaine) {
    chaine[strlen(chaine)-1] = '\0'; // Enleve le caractère '\n' de chaine quand l'utilisateur tape entrée
}

void copyCharToLower(const char *copie, char *colle) {
    for(int i=0; i<strlen(copie); ++i) {
        if(copie[i]>=65 && copie[i]<=90) {
            colle[i] = copie[i] + 32;
        }else {
            colle[i] = copie[i];
        }
    }
    colle[strlen(copie)] = '\0'; // evite les erreurs
}

// GESTION DATES
void catchDate(const char *chaine, char *jour, char *mois, char *annee) {
    int element = 0, ind = 0;
    char info[5] = "";
    clearChar(info);

    for(int i=0; i<11; ++i) { //pas touche au 11 ou wallah je te nik
        if(chaine[i] == '/' || i == strlen(chaine)) {
            switch(element) {
                case 0: copieChar(info, jour); break;
                case 1: copieChar(info, mois); break;
                case 2: copieChar(info, annee); break;
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

// GESTION HEURES
void setHeure(const char *chaine, struct Heure *heure) {
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
    // val en minutes
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

void afficherHeureDans(struct Heure heure, char *chaine) {
    if(heure.minute < 10) {
        sprintf(chaine, "%d:0%d", heure.heure, heure.minute);
    }else {
        sprintf(chaine, "%d:%d", heure.heure, heure.minute);
    }
}

int ecartHeures(struct Heure heure1, struct Heure heure2)
{
    int ecart = 0, heureEcart = 0, minuteEcart = 0 ;
    heureEcart = heure1.heure - heure2.heure ;
    minuteEcart = heure1.minute - heure2.minute ;
    if (minuteEcart < 0) {
        minuteEcart = minuteEcart + 60 ;
        heureEcart = heureEcart - 1 ;
    }
    return heureEcart*60 + minuteEcart ;
}

void DecalerDeJusqua(int n, int nbVols, int tabIndices[n], int indiceVolRetarde, int nouvelIndice)
{
    int temp = tabIndices[indiceVolRetarde] ;
    for (int i = indiceVolRetarde ; i < nouvelIndice ; i++) {
        tabIndices[i] = tabIndices[i+1] ;
    }
    tabIndices[nouvelIndice] = temp ;
}

void retarderVol(int n, int tabIndices[n], struct Vol listeVols[n],int retardAccumule, int indiceVolRetarde, struct Heure heureActuelle)
{
    char chaine[30] ;
    sprintf(chaine,"Retarde %d min",retardAccumule) ;
    strcpy(listeVols[tabIndices[indiceVolRetarde]].etatVol,chaine) ;
    listeVols[tabIndices[indiceVolRetarde]].h_decollage.heure = heureActuelle.heure ;
    listeVols[tabIndices[indiceVolRetarde]].h_decollage.minute = heureActuelle.minute ;
}

int etatVol(int n, int nbVols, int tabIndices[n], struct Vol listeVols[n], int indiceVolRetarde) {
    char chaine[30] ;
    strcpy(chaine,listeVols[tabIndices[indiceVolRetarde]].etatVol) ;
    if (chaine[0] == 'A') {
        if (chaine[1] == ' ') {
            return 0 ;
        }
        else {
            return 1 ;
        }
    }

    else {
        char chaineRetard[3] ;
        int i = 0, j = 0 ;
        while (chaine[i] != '\0' && j < 2) {
           if (chaine[i] == '0' || chaine[i] == '1' || chaine[i] == '2' || chaine[i] == '3' || chaine[i] == '4' || chaine[i] == '5' || chaine[i] == '6' || chaine[i] == '7'|| chaine[i] == '8' || chaine[i] == '9') {
                chaineRetard[j] = chaine[i] ;
                j++ ;
           }
           i++ ;
        }
        return atoi(chaineRetard) ;
    }
}

int ajoutRetard(int n, int nbVols, int tabIndices[n], struct Vol listeVols[n], int indiceVolRetarde, int tpsRetard) {

    int retardInitial = etatVol(n, nbVols, tabIndices, listeVols, indiceVolRetarde) ;
    if (retardInitial==-1) {
        printf("Le vol ne peut pas etre retarde car il est annule") ;
        return -2 ;
    }

    struct Heure heureMin , heureMax ;
    heureMin.heure = listeVols[tabIndices[indiceVolRetarde]].h_decollage.heure ;
    heureMin.minute = listeVols[tabIndices[indiceVolRetarde]].h_decollage.minute ;
    heureMax.heure = listeVols[tabIndices[indiceVolRetarde]].h_decollage.heure ;
    heureMax.minute = listeVols[tabIndices[indiceVolRetarde]].h_decollage.minute ;

    int place = 0, retardAccumule = tpsRetard + retardInitial, indiceVol = indiceVolRetarde ;
    struct Heure heurePrecedente, heureActuelle, heureSuivante ;
    int ecart, ecart1, ecart2 ;

    ajouterHeure(&heureMin,retardAccumule) ;
    ajouterHeure(&heureMax,60) ;

    if (nbVols > 1) {

        // Se place à l'heure juste avant l'heure minimum
        while (indiceVol + 1 < nbVols) {
            heureSuivante.heure = listeVols[tabIndices[indiceVol + 1]].h_decollage.heure ;
            heureSuivante.minute = listeVols[tabIndices[indiceVol + 1]].h_decollage.minute ;
            ecart = ecartHeures(heureMin, heureSuivante) ;
            if (ecart <= 0) {
                break ;
            }
            indiceVol++ ;
        }

        if (indiceVol > indiceVolRetarde) {
            heurePrecedente.heure = listeVols[tabIndices[indiceVol]].h_decollage.heure ;
            heurePrecedente.minute = listeVols[tabIndices[indiceVol]].h_decollage.minute ;
        }

        heureActuelle.heure = heureMin.heure ;
        heureActuelle.minute = heureMin.minute ;
        if (indiceVol + 1 < nbVols) {
            heureSuivante.heure = listeVols[tabIndices[indiceVol + 1]].h_decollage.heure ;
            heureSuivante.minute = listeVols[tabIndices[indiceVol + 1]].h_decollage.minute ;
        }
        // Vérifie si on peut insérer le vol à l'heure sélectionnée, sinon on ajout 1 minute à l'heure
        while (place == 0 && retardAccumule <=60) {
            ecart = ecartHeures(heureMax,heureActuelle) ;
            if (heureActuelle.heure >= 22) {
                if (heureActuelle.minute > 0) {
                    break ;
                }
            }

            if (ecart < 0) {
                break ;
            }

            if (indiceVol > indiceVolRetarde)
                ecart1 = ecartHeures(heureActuelle, heurePrecedente) ;
                if (ecart1 >= 5) {
                    place = 1 ;
                }

            if (indiceVol + 1 < nbVols) {
                ecart2 = ecartHeures(heureSuivante,heureActuelle) ;

                if (ecart2 >= 5) {
                    place = 1 ;
                }

                else {
                    place = 0 ;
                }
            }
            // Incremente et situe l'heure dans le tableau
            if (place == 0) {
                if (indiceVol + 1 < nbVols) {
                    ecart = ecartHeures(heureSuivante,heureActuelle) ;

                    if (ecart == 0) {
                        indiceVol++ ;
                        heurePrecedente.heure = heureSuivante.heure ;
                        heurePrecedente.minute = heureSuivante.minute ;
                        heureSuivante.heure = listeVols[tabIndices[indiceVol + 1]].h_decollage.heure ;
                        heureSuivante.minute = listeVols[tabIndices[indiceVol + 1]].h_decollage.minute ;

                        retardAccumule = retardAccumule + 4 ;
                        ajouterHeure(&heureActuelle,4) ;
                    }
                }

                retardAccumule++ ;
                ajouterHeure(&heureActuelle,1) ;
            }
        }
    }


    else {
        retarderVol(n, tabIndices, listeVols, tpsRetard, indiceVolRetarde, heureActuelle) ;
        return tpsRetard ;
    }

    // Annule le vol et modifie la liste des vols
    if (place == 0) {
        retardAccumule = -1 ;
        strcpy(listeVols[tabIndices[indiceVolRetarde]].etatVol,"Annule") ;
    }

    // Retarde le vol, modifie le tableau d'incides et la liste des vols
    else {
        retarderVol(n, tabIndices, listeVols, retardAccumule, indiceVolRetarde, heureActuelle) ;
        DecalerDeJusqua(n, nbVols, tabIndices, indiceVolRetarde, indiceVol) ;
    }

    return retardAccumule ;
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
            printf("\n---- Veuillez saisir une valeur entre %d et %d ----\n", nbMin, nbMax);
        }
    }while(*data<nbMin || *data>nbMax);
}

void waitPress() {
    printf("\n\nAppuyez sur [entree]...");
    getchar();
    system("cls");
}
