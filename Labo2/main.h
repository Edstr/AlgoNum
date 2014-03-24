/*
 * Recherche des y = 0 à l'aide de la méthode de la bissection.
 *
 * Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#ifndef GEOMETRIE_H
#define GEOMETRIE_H

#include <iostream>
#include <limits>
#include <cmath>
#include <time.h>

double f1(double x);
double f2(double x);

void mainFunction(void);

double bissection(float a, float b, float pas, double (*f)(double));
void dessinerFonction(float borneInf, float borneSup, float pas, double (*f)(double));
void dessinerIntervales(float borneInf, float borneSup, float &h);
void dessinerUnites();
bool estDansLimites(const float &valeur, const float &borneMin, const float &borneMax);
void resultats();
template<class T> void saisie(T &t, std::string texte);
void setBorne(float &valeur, const float &limiteMin, const float &limiteMax, std::string texte);

#endif
