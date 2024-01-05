#pragma once

/** ##---- DECLARATIONS FONCTIONS RECHERCHE ----## */

int rechercheIndiceAvecNumVol(int n, int nbVols, int tabIndices[n], struct Vol listeVols[n], int numVol);

int recherchePrixMaxFrom(int nbPassagers, struct Passager listePassagers[nbPassagers], int indices[nbPassagers], int deb);

int rechercheCompagnieMinFrom(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols, int iDeb);

int rechercheDestinationMinFrom(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols, int iDeb);

int rechercheHeureDecollageMinFrom(int nbVols, struct Vol listeVols[nbVols], int indices[nbVols], int deb);

void rechercheCompagnie(const char *nomCompagnie, int nbVols, struct Vol listeVol[nbVols], int indices[nbVols]);

void rechercheDestination(const char *nomDestination, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]);

void rechercheHeureDecollage(const char *heureDecollage, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]);

/** ##---- RECHERCHE AVANCEE ----## */

void rechercheAvancee(const char *compagnie, const char *destination, const char *heureDecollage, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]);
