#pragma once

void afficheVol(struct Vol *vol);

void afficheTableauVols(struct Vol *listeVols, int *tab, int taille);

void afficheTableauPassagers(struct Vol vol, int nbPassagers, int indices[nbPassagers]);
