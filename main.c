#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "structures.h"
#include "fichier.h"
#include "fonctions.h"
#include "IHM.h"

#define NB_VOLS 192 //attention aussi dans structures.c

int main(int argc, char *argv[])
{
    struct Vol listeVols[NB_VOLS];

    const char* nomFichier = "data_vols.csv";
    FILE *fichier;
    fichier = fopen(nomFichier, "r");

    if(fichier==NULL) {
        perror(nomFichier);
    }
    else
    {
        importDataBase(fichier, listeVols);

        // MET EN PLEIN ECRAN
        keybd_event(VK_MENU,0x38,0,0); //Appuie sur ALT
        keybd_event(VK_RETURN,0x1c,0,0); //Appuie ENTREE
        keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0); // Relache ENTREE
        keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0); //Relache ALT

        // VARIABLES
        struct Vol *v;
        int entry, recherche, numVol, heure, quit = 0;
        char compagnie[20], destination[20];

        // ARBRE EVENEMENTS
        do {
            showTitle();
            userEntryInt("1 - Rechercher un vol\n2 - Voir la piste\n3 - Quitter", &entry, 1, 3);

            // RECHERCHE VOL
            if(entry==1) {
                userEntryInt("Vous souhaitez rechercher par :\n1 - Numero\n2 - Compagnie\n3 - Destination\n4 - Horaire", &recherche, 0, 3);
                printf("\nRecherche : %d\n", recherche);

                // PAR NOM
                if(recherche==1) {
                    userEntryInt("Numero du vol", &numVol, 1, NB_VOLS);
                    /*
                    v = &listeVols[numVol-1];
                    afficheVol(v);
                    */
                    int num[1] = {numVol};
                    afficheTableauVols(listeVols, num, 1);
                    waitPress();
                }
                // PAR COMPAGNIE
                else if(recherche==2) {
                    printf("Nom de la compagnie : ");
                    fgets(compagnie, 20, stdin);
                }
                // PAR DESTINATION
                else if(recherche==3) {
                    printf("Destination : ");
                    fgets(destination, 20, stdin);
                }
                // PAR HORAIRE
                else if(recherche==4) {
                    userEntryInt("Horaire (HH:MM)", &heure, 0, 2359);
                }
                // RETOUR
                else {
                    continue; // retour menu
                }
            }

            // VOIR PISTE
            else if(entry==2) {

            }


            // QUIT
            else {
                quit=1;
            }
        }while(quit==0);

/*
        int indices[10] = {1, 5, 8, 9, 7, 11, 35, 18};
        afficheTableauVols(listeVols, indices, 8);
        printf("\n");
        afficheTableauPassagers(listeVols[1]);
*/
        fclose(fichier);
    }
    return 0;
}
