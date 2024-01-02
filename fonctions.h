#pragma once

void copieChar(const char* copie, char *colle);

void getCharTo(const char *chaine, char stop, char *sortie);

void getCharFromTo(const char *chaine, char start, char stop, char *sortie);

void clearChar(char *chaine);

void setCharClean(char *chaine);

void copyCharToLower(const char *copie, char *colle);

void catchDate(const char *chaine, char *jour, char *mois, char *annee);

void setHeure(const char *chaine, struct Heure *heure);

//==============================================

void showTitle();

void userEntryInt(const char *message, int *data, int nbMin, int nbMax);

void waitPress();
