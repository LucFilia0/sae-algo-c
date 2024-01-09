#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "fichier.h"
#include "fonctions.h"
#include "IHM.h"
#include "tri.h"
#include "recherches.h"

/** ##-- DEFINITIONS FONCTIONS CHAINES DE CARACTERES --## */

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
    int i=0;
    while(i<strlen(copie)) {
        if(copie[i]>='A' && copie[i]<='Z') {
            colle[i] = copie[i] + 32;
        }else {
            colle[i] = copie[i];
        }
        ++i;
    }
    colle[i] = '\0'; // evite les erreurs
}

int compareOrdreAlpha(const char *chaine1, const char *chaine2) {
    /*
        :fontion:
            renvoie 1 si 'chaine1' est avant 'chaine2' dans l'ordre alphabétique
            renvoie 2 si 'chaine2' est avant
            renvoie 0 si elles sont égales

            La casse est gérée => nn
    */
    int alpha = 0;
    int taille = 0;

    if(strlen(chaine1)>strlen(chaine2)) {
        taille = strlen(chaine1);
    }
    else {
        taille = strlen(chaine2);
    }

    char *c1 = "";
    char *c2 = "";

    int i=0;
    while(i<taille) {
        if(chaine1[i] != chaine2[i]) {
            if(chaine1[i] == '\0') {
                alpha = 1;
                break;
            }
            else if(chaine2[i] == '\0') {
                alpha = 2;
                break;
            }
            else if(chaine1[i]>chaine2[i]) {
                alpha = 2;
                break;
            }
            else if(chaine1[i]<chaine2[i]) {
                alpha = 1;
                break;
            }
        }
        ++i;
    }

    return alpha;
}

/** ##---- DEFINITIONS FONCTIONS TABLEAUX ----## */

void indexFill(int n, int tabIndices[n], int nbVols)
{
    /*
    :entree:
        'n' -> Taille maximum du tableau
        'tabIndices' -> tableau à remplir
        'nbVols' -> nombre de Vols dans listeVols
    :fonction:
        Remplie le tableau d'indices (done 0, 1, 2...) jusqu'à en avoir mis nbVols, puis finis de remplir le tableau avec des -1.
    */
    for (int i = 0 ; i < nbVols ; i++) {
        tabIndices[i] = i ;
    }
    for (int i = nbVols ; i < n ; i++) {
        tabIndices[i] = -1 ;
    }
}

void afficheTab(int taille, int tab[taille]) {
    /*
        :fonction:
            affiche le tableau passé en paramètre (pour les tests)
    */
    int i=0;
    printf("[");
    while(i<taille-1) {
        printf("%d ", tab[i]);
        ++i;
    }
    printf("%d]\n", tab[i]);
}

void echangeIndicesTab(int taille, int tab[taille], int ind1, int ind2) {
    /*
        :fonction:
            échange les valeurs des indices 'ind1' et 'ind2' dans 'tab'
    */
    int temp = tab[ind1];
    tab[ind1] = tab[ind2];
    tab[ind2] = temp;
}

void copieTabDansTab(int taille, int copie[taille], int colle[taille]) {
    /*
        :entree:
            'taille' -> la taille du tableau
            'copie' -> le tableau à copier
            'colle' -> le tableau à coller
        :fonction:
            Copie les éléments de 'copie' dans 'colle', jusq'à la fin, ou jusq'à rencontrer '-1'
    */
    int i = -1;
    do {
        ++i;
        colle[i] = copie[i];
    }while(copie[i] != -1 && i<taille);
}

void concatenerTableaux(int taille1, int tab1[taille1], int taille2, int tab2[taille2], int taille3, int tab3[taille3]) {
    /*
        :fonction:
            Concatenne tab2 à la suite de tab1, sans stocker les '-1', copie le tout dans tab3, avec un '-1' au bout
    */
    int ind3 = 0;
    int ind1 = 0;
    int ind2 = 0;
    while(ind1<taille1 && tab1[ind1] != -1) {
        tab3[ind3] = tab1[ind1];
        ++ind1;
        ++ind3;
    }
    while(ind2<taille2 && tab2[ind2] != -1) {
        tab3[ind3] = tab2[ind2];
        ++ind2;
        ++ind3;
    }
    if(ind3<taille3)
        tab3[ind3] = -1;
}

