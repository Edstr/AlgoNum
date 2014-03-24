/*
 * Recherche des y = 0 à l'aide de la méthode de la bissection.
 *
 * Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */
#include "main.h"
#include "GeomGlut.h"

extern GeomGlut graphWin;

/*
 * Cette partie devrait figurer dans le fichier main.h mais comme GeomGlut.h
 * rappelle main.h après, ces fonctions vont être définies deux fois ce qui
 * produit un bug.
 */
const float EPSILON_MINIMUM = 0.0001;
const float LIMITE_X = 100;
const float LIMITE_Y = 60;
const float INTROUVABLE = LIMITE_X + 1;
const int FACTEUR_DETECTION_ASYMPTOTE = 100;
const string ERREUR = "Erreur : aucune racine n'a ete trouvee dans cet interval !";
int choix;
float borneInferieure;
float borneSuperieure;
float epsilon;
float racine;


/**
 * Calcul la première fonction à partir de X.
 * @param x Position sur l'axe des X.
 * @return y
 */
double f1(double x)
{
    return (sin(x) - (x / 3));
}

/**
 * Calcul la deuxième fonction à partir de X.
 * @param x Position sur l'axe des X.
 * @return y
 */
double f2(double x)
{
    return x / (1-pow(x,2));
}

/**
 * Dessine la fonction.
 * @param borneInf Borne inférieure.
 * @param borneSup Borne supérieure.
 * @param pas Espace entre chaque point.
 * @param f Fonction à dessiner.
 */
void dessinerFonction(float borneInf, float borneSup, float pas, double (*f) (double) )
{
    for(float x = borneInf; x <= borneSup; x += pas)
		graphWin.segment(x, f(x), x + pas, f(x + pas));
}


/**
 * Affiche les intervales où le programme calcul la bissection.
 * @param borneInf Borne inférieure.
 * @param borneSup Borne supérieure.
 * @param h Hauteur des bornes.
 */
void dessinerIntervales(float borneInf, float borneSup, float &h)
{
	float r = 1.0f;
	float g = 0.4f;
	float b = 0.2f;

    graphWin.segmentCouleur(borneInf, h / 2, borneInf, -h / 2, r, g, b);
    graphWin.segmentCouleur(borneInf, h / 2, borneInf + 0.2, h / 2, r, g, b);
    graphWin.segmentCouleur(borneInf, -h / 2, borneInf + 0.2, -h / 2, r, g, b);

    graphWin.segmentCouleur(borneSup, h / 2, borneSup, -h / 2, r, g, b);
    graphWin.segmentCouleur(borneSup - 0.2, h / 2, borneSup, h / 2, r, g, b);
    graphWin.segmentCouleur(borneSup - 0.2, -h / 2, borneSup, -h / 2, r, g, b);

    h /= 1.5;
}

/**
 * Dessine la grille.
 */
void dessinerUnites()
{
	// Grille.
    for(int x = -LIMITE_X; x <= LIMITE_X; x++)
		graphWin.segmentCouleur(x, LIMITE_Y, x, -LIMITE_Y, 0.9f, 0.9f, 0.9f);
	for(int y = -LIMITE_Y; y <= LIMITE_Y; y++)
		graphWin.segmentCouleur(-LIMITE_X, y, LIMITE_X, y, 0.9f, 0.9f, 0.9f);

	// Axes (les axes de base sont effacés donc il faut les redessiner).
	graphWin.segmentCouleur(-LIMITE_X, 0, LIMITE_X, 0, 0.2f, 0.4f, 0.6f);
	graphWin.segmentCouleur(0, LIMITE_Y, 0, -LIMITE_Y, 0.2f, 0.4f, 0.6f);
}

/**
 * Calcul la bissection entre deux bornes puis affiche les intervales
 * traitées.
 * Utilise le 2e algorithme.
 * Retourne le premier zéro trouvé de la fonction.
 *
 * @param borneInf Borne inférieure.
 * @param borneSup Borne supérieure.
 * @param pas Interval de calcul.
 * @param f Fonction à calculer.
 * @return Zéro de la fonction.
 */
