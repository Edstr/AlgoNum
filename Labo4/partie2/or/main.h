/*
 * Dérivations numériques
 * Partie 2
 *
 * Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

// Fichier Geometrie.h

#ifndef GEOMETRIE_H
#define GEOMETRIE_H

#include "CSV.h"
#include "GeomGlut.h"

#include <iostream>
#include <string>
#include <math.h>

extern GeomGlut graphWin;

void mainFunction(void);

void intro();
void calculs();
void graphique();

const float calculerIPC(const float valeur, const float ipc);
void calculerMeilleureAnnee(CSV &coursOr, CSV &inflation);
void calculerMeilleurePeriode(CSV &coursOr, CSV &inflation);

void dessinerGrille();
void dessinerGraph(CSV &csv, const float echelle, const float r, const float g, const float b);

#endif

