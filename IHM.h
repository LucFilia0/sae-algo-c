#pragma once

void showTitle();

void userEntryInt(const char *message, int *data, int nbMin, int nbMax);

void userEntryChar(const char *message, char *data, int length, int clearChaine);

void waitPress();

void returnMenu(int *menu);

void afficheVol(struct Vol *vol);

void afficheTableauVols(struct Vol *listeVols, int *tab, int taille);

void afficheTableauPassagers(struct Vol vol, int nbPassagers, int indices[nbPassagers]);
