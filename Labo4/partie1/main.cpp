 /*
 * Affichage des dérivées premières et secondes de 2 fonctions
 *
 *  Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#include <GL/glut.h>
#include <stdlib.h>

#include "main.h"
#include "GeomGlut.h"
#include "derivation.h"

extern GeomGlut graphWin;

char res1;
char res2;

double f1(double x)
{
    return pow(x,5) + 5*pow(x,3) + 2*x;
}

double f2(double x)
{
    return x / (1 - pow(x,2));
}

void mainFunction(void)
{
    derivation *d = new derivation();

    switch(res1)
    {
        case '1':

            cout << "F1 en noire" << endl;
            d->dessinerFonction(X_MIN, X_MAX, 0.1, &f1);

            if(res2 == '1')
            {
                cout << "Derivee premiere en rouge" << endl;
                d->dessinerDeriveePremiere(X_MIN, X_MAX, 0.1, 0.1, &f1);
            }
            else if(res2 == '2')
            {
                cout << "Derivee seconde en verte" << endl;
                d->dessinerDeriveeSeconde(X_MIN, X_MAX, 0.1, 0.1, &f1);
            }
            else
            {
               cout << "Pas de derivee choisie" << endl;
            }

        break;

        case '2':

            cout << "F2 en noire" << endl;
            d->dessinerFonction(X_MIN, X_MAX, 0.1, &f2);

            if(res2 == '1')
            {
                cout << "Derivee premiere en rouge" << endl;
                d->dessinerDeriveePremiere(X_MIN, X_MAX, 0.01, 0.1, &f2);
            }
            else if(res2 == '2')
            {
                cout << "Derivee seconde en verte" << endl;
                d->dessinerDeriveeSeconde(X_MIN, X_MAX, 0.01, 0.1, &f2);
            }
            else
            {
               cout << "Pas de derivee choisie" << endl;
            }

        break;

        default:
            cout << "Mauvais choix, ressayez." << endl;
        break;
    }
}

int main(int argc, char *argv[])
{
    cout << "Choisir une fonction a afficher : " << endl;
    cout << "1) x^5 + 5*x^3 + 2*x" << endl;
    cout << "2) x/(1-x^2)" << endl;
    cout << "x) Quitter" << endl << endl;
    cout << "Choix : ";
    cin >> res1;

    cout << "Choix de la derivee:" << endl;
    cout << "1) derivee premiere" << endl;
    cout << "2) derivee seconde" << endl;
    cout << "Choix : ";
    cin >> res2;

    graphWin.initGraphicsWin(1000, X_MIN, X_MAX, Y_MIN, Y_MAX);

    return 0;
}
