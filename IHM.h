#pragma once

/** ##---- DECLARATIONS FONCTIONS AFFICHAGE ----## */

void userEntryInt(const char *message, int *data, int nbMin, int nbMax);

void userEntryChar(const char *message, char *data, int length, int clearChaine);

void waitPress();

void returnMenu(int *menu);

void showTitle(const char *title);

void showTime(struct Date ajd, struct Heure mtn);

void afficheTableauVols(struct Vol *listeVols, int nbVols, int indices[nbVols]);

void afficheTableauPassagers(struct Vol vol, int nbPassagers, int indices[nbPassagers]);

void afficherSallesActuelles(int nbVols, struct Vol listeVols[nbVols], int tabIndicesSallesEmbarquement[nbVols], int nbSalles, struct Date ajd, struct Heure mtn, int temp[nbVols]);

void afficherComtoirsActuels(int nbVols, struct Vol listeVols[nbVols], int tabIndicesComptoirsErg[nbVols], int nbComptoirs, struct Date ajd, struct Heure mtn, int temp[nbVols]);
