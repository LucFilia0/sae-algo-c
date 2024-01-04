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

void afficheTab(int taille, int tab[taille]);

void echangeIndicesTab(int taille, int tab[taille], int ind1, int ind2);

int copieTabDansTab(int taille, int copie[taille], int colle[taille]);
