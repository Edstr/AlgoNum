 /*
 * Approximation de PI et représentation graphique
 *
 *  Auteurs:
 *	Fábio Marques
 *	Cyriaque Skrapits
 *	Eddy Strambini
 */

#ifndef SIMPSON_H
#define SIMPSON_H

#include <iostream>

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h> // Librairie GLUT
#endif

using namespace std;

class simpson
{
    public:
        simpson();
        double approximation(double, double, int, double (*f)(double));
        void drawFunction(double, double, int, double (*f)(double));
        virtual ~simpson();
    protected:
    private:
};

#endif // SIMPSON_H
