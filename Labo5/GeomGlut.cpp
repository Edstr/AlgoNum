//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------


#include "GeomGlut.h"
#include "main.h"

//include this file for cout
#include <iostream>


GeomGlut graphWin;

GeomGlut::GeomGlut( void )
{
  m_scale = 1.0f;
}

GeomGlut::~GeomGlut( void )
{

}

void GeomGlut::initGraphicsWin( unsigned int pixelWinX, double xMin, double xMax, double yMin, double yMax )
{
  if(xMax-xMin<=0)
    {
        cout << "xMax-xMin cannot be < or = to 0" << endl << endl;
        return;
    }

  winFuncPixels.x = pixelWinX;
  winFuncPixels.y = (unsigned int)((yMax-yMin) * (double)winFuncPixels.x/(xMax-xMin));

  char *myargv [1];
	int myargc=1;
	myargv [0]= "";
	glutInit(&myargc, myargv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowPosition(0, 0);

  cout << "System coordinate min(" << xMin << ", " << yMin << ") max(" << xMax << ", " << yMax << " give for " << winFuncPixels.x << " pixels in X, a Y pixel number of " << winFuncPixels.y << endl << endl;

  cout << "pixelWin(" << winFuncPixels.x << ", " << winFuncPixels.y << ")...";
  glutInitWindowSize(winFuncPixels.x, winFuncPixels.y);
  cout << " success!" << endl << endl;

  // at the begining, the function win pixel and the actual win pixel are identical:
  graphWin.setWinPixels( winFuncPixels.x, winFuncPixels.y );

  minWin.x = xMin;
  minWin.y = yMin;
  maxWin.x = xMax;
  maxWin.y = yMax;

  glutCreateWindow("Labo 5 : Approximation de PI");

  // Initialiser la couleur du fond (blanc)
  glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

  glutMouseFunc( Scale );

  glutReshapeFunc( Reshape );
  glutDisplayFunc( Display );
  glutMainLoop();
}

void GeomGlut::drawAxes()
{
  // Draw the white background:
  glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f); // red
    glVertex3d(minWin.x, minWin.y, -1.0);
    glVertex3d(maxWin.x, minWin.y, -1.0);
    glVertex3d(maxWin.x, maxWin.y, -1.0);
    glVertex3d(minWin.x, maxWin.y, -1.0);
  glEnd();

  // Draw the axes :
  glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // red
    // Axe X
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(1.0-ARROW, -ARROW, 0.0);
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(1.0-ARROW, ARROW, 0.0);

    // Axe Y
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(ARROW, 1.0-ARROW, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(-ARROW, 1.0-ARROW, 0.0);

    glColor3f(0.0f, 0.0f, 1.0f); // blue
    // Axe X  maxWin.x = xMax;

    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(maxWin.x, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(minWin.x, 0.0, 0.0);

    // Axe Y
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, maxWin.y, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, minWin.y, 0.0);

  glEnd();
}

void GeomGlut::plot( GLfloat x, GLfloat y )
{
    plot(x, y, DEFAUL_SIZE_POINT);
}

void GeomGlut::plot( GLfloat x, GLfloat y, GLfloat sizePoint )
{
  if( (x<minWin.x) || (x>maxWin.x) || (y<minWin.y) || (y>maxWin.y) )
    glColor3f(0.7f, 0.7f, 0.7f);
  else
    glColor3f(0.0f, 0.0f, 0.0f);

  glPointSize( sizePoint );
  glBegin( GL_POINTS );
    glVertex3d(x, y, 0.0);
  glEnd();
}

void GeomGlut::segment(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    //Pas de duplication du code ! Plus facile � maintenir
    segmentCouleur(x1,y1,x2,y2,0.0f,0.0f,0.0f);
}

void GeomGlut::segmentCouleur(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat r, GLfloat g, GLfloat b)
{
  if( (x1<minWin.x) || (x1>maxWin.x) || (y1<minWin.y) || (y1>maxWin.y) ||
      (x2<minWin.x) || (x2>maxWin.x) || (y2<minWin.y) || (y2>maxWin.y) )
    glColor3f(0.7f, 0.7f, 0.7f);
  else
    glColor3f(r, g, b);

  glBegin( GL_LINES );
    glVertex3d(x1, y1, 0.0);
    glVertex3d(x2, y2, 0.0);
  glEnd();
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

void Display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  graphWin.drawAxes();
  mainFunction();
  glFlush();
}

void Reshape(int w, int h)
{
  GLfloat left, right, bottom, top;
  if (h == 0) h = 1;
  if (w == 0) w = 1;
  glViewport(0, 0, w, h);

  graphWin.setWinPixels( w, h );

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float xRatio = (float)w*graphWin.getScale()/(float)graphWin.xWinFunc();
  float yRatio = (float)h*graphWin.getScale()/(float)graphWin.yWinFunc();

  // Volume de clipping : (left, right, bottom, top, near, far)
  glOrtho(graphWin.xMin()*xRatio, graphWin.xMax()*xRatio, graphWin.yMin()*yRatio, graphWin.yMax()*yRatio, -2.0f, 2.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Scale(int button, int state, int x, int y)
{
	float value;

	switch(button)
	{
        #ifdef WIN32
            case 0: value = 0.9f; break;
            case 2: value = 1.1f; break;
        #else
            case 3: value = 0.9f; break;
            case 4: value = 1.1f; break;
        #endif
	}

	if (graphWin.getScale() * value < 0.01f)
		return;

	if (graphWin.getScale() * value > 5.0f)
		return;

	graphWin.setScale(graphWin.getScale() * value);
	Reshape(graphWin.xWinFunc(), graphWin.yWinFunc());
	Display();
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------


