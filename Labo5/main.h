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
#include "Simpson.h"

using namespace std;

// Limites du graphe
const double X_MIN = -2.1;
const double Y_MIN = -2.1;
const double X_MAX = 2.1;
const double Y_MAX = 2.1;
const double PI = 3.14159265358979323846;
const int FONT = (int)GLUT_BITMAP_8_BY_13;

// Fonction main
void mainFunction(void);

#endif
