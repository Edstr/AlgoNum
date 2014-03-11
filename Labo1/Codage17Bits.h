/*
 * Encodage d'une valeur flottante sur 17 bits.
 *
 * Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#ifndef CODAGE17BITS_H
#define CODAGE17BITS_H

#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <cmath>

#define EXPOSANT 5					// Taille de l'exposant
#define MANTISSE 11					// Taille de la mantisse
#define D 14 						// Valeur D de l'exposant 2^(e - d)
#define PUISSANCEMANTISSE 4096		// 2^12 (évite de recalculer avec pow)

using namespace std;

/**
 * Classe permettant de coder un nombre sur 17 bits sous forme de suite binaire2
 * ou en nombre réel.
 *
 * Notons qu'il est tout à fait possible d'utiliser cette classe pour coder
 * sur 32 bits. Il suffit de remplacer les valeurs des #define par les valeurs
 * nécessaires à l'encodage 32 bits.
 *
 * Limites:
 *	- Max : 65'520
 *	- Min : 6.10352e-05
 *
 * @author Fábio Marques
 * @author Cyriaque Skrapits
 * @author Eddy Strambini
 */
class Codage17Bits
{
	friend Codage17Bits operator+(const Codage17Bits&, const Codage17Bits&);

	public:
		// Alias
		typedef bitset<EXPOSANT> Exposant;
		typedef bitset<MANTISSE> Mantisse;

		Codage17Bits();
		virtual ~Codage17Bits();

		void decoder(const string chaine);
		void encoder(const float nombre);

		inline const Exposant getExposant() { return exposant; };
		inline const Mantisse getMantisse() { return mantisse; };
		inline bool isNormalise() { return normalise; };
		string toString(bool format = false);
		inline float toFloat() { return valeur; };

	protected:
	private:
		float valeur;

		bool signe;
		bool normalise;

		Exposant exposant;
		Mantisse mantisse;

		void calculerValeur();
};



#endif // CODAGE17BITS_H
