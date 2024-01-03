#pragma once

void copieChar(const char* copie, char *colle, int alpha);

void getCharTo(const char *chaine, char stop, char *sortie);

void getCharFromTo(const char *chaine, char start, char stop, char *sortie);

void clearChar(char *chaine);

void setCharClean(char *chaine);

void copyCharToLower(const char *copie, char *colle);

void catchDate(const char *chaine, char *jour, char *mois, char *annee);

void setHeure(const char *chaine, struct Heure *heure);

void ajouterHeure(struct Heure *heure, int val);

void afficherHeureDans(struct Heure heure, char *chaine);

void echangeIndicesTab(int taille, int tab[taille], int ind1, int ind2);

int recherchePrixMaxFrom(int nbPassagers, struct Passager listePassagers[nbPassagers], int indices[nbPassagers], int deb);
//==============================================

void showTitle();

void userEntryInt(const char *message, int *data, int nbMin, int nbMax);

void userEntryChar(const char *message, char *data, int length, int clearChaine);

void waitPress();

void returnMenu(int *menu);
