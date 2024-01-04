#pragma once

/** ##---- DECLARATIONS FONCTIONS RECHERCHE ----## */

void rechercheCompagnie(const char *nomCompagnie, int nbVols, struct Vol listeVol[nbVols], int indices[nbVols]);

void rechercheDestination(const char *nomDestination, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]);

void rechercheHeureDecollage(const char *heureDecollage, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]);

void rechercheAvancee(const char *compagnie, const char *destination, const char *heureDecollage, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]);
