 /*
 * Affichage des d�riv�es premi�res et secondes de 2 fonctions
 *
 *  Auteurs:
 *	F�bio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#ifndef DERIVATION_H
#define DERIVATION_H

class derivation
{
    public:
        derivation();
        virtual ~derivation();

        void dessinerFonction(float a, float b, float pas, double (*fonction) (double));
        void dessinerDeriveePremiere(float a, float b, float pas, float h, double (*fonction) (double));
        void dessinerDeriveeSeconde(float a, float b, float pas, float h, double (*fonction) (double));

    protected:
    private:
};

#endif // DERIVATION_H
