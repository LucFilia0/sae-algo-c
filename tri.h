#pragma once

/** ##---- DECLARATIONS FONCTIONS TRI */

void trierPassagers(int nbPassagers, struct Passager listePassagers[nbPassagers], int indices[nbPassagers]);

void trierPiste(int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]);

void trierCompagnie(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols) ;

void trierDestination(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols) ;

void trierHeureDecollage(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols) ;
