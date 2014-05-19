/*
 * Approximation et représentation graphique de PI.
 *
 * Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#include "main.h"

using namespace std;

//Variables nécessaire pour le dessin des fonctions
extern GeomGlut graphWin;

int n = 0; //Précision du calcul (nombre de découpage)
Simpson simpson;

/**
 * Fonction d'approximation de Pi.
 *
 * @param x Valeur réelle entre 0 et 1.
 * @return Approximation de Pi / 4.
 */
inline double f(const double x)
{
    return 1 / (1 + pow(x, 2));
}

/**
 * Fonction demandant une valeur.
 * @param t Variable stockant la valeur entrée.
 * @param texte Titre de la saisie.
 */
template<class T> inline void saisie(T &t, string texte)
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

/**
 * Fonction principale pour Glut.
 */
void mainFunction(void)
{

    simpson.dessinerFonction(0, 1, n, &f);

    // Axes principaux
    graphWin.segmentCouleur(X_MIN, 0, X_MAX, 0, 0.2f, 0.4f, 0.6f);
    graphWin.segmentCouleur(0, Y_MAX, 0, Y_MIN, 0.2f, 0.4f, 0.6f);

    // Axes unitaires
    graphWin.segmentCouleur(1, Y_MAX, 1, Y_MIN, 0.8f, 0.9f, 1.f);
    graphWin.segmentCouleur(-1, Y_MAX, -1, Y_MIN, 0.8f, 0.9f, 1.f);
    graphWin.segmentCouleur(X_MIN, 1, X_MAX, 1, 0.8f, 0.9f, 1.f);
    graphWin.segmentCouleur(X_MIN, -1, X_MAX, -1, 0.8f, 0.9f, 1.f);

    // Unités
    graphWin.setCouleur(0.2f, 0.2f, 0.2f);
    graphWin.texte(0.05f, 0.05f,(void *)FONT, "0");
    graphWin.texte(1.05f, 0.05f,(void *)FONT, "1");
    graphWin.texte(0.05f, 1.05f,(void *)FONT, "1");
    graphWin.texte(0.05f, -1.1f,(void *)FONT, "-1");
    graphWin.texte(-1.1f, 0.05f,(void *)FONT, "-1");

    // Titre (positionnement approximatif)
    float scale = graphWin.getScale();
    graphWin.setCouleur(0.2f, 0.4f, 0.6f);
    graphWin.texte(scale * 0.f, 1.23f,(void *)FONT, "Integrale de 0 a 1 de f(x) =");
    graphWin.texte(scale * 1.55f, 1.3f,(void *)FONT, "1");
    graphWin.texte(scale * 1.4f, 1.15f,(void *)FONT, "1 + x^2");
    graphWin.segment(scale * 1.4f, 1.25f, scale * 1.75f, 1.25f);
}

void intro()
{
    cout << "================================================================================" << endl;
    cout << "Algorithmes numeriques" << endl;
    cout << "Laboratoire 5" << endl;
    cout << endl;
    cout << "Equipe : 7" << endl;
    cout << "Eleves : Febio Marques, Cyriaque Skrapits, Eddy Strambini" << endl;
    cout << "Professeur : Dr. Stephane Gobron" << endl;
    cout << endl;
    cout << "Note 1 : utilisez les clics pour zoomer sur le graphique." << endl;
    cout << "Note 2 : un N d'environ 1000 semble etre optimal." << endl;
    cout << "================================================================================" << endl;
    cout << endl;
}

/**
 * Saisie du découpage par l'utilisateur.
 */
void saisieDecoupage()
{
    bool ok;
    do
    {
        saisie(n, "Entrez un nombre pair de decoupage (n) : ");
        ok = n > 0 && n % 2 == 0;
        if (!ok)
            cout << "Erreur : nombre invalide !" << endl;
    } while(!ok);
}

/**
 * Calcule Pi puis affiche les résultats.
 */
void resultats()
{
    // Calcule le temps d'éxecution.
    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
    LARGE_INTEGER Frequency;

    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&StartingTime); // Temps de départ

    double pi = 4 * simpson.integration(0, 1, n, &f);

    QueryPerformanceCounter(&EndingTime); // Temps de fin
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

    // Affiche les résultats.
    cout << setprecision(25);
    cout << "Temps de calcul: " << ElapsedMicroseconds.QuadPart << " microsecondes" << endl;
    cout << endl;
    cout << "Valeur approximee de Pi (surface rouge + surface grise):\n\t" << pi << endl;
    cout << "Valeur reelle de Pi:\n\t" << PI << endl;
    cout << "Erreur comparee a Pi:\n\t" << abs(PI - pi) << endl;
    cout << endl << setprecision(2);
}

int main()
{
    intro();
    saisieDecoupage();
    resultats();

    graphWin.initGraphicsWin(700, X_MIN, X_MAX, Y_MIN, Y_MAX );

    return 0;
}
