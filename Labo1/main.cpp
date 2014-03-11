/*
 * Encodage d'une valeur flottante sur 17 bits.
 *
 * Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#include "Codage17Bits.h"
#include <iostream>
#include <limits>

using namespace std;

/**
 * Demande à l'utilisateur de saisir une valeur flottante.
 * Si la valeur n'est pas un nombre, lui redemander.
 * @param texte Question à afficher.
 * @return valeur flottante.
 */
float saisie(string texte)
{
    float nombre;

    cout << texte;

    while (!(cin >> nombre))
    {
        cerr << "Erreur de saisie.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << texte;
    }

    return nombre;
}

/**
 * Affiche une valeur intitulée.
 * @param c Object Codage17Bits servant à décoder la chaîne.
 * @param chaine Suite de bits à décoder.
 * @param titre Intitulé du décodage.
 */
void afficher(Codage17Bits& c, string chaine, string titre)
{
	// Valeur maximum.
    c.decoder(chaine);
    cout << "== " << titre << " ==" << endl;
	cout << "Nombre : \t" << c.toFloat() << endl;
    cout << "Mantisse : \t" << c.toString(true) << endl;
    cout << "Normalisé : \t" << boolalpha << c.isNormalise() << endl;
    cout << endl;
}

int main()
{
	// Valeur entrée par l'utilisateur.
	float nombreSaisie = saisie("Nombre à coder : ");
	Codage17Bits c;
	c.encoder(nombreSaisie);
	cout << "Nombre : \t" << c.toFloat() << endl;
    cout << "Mantisse : \t" << c.toString(true) << endl;
    cout << "Normalisé : \t" << boolalpha << c.isNormalise() << endl;
    cout << endl;

    // Valeur minimum.
    afficher(c, "00000100000000000", "Valeur minimum");

    // Valeur maximum.
    afficher(c,"01111011111111111", "Valeur maximum");

	// Valeur proche de 1 par le haut.
	afficher(c, "00111100000000001", "Valeur proche de 1 par le haut");

	// Valeur proche de 1 par le bas.
	afficher(c, "00111011111111111", "Valeur proche de 1 par le bas");

    return 0;
}
