/*
 * Encodage d'une valeur flottante sur 17 bits.
 *
 * Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#include "Codage17Bits.h"

Codage17Bits::Codage17Bits()
{
	this->exposant = 0;
	this->mantisse = 0;
	this->valeur = 0;
}

Codage17Bits::~Codage17Bits()
{

}

/*
 * Surcharge d'opérateur pour l'addition.
 * N'est pour le moment pas fonctionnel.
 *
 * TODO: à implémenter.
 */
Codage17Bits operator+(const Codage17Bits& a, const Codage17Bits& b)
{
	//http://users-tima.imag.fr/cis/guyot/Cours/Oparithm/francais/Flottan.htm
	Codage17Bits d;

	Codage17Bits::Mantisse m1 = a.mantisse;
	Codage17Bits::Mantisse m2 = b.mantisse;
	Codage17Bits::Exposant e1 = a.exposant;
	Codage17Bits::Exposant e2 = b.exposant;

	Codage17Bits::Mantisse t;

	int c = 0;
	for (unsigned int i = t.size() - 1; i > 0; i--)
	{
		t[i] = ((m1[i] ^ m2[i]) ^ c); // c is carry
		cout << t[i];
		c = ((m1[i] & m2[i]) | (m1[i] & c)) | (m2[i] & c);
	}
	d.mantisse = t;
	d.mantisse = d.mantisse>>1;
	d.normalise = false;

	Codage17Bits::Exposant u;
	c = 0;
	for (unsigned int i = u.size() - 1; i > 0; i--)
	{
		u[i] = ((e1[i] ^ e2[i]) ^ c); // c is carry
		cout << u[i];
		c = ((e1[i] & e2[i]) | (e1[i] & c)) | (e2[i] & c);
	}
	d.exposant = u;
	return d;
}

/**
 * Décode une chaîne de bits en une valeur réelle.
 */
void Codage17Bits::decoder(const string chaine)
{
	// Extraction.
	signe = chaine[0] == '1';
	exposant = Exposant(chaine.substr(1, EXPOSANT));
	mantisse = Mantisse(chaine.substr(1 + EXPOSANT, 1 + EXPOSANT + MANTISSE));

	// Calcul de la valeur.
	calculerValeur();
}

/**
 * Encode un nombre sous forme binaire.
 * @param nombre Nombre à encoder.
 */
void Codage17Bits::encoder(const float nombre)
{
	// Décalage (forcer à 0 si nombre = 0 car log(0) impossible (en théorie).
	int decalage = nombre == 0 ? -D - 1 : (int)floor(log(abs(nombre)) / log(2));

	// Signe
	signe = nombre < 0; // Vrai si négatif.

	// Exposant
	exposant = D + decalage + 1;

	//
	// MANTISSE
	//
	// La technique est de partir depuis 2^décalage et de rajouter toutes les
	// puissances inférieures à l'exposant afin d'obtenir le nombre entré.
	//
	int d = decalage; 				// Puissance de 2 à décrémenter.
	float m = pow(2, decalage); 	// Mantisse.
	float p = 0; 					// Puissance à rajouter.
	float n = abs(nombre);

	// On place les bits sur la mantisse en fonction des puissances de 2.
	for (int i = mantisse.size() - 1; i >= 0 && m < n; i--)
	{
		p = pow(2, --d);

		// Si le nombre n'est pas encore atteint...
		if (m + p <= n)
		{
			mantisse.set(i);
			m += p;
		}
	}

	// Calcul de la valeur.
	calculerValeur();
}

/**
 * Recalcule la valeur en fonction de l'exposant et de la mantisse.
 */
void Codage17Bits::calculerValeur()
{
	int s;		// Signe
	float m;	// Mantisse

	// Normalisé ?
	int puissance = exposant.to_ulong() == 0 ? pow(2, MANTISSE) : PUISSANCEMANTISSE; // 2^n-1 oû 2^n en fonction de la normalisation.
	m = (float)(mantisse.to_ulong() + pow(2, MANTISSE)) / puissance; // M = m / 2^n
	normalise = m >= 0.5 && m < 1.0;

	// Résultat
	// On rajoute le bit caché si la mantisse est normalisée ([0.5, 1.0[).
	int bit_cache = normalise ? pow(2, MANTISSE) : 0;
	s = (-2 * signe + 1);
	m = ((float)(mantisse.to_ulong() + bit_cache) / (normalise ? PUISSANCEMANTISSE : pow(2, MANTISSE)));
	this->valeur = s * m * pow(2, (int)exposant.to_ulong() - D); // SM2^(e - d)

}

/**
 * Retourne la valeur codée sous forme de bits dans une chaîne.
 * @param format Sépare chaque partie de la suite binaire.
 * @return Chaîne binaire.
 */
string Codage17Bits::toString(bool format)
{
	stringstream ss;
	string separation = format ? " " : "";

	ss 	<< signe << separation
		<< exposant.to_string() << separation
		<< mantisse.to_string();

	return ss.str();
}
