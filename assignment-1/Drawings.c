#include "stdbool.h"
#include <math.h>

#include "GL/glut.h"

#include "Drawings.h"
#include "Turtle.h"

void Square()
{
	ClearScreen();
	Init(250, 250, 0);		// Move to the center (facing right)
	BGColor(0, 0, 0);		// Set Background color black
	LineColor(1, 1, 1);		// Set Line color white
	PenDown(false);                 // Move without drawing
        
	Forward(50);			// Move forward (right) 50 units
	Left(90);			// Turn left 90 degrees (facing up)
	PenDown(true);                  // Start Drawing
	        
        Forward(50);			// Move forward (up) 50 units
	Left(90);			// Turn left 90 degrees (facing left)
	Forward(100);			// ...
	Left(90);
	Forward(100);
	Left(90);
	Forward(100);
	Left(90);
	Forward(50);
}

/**
 * Draws a "Swastik" using the turtle library.
 */
void Original1()
{
    _init_();
    
    float l = SIZE/5;
    float c = SIZE/2;
    ClearScreen();
    Init(c-l, c-l/2.0, 0);
    BGColor(0, 0, 0);		// Set Background color black
    LineColor(1, 0, 0);
    
    PenDown(true);
    Forward(3*l/4);
    Left(90);
    Forward(3*l/2);
    Right(90);
    Forward(l);
    Right(90);
    Forward(l/4);
    Right(90);
    Forward(3*l/4);
    Left(90);
    Forward(3*l/2);
    Right(90);
    Forward(l);
    Right(90);
    Forward(l/4);
    
    PenDown(false);
    Right(90);
    Forward(3*l/4);
    Left(90);
    Forward(l/2);
    Left(90);    
    
    PenDown(true);
    Forward(3*l/4);
    Right(90);
    Forward(l);
    Right(90);
    Forward(l/4);
    Right(90);
    Forward(3*l/4);
    Left(90);
    Forward(l/2);
    
    PenDown(false);
    Forward(l/4);
    PenDown(true);
    Forward(3*l/4);
    Right(90);
    Forward(l);
    Right(90);
    Forward(l/4);
    Right(90);
    Forward(3*l/4);
    Left(90);
    Forward(l/2);
    
          
    glFlush();    
}


/**
 * Draws an ellipse with center (x_0, y_0)
 * @param x_0
 * @param y_0
 * @param a     length of major axis.
 * @param b     length of minor axis.
 */
void drawEllipse(float x_0, float y_0, float a, float b)
{
    float PI = 3.141592654f;    
    
    GLint ellipse_points = 100;
    glBegin(GL_POLYGON);
    int i = 0;
    float angle = 0.0f;
    
    for(i = 0; i<ellipse_points;i++)
    {
        angle = i*(2*PI/ellipse_points);
        glVertex2f(x_0 + a*cos(angle), y_0 + b*sin(angle));
    }
    glEnd();
    
    
}


void Original2()
{
    float a = 80;
    float b = 40;            
    
    float x_0 = SIZE/2;
    float y_0 = SIZE/2;
    
    _init_();    
    
    glColor3f(0.0, 0.5, 0.7);
    drawEllipse(x_0, y_0, a, b);
    
    glColor3f(1.0, 0.5, 0.7);
    drawEllipse(x_0, y_0, 0.75*a, 0.75*b);
}


void Example()
{
	// For Instructor/TA to fill	
}
