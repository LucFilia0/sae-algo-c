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
    fichier = fopen(nomFichier, "r");

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
        int entry, recherche, quit = 0;


        // ##==== ARBRE EVENEMENTS ====##
        do {
            int menu = 1;

            showTitle();
            userEntryInt("1 - Voir un vol\n2 - Recherche avancee\n3 - Voir la piste\n4 - Quitter", &entry, 1, 4);

            /** ---- VOIR UN VOL ----## */
            if(entry == 1) {
                do {
                    int numVol = 0;
                    int indices[10] = {0};

                    userEntryInt("Entrez le numero du vol", &numVol, 1, nbVols);

                    int vol[1] = {numVol-1};

                    printf("Vol %d :\n", numVol);
                    afficheTableauVols(listeVols, 1, vol);

                    printf("\n\nListe des passagers :\n");
                    trierPassagers(10, listeVols[numVol-1].listePassagers, indices);
                    afficheTableauPassagers(listeVols[numVol-1], 10, indices);

                    waitPress();
                    returnMenu(&menu);
                }while(menu != 2);

            }

            /** ---- RECHERCHE AVANCEE ----- **/
            else if(entry == 2) {
                do {
                    char compagnie[50] = "", destination[50] = "", heureDecollage[7] = "";

                    int tabIndices[NB_VOLS_MAX] = {0};
                    int rechercheValidee = 0, retour = 0; // 1 pour 'valid�e'

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
                                retour = 1; //r�affiche l'�cran de recherche avanc�e
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

                        rechercheAvancee(compagnie, destination, heureDecollage, nbVols, listeVols, tabIndices);
                        if(tabIndices[0] != -1) { //Si au moins un vol est trouv�
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


            /** ---- VOIR PISTE ---- **/
            /*
                Les passagers sont rang�s selon leur age -> les 12 et - devant, puis les "adultes".
                Les deux tranches d'�ge sont ensuite tri�es, de fa�on ind�pendante, selon le prix de leur billet (ordre d�croissant).
            */
            else if(entry==3) {
                int tousIndices[nbVols];
                int a=23;
                for(int i=0; i<nbVols; ++i) {
                    tousIndices[i] = i;
                }
                printf("\nPISTE :\n");
                afficheTableauVols(listeVols, nbVols, tousIndices);
                waitPress();
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
