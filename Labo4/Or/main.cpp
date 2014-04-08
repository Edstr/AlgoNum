#include <math.h>

#include "main.h"
#include "GeomGlut.h"

extern GeomGlut graphWin;

double f( double x )
{
  double y = 3.*sin( x*x ) / x*x*x;

  return( y );
}

void mainFunction( void )
{
  const float STEP = graphWin.findSmartStepX();
  double x1, x2, y1, y2;

  // draw points:
  for(float x=graphWin.xMin(); x<graphWin.xMax(); x+=STEP)
    graphWin.plot( x, f(x), 5 );

  // draw segments:
  x1 = graphWin.xMin();
  y1 = f(x1);

  for(float x2=graphWin.xMin()+STEP; x2<graphWin.xMax(); x2+=STEP)
  {
    y2 = f(x2);
    graphWin.segment( x1, y1, x2, y2 );

    // for next segment:
    x1 = x2;
    y1 = y2;
  }
}

int main(int argc, char **argv)
{
  graphWin.initGraphicsWin( 1000, -15.1, 15.1, -4.1, 4.1 );

  return( 0 );
}

