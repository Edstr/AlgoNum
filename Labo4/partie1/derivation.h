 /*
 * Affichage des dérivées premières et secondes de 2 fonctions
 *
 *  Auteurs:
 *	Fábio Marques
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
