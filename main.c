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

#define NB_VOLS_MAX 192 //attention aussi dans structures.c & tri.c

int main(int argc, char *argv[])
{
    struct Vol listeVols[NB_VOLS_MAX];

    const char* nomFichier = "data_vols.csv";
    FILE *fichier;
    fichier = fopen(nomFichier, "r") ;

    if(fichier==NULL) {
        perror(nomFichier);
    }
    else
    {
        int nbVols = 0;
        importDataBase(fichier, listeVols, &nbVols);

        // TECHNIQUE DE BRIGAND POUR METTRE EN PLEIN ECRAN
        keybd_event(VK_MENU,0x38,0,0); //Appuie sur ALT
        keybd_event(VK_RETURN,0x1c,0,0); //Appuie ENTREE
        keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0); // Relache ENTREE
        keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0); //Relache ALT

        // VARIABLES
        struct Vol *v;
        int entry, recherche, numVol, heure, quit = 0;
        char compagnie[50], destination[50];
        int tabIndicesH_Decollage[NB_VOLS_MAX], tabIndicesDestination[NB_VOLS_MAX], tabIndicesNomsCompagnie[NB_VOLS_MAX], temp[NB_VOLS_MAX];

        // TRI INDIRECTS
        indexFill(NB_VOLS_MAX, tabIndicesH_Decollage, nbVols) ;
        indexFill(NB_VOLS_MAX, tabIndicesDestination, nbVols) ;
        indexFill(NB_VOLS_MAX, tabIndicesNomsCompagnie, nbVols) ;

        triFusion(nbVols, tabIndicesH_Decollage, temp, listeVols, 1) ;
        triFusion(nbVols, tabIndicesDestination, temp, listeVols, 2) ;
        triFusion(nbVols, tabIndicesNomsCompagnie, temp, listeVols, 3) ;

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
            int menu = 1;

            showTitle();

            userEntryInt("1 - Voir un vol\n2 - Recherche avancee\n3 - Gestion de la piste\n4 - Quitter", &entry, 1, 4);

            /** ---- VOIR UN VOL ----## **/
            if(entry == 1) {
                do {
                    int numVol = 0;
                    int indices[100] = {0};

                    userEntryInt("Entrez le numero du vol", &numVol, 1, nbVols);

                    int vol[1] = {numVol-1};

                    printf("Vol %d :\n", numVol);
                    afficheTableauVols(listeVols, 1, vol);

                    printf("\n\nListe des passagers :\n");
                    trierPassagers(100, listeVols[numVol-1].listePassagers, indices);
                    afficheTableauPassagers(listeVols[numVol-1], 100, indices);

                    waitPress();
                    returnMenu(&menu);
                }while(menu != 2);

            }

            /** ---- RECHERCHE AVANCEE ----- **/
            else if(entry == 2) {
                do {
                    char compagnie[50] = "", destination[50] = "", heureDecollage[7] = "";

                    int tabIndices[NB_VOLS_MAX] = {0};
                    int rechercheValidee = 0, retour = 0; // 1 pour 'validée'

                    do {
                        int rechercheMult = 0;

                        printf("RECHERCHE AVANCEE :"
                               "\n======================================="
                               "\n1 - Compagnie : %s"
                               "\n2 - Destination : %s"
                               "\n3 - Heure de decollage : %s"
                               "\n=======================================\n", compagnie, destination, heureDecollage);

                        userEntryInt("Choisissez les criteres a appliquer\n\n[entree] pour valider/retour", &rechercheMult, 0, 3);

                        if(rechercheMult == 1) {
                            userEntryChar("Compagnie", compagnie, 50, 1);
                        }
                        else if(rechercheMult == 2) {
                            userEntryChar("Destination", destination, 50, 1);
                        }
                        else if(rechercheMult == 3) {
                            userEntryChar("Heure de decollage (HH:MM)", heureDecollage, 50, 1);
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
                        //On garde l'affichage sympa
                        printf("RECHERCHE AVANCEE :"
                               "\n======================================="
                               "\n1 - Compagnie : %s"
                               "\n2 - Destination : %s"
                               "\n3 - Heure de decollage : %s"
                               "\n=======================================\n", compagnie, destination, heureDecollage);

                        rechercheAvancee(compagnie, destination, heureDecollage, nbVols, listeVols, tabIndicesNomsCompagnie, tabIndicesDestination, tabIndicesH_Decollage, tabIndices);
                        if(tabIndices[0] != -1) { //Si au moins un vol est trouvé
                            afficheTableauVols(listeVols, nbVols, tabIndices);
                        }else {
                            printf("\n---- Aucun vol ne correspond a votre recherche ----\n");
                        }


                        waitPress();
                        returnMenu(&menu);
                    }else {
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
                userEntryInt("1 - Voir la piste\n2 - Retarder un vol", &choix, 1, 2);

                // --> VOIR LA PISTE
                if(choix == 1) {
                    printf("\nPISTE :\n");

                    afficheTableauVols(listeVols, nbVols, tabIndicesH_Decollage);
                    waitPress();
                }

                // --> AJOUTER RETARD
                else if(choix == 2) {
                    if (nbVols <= 0) {
                        printf("La liste des vols est vide") ;
                    }
                    else {
                        do {
                            int numVol, tpsRetard, indiceVolRetarde, retardFinal ;
                            struct Heure ancienneHeure ;

                            userEntryInt("Entrez le numero du vol que vous souhaitez retarder", &numVol, 1, nbVols);
                            indiceVolRetarde = rechercheIndiceAvecNumVol(nbVols, tabIndicesH_Decollage, listeVols, numVol) ;
                            ancienneHeure.heure = listeVols[tabIndicesH_Decollage[indiceVolRetarde]].h_decollage.heure ;
                            ancienneHeure.minute = listeVols[tabIndicesH_Decollage[indiceVolRetarde]].h_decollage.minute ;

                            userEntryInt("Entrez le retard qu'a le vol", &tpsRetard, 1, 60);
                            retardFinal = ajoutRetard(nbVols, tabIndicesH_Decollage, listeVols, numVol, tpsRetard) ;

                            if (retardFinal == -1) {
                                printf("Le vol n'a pas pu etre place, il a donc ete annule\n");
                            }

                            else if(retardFinal == -2) {
                                printf("Le vol est annule, il ne peut pas etre retarde\n");
                            }

                            else {
                                struct Heure nouvelleHeure ;
                                nouvelleHeure.heure = ancienneHeure.heure ;
                                nouvelleHeure.minute = ancienneHeure.minute ;

                                printf("Le vol a ete retarde de %d minutes\n",retardFinal);
                                ajouterHeure(&nouvelleHeure, retardFinal) ;
                                printf("%d:%d -> %d:%d\n",ancienneHeure.heure, ancienneHeure.minute, nouvelleHeure.heure, nouvelleHeure.minute) ;
                            }
                            waitPress() ;
                            returnMenu(&menu) ;
                        } while (menu != 2) ;
                    }
                }
            }

            /** ---- QUIT ---- **/
            else {
                quit=1;
            }
        }while(quit==0);



        /** THE END **/
        fclose(fichier);
    }
    return EXIT_SUCCESS;
}
