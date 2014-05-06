 /*
 * Approximation de PI et représentation graphique
 *
 *  Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#include <cmath>
#include <iomanip>

#include "simpson.h"
#include "GeomGlut.h"


//Variables nécessaires pour le dessin des fonctions
extern GeomGlut graphWin;

//Limites du graphe
double X_MIN = -2.1;
double Y_MIN = -2.1;
double X_MAX = 2.1;
double Y_MAX = 2.1;

simpson::simpson()
{
    //ctor
}

//dessine une fonction entre a et b avec une précision n
//
//double b1 --> borne inférieure du dessin
//double b2 --> borne supérieure du dessin
//int n --> la distance entre les points
//double (*f) --> foncteur sur la fonction à représenter
void simpson::drawFunction(double b1, double b2, int n, double (*f)(double))
{
    const float PAS = 0.00001;
    float xNew, yNew;
    float xOld = b1;
    float yOld = f(b1);
    float pas = (b2-b1)/n;

    for(float x=b1; x<=b2; x+=PAS)
    {
        xNew = x;
        yNew = f(x);

        graphWin.segmentCouleur(xOld,yOld,xNew,yNew,0.33f,0.61f,1.0f); //fonction en bleu foncé

        xOld = xNew;
        yOld = yNew;
    }

    for(float x=b1;x<=b2;x+=pas)
    {
        xNew = x;
        yNew = f(x);

        //Cadran haut droite
        graphWin.segmentCouleur(xOld,0,xOld,yOld,0.33f,0.99f,1.0f); //dessin des barres verticales
        graphWin.segmentCouleur(xOld,0,xOld,yOld,0.33f,0.99f,1.0f); //dessin des barres verticales

        //Cadran haut gauche
        graphWin.segmentCouleur(-xOld,0,-xOld,yOld,0.9f,0.9f,0.9f); //dessin des barres verticales
        graphWin.segmentCouleur(-xNew,0,-xNew,yNew,0.9f,0.9f,0.9f); //dessin des barres verticales

        //Cadran bas gauche
        graphWin.segmentCouleur(-xOld,0,-xOld,-yOld,0.9f,0.9f,0.9f); //dessin des barres verticales
        graphWin.segmentCouleur(-xNew,0,-xNew,-yNew,00.9f,0.9f,0.9f); //dessin des barres verticales

        //Cadran bas droite
        graphWin.segmentCouleur(xOld,0,xOld,-yOld,0.9f,0.9f,0.9f); //dessin des barres verticales
        graphWin.segmentCouleur(xNew,0,xNew,-yNew,0.9f,0.9f,0.9f); //dessin des barres verticales

        xOld = xNew;
        yOld = yNew;
    }
}

//permet de calculer l'approximation d'une intégrale définie, méthode de Simpson
//
//double borne1 --> borne inférieure d'intégration
//double borne2 --> borne supérieure d'intégration
//int n --> le nombre de sous-blocs compris dans les bornes d'intégration
//double (*f) --> foncteur de la fonction à intégrer
double simpson::approximation(double borne1, double borne2, int n, double (*f)(double))
{
    double h = (borne2 - borne1)/ n;

    double value = 0.0;

    double fa = f(borne1); //f(a)

    //Pour les i paires
    double iImpaire = 0.0;
    for(int i = 1; i < (n/2)-1; i++)
    {
        iImpaire += f(borne1+2*i*h);
    }
    iImpaire *= 2;

    //Pour les i impaires
    double iPair = 0.0;
    for(int i = 1; i < n/2; i++)
    {
        iPair += f(borne1+(2*i-1)*h);
    }
    iPair *= 4;

    double fb = f(borne2); //f(b)

    value = (h/3) * (fa + iImpaire + iPair + fb);

    return value;
}

simpson::~simpson()
{
    //dtor
}
