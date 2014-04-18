/*
 * Dérivations numériques
 * Partie 2
 *
 * Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#include <math.h>

#include "main.h"
#include "GeomGlut.h"
#include "CSV.h"

#include <iostream>
#include <string>

extern GeomGlut graphWin;

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
 * @r r Valeur rouge.
 * @g g Valeur verte.
 * @b b Valeur bleue.
 */
void dessinerGraph(CSV &csv, const float echelle, const float r, const float g, const float b)
{
	// Affiche le nombre d'entrée du CSV.
	std::cout << csv.getFileName() << ": " << csv.toMap().size() << " entrées" << std::endl;

	// Récupération des premières valeurs à dessiner.
	CSV::KEY premiereAnnee = coursOr.toMap().begin()->first;
	CSV::KEY x = 0;
	CSV::VALUE y = csv.get(premiereAnnee) * echelle;

	// Dessine toutes les valeurs du CSV.
	for(auto& i: csv.toMap()) {
		float curX = i.first - premiereAnnee;
		float curY = i.second * echelle;
		graphWin.plot(curX, curY, 3);
		graphWin.setColorForPlotWithoutColor(r, g, b); // Redéfinition de la couleur (nécessaire à cause du plot précédent).
		graphWin.segment(x, y, curX, curY);
		x = curX;
		y = curY;
	}
}

void mainFunction( void )
{
	dessinerGrille();
	dessinerGraph(coursOr, 0.01f, 1.0f, 0.5f, 0.0f);
	dessinerGraph(coursInflation, 1.0f, 0.0f, 0.4f, 0.8f);
}

int main(int argc, char **argv)
{
    graphWin.initGraphicsWin(1000, MIN_X, MAX_X, MIN_Y, MAX_Y);

    return( 0 );
}

