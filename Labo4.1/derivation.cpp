 /*
 * Affichage des dérivées premières et secondes de 2 fonctions
 *
 *  Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#include <cmath>
#include <iostream>

#include "derivation.h"
#include "main.h"
#include "GeomGlut.h"

extern GeomGlut graphWin;

derivation::derivation()
{

}

// Fonction qui dessine la dérivée première d'une fonction.
// La méthode utilisée est la dérivée centrée.
//
// float b1, float b2 --> représente les bornes de la fonction
// float delta --> représente le delta, différence avec lequel on choisi les points de la fonction
// float h --> nécessaire pour la méthode de la dérivée centrée
// double (*fonction) (double) --> foncteur sur la fonction f1 ou f2
void derivation::dessinerDeriveePremiere(float b1, float b2, float delta, float h, double (*fonction) (double))
{
    float xNew, yNew;
    float xOld = b1+h;

    //Formule pour la dérivée centrée
    float yOld = (fonction(xOld+h) - fonction(xOld-h))/2*h + pow(h,2);

    for(float x=b1;x<=b2-h;x+=delta)
    {
        xNew = x;
        //Formule pour la dérivée centrée
        yNew = (fonction(xOld+h) - fonction(xOld-h))/2*h + pow(h,2);

        graphWin.segmentCouleur(xOld, yOld, xNew, yNew, 1.0f, 0.1f, 0.1f);

        xOld = xNew;
        yOld = yNew;
    }
}

// Fonction qui dessine la dérivée seconde d'une fonction.
// La méthode utilisée est la dérivée centrée.
//
// float b1, float b2 --> représente les bornes de la fonction
// float delta --> représente le pas avec lequel on choisi les points de la fonction
// float h --> nécessaire pour la méthode de la dérivée centrée
// double (*fonction) (double) --> foncteur sur la fonction f1 ou f2
void derivation::dessinerDeriveeSeconde(float b1, float b2, float delta, float h, double (*fonction) (double))
{
    float xNew, yNew;
    float xOld = b1+h;

    //Formule pour la dérivée centrée
    float yOld = (fonction(xOld+h) + fonction(xOld-h) - 2*fonction(xOld))/2*h + pow(h,2);

    for(float x=b1;x<=b2-h;x+=delta)
    {
        xNew = x;
        //Formule pour la dérivée centrée
        yNew = (fonction(xOld+h) + fonction(xOld-h) - 2*fonction(xOld))/2*h + pow(h,2);

        graphWin.segmentCouleur(xOld, yOld, xNew, yNew, 0.1f, 1.0f, 0.1f);

        xOld = xNew;
        yOld = yNew;
    }
}

// Dessine une fonction dans l'intervalle [b1,b2]
//
// float b1, float b2 --> représente les bornes de la fonction
// float delta --> représente le pas avec lequel on choisi les points de la fonction
// double (*fonction) (double) --> foncteur sur la fonction f1 ou f2
void derivation::dessinerFonction(float b1, float b2, float delta, double (*fonction) (double))
{
    float xNew, yNew;
    float xOld = b1;
    float yOld = fonction(b1);

    for(float x=b1;x<=b2;x+=delta)
    {
        xNew = x;
        yNew = fonction(x);

        graphWin.segment(xOld, yOld, xNew, yNew);

        xOld = xNew;
        yOld = yNew;
    }
}

derivation::~derivation()
{
    //dtor
}


