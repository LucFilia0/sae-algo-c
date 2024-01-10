#pragma once

/** ##---- DECLARATIONS FONCTIONS TRI */

void trierPassagers(int nbPassagers, struct Passager listePassagers[nbPassagers], int indices[nbPassagers],int temp[],  struct Date ajd);

void trierPiste(int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]);


//===============================================

void fusion(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin, int  typeTri) ;

void triFusionH_Decollage(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin) ;

void triFusionDestination(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin) ;

void triFusionCompagnie(int tabIndices[], int temp[], struct Vol listeVols[], int iDeb, int iFin) ;

void triFusion(int nbVols, int tabIndices[], int temp[], struct Vol listeVols[], int typeTri) ;

void fusionPrixBillet(int tabIndices[], int temp[], struct Passager listePassagers[], int iDeb, int iFin) ;

void triFusionPrixBillet(int tabIndices[], int temp[], struct Passager listePassagers[], int iDeb, int iFin) ;
