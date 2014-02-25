/*
    Date: 25.02.2014
    Auteurs: Eddy Strambini, Cyriaque Skrapits, Da Mota Marques Fabio Manuel
*/

#include <iostream>
#include <limits>

using namespace std;

double saisie(string texte)
{
    double nombre;

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
    double nmb1, nmb2;

    nmb1 = saisie("Premier nombre : ");
    nmb2 = saisie("Deuxieme nombre : ");

    return 0;
}
