#pragma once

/** ##---- DECLARATIONS FONCTIONS CHAINES DE CARACTERES ----## */

void copieChar(const char* copie, char *colle, int alpha);

void getCharTo(const char *chaine, char stop, char *sortie);

void getCharFromTo(const char *chaine, char start, char stop, char *sortie);

void clearChar(char *chaine);

void setCharClean(char *chaine);

void copyCharToLower(const char *copie, char *colle);

int compareOrdreAlpha(const char *chaine1, const char *chaine2);

/** ##---- DECLARATIONS FONCTIONS TABLEAUX ----## */

void indexFill(int n, int tabIndices[n], int nbVols);

void afficheTab(int taille, int tab[taille]);

void echangeIndicesTab(int taille, int tab[taille], int ind1, int ind2);

void copieTabDansTab(int taille, int copie[taille], int colle[taille]);

void concatenerTableaux(int taille1, int tab1[taille1], int taille2, int tab2[taille2], int taille3, int tab3[taille3]);

/** ##---- RETARD LIEGEON ----## */

int ecartHeures(struct Heure heure1, struct Heure heure2) ;

int ajoutRetard(int n, int nbVols, int tabIndices[n], struct Vol listeVols[n], int indiceVolRetarde, int tpsRetard) ;

void retarderVol(int n, int tabIndices[n], struct Vol listeVols[n],int retardAccumule, int indiceVolRetarde, struct Heure heureActuelle) ;
