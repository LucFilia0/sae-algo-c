#pragma once

void indexFill(int n, int tabIndices[n], int nbVols) ;

void printTab(int n, int tab[n]) ;

void echange(int a, int b, int *tab) ;

void lowerCase(char *strIn, char *strOut) ;

int minCompagnieFrom(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols, int iDeb) ;

void triCompagnie(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols) ;

int minDestinationFrom(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols, int iDeb) ;

void triDestination(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols) ;

int minH_DecollageFrom(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols, int iDeb) ;

void triH_Decollage(int n, int tabIndices[n], struct Vol listeVols[n],int nbVols) ;

void rechercheCompagnie(const char *nomCompagnie, int nbVols, struct Vol listeVol[nbVols], int indices[nbVols]);

void rechercheDestination(const char *nomDestination, int nbVols, struct Vol listeVols[nbVols], int indices[nbVols]);

int rechercheIndiceAvecNumVol(int n, int nbVols, int tabIndices[n], struct Vol listeVols[n], int numVol) ;
