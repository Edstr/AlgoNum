/*
 * Dérivations numériques
 * Partie 2
 *
 * Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#include "main.h"

const int MIN_X = -5;
const int MIN_Y = -5;
const int MAX_X = 25;
const int MAX_Y = 20;

CSV coursOr("../doc/or.csv");
CSV coursInflation("../doc/inflation.csv");

/**
 * Dessine une grille et les axes (qui ont été effacés).
 */
void dessinerGrille()
{
    // Grille
    graphWin.setColorForPlotWithoutColor(0.9f, 0.9f, 0.9f);
    for(int x = MIN_X; x < MAX_X; x++)
        graphWin.segment(x, MIN_Y, x, MAX_Y);

    for(int y = MIN_Y; y < MAX_Y; y++)
        graphWin.segment(MIN_X, y, MAX_X, y);

    // Axes
    graphWin.setColorForPlotWithoutColor(0.5f, 0.5f, 0.5f);
    graphWin.segment(MIN_X, 0, MAX_X, 0);
    graphWin.segment(0, MIN_Y, 0, MAX_Y);
}

/**
 * dessinerGraphe(csv, echelle, r, g, b)
 * @param csv CSV à lire.
 * @param echelle Echelle du graphe.
 * @param r Valeur rouge.
 * @param g Valeur verte.
 * @param b Valeur bleue.
 */
void dessinerGraph(CSV &csv, const float echelle, const float r, const float g, const float b)
{
    // Affiche le nombre d'entrée du CSV.
    //std::cout << csv.getFileName() << ": " << csv.toMap().size() << " entrées" << std::endl;

    // Récupération des premières valeurs à dessiner.
    CSV::KEY premiereAnnee = coursOr.toMap().begin()->first;
    CSV::KEY x = 0;
    CSV::VALUE y = csv.get(premiereAnnee) * echelle;

    // Dessine toutes les valeurs du CSV.
    for(auto& i: csv.toMap())
    {
        float curX = i.first - premiereAnnee;
        float curY = i.second * echelle;
        graphWin.plot(curX, curY, 3);
        graphWin.setColorForPlotWithoutColor(r, g, b); // Redéfinition de la couleur (nécessaire à cause du plot précédent).
        graphWin.segment(x, y, curX, curY);
        x = curX;
        y = curY;
    }
}

/**
 * Calcul le prix de l'or d'une année en fonction de l'IPC.
 *
 * @param valeur Prix de l'or.
 * @param ipc Pourcentage de l'IPC.
 * @return Prix de l'or en fonction de l'IPC.
 */
const float calculerIPC(const float valeur, const float ipc)
{
    return valeur + valeur * (ipc / 100);
}

/**
 * Calcul la meilleure année pour l'achat d'or puis la revente.
 *
 * @param coursOr CVS du cours de l'or.
 * @param coursInflation CVS du cours de l'inflation.
 */
void calculerMeilleureAnnee(CSV &coursOr, CSV &inflation)
{
    CSV::KEY premiereAnnee = coursOr.toMap().begin()->first;
    unsigned int annees = coursOr.toMap().size() - 1;
    unsigned int annee = premiereAnnee;
    float maximum = 0.0f;
    float variance = 0.0f;

    for(unsigned int i = premiereAnnee + 1; i <= premiereAnnee + annees; i++)
    {
        variance = calculerIPC(coursOr.get(i), coursInflation.get(i)) - calculerIPC(coursOr.get(i - 1), coursInflation.get(i - 1));
        if (variance > maximum)
        {
            maximum = variance;
            annee = i;
        }
    }

    std::cout << "Meilleure periode d'achat sur un 1 an : " << annee - 1 << " -> " << annee << ", gain : " << maximum  << " CHF" << std::endl;
}

/**
 * Calcul la meilleure période entre 1994 et 2014 pour l'achat d'or puis la
 * revente.
 *
 * @param coursOr CVS du cours de l'or.
 * @param coursInflation CVS du cours de l'inflation.
 */
void calculerMeilleurePeriode(CSV &coursOr, CSV &coursInflation)
{
    CSV::KEY premiereAnnee = coursOr.toMap().begin()->first;
    unsigned int annees = coursOr.toMap().size() - 1;
    unsigned int anneeDebut = premiereAnnee;
    unsigned int anneeFin = premiereAnnee;
    float maximum = 0.0f;
    float variance = 0.0f;

	// Calcul chaque période possible puis retourne la meilleure.
    for(unsigned int k = premiereAnnee; k < premiereAnnee + annees; k++)
    {
        for(unsigned int j = k + 1; j <= premiereAnnee + annees; j++)
        {
            variance = calculerIPC(coursOr.get(j), coursInflation.get(j)) - calculerIPC(coursOr.get(k), coursInflation.get(k));
            if (variance > maximum)
            {
                maximum = variance;
                anneeDebut = k;
                anneeFin = j;
            }
        }
    }

    std::cout << "Meilleure periode d'achat globale : " << anneeDebut << " -> " << anneeFin << ", gain : " << maximum << " CHF" << std::endl;

}

void intro()
{
	std::cout << "================================================================================" << std::endl;
    std::cout << "Algorithmes numeriques" << std::endl;
    std::cout << "Laboratoire 4 partie 2" << std::endl;
    std::cout << std::endl;
    std::cout << "Eleves : Febio Marques, Cyriaque Skrapits, Eddy Strambini" << std::endl;
    std::cout << "Professeur : Dr. Stephane Gobron" << std::endl;
	std::cout << "================================================================================" << std::endl;
	std::cout << std::endl;
}

void calculs()
{
	calculerMeilleureAnnee(coursOr, coursInflation);
    calculerMeilleurePeriode(coursOr, coursInflation);
    std::cout << std::endl;
}

void graphiques()
{
	std::cout << "Rendu des graphes." << std::endl;
	std::cout << "-> Bleu : IPC Suisse" << std::endl;
	std::cout << "-> Orange : cours de l'or en Suisse" << std::endl;
	std::cout << std::endl;
    graphWin.initGraphicsWin(1000, MIN_X, MAX_X, MIN_Y, MAX_Y);
}

void mainFunction(void)
{
    dessinerGrille();
    dessinerGraph(coursOr, 0.01f, 1.0f, 0.5f, 0.0f);
    dessinerGraph(coursInflation, 1.0f, 0.0f, 0.4f, 0.8f);
}

int main(int argc, char **argv)
{
	intro();
	calculs();
	graphiques();

    return(0);
}

