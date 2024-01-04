#pragma once

/** ##---- DECLARATIONS FONCTIONS AFFICHAGE ----## */

void showTitle();

void userEntryInt(const char *message, int *data, int nbMin, int nbMax);

void userEntryChar(const char *message, char *data, int length, int clearChaine);

void waitPress();

void returnMenu(int *menu);

void afficheVol(struct Vol *vol);

void afficheTableauVols(struct Vol *listeVols, int nbVols, int indices[nbVols]);

void afficheTableauPassagers(struct Vol vol, int nbPassagers, int indices[nbPassagers]);
