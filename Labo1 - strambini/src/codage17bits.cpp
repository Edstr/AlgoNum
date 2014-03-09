#include "codage17bits.h"

#include <cmath>
#include <iostream>
#include<bitset>

codage17bits::codage17bits(float nombre)
{
    int puissanceDeux = 0; // Utilisé pour calculer le nombre de division/multiplication faites
    float multipleDivision; // Variable permettant de définir si on va se rapprocher entre 1 et 0.5 en multipliant ou diviant

    nombre = controleSigne(nombre);

    // Set du bit de signe :
    this->bitSetNombre.set(TAILLE-1,this->s);

    if(nombre >= 1.0)
    {
        multipleDivision = 0.5; // Si le nombre est plus grand que 1 on va diviser ce nombre
    }

    else if (nombre <= 0.5)
    {
        multipleDivision = 2; // Si plus grand que 0.5 on va le multiplier par 2 pour être entre 0.5 et 1
    }

    while(nombre <= 0.5 || nombre >= 1.0)
    {
        nombre = nombre*multipleDivision;
        puissanceDeux++;
    }

    // Set de l'exposant :
    float exposant = this->d + puissanceDeux;
    std::bitset<E> bitsetExp(exposant); // Création d'un bitset temporaire contenant la valeur binaire du nombre de puissance de 2 décalé par "d"

    for(int i=0; i < puissanceDeux; i++)
    {
        this->bitSetNombre.set(TAILLE-6+i,bitsetExp[i]);
        // Remplissage du bitset des bits de l'exposant, on commence au bit n° 11 jusqu'au 16
    }

    delete &bitsetExp;

    // Set de la mantisse :
    float mantisse = nombre * pow(2,this-> m + 1);
    std::bitset<TAILLE - E - 1> bitsetDeca(mantisse);

    for(int i=0; i < this->m; i++)
    {
        this->bitSetNombre.set(i,bitsetDeca[i]);
    }

    delete &bitsetDeca;

    std::cout << "Nombre code : " << this->bitSetNombre << "\n";
    std::cout << "Nombre re-calcule : " << this->S * (mantisse/pow(2,12)) * (pow(2,exposant - this->d)) << "\n";
}

float codage17bits::controleSigne(float nombre)
{
    // Contrôle du signe du nombre :
    if(nombre < 0.0)
    {
        this->s = 1;
        this->S = -1;
        nombre = std::abs(nombre); // Met le bit de signe a 1 car négatif et prend la valeur absolu du nombre
    }

    return nombre;
}


codage17bits::~codage17bits()
{
    //dtor
}
