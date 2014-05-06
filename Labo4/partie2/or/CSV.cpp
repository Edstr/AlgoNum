/*
 * Dérivations numériques
 * Partie 2
 *
 * Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#include "CSV.h"

CSV::CSV(const std::string &fileName)
{
	this->fileName = fileName;

	// Ouverture du fichier CSV.
	std::ifstream file(fileName.c_str());
	std::string buffer;

	int key;
	float value;

	// Récupère chaque ligne et en ressort les données.

	while(std::getline(file, buffer))
	{
	    // Méthode C++11
		//key = stoi(buffer.substr(0, 4));
		//value = stof(buffer.substr(5, buffer.length() - 5));

        // Workaround si C++11 n'est pas supporté par G++.
		std::stringstream ssKey(buffer.substr(0, 4));
	    std::stringstream ssValue(buffer.substr(5, buffer.length() - 5));
        ssKey >> key;
        ssValue >> value;

		values[key] = value;
	}

	file.close();
}

CSV::~CSV()
{

}
