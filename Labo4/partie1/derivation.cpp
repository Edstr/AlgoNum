 /*
 * Affichage des d�riv�es premi�res et secondes de 2 fonctions
 *
 *  Auteurs:
 *	F�bio Marques
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

// Fonction qui dessine la d�riv�e premi�re d'une fonction.
// La m�thode utilis�e est la d�riv�e centr�e.
//
// float b1, float b2 --> repr�sente les bornes de la fonction
// float delta --> repr�sente le delta, diff�rence avec lequel on choisi les points de la fonction
// float h --> n�cessaire pour la m�thode de la d�riv�e centr�e
// double (*fonction) (double) --> foncteur sur la fonction f1 ou f2
void derivation::dessinerDeriveePremiere(float b1, float b2, float delta, float h, double (*fonction) (double))
{
    float xNew, yNew;
    float xOld = b1+h;

    //Formule pour la d�riv�e centr�e
    float yOld = (fonction(xOld+h) - fonction(xOld-h))/2*h + pow(h,2);

    for(float x=b1;x<=b2-h;x+=delta)
    {
        xNew = x;
        //Formule pour la d�riv�e centr�e
        yNew = (fonction(xOld+h) - fonction(xOld-h))/2*h + pow(h,2);

        graphWin.segmentCouleur(xOld, yOld, xNew, yNew, 1.0f, 0.1f, 0.1f);

        xOld = xNew;
        yOld = yNew;
    }
}

// Fonction qui dessine la d�riv�e seconde d'une fonction.
// La m�thode utilis�e est la d�riv�e centr�e.
//
// float b1, float b2 --> repr�sente les bornes de la fonction
// float delta --> repr�sente le pas avec lequel on choisi les points de la fonction
// float h --> n�cessaire pour la m�thode de la d�riv�e centr�e
// double (*fonction) (double) --> foncteur sur la fonction f1 ou f2
void derivation::dessinerDeriveeSeconde(float b1, float b2, float delta, float h, double (*fonction) (double))
{
    float xNew, yNew;
    float xOld = b1+h;

    //Formule pour la d�riv�e centr�e
    float yOld = (fonction(xOld+h) + fonction(xOld-h) - 2*fonction(xOld))/2*h + pow(h,2);

    for(float x=b1;x<=b2-h;x+=delta)
    {
        xNew = x;
        //Formule pour la d�riv�e centr�e
        yNew = (fonction(xOld+h) + fonction(xOld-h) - 2*fonction(xOld))/2*h + pow(h,2);

        graphWin.segmentCouleur(xOld, yOld, xNew, yNew, 0.1f, 1.0f, 0.1f);

        xOld = xNew;
        yOld = yNew;
    }
}

// Dessine une fonction dans l'intervalle [b1,b2]
//
// float b1, float b2 --> repr�sente les bornes de la fonction
// float delta --> repr�sente le pas avec lequel on choisi les points de la fonction
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


