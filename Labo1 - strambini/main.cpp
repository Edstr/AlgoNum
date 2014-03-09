/*
    Date: 25.02.2014
    Auteurs: Eddy Strambini, Cyriaque Skrapits, Da Mota Marques Fabio Manuel
*/

#include <iostream>
#include <limits>
#include "codage17bits.h""

using namespace std;

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

int main()
{
    float nombreSaisie;

    nombreSaisie = saisie("Saisir le nombre a coder : ");

    codage17bits nombreCode = codage17bits(nombreSaisie);

    return 0;
}
