#pragma once

void afficheTab(int taille, int tab[taille]);

void tableauVols(int taille, int indices[taille], struct Vol listeVols[taille]);

void rechercheCompagnie(const char *nomCompagnie, int nbVols, struct Vol listeVol[nbVols], int indices[nbVols]);

void rechercheDestination(const char *nomDestination, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]);

void rechercheHeureDecollage(const char *horaire, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]);