int ecartHeures(struct Heure heure1, struct Heure heure2)
{
    /*
        :entree:
            'heure1' -> 1ere heure à comparer
            'heure2' -> 2eme heure à comparer
        :fonction:
            Renvoie l'ecart en minutes entre les 2, l'écart sera négatif si la 1ere heure est avant la 2eme.
    */
    int ecart = 0, heureEcart = 0, minuteEcart = 0 ;
    heureEcart = heure1.heure - heure2.heure ;
    minuteEcart = heure1.minute - heure2.minute ;
    if (minuteEcart < 0) {
        minuteEcart = minuteEcart + 60 ;
        heureEcart = heureEcart - 1 ;
    }
    return heureEcart*60 + minuteEcart ;
}

void decalerDeJusqua(int nbVols, int tabIndices[], int indiceVolRetarde, int nouvelIndice)
{
    int temp = tabIndices[indiceVolRetarde] ;
    for (int i = indiceVolRetarde ; i < nouvelIndice ; i++) {
        tabIndices[i] = tabIndices[i+1] ;
    }
    tabIndices[nouvelIndice] = temp ;
}

void retarderVol(int tabIndices[], struct Vol listeVols[],int retardAccumule, int indiceVolRetarde, struct Heure heureActuelle)
{
    char chaine[30] ;
    sprintf(chaine,"Retarde (%d min)",retardAccumule) ;
    strcpy(listeVols[tabIndices[indiceVolRetarde]].etatVol,chaine) ;
    listeVols[tabIndices[indiceVolRetarde]].h_decollage.heure = heureActuelle.heure ;
    listeVols[tabIndices[indiceVolRetarde]].h_decollage.minute = heureActuelle.minute ;
}