double bissection(float borneInf, float borneSup, float pas, double (*f)(double))
{
	float hauteurSegment = 3.0;
	float a = borneInf;
	float b = borneSup;
    float fa = f(a);
    float mnew = abs(a) + abs(b);
    float mold = 2 * mnew;
    float fm;

	// On cherche jusqu'à que la différence entre les bornes soit plus petite
	// que l'epsilon.
    while(abs(mnew - mold) > epsilon)
	{
		dessinerIntervales(a, b, hauteurSegment);

		mold = mnew;
		mnew = (a + b) / 2;

		fm = f(mnew);
		if(fm * fa <= 0)
		{
			b = mnew;
		}
		else
		{
			a = mnew;
			fa = fm;
		}
	}

	// Si la valeur retournée semble s'approcher du 0, alors le retourner.
	if(f(mnew) <= epsilon)
		return mnew;
	return INTROUVABLE; // Sinon, introuvable.
}

/**
 * Dessin.
 */
void mainFunction(void)
{
	dessinerUnites(); // Affiche les unités.

    switch(choix)
    {
        case 1:
			dessinerFonction(-LIMITE_X, LIMITE_X, 0.1, &f1);
			bissection(borneInferieure, borneSuperieure, epsilon, &f1);
			break;
        case 2:
            dessinerFonction(-LIMITE_X, LIMITE_X, 0.1, &f2);
			bissection(borneInferieure, borneSuperieure, epsilon, &f2);
			break;
        break;
    }

    graphWin.plot(racine, 0, 5);
}

/**
 * Vérifie qu'une valeur appartient bien à un interval.
 */
bool estDansLimites(const float &valeur, const float &borneMin, const float &borneMax)
{
    return (valeur >= -borneMin) && (valeur <= borneMax);
}

/**
 * Fonction demandant une valeur.
 * @param t Variable stockant la valeur entrée.
 * @param texte Titre de la saisie.
 */
template<class T>
void saisie(T &t, string texte)
{
    cout << texte;

    while(!(cin >> t))
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

/**
 * Affiche les résultats.
 */
void resultats()
{
	cout << endl;
    if (racine != INTROUVABLE)
		cout << "Racine approchee pour f" << choix << ": " << racine << endl;
	else
		cout << ERREUR << endl;
    cout << endl;
}

int main(int argc, char **argv)
{
	choix = -1;

    // Menu.
    cout << "================================================================================" << endl;
    cout << "Algorithmes numériques" << endl;
    cout << "Laboratoire 2" << endl;
    cout << endl;
    cout << "Fábio Marques, Cyriaque Skrapits, Eddy Strambini" << endl;
	cout << "================================================================================" << endl;
	cout << endl;
    cout << "Fonctions:" << endl;
    cout << "----------" << endl;
    cout << "1) sin(x)+x/3)" << endl;
    cout << "2) x/(1-x^2)" << endl;
    cout << "0) Quitter" << endl;
    cout << endl;

    while (choix < 0 || choix > 2)
		saisie(choix, "Choix : ");

    if (choix == 0) return 0;

    // Saisies des bornes.
    setBorne(borneInferieure, -LIMITE_X, LIMITE_X, "Borne inferieure : ");
    setBorne(borneSuperieure, borneInferieure, LIMITE_X, "Borne superieure : ");

    // Saisie de l'epsilon.
    saisie(epsilon, "Epsilon : ");

	// Calcul la racine.
	racine = bissection(borneInferieure, borneSuperieure, epsilon, (choix == 1 ? &f1 : &f2));

	// Résultats.
	resultats();

    // Graphe.
    graphWin.initGraphicsWin(1000, -LIMITE_X, LIMITE_X, -LIMITE_Y, LIMITE_Y);

    return(0);
}

