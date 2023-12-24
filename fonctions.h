#pragma once

void copieChar(const char* copie, char *colle);

void getCharTo(const char *chaine, char stop, char *sortie);

void getCharFromTo(const char *chaine, char start, char stop, char *sortie);

void clearChar(char *chaine);

void adjustChar(const char *chaine, char *sortie);

void userEntryInt(const char *message, int *data, int nbMin, int nbMax);
