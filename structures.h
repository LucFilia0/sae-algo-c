#pragma once

/** ##-- STRUCTURES --## */

struct Date {
    int jour;
    int mois;
    int annee;
};

struct Heure {
    int heure;
    int minute;
};

struct Passager {
    char nom[30];
    char prenom[30];
    struct Date dateNaissance; /* format JJ/MM/AAAA */
    int numSiege;
    double prixBillet;
};

struct Vol {
    int numVol;
    char compagnie[30];
    char destination[30];
    int numComptoir;
    struct Heure h_debEnregistrement;
    struct Heure h_finEnregistrement;
    int salleEmbarquement;
    struct Heure h_debEmbarquement;
    struct Heure h_finEmbarquement;
    struct Heure h_decollage;
    char etatVol[30];
    struct Passager listePassagers[100];
};

/** ##---- DECLARATIONS FONCTIONS HEURES ----## */

void setHeure(const char *chaine, struct Heure *heure);

void ajouterHeure(struct Heure *heure, int val);

int ecartHeures(struct Heure heure1, struct Heure heure2) ;

int castHeureEnMinute(struct Heure heure);

void afficherHeureDans(struct Heure heure, char *chaine);

/** ##---- DECLARATIONS FONCTIONS IMPORTATION DONNEES ----## */

void importDataBase(FILE *fichier, struct Vol *listeVols, int *nb_vols);

void initVol(struct Vol *vol, char *informations);

void initPassagers(struct Vol *vol, const char *listePassagers);

/** ##---- FONCTIONS TIME.H ----## */

void getHeureSystemInto(struct Heure *heure);

void getDateSystemInto(struct Date *date);
