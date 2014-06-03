/*
 * Approximation et représentation graphique de PI.
 *
 * Auteurs:
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

class Simpson
{
    public:
        Simpson();
        virtual ~Simpson();

        static long double integration(const double, const double, const unsigned int, long double (*f)(long double));
        static void dessinerFonction(const double, const double, const int, long double (*f)(long double));

    protected:
    private:
};

#endif // SIMPSON_H
