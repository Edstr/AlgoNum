/*
 * Algorithmes numériques
 * Laboratoire 2
 *
 * Simon Guillaume-Gentil, Eddy Strambini, Cyriaque Skrapits
 * INF2dlm-a
 */

#include "main.h"
#include "GeomGlut.h"

extern GeomGlut graphWin;

//==============================================================================
// Cette partie devrait figurer dans le fichier main.h mais comme GeomGlut.h
// rappelle main.h après, ces fonctions vont être définies deux fois ce qui
// produit un bug.
//==============================================================================
int choix;
float borneInferieure;
float borneSuperieure;
float epsilon;
double racine;
const float EPSILON_MINIMUM = 0.0001;
const float LIMITE_X = 20; // 15.1
const float LIMITE_Y = 10; // 10.1
const int FACTEUR_DETECTION_ASYMPTOTE = 100;
const string ERREUR = "Erreur : Aucune racine n'a ete trouvee dans cet interval !";
//==============================================================================

double f1(double x)
{
    return (sin(x) -
			 (x / 3));
}

double f2(double x)
{
    return x / (1-pow(x,2));
}

void dessinerFonction(float borneInf, float borneSup, float pas, double (*f) (double) )
{
    for(float x = borneInf; x <= borneSup; x += pas)
		graphWin.segment(x, f(x), x + pas, f(x + pas));
}

void dessinerIntervales(float borneInf, float borneSup, float &h)
{
	float r = 1.0f;
	float g = 0.2f;
	float b = 0.0f;

    graphWin.segmentCouleur(borneInf, h / 2, borneInf, -h / 2, r, g, b);
    graphWin.segmentCouleur(borneInf, h / 2, borneInf + 0.2, h / 2, r, g, b);
    graphWin.segmentCouleur(borneInf, -h / 2, borneInf + 0.2, -h / 2, r, g, b);

    graphWin.segmentCouleur(borneSup, h / 2, borneSup, -h / 2, r, g, b);
    graphWin.segmentCouleur(borneSup - 0.2, h / 2, borneSup, h / 2, r, g, b);
    graphWin.segmentCouleur(borneSup - 0.2, -h / 2, borneSup, -h / 2, r, g, b);

    h /= 1.5;
}

void dessinerUnites()
{
	float taille = 0.2; // Taille des barres.

    for(int x = -LIMITE_X; x <= LIMITE_X; x++)
		graphWin.segmentCouleur(x, taille, x, -taille, 0.0f, 0.0f, 1.0f);
	for(int y = -LIMITE_Y; y <= LIMITE_Y; y++)
		graphWin.segmentCouleur(-taille, y, taille, y, 0.0f, 0.0f, 1.0f);
}

double bissection(float borneInf, float borneSup, float pas, double (*f)(double))
{
    double milieu;
    float hauteurSegment = 3.0;

	// On cherche jusqu'à que la différence entre les bornes soit plus petite
	// que l'epsilon.
    while(abs(borneSup - borneInf) > epsilon)
    {
        dessinerIntervales(borneInf, borneSup, hauteurSegment);

        milieu = (borneInf + borneSup) / 2;

        if(f(borneInf) * f(milieu) > 0)
            borneInf = milieu;
        else
            borneSup = milieu;
    }

	// Affichage du point de la bissectrice.
    if(f(borneInf)*f(borneSup) < 0 && abs(f(borneSup)-f(borneInf)) < epsilon)
    {
        graphWin.plot(milieu, 0, 5);
        return milieu;
    }
    return milieu;
}

void mainFunction(void)
{
	dessinerUnites(); // Affiche les unités.

    switch(choix)
    {
        case 1:
			dessinerFonction(-LIMITE_X, LIMITE_X, 0.1, &f1);
			racine = bissection(borneInferieure, borneSuperieure, epsilon, &f1);
			break;
        case 2:
            dessinerFonction(-LIMITE_X, LIMITE_X, 0.1, &f2);
            racine = bissection(borneInferieure, borneSuperieure, epsilon, &f2);
			break;
        break;
    }

    // Résultats.
	resultats();
}

bool estDansLimites(const float &valeur, const float &borneMin, const float &borneMax)
{
    return (valeur >= -borneMin) && (valeur <= borneMax);
}

template<class T>
void saisie(T &t, string texte)
{
    cout << texte;

    while (!(cin >> t))
    {
        cerr << "Erreur de saisie." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << texte;
    }
}

void setBorne(float &borne, const float &limiteMin, const float &limiteMax, string texte)
{
    bool ok;
    do
    {
        saisie(borne, texte);
        ok = estDansLimites(borne, -limiteMin, limiteMax);
        if (!ok)
            cerr << "Erreur : la borne doit etre comprise entre " << limiteMin << " et " << limiteMax << endl;
    }
    while(!ok);
}

void resultats()
{
	switch(choix)
    {
        case 1:
            try
            {
            	cout << "Racine approchee pour f1: " << racine << endl;
            }
            catch(...)
            {
            	cout << ERREUR << endl;
            }
			break;

        case 2:
            try
            {
				cout << "Racine approchee pour f2: " << racine << endl;
            }
            catch(...)
            {
            	cout << ERREUR << endl;
            }
			break;
    }
}

int main(int argc, char **argv)
{
	choix = -1;

    // Menu.
    cout << "================================================================================" << endl;
    cout << "Algorithmes numériques" << endl;
    cout << "Laboratoire 2" << endl << endl;
    cout << "Simon Guillaume-Gentil, Eddy Strambini, Cyriaque Skrapits" << endl;
	cout << "INF2dlm-a";
	cout << "================================================================================" << endl << endl;
    cout << "Fonctions:" << endl;
    cout << "----------" << endl;
    cout << "1) sin(x)+x/3)" << endl;
    cout << "2) x/(1-x^2)" << endl;
    cout << "0) Quitter" << endl << endl;

    while (choix < 0 || choix > 2)
		saisie(choix, "Choix : ");

    if (choix == 0) return 0;

    // Saisies des bornes.
    setBorne(borneInferieure, -LIMITE_X, LIMITE_X, "Borne inferieure : ");
    setBorne(borneSuperieure, borneInferieure, LIMITE_X, "Borne superieure : ");

    // Saisie de l'epsilon.
    saisie(epsilon, "Epsilon : ");

    // Graphe.
    graphWin.initGraphicsWin(1000, -LIMITE_X, LIMITE_X, -LIMITE_Y, LIMITE_Y);

    return(0);
}

