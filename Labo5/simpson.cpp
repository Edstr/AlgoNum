/*
 * Approximation et repr�sentation graphique de PI.
 *
 * Auteurs:
 *	F�bio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#include <cmath>
#include <iomanip>
#include <omp.h>
#include "simpson.h"
#include "GeomGlut.h"


//Variables n�cessaires pour le dessin des fonctions
extern GeomGlut graphWin;

//Limites du graphe
double X_MIN = -2.1;
double Y_MIN = -2.1;
double X_MAX = 2.1;
double Y_MAX = 2.1;

Simpson::Simpson()
{
    //ctor
}

/**
 * Dessine une fonction entre A et B avec une pr�cision de n.
 *
 * @param b1 Borne inf�rieure du dessin.
 * @param b2 Borne sup�rieure du dessin.
 * @param n Distance entre les points.
 * @param f Foncteur sur la fonction � repr�senter.
 */
void Simpson::dessinerFonction(const double b1, const double b2, const int n, long double (*f)(long double))
{
    const float PAS = 0.00001;
    float xNew, yNew;
    float xOld = b1;
    float yOld = f(b1);
    float pas = (b2 - b1) / n;

	graphWin.setColorForPlotWithoutColor(0.8f, 0.2f, 0.f);

    for(float x = b1; x <= b2; x += PAS)
    {
        xNew = x;
        yNew = f(x);

        graphWin.segment(xOld, yOld, xNew, yNew); // Fonction en rouge fonc�

        xOld = xNew;
        yOld = yNew;
    }

    for(float x = b1; x <= b2; x += pas)
    {
        xNew = x;
        yNew = f(x);

        // Cadran haut droite
        graphWin.setColorForPlotWithoutColor(1.f, 0.6f, 0.3f);
        graphWin.segment(xOld, 0, xOld, yOld);
        graphWin.segment(xOld, 0, xOld, yOld);

        // Cadran haut gauche
        graphWin.setColorForPlotWithoutColor(0.9f, 0.9f, 0.9f);
        graphWin.segment(-xOld, 0, -xOld, yOld);
        graphWin.segment(-xNew, 0, -xNew, yNew);

        // Cadran bas gauche
        graphWin.segment(-xOld, 0, -xOld, -yOld);
        graphWin.segment(-xNew, 0, -xNew, -yNew);

        // Cadran bas droite
        graphWin.segment(xOld, 0, xOld, -yOld);
        graphWin.segment(xNew, 0, xNew, -yNew);

        xOld = xNew;
        yOld = yNew;
    }
}

/**
 * Calcule l'int�grale d'une fonction par la m�thode de Simpson.
 *
 * @param a Borne inf�rieure d'int�gration.
 * @param b Borne sup�rieure d'int�gration.
 * @param n Nombre de sous-blocs compris dans les bornes d'int�gration.
 * @param double f Foncteur de la fonction � int�grer.
 */
long double Simpson::integration(const double a, const double b, const unsigned int n, long double (*f)(long double))
{
    const long double h = (b - a) / n;
    long double s = f(a) + f(b);
    long double ni = 0, np = 0; // N impairs / pairs
    unsigned int i, j; // It�rateurs

    // Impairs
    for(i = 1; i < n; i += 2)
        ni += f(a + i * h);

    // Pairs
    for(j = 2; j < n - 1; j += 2)
        np += f(a + j * h);

    s += 4 * ni + 2 * np;

    return s * h / 3;
}

Simpson::~Simpson()
{
    //dtor
}
