/*
    Date: 25.02.2014
    Auteurs: Eddy Strambini, Cyriaque Skrapits, Da Mota Marques Fabio Manuel
*/

#include <iostream>
#include <limits>
#include <bitset>
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

    cout << "------------------------ \n";

    cout << "Nombre MAX sur 17 bits : \n";
    int exposantMax = 30; // 11110
    int mantisseMax = 4095; // bit caché à 1 et les 11 de la mantisse aussi
    bitset<17> nombreMaxCode(std::string("01111011111111111"));

    float nombreMax = 1 * mantisseMax / pow(2,11) * (pow(2,exposantMax - 15));

    cout << nombreMaxCode << " : " << nombreMax << "\n";

    cout << "Nombre MIN sur 17 bits : \n";
    int exposantMin = 1; // 00001
    int mantisseMin = 0; // bit caché à 1 et les 11 de la mantisse a 0
    bitset<17> nombreMinCode(std::string("00000100000000000"));

    float nombreMin = 1 * mantisseMin / pow(2,11) * (pow(2,exposantMin - 15));

    cout << nombreMinCode << " : " << nombreMin << "\n";

    cout << "Nombre le PLUS PROCHE DE 1 sur 17 bits : \n";
    int exposantProche = 14; // 01111
    int mantisseProche = 4095; // bit caché à 1 et les 11 de la mantisse a 0
    bitset<17> nombreProcheCode(std::string("00111011111111111"));

    float nombreProche = 1 * mantisseProche / pow(2,11) * (pow(2,exposantProche - 15));

    cout << nombreProcheCode << " : " << nombreProche << "\n";


    return 0;
}
