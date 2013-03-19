/* 
 * File:   main.c
 * Author: apurv
 *
 * Created on 28 August, 2011, 2:26 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>
#include "GL/gl.h"

#include "Drawings.h"
#include "Turtle.h"


int exampleNum = 0;


/**
 * Initializes the buffers and matrices.
 */
void _init_(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);   //Specify the clear color to black.
    glClear(GL_COLOR_BUFFER_BIT);       //Clear the color buffer.
    glColor3b(1.0, 1.0, 1.0);           //Specify the color of the brush.(openGL is a state machine
                                        //so it remembers this color until it is changed.
}

/**
 * GLUT display callback
 * 
 */
void display( void )
{    
    // Clear Screen
    glClear(GL_COLOR_BUFFER_BIT);    
                
    switch(exampleNum)
    {
        case 1:            
            Square();           
            break;
        case 2:
            Original1();
            break;
        case 3:
            Original2();
            break;
        case 4:
            Example();
            break;
        default:
            break;
    }
    glFlush();
}


/**
 * GLUT callback to handle keyboard events
 * @param key
 * @param x
 * @param y
 */
void keyboard( unsigned char key, int x, int y )
{    
    exampleNum++;
    if(exampleNum > 4){
        exampleNum = exampleNum-4;
    }
    glutPostRedisplay();        //This tells that there is a need to redisplay so call the display() asap.
}

/**
 * Draws the window.
 */
void drawWindow(void)
{    
    glutInitWindowSize (SIZE, SIZE);
    glutInitWindowPosition (50, 100);
    glutCreateWindow ("Turtle Graphics");
    glOrtho(0,SIZE,0,SIZE,-1,1);
}

/**
 * Main
 * @param argc
 * @param argv
 * @return 
 */
int main (int argc, char **argv)
{

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE);
    
    drawWindow();
    
    //Register the GLUT callbacks
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    
    _init_();
    glutMainLoop(); 

    return EXIT_SUCCESS;
}