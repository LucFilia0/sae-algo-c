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
    sprintf(chaine,"Replace (%d min)",retardAccumule) ;
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
           if (chaine[i] >= '0' && chaine[i] <= '9') {
                chaineRetard[j] = chaine[i] ;
                j++ ;
           }
           i++ ;
        }
        return atoi(chaineRetard) ;
    }
}

int prochainVolsAnnules(int nbVols, int tabIndices[], struct Vol listeVols[],int indiceVol)
{
    while (indiceVol + 1 < nbVols) {
        if (etatVol(nbVols, tabIndices, listeVols, indiceVol+1) != -1) {
            return 0 ;
        }
        indiceVol++ ;
    }
    return 1 ;
}

int ajoutRetard(int nbVols, int tabIndices[], struct Vol listeVols[], int indiceVolRetarde, int tpsRetard) {

    if (etatVol(nbVols, tabIndices, listeVols, indiceVolRetarde) == -1) {
        printf("Un vol annule ne peut pas etre retarde") ;
        return -2 ;
    }

    struct Heure heureMin , heureMax ;
    heureMin.heure = listeVols[tabIndices[indiceVolRetarde]].h_decollage.heure ;
    heureMin.minute = listeVols[tabIndices[indiceVolRetarde]].h_decollage.minute ;
    heureMax.heure = listeVols[tabIndices[indiceVolRetarde]].h_decollage.heure ;
    heureMax.minute = listeVols[tabIndices[indiceVolRetarde]].h_decollage.minute ;

    int place = 0, retardAccumule = tpsRetard , indiceVol = indiceVolRetarde, test, done = 0 ;
    struct Heure heurePrecedente, heureActuelle, heureSuivante ;
    int ecart, ecart1, ecart2, cpt = 0 ;

    ajouterHeure(&heureMin,retardAccumule) ;
    ajouterHeure(&heureMax,60) ;

    if ((heureMax.heure >= 22 && heureMax.minute > 0) || heureMax.heure >= 23) {
        heureMax.heure = 22 ;
        heureMax.minute = 0 ;
    }

    // Se place à l'heure juste avant l'heure minimum
    while (indiceVol + 1 < nbVols) {
        if (etatVol(nbVols, tabIndices, listeVols, indiceVol+1) != -1) {
            heureSuivante.heure = listeVols[tabIndices[indiceVol + 1]].h_decollage.heure ;
            heureSuivante.minute = listeVols[tabIndices[indiceVol + 1]].h_decollage.minute ;
            ecart = ecartHeures(heureMin, heureSuivante) ;
            if (ecart <= 0) {
                break ;
            }
        }
        else {
            cpt++ ;
        }
        indiceVol++ ;
    }

    if (indiceVolRetarde == nbVols - 1 || prochainVolsAnnules(nbVols, tabIndices, listeVols, indiceVolRetarde) == 1) {
        ajouterHeure(&listeVols[tabIndices[indiceVolRetarde]].h_decollage, tpsRetard) ;
        retarderVol(tabIndices, listeVols, tpsRetard, indiceVolRetarde, listeVols[tabIndices[indiceVolRetarde]].h_decollage) ;
        return retardAccumule ;
    }

    if (indiceVol - cpt > indiceVolRetarde) {
        cpt = 0 ;
        do {
            test = etatVol(nbVols, tabIndices, listeVols, indiceVol+1) ;
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

    // Vérifie si on peut insérer le vol à l'heure sélectionnée, sinon on ajout 1 minute à l'heure
    while (place == 0 && retardAccumule <=60) {
        ecart = ecartHeures(heureMax,heureActuelle) ;
        if (ecart < 0) {
            break ;
        }

        if (indiceVol - cpt > indiceVolRetarde) {
            ecart1 = ecartHeures(heureActuelle, heurePrecedente) ;
            if (ecart1 >= 5) {
                place = 1 ;
                test = 0 ;
            }

            else {
                place = 0 ;
                test = 1 ;
            }
        }

        else {
            test = 0 ;
        }

        if (indiceVol + 1 < nbVols) {
            ecart2 = ecartHeures(heureSuivante,heureActuelle) ;

            if (ecart2 >= 5 && test == 0) {
                place = 1 ;
            }

            else {
                place = 0 ;
            }
        }

        // Incremente et situe l'heure dans le tableau
        if (place == 0) {
            done = 0 ;
            if (indiceVol + 1 < nbVols) {

                if (ecart2 == 0) {
                    done = 1 ;
                    indiceVol++ ;
                    heurePrecedente.heure = heureSuivante.heure ;
                    heurePrecedente.minute = heureSuivante.minute ;
                    cpt = 0 ;
                    do {
                        test = etatVol(nbVols, tabIndices, listeVols, indiceVol+1) ;
                        if (test != -1){
                            heureSuivante.heure = listeVols[tabIndices[indiceVol + 1]].h_decollage.heure ;
                            heureSuivante.minute = listeVols[tabIndices[indiceVol + 1]].h_decollage.minute ;
                            done = 2 ;
                        }

                        else {
                            indiceVol++ ;
                        }
                    } while ((test == -1) && (indiceVol + 1 < nbVols)) ;

                    if (done == 1) {
                        retardAccumule = retardAccumule + 5 ;
                        ajouterHeure(&heureActuelle,5) ;
                    }
                }

                else {

                    if (ecart2 < 5) {
                        retardAccumule = retardAccumule + ecart2 ;
                        ajouterHeure(&heureActuelle,ecart2) ;
                        done = 1 ;
                    }

                    else {

                        if (indiceVol > indiceVolRetarde && ecart1 > 0) {
                            retardAccumule = retardAccumule + 5 - ecart1 ;
                            ajouterHeure(&heureActuelle, 5 - ecart1) ;
                            done = 1 ;
                        }
                    }
                }
            }

            if (done == 0) {
                retardAccumule++ ;
                ajouterHeure(&heureActuelle,1) ;
            }
        }
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

