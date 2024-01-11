#pragma once

/** ##---- RECHERCHE DICHOTOMIE ----## */

void rechercheCompagnieD(const char *compagnie, int nbVols, struct Vol listeVols[], int indicesTri[], int indices[nbVols]);

/** ##---- DECLARATIONS FONCTIONS RECHERCHE ----## */

int rechercheIndiceAvecNumVol(int nbVols, int tabIndices[], struct Vol listeVols[], int numVol) ;

void rechercheCompagnie(const char *nomCompagnie, int nbVols, struct Vol listeVol[], int indices[]);

void rechercheDestination(const char *nomDestination, int nbVols, struct Vol listeVols[], int indices[]);

void rechercheHeureDecollage(const char *heureDecollage, int nbVols, struct Vol listeVols[], int indices[]);

/** ##---- RECHERCHE AVANCEE ----## */

void rechercheAvancee(const char *compagnie, const char *destination, const char *heureDecollage, int nbVols, struct Vol listeVols[], int temp[], int indicesTriCompagnie[], int indicesTriDestination[], int indicesTriH_Decollage[], int indices[]);
/** ##---- AFFICHAGE ACCUEIL DES VOLS ----## **/

void rechercheVolsAccueil(int nbVols, struct Vol listeVols[nbVols], int indicesTri[nbVols], int indices[nbVols], struct Heure heureActuelle);

/** ##---- RECHERCHE VOL A VENIR DANS SALLE EMBARQUEMENT ----## */

void rechercheVolActuelDansSalleEmb(int nbVols, struct Vol listeVols[nbVols], int indicesTri[nbVols], int indices[nbVols], int salleEmb, struct Heure mtn);

/** ##---- RECHERCHE VOLS AU NUM DE COMPTOIR ----## */

void rechercheVolAuNumComptoir(int nbVols, struct Vol listeVols[nbVols], int indicesTri[nbVols], int indices[nbVols], int comptoir, struct Heure mtn);
