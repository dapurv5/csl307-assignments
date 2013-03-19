#include "Turtle.h"

#include <GL/glut.h>
#include <GL/gl.h>

#include <math.h>
#include <stdbool.h>

float PI = 3.141592654f;

float x=0;
float y=0;
float theta=0;
bool draw=true;

/**
 * Initializes the current position and orientation.
 * @param _x
 * @param _y
 * @param _theta
 */
void Init(float _x,float _y, float _theta)
{
    x = _x;
    y = _y;
    theta = _theta;
}

/**
 * Moves forward dist units along the current orientation.
 * @param dist
 */
void Forward(float dist)
{   
    float thetaRadians = (theta/180.0f)*PI;
    
    float lx = dist*cos(thetaRadians);
    float ly = dist*sin(thetaRadians);
    
    float x1 = x + lx;
    float y1 = y + ly;
    
    float x0 = x;
    float y0 = y;        
    
    if(draw){
        glBegin(GL_LINE_STRIP);   
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
        glEnd();
    }
    
    x = x1;
    y = y1;
    
    glFlush();
}


/**
 * Moves backward dist units along the current orientation.
 * @param dist
 */
void Backward(float dist)
{
    float thetaRadians = (theta/180.0f)*PI;
    float x1 = x - dist*cos(thetaRadians);
    float y1 = y - dist*sin(thetaRadians);
    
    float x0 = x;
    float y0 = y;
    
    if(draw){
        glBegin(GL_LINE_STRIP);
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
        glEnd();
    }
    
    x = x1;
    y = y1;        
    
    glFlush();
}


void Right(float _theta)
{    
    theta = theta - _theta;
    if(theta < 0){
        theta = 360 + theta;
    }
}

void Left(float _theta)
{
    theta = theta + _theta;
    if(theta > 360){
        theta = theta - 360;
    }    
}

void PenDown( bool down ) 
{    
    draw = down;
}

/**
 * Sets the color of the line.
 * @param r
 * @param g
 * @param b
 */
void LineColor(float r,float g, float b)
{
    GLfloat red = (GLfloat)r;
    GLfloat green = (GLfloat)g;
    GLfloat blue = (GLfloat)b;
    glColor3f(red, green, blue);
}


void BGColor(float r,float g, float b)
{    
    glClearColor((GLclampf)r, (GLclampf)g, (GLclampf)b, (GLclampf)0.5);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

/**
 * Sets the line width.
 * @param width
 */
void LineWidth( float width ) 
{
    glLineWidth(width);
}

/**
 * 
 */
void ResetPosition() 
{
    x = 0;
    y = 0;
    theta = 0;
}

void ClearScreen()
{
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
    //glColor3b(1.0, 1.0, 1.0);
}