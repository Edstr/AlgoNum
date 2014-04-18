/*
 * Dérivations numériques
 * Partie 2
 *
 * Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#ifndef CSV_H
#define CSV_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <string>

/**
 * Classe permettant de lire un fichier CSV et d'en tirer les données.
 */
class CSV
{
	public:
		typedef int KEY;
		typedef float VALUE;
		typedef std::map<const KEY, VALUE> MAP;

		CSV(const std::string &);
		virtual ~CSV();

		const VALUE get(const KEY key) { return values.at(key); }
		const std::string getFileName() { return fileName; }
		const MAP toMap() { return values; }

	protected:
	private:
		MAP values;
		std::string fileName;
};

#endif // CSV_H
