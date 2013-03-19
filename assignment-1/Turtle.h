/* 
 * File:   Turtle.h
 * Author: apurv
 *
 * Created on 28 August, 2011, 2:30 PM
 */

#include <stdbool.h>

#ifndef TURTLE_H
#define	TURTLE_H

   
void Init(float _x,float _y, float _theta);
void Forward(float dist);
void Backward(float dist);
void Right(float _theta);
void Left(float _theta);
void PenDown ( bool down );
void LineColor(float r,float g, float b);
void BGColor(float r,float g, float b);
void LineWidth( float width );
void ResetPosition();
void ClearScreen();

void initCanvas(int size);
    


#endif	/* TURTLE_H */