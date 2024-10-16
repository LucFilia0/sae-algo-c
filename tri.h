#pragma once

/** ##---- DECLARATIONS FONCTIONS TRI */

void fusion(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin, int  typeTri) ;

void triFusionH_Decollage(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin) ;

void triFusionDestination(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin) ;

void triFusionCompagnie(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin) ;

void triFusionSalleEmbarquement(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin) ;

void triFusionNumComptoir(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin) ;

void triFusionNumVol(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin) ;

void triFusion(int nbVols, int tabIndices[], int temp[], struct Vol listeVols[], int typeTri) ;

void fusionPrixBillet(int tabIndices[], int temp[], struct Passager listePassagers[], int iDeb, int iFin) ;

void triFusionPrixBillet(int tabIndices[], int temp[], struct Passager listePassagers[], int iDeb, int iFin) ;

void trierPassagers(int nbPassagers, struct Passager listePassagers[nbPassagers], int indices[nbPassagers],int temp[],  struct Date ajd);
