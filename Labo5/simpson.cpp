/*
 * Approximation et représentation graphique de PI.
 *
 * Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#include <cmath>
#include <iomanip>
#include <omp.h>
#include "Simpson.h"
#include "GeomGlut.h"


//Variables nécessaires pour le dessin des fonctions
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
 * Dessine une fonction entre A et B avec une précision de n.
 *
 * @param b1 Borne inférieure du dessin.
 * @param b2 Borne supérieure du dessin.
 * @param n Distance entre les points.
 * @param f Foncteur sur la fonction à représenter.
 */
void Simpson::dessinerFonction(const double b1, const double b2, const int n, double (*f)(double))
{
    const float PAS = 0.00001;
    float xNew, yNew;
    float xOld = b1;
    float yOld = f(b1);
    float pas = (b2 - b1) / n;

    for(float x = b1; x <= b2; x += PAS)
    {
        xNew = x;
        yNew = f(x);

        graphWin.segmentCouleur(xOld, yOld, xNew, yNew, 0.8f, 0.2f, 0.f); // Fonction en rouge foncé

        xOld = xNew;
        yOld = yNew;
    }

    for(float x = b1; x <= b2; x += pas)
    {
        xNew = x;
        yNew = f(x);

        // Cadran haut droite
        graphWin.segmentCouleur(xOld, 0, xOld, yOld, 1.f, 0.6f, 0.3f);
        graphWin.segmentCouleur(xOld, 0, xOld, yOld, 1.f, 0.6f, 0.3f);

        // Cadran haut gauche
        graphWin.segmentCouleur(-xOld, 0, -xOld, yOld, 0.9f, 0.9f, 0.9f);
        graphWin.segmentCouleur(-xNew, 0, -xNew, yNew, 0.9f, 0.9f, 0.9f);

        // Cadran bas gauche
        graphWin.segmentCouleur(-xOld, 0, -xOld, -yOld, 0.9f, 0.9f, 0.9f);
        graphWin.segmentCouleur(-xNew, 0, -xNew, -yNew, 00.9f, 0.9f, 0.9f);

        // Cadran bas droite
        graphWin.segmentCouleur(xOld, 0, xOld, -yOld, 0.9f, 0.9f, 0.9f);
        graphWin.segmentCouleur(xNew, 0, xNew, -yNew, 0.9f, 0.9f, 0.9f);

        xOld = xNew;
        yOld = yNew;
    }
}

/**
 * Calcule l'intégrale d'une fonction par la méthode de Simpson.
 *
 * @param a Borne inférieure d'intégration.
 * @param b Borne supérieure d'intégration.
 * @param n Nombre de sous-blocs compris dans les bornes d'intégration.
 * @param double f Foncteur de la fonction à intégrer.
 */
double Simpson::integration(const double a, const double b, const int n, double (*f)(double))
{
    const double h = (b - a) / n;
    double s = f(a) + f(b);
    double ni = 0, np = 0; // N impairs / pairs
    int i, j; // Itérateurs

    // Impairs
    #pragma omp parallel for reduction(+:ni) schedule(static,1)
    for(i = 1; i < n; i += 2)
        ni += f(a + i * h);

    // Pairs
    #pragma omp parallel for reduction(+:np) schedule(static,1)
    for(j = 2; j < n - 1; j += 2)
        np += f(a + j * h);

    s += 4 * ni + 2 * np;

    return s * h / 3;
}

Simpson::~Simpson()
{
    //dtor
}
