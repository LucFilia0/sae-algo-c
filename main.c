#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "structures.h"
#include "fichier.h"
#include "fonctions.h"
#include "IHM.h"
#include "tri.h"

#define NB_VOLS_MAX 192 //attention aussi dans structures.c

int main(int argc, char *argv[])
{
    struct Vol listeVols[NB_VOLS_MAX];

    const char* nomFichier = "data_vols.csv";
    FILE *fichier;
    fichier = fopen(nomFichier, "r");

    if(fichier==NULL) {
        perror(nomFichier);
    }
    else
    {
        int nbVols = 0;
        importDataBase(fichier, listeVols, &nbVols);

        // MET EN PLEIN ECRAN
        keybd_event(VK_MENU,0x38,0,0); //Appuie sur ALT
        keybd_event(VK_RETURN,0x1c,0,0); //Appuie ENTREE
        keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0); // Relache ENTREE
        keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0); //Relache ALT

        // VARIABLES
        struct Vol *v;
        int entry, recherche, numVol, quit = 0;
        char compagnie[50], destination[50], heure[7];


        // ARBRE EVENEMENTS
        do {
            int menu = 1;

            showTitle();
            userEntryInt("1 - Rechercher un vol\n2 - Voir la piste\n3 - Liste de passagers\n4 - Quitter", &entry, 1, 4);

            // RECHERCHE VOL
            if(entry==1) {
                int tabIndices[NB_VOLS_MAX];

                userEntryInt("Vous souhaitez rechercher par :\n[entree] pour retour\n\n1 - Numero\n2 - Compagnie\n3 - Destination\n4 - Horaire", &recherche, 0, 4);

                // PAR NOM
                if(recherche==1) {
                    do {
                        userEntryInt("Numero du vol", &numVol, 1, NB_VOLS_MAX);
                        int num[1] = {numVol-1};
                        afficheTableauVols(listeVols, num, 1);

                        waitPress();
                        returnMenu(&menu);
                    }while(menu != 2);

                }
                // PAR COMPAGNIE
                else if(recherche==2) {
                    do {
                        printf("Nom de la compagnie : ");
                        fgets(compagnie, 50, stdin);

                        setCharClean(compagnie); //enleve le '\n' provoqué par le [entrée]
                        rechercheCompagnie(compagnie, nbVols, listeVols, tabIndices);

                        if(tabIndices[0] != -1) {
                            afficheTableauVols(listeVols, tabIndices, NB_VOLS_MAX); //fonction prévue pour s'arreter si '-1' rencontré
                        }else {
                            printf("\n---- Cette compagnie n'existe pas ou syntaxe inconnue ----\n");
                        }

                        waitPress();
                        clearChar(compagnie);

                        returnMenu(&menu);
                    }while(menu!=2);
                }
                // PAR DESTINATION
                else if(recherche==3) {
                    do {
                        printf("Destination : ");
                        fgets(destination, 50, stdin);

                        setCharClean(destination);
                        rechercheDestination(destination, nbVols, listeVols, tabIndices);

                        if(tabIndices[0] != -1) { //si au moins un vol est trouvé
                            afficheTableauVols(listeVols, tabIndices, NB_VOLS_MAX);
                        }else {
                            printf("\n---- Cette destination n'existe pas ou syntaxe inconnue ----\n");
                        }

                        waitPress();
                        clearChar(destination);

                        returnMenu(&menu);
                    }while(menu != 2);
                }
                // PAR HORAIRE
                else if(recherche==4) {
                    do {
                        printf("Entrez l'heure de decollage (HH:MM)\n => ");
                        fgets(heure, 7, stdin);

                        setCharClean(heure);

                        // enlever le ':'
                        char heureClean[5];
                        int ind = 0;
                        for(int i=0; i<strlen(heure); ++i) {
                            if(heure[i] != ':' || i != 2) {
                                heureClean[ind] = heure[i];
                                ++ind;
                            }
                        }

                        rechercheHeureDecollage(heureClean, nbVols, listeVols, tabIndices);

                        if(tabIndices[0] != -1) { //si au moins un vol est trouvé
                            afficheTableauVols(listeVols, tabIndices, NB_VOLS_MAX);
                        }else {
                            printf("\n---- Aucun vol ne decolle a cette heure-ci ou syntaxe inconnue ----\n");
                        }

                        waitPress();
                        clearChar(heure);

                        returnMenu(&menu);
                    }while(menu != 2);

                }
                // RETOUR
                else {
                    continue; // retour menu
                }
            }

            // VOIR PISTE
            else if(entry==2) {
                int tousIndices[nbVols];
                int a=23;
                for(int i=0; i<nbVols; ++i) {
                    tousIndices[i] = i;
                }
                printf("\nPISTE :\n");
                afficheTableauVols(listeVols, tousIndices, nbVols);
                waitPress();
            }

            // LISTE PASSAGERS
            else if(entry == 3) {
                do {
                    int numVol = 0;
                    userEntryInt("Entrez le numero du vol", &numVol, 1, nbVols);

                    printf("\nListe des passagers du vol %d :\n", numVol);
                    afficheTableauPassagers(listeVols[numVol]);

                    waitPress();
                    userEntryInt("1 - Nouvelle Recherche\n2 - Menu", &menu, 1, 2);
                }while(menu != 2);

            }


            // QUIT
            else {
                quit=1;
            }
        }while(quit==0);




        // END
        fclose(fichier);
    }
    return 0;
}
