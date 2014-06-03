/*
 * Approximation et représentation graphique de PI.
 *
 * Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#ifndef GEOMETRIE_H
#define GEOMETRIE_H

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>                // Librairie GLUT
#endif

#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>
#include <iomanip>
#include <windows.h>

#include "GeomGlut.h"
#include "simpson.h"

using namespace std;

// Limites du graphe
const double X_MIN = -2.1;
const double Y_MIN = -2.1;
const double X_MAX = 2.1;
const double Y_MAX = 2.1;
const long double PI = 3.1415926535897932384626433832795L;

// Fonction main
void intro();
void resultats();
void saisieDecoupage();
template<class T> inline void saisie(T& t, string texte);
void mainFunction(void);

#endif
