#pragma once

/** ##---- DECLARATIONS FONCTIONS CHAINES DE CARACTERES ----## */

void copieChar(const char* copie, char *colle, int alpha);

void getCharTo(const char *chaine, char stop, char *sortie);

void getCharFromTo(const char *chaine, char start, char stop, char *sortie);

void clearChar(char *chaine);

void setCharClean(char *chaine);

void copyCharToLower(const char *copie, char *colle);

/** ##---- DECLARATIONS FONCTIONS TABLEAUX ----## */

void echangeIndicesTab(int taille, int tab[taille], int ind1, int ind2);

int recherchePrixMaxFrom(int nbPassagers, struct Passager listePassagers[nbPassagers], int indices[nbPassagers], int deb);

int copieTabDansTab(int taille, int copie[taille], int colle[taille]);
