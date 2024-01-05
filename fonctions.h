#pragma once

void copieChar(const char* copie, char *colle);

void getCharTo(const char *chaine, char stop, char *sortie);

void getCharFromTo(const char *chaine, char start, char stop, char *sortie);

void clearChar(char *chaine);

void setCharClean(char *chaine);

void copyCharToLower(const char *copie, char *colle);

void catchDate(const char *chaine, char *jour, char *mois, char *annee);

void setHeure(const char *chaine, struct Heure *heure);

void ajouterHeure(struct Heure *heure, int val);

void afficherHeureDans(struct Heure heure, char *chaine);

int ecartHeures(struct Heure heure1, struct Heure heure2) ;

int ajoutRetard(int n, int nbVols, int tabIndices[n], struct Vol listeVols[n], int indiceVolRetarde, int tpsRetard) ;

void retarderVol(int n, int tabIndices[n], struct Vol listeVols[n],int retardAccumule, int indiceVolRetarde, struct Heure heureActuelle) ;

//==============================================

void showTitle();

void userEntryInt(const char *message, int *data, int nbMin, int nbMax);

void waitPress();
