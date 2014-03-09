#ifndef CODAGE17BITS_H
#define CODAGE17BITS_H

#include <cmath>
#include <iostream>
#include<bitset>

#define TAILLE 17 // Nombre de bits total
#define E 5 // nombre de bits pour l'exposant

class codage17bits
{
    public:
        codage17bits(float); // Nombre a coder en argument

        float controleSigne(float); // Permet de contrôler le signe du nombre reçu

        virtual ~codage17bits();

    private:
        bool s = 0;     // bit de signe de base positif (0)
        int S = 1;
        int d = pow(2,E-1) - 1;          // décalage (formuule dans la norme IEE754 -> ici d = 15)
        int m = TAILLE - E - 1;          // mantisse

        std::bitset<TAILLE> bitSetNombre; // Set de bits de taille fixe (TAILLE)

    protected:
    private:
};

#endif // CODAGE17BITS_H
