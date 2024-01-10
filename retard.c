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

        /*
        ====== Partie qui a de grandes chances de servir à rien ========
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
        */

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

                    if (ecart2 == 0) {
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
                        retardAccumule = retardAccumule + ecart2 ;
                        ajouterHeure(&heureActuelle,ecart2) ;
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

