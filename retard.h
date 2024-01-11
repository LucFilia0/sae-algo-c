#pragma once

void decalerDeJusqua(int nbVols, int tabIndices[], int indiceVolRetarde, int nouvelIndice) ;

void retarderVol(int tabIndices[], struct Vol listeVols[],int retardAccumule, int indiceVolRetarde, struct Heure heureActuelle) ;

int etatVol(int nbVols, int tabIndices[], struct Vol listeVols[], int indiceVolRetarde) ;

int ajoutRetard(int nbVols, int tabIndices[], struct Vol listeVols[], int indiceVolRetarde, int tpsRetard) ;

void updatePiste(int nbVols, int tabIndices[], struct Vol listeVols[], int n, int tabNumVol[n]) ;


