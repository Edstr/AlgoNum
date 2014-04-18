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
		key = stoi(buffer.substr(0, 4));
		value = stof(buffer.substr(5, buffer.length() - 5));

		values[key] = value;
	}

	file.close();
}

CSV::~CSV()
{

}
