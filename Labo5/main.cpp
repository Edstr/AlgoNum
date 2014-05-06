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

#include "main.h"
#include "GeomGlut.h"
#include "simpson.h"

using namespace std;

//Variables nécessaire pour le dessin des fonctions
extern GeomGlut graphWin;

int n = 0; //Précision du calcul (nombre de découpage)

//double x --> la valeur que l'on veut passer à la fonction
double f(double x)
{
    return 1 / (1 + pow(x,2));
}

//Permet de dessiner une fonction sur le graphe principal
void mainFunction(void)
{
    simpson *s = new simpson();
    s->drawFunction(0,1,n,&f);

    double pi = 4 * s->approximation(0,1,n,&f);

    cout << endl << "Valeur approximee de Pi (surface bleue + surface grise): " << setprecision(10) << pi << endl;
    cout << "Valeur reelle de Pi: " << M_PI << endl;

    cout << "Erreur comparee a Pi: " << abs(M_PI - pi) << endl;

    cout << endl << "-------------------------" << endl << setprecision(2);

}

int main()
{
    do
    {
        cout << "Entrer un nombre de decoupage (n), pair : ";
        cin >>  n;
    }
    while(n<=0 || n%2!=0);

    graphWin.initGraphicsWin(700, X_MIN, X_MAX, Y_MIN, Y_MAX );

    return 0;
}
