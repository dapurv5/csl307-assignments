/*
 * Color.cpp
 *
 *  Created on: 29-Oct-2011
 *      Author: apurv
 */

#include "Color.h"
#include <iostream>
#include <math.h>

using namespace std;

Color::Color(int r, int g, int b) {
	this->red = r;
	this->green = g;
	this->blue = b;
}

int Color::getBlue()
{
    return blue;
}

int Color::getGreen()
{
    return green;
}

int Color::getRed()
{
    return red;
}

void Color::setBlue(int blue)
{
    this->blue = blue;
}

void Color::setGreen(int green)
{
    this->green = green;
}

void Color::setRed(int red)
{
    this->red = red;
}

Color::~Color() {
	// TODO Auto-generated destructor stub
}


void Color::printColor(){
	cout<<"\n ("<<red<<", "<<green<<", "<<blue<<") ";
}


void Color::addMoreRed(int deltaRed){
	if(this->red + deltaRed >= 255){
		this->red = 255;
	}else{
		this->red = this->red + deltaRed;
	}
}

void Color::addMoreGreen(int deltaGreen){
	if(this->green + deltaGreen >= 255){
		this->green = 255;
	}else{
		this->green = this->green + deltaGreen;
	}
}

void Color::addMoreBlue(int deltaBlue){
	if(this->blue + deltaBlue >= 255){
		this->blue = 255;
	}else{
		this->blue = this->blue + deltaBlue;
	}
}
