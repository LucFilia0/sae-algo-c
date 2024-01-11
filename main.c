#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "structures.h"
#include "fichier.h"
#include "fonctions.h"
#include "IHM.h"
#include "tri.h"
#include "recherches.h"
#include "retard.h"

#define NB_VOLS_MAX 192 //attention aussi dans structures.c & tri.c

int main(int argc, char *argv[])
{
    char nomFichier[50] = "";
    const char* csvBase = "data_vols.csv";

    int whatFile = 0;
    printf("\n===== CHOIX DU FICHIER CSV ======\n");
    userEntryInt(" 1 - Utiliser les vols de base\n 2 - Importer un fichier", &whatFile, 0, 2);

    if(whatFile == 2) {
        char newFile[50] = "";
        userEntryChar("Nom du fichier a importer", newFile, 50, 0);
        copieChar(newFile, nomFichier, 0);
    }else {
        copieChar(csvBase, nomFichier, 0);
    }
    FILE *fichier;
    fichier = fopen(nomFichier, "r");

    if(fichier==NULL) {
        perror(nomFichier);
    }

    else
    {
        // SET KKKONSOLE
        //system("color 3f");

        // SET HEURE ET DATE
        struct Heure mtn;
        struct Date ajd;
        getDateSystemInto(&ajd);

        struct Vol listeVols[NB_VOLS_MAX];
        int nbVols = 0;
        importDataBase(fichier, listeVols, &nbVols);

        if(nbVols<=0) {
            printf("\n/!\\ - ERREUR : Aucun vol à importer\n");
            exit(EXIT_FAILURE);
        }

        // TECHNIQUE DE BRIGAND POUR METTRE EN PLEIN ECRAN
        keybd_event(VK_MENU,0x38,0,0); //Appuie sur ALT
        keybd_event(VK_RETURN,0x1c,0,0); //Appuie ENTREE
        keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0); // Relache ENTREE
        keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0); //Relache ALT

        // VARIABLES
        struct Vol *v;
        int entry, recherche, numVol, heure, quit = 0;
        char compagnie[50], destination[50];
        int tabIndicesH_Decollage[NB_VOLS_MAX], tabIndicesDestination[NB_VOLS_MAX] ;
        int tabIndicesNomsCompagnie[NB_VOLS_MAX], tabIndicesSalleEmbarquement[NB_VOLS_MAX];
        int tabIndicesComptoirsErg[NB_VOLS_MAX], temp[NB_VOLS_MAX];

        // TRI INDIRECTS
        indexFill(NB_VOLS_MAX, tabIndicesH_Decollage, nbVols) ;
        indexFill(NB_VOLS_MAX, tabIndicesDestination, nbVols) ;
        indexFill(NB_VOLS_MAX, tabIndicesNomsCompagnie, nbVols) ;
        indexFill(NB_VOLS_MAX, tabIndicesSalleEmbarquement, nbVols) ;
        indexFill(NB_VOLS_MAX, tabIndicesComptoirsErg, nbVols);

        triFusion(nbVols, tabIndicesH_Decollage, temp, listeVols, 1) ;
        triFusion(nbVols, tabIndicesDestination, temp, listeVols, 2) ;
        triFusion(nbVols, tabIndicesNomsCompagnie, temp, listeVols, 3) ;
        triFusion(nbVols, tabIndicesSalleEmbarquement, temp, listeVols, 4) ;
        triFusion(nbVols, tabIndicesComptoirsErg, temp, listeVols, 5);

        // GESTION DE LA PISTE
        for (int i = 0 ; i < NB_VOLS_MAX ; i++) {
                if (i < nbVols) {
                    temp[i] = listeVols[tabIndicesH_Decollage[i]].numVol ;
                }
                else {
                    temp[i] = -1 ;
                }
        }
        updatePiste(nbVols, tabIndicesH_Decollage, listeVols, NB_VOLS_MAX, temp) ;

        // ARBRE EVENEMENTS
        do {
            getHeureSystemInto(&mtn);
            int menu = 1;

            /** ---- ACCUEIL ---- **/
            showTitle("ACCUEIL");
            showTime(ajd, mtn);

            printf("\n Vols a venir (dans les 3 prochaines heures) :\n");
            int indicesVolsAccueil[NB_VOLS_MAX] = {0};
            rechercheVolsAccueil(nbVols, listeVols, tabIndicesH_Decollage, indicesVolsAccueil, mtn);
            if(indicesVolsAccueil[0] != -1) {
                int nbVolsAccueil = compterElmntTab(nbVols, indicesVolsAccueil);
                triFusion(nbVolsAccueil, indicesVolsAccueil, temp, listeVols, 1) ;
                afficheTableauVols(listeVols, nbVols, indicesVolsAccueil);
            }else {
                printf("\n---- Aucun vol a venir ----\n");
            }

            userEntryInt("\n\n1 - Voir un vol\n2 - Recherche avancee\n3 - Gestion de la piste\n4 - Voir les ecrans\n5 - Quitter", &entry, 1, 5);

            /** ---- VOIR UN VOL ----## **/
            if(entry == 1) {
                do {
                    showTitle("VOIR UN VOL");
                    int numVol = 0;
                    int indices[100] = {0};

                    userEntryInt("Entrez le numero du vol", &numVol, 0, nbVols);

                    if(numVol>0) {
                        showTitle("VOIR UN VOL");
                        int vol[1] = {numVol-1};

                        printf("\nVol %d :\n", numVol);
                        afficheTableauVols(listeVols, 1, vol);

                        printf("\n\nListe des passagers :\n");
                        trierPassagers(100, listeVols[numVol-1].listePassagers, indices, temp, ajd);
                        afficheTableauPassagers(listeVols[numVol-1], 100, indices);

                        waitPress();
                        returnMenu(&menu);
                    }else {
                        menu = 2;
                    }
                }while(menu != 2);
            }

            /** ---- RECHERCHE AVANCEE ----- **/
            else if(entry == 2) {
                do {
                    char compagnie[50] = "", destination[50] = "", heureDecollage[7] = "";

                    int tabIndices[NB_VOLS_MAX] = {0};
                    int rechercheValidee = 0, retour = 0; // 1 pour 'validée'

                    do {
                        showTitle("RECHERCHE AVANCEE");
                        int rechercheMult = 0;

                        printf("\n======================================="
                               "\n 1 - Compagnie : %s"
                               "\n 2 - Destination : %s"
                               "\n 3 - Heure de decollage (+3h) : %s"
                               "\n=======================================\n", compagnie, destination, heureDecollage);

                        userEntryInt("Choisissez les criteres a appliquer\n\n[entree] pour valider/retour", &rechercheMult, 0, 3);

                        if(rechercheMult == 1) {
                            showTitle("RECHERCHE AVANCEE -> Compagnie");
                            userEntryChar("\nCompagnie", compagnie, 50, 1);
                        }
                        else if(rechercheMult == 2) {
                            showTitle("RECHERCHE AVANCEE -> Destination");
                            userEntryChar("\nDestination", destination, 50, 1);
                        }
                        else if(rechercheMult == 3) {
                            showTitle("RECHERCHE AVANCEE -> Heure de decollage");
                            userEntryChar("\nHeure de decollage (HH:MM)", heureDecollage, 50, 1);
                        }
                        else {
                            if(strcmp(compagnie, "") != 0 || strcmp(destination, "") != 0 || strcmp(heureDecollage, "") != 0) {
                                rechercheValidee = 1;
                            }else {
                                retour = 1; //réaffiche l'écran de recherche avancée
                            }
                        }
                    }while(rechercheValidee != 1 && retour != 1);

                    if(rechercheValidee == 1) {
                        showTitle("RECHERCHE AVANCEE");
                        //On garde l'affichage sympa
                        printf("\n======================================="
                               "\n 1 - Compagnie : %s"
                               "\n 2 - Destination : %s"
                               "\n 3 - Heure de decollage (+3h) : %s"
                               "\n=======================================\n", compagnie, destination, heureDecollage);

                        rechercheAvancee(compagnie, destination, heureDecollage, nbVols, listeVols, temp, tabIndicesNomsCompagnie, tabIndicesDestination, tabIndicesH_Decollage, tabIndices);
                        if(tabIndices[0] != -1) { //Si au moins un vol est trouvé
                            afficheTableauVols(listeVols, nbVols, tabIndices);
                        }else {
                            printf("\n---- Aucun vol ne correspond a votre recherche ----\n");
                        }

                        waitPress();
                        returnMenu(&menu);
                    }else if(retour == 1) {
                        menu = 2;
                    }
                }while(menu != 2);
            }


            /** ---- GESTION PISTE ---- **/
            /*
                Les passagers sont rangés selon leur age -> les 12 et - devant, puis les "adultes".
                Les deux tranches d'âge sont ensuite triées, de façon indépendante, selon le prix de leur billet (ordre décroissant).
            */
            else if(entry==3) {
                int choix = 0;
                showTitle("PISTE");
                userEntryInt("Voir la piste triee par :\n\n1 - heure de decollage\n2 - numero de vol", &choix, 0, 2);

                showTitle("PISTE");
                // --> VOIR LA PISTE
                if(choix != 0) {
                    if(choix == 1) {
                        printf("\nTriee par heure de decollage :\n");
                        afficheTableauVols(listeVols, nbVols, tabIndicesH_Decollage);
                    }
                    else if(choix == 2) {
                        printf("\nTriee par numero de vol :\n");
                        int indicesOrdreNumVol[NB_VOLS_MAX] = {0};
                        for(int i=0; i<nbVols; ++i) {
                            indicesOrdreNumVol[i] = i;
                        }
                        indicesOrdreNumVol[nbVols] = -1;

                        afficheTableauVols(listeVols, nbVols, indicesOrdreNumVol);
                    }

                    int choixRetard = 0;
                    userEntryInt("\n1 - Retarder un vol\n2 - Retour", &choixRetard, 1, 2);

                    // --> AJOUTER RETARD
                    if(choixRetard == 1) {
                        do {
                            showTitle("RETARDER UN VOL");
                            if (nbVols <= 0) {
                                printf("\nLa liste des vols est vide") ;
                            }
                            else {
                                int numVol, tpsRetard, indiceVolRetarde, retardFinal ;
                                struct Heure ancienneHeure ;

                                userEntryInt("\nEntrez le numero du vol que vous souhaitez retarder", &numVol, 0, nbVols);
                                showTitle("RETARDER UN VOL");
                                if (numVol != 0) {
                                    indiceVolRetarde = rechercheIndiceAvecNumVol(nbVols, tabIndicesH_Decollage, listeVols, numVol) ;
                                    ancienneHeure.heure = listeVols[tabIndicesH_Decollage[indiceVolRetarde]].h_decollage.heure ;
                                    ancienneHeure.minute = listeVols[tabIndicesH_Decollage[indiceVolRetarde]].h_decollage.minute ;

                                    userEntryInt("\nEntrez le retard qu'a le vol", &tpsRetard, 1, 60);
                                    showTitle("RETARD FINAL");
                                    retardFinal = ajoutRetard(nbVols, tabIndicesH_Decollage, listeVols, indiceVolRetarde, tpsRetard) ;

                                    if (retardFinal == -1) {
                                        printf("\nLe vol n'a pas pu etre place, il a donc ete annule\n");
                                    }

                                    else if(retardFinal == -2) {
                                        printf("\nLe vol est annule, il ne peut pas etre retarde\n");
                                    }

                                    else {
                                        struct Heure nouvelleHeure ;
                                        nouvelleHeure.heure = ancienneHeure.heure ;
                                        nouvelleHeure.minute = ancienneHeure.minute ;

                                        printf("\nLe vol a ete retarde de %d minutes\n",retardFinal);
                                        ajouterHeure(&nouvelleHeure, retardFinal) ;
                                        char chaineHeure1[10], chaineHeure2[10] ;
                                        afficherHeureDans(ancienneHeure, chaineHeure1) ;
                                        afficherHeureDans(nouvelleHeure, chaineHeure2) ;
                                        printf("%s -> %s\n",chaineHeure1, chaineHeure2) ;
                                    }
                                    waitPress();
                                    returnMenu(&menu);
                                }
                                else {
                                    menu = 2 ;
                                }
                            }
                        }while(menu != 2);

                    }else {
                        continue;
                    }
                }
            }

            /** ##---- VOIR LES ECRANS ----## */
            if(entry == 4) {
                showTitle("VOIR LES ECRANS");
                int ecranAVoir = 0;
                userEntryInt("Voir les ecrans des :\n\n1 - salles d'embarquement\n2 - comptoirs d'enregistrement", &ecranAVoir, 0, 2);

                if(ecranAVoir == 1) {
                    /** ##---- SALLES EMBARQUEMENT ----## */
                    do {
                        getHeureSystemInto(&mtn);
                        int salleEmb = 0;

                        showTitle("VOIR LES ECRANS -> salles d'embarquement (-10/+30mn)");
                        printf("\n(Salles d'embarquement : %d - %d)\n", listeVols[tabIndicesSalleEmbarquement[0]].salleEmbarquement, listeVols[tabIndicesSalleEmbarquement[nbVols-1]].salleEmbarquement);

                        afficherSallesActuelles(nbVols, listeVols, tabIndicesSalleEmbarquement, listeVols[tabIndicesSalleEmbarquement[nbVols-1]].salleEmbarquement, ajd, mtn, temp);

                        waitPress();
                        returnMenu(&menu);
                    }while(menu != 2);
                }

                else if(ecranAVoir == 2) {
                    do {
                        getHeureSystemInto(&mtn);
                        int comptoir = 0;

                        showTitle("VOIR LES ECRANS -> comptoirs d'enregistrement");
                        printf("\n(Comptoirs d'enregistrement : %d - %d)\n", listeVols[tabIndicesComptoirsErg[0]].numComptoir, listeVols[tabIndicesComptoirsErg[nbVols-1]].numComptoir);

                        afficherComtoirsActuels(nbVols, listeVols, tabIndicesComptoirsErg, listeVols[tabIndicesComptoirsErg[nbVols-1]].numComptoir, ajd, mtn, temp);

                        waitPress();
                        returnMenu(&menu);
                    }while(menu != 2);
                }else {
                    continue;
                }
            }

            /** ---- QUIT ---- **/
            else if(entry == 5) {
                quit=1;
            }
        }while(quit==0);



        /** THE END **/
        fclose(fichier);
    }
    exit(EXIT_SUCCESS);
}
