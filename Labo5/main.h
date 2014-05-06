 /*
 * Approximation de PI et représentation graphique
 *
 *  Auteurs:
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

using namespace std;

//Limites du graphe
const double X_MIN = -2.1;
const double Y_MIN = -2.1;
const double X_MAX = 2.1;
const double Y_MAX = 2.1;

//Fonction main
void mainFunction(void);

#endif
