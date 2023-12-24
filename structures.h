#pragma once

/* ##-- STRUCTURES --## */

struct Passager {
    char nom[30];
    char prenom[30];
    char dateNaissance[10]; /* format JJ/MM/AAAA */
    int numSiege;
    double prixBillet;
};

struct Vol {
    int numVol;
    char compagnie[30];
    char destination[30];
    int numComptoir;
    int h_debEnregistrement;
    int h_finEnregistrement;
    int salleEmbarquement;
    int h_debEmbarquement;
    int h_finEmbarquement;
    int h_decollage;
    char etatVol[30];
    struct Passager listePassagers[10];
};


/* ##-- DECLARATIONS FONCTIONS --## */

void importDataBase(FILE *fichier, struct Vol *listeVols);

void afficheVol(struct Vol *V);

void initVol(struct Vol *vol, char *informations);

void initPassagers(struct Vol *vol, const char *listePassagers);

void clearPassagers(struct Vol *vol);