int etatVol(int nbVols, int tabIndices[], struct Vol listeVols[], int indiceVol)
{
    char chaine[30] ;
    strcpy(chaine,listeVols[tabIndices[indiceVol]].etatVol) ;
    if (chaine[0] == 'A') {
        if (chaine[1] == ' ') {
            return 0 ;
        }
        else {
            return -1 ;
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

int ajoutRetard(int nbVols, int tabIndices[], struct Vol listeVols[], int indiceVolRetarde, int tpsRetard) {

    if (etatVol(nbVols, tabIndices, listeVols, indiceVolRetarde) == -1) {
        printf("Un vol annule ne peut pas etre retarde") ;
        printf("%d",indiceVolRetarde) ;
        return -2 ;
    }

    struct Heure heureMin , heureMax ;
    heureMin.heure = listeVols[tabIndices[indiceVolRetarde]].h_decollage.heure ;
    heureMin.minute = listeVols[tabIndices[indiceVolRetarde]].h_decollage.minute ;
    heureMax.heure = listeVols[tabIndices[indiceVolRetarde]].h_decollage.heure ;
    heureMax.minute = listeVols[tabIndices[indiceVolRetarde]].h_decollage.minute ;

    int place = 0, retardAccumule = tpsRetard , indiceVol = indiceVolRetarde, test ;
    struct Heure heurePrecedente, heureActuelle, heureSuivante ;
    int ecart, ecart1, ecart2 ;

    ajouterHeure(&heureMin,retardAccumule) ;
    ajouterHeure(&heureMax,60) ;

    if ((heureMax.heure >= 22 && heureMax.minute > 0) || heureMax.heure >= 23) {
        heureMax.heure = 22 ;
        heureMax.minute = 0 ;
    }

    if (nbVols > 1) {

        // Se place à l'heure juste avant l'heure minimum
        while (indiceVol + 1 < nbVols) {
            if (etatVol(nbVols, tabIndices, listeVols, indiceVol) != -1) {
                heureSuivante.heure = listeVols[tabIndices[indiceVol + 1]].h_decollage.heure ;
                heureSuivante.minute = listeVols[tabIndices[indiceVol + 1]].h_decollage.minute ;
                ecart = ecartHeures(heureMin, heureSuivante) ;
                if (ecart <= 0) {
                    break ;
                }
            }
            indiceVol++ ;
        }

        if (indiceVol > indiceVolRetarde) {
            do {
                test = etatVol(nbVols, tabIndices, listeVols, indiceVol) ;
                if (test != -1) {
                    heurePrecedente.heure = listeVols[tabIndices[indiceVol]].h_decollage.heure ;
                    heurePrecedente.minute = listeVols[tabIndices[indiceVol]].h_decollage.minute ;
                }
                else {
                    indiceVol-- ;
                }
            } while ((test == -1) && (indiceVol > indiceVolRetarde)) ;
        }

        heureActuelle.heure = heureMin.heure ;
        heureActuelle.minute = heureMin.minute ;

        if (indiceVol + 1 < nbVols) {
            do {
                test = etatVol(nbVols, tabIndices, listeVols, indiceVol) ;
                if (test != -1){
                    heureSuivante.heure = listeVols[tabIndices[indiceVol + 1]].h_decollage.heure ;
                    heureSuivante.minute = listeVols[tabIndices[indiceVol + 1]].h_decollage.minute ;
                }

                else {
                    indiceVol++ ;
                }
            } while ((test == -1) && (indiceVol + 1 < nbVols)) ;
        }

        // Vérifie si on peut insérer le vol à l'heure sélectionnée, sinon on ajout 1 minute à l'heure
        while (place == 0 && retardAccumule <=60) {
            ecart = ecartHeures(heureMax,heureActuelle) ;
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
                        do {
                            test = etatVol(nbVols, tabIndices, listeVols, indiceVol) ;
                            if (test != -1){
                                heureSuivante.heure = listeVols[tabIndices[indiceVol + 1]].h_decollage.heure ;
                                heureSuivante.minute = listeVols[tabIndices[indiceVol + 1]].h_decollage.minute ;
                            }

                            else {
                                indiceVol++ ;
                            }
                        } while ((test == -1) && (indiceVol + 1 < nbVols)) ;

                        retardAccumule = retardAccumule + 5 ;
                        ajouterHeure(&heureActuelle,5) ;
                    }

                    else {
                        retardAccumule = retardAccumule + ecart ;
                        ajouterHeure(&heureActuelle,ecart) ;
                    }

                }

                else {
                    retardAccumule++ ;
                    ajouterHeure(&heureActuelle,1) ;

                }

            }

        }
    }


    else {
        retarderVol(tabIndices, listeVols, tpsRetard, indiceVolRetarde, heureActuelle) ;
        return tpsRetard ;
    }

    // Annule le vol et modifie la liste des vols
    if (place == 0) {
        retardAccumule = -1 ;
        strcpy(listeVols[tabIndices[indiceVolRetarde]].etatVol,"Annule") ;
    }

    // Retarde le vol, modifie le tableau d'incides et la liste des vols
    else {
        retarderVol(tabIndices, listeVols, retardAccumule, indiceVolRetarde, heureActuelle) ;
        decalerDeJusqua(nbVols, tabIndices, indiceVolRetarde, indiceVol) ;
    }

    return retardAccumule ;
}

void updatePiste(int nbVols, int tabIndices[], struct Vol listeVols[], int n, int tabIndiceVol[n])
{
    int etatRetard, indiceVol ;
    for (int i = 0 ; i < nbVols ; i++) {
        indiceVol = rechercheIndiceAvecNumVol(nbVols, tabIndices, listeVols, tabIndiceVol[i]) ;
        etatRetard = etatVol(nbVols, tabIndices, listeVols, indiceVol) ;
        if (etatRetard > 0) {
            ajoutRetard(nbVols, tabIndices, listeVols, indiceVol, etatRetard) ;
       }
    }
}
