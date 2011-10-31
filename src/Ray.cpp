/*
 * Ray.cpp
 *
 *  Created on: 26-Oct-2011
 *      Author: apurv
 */

#include <math.h>
#include "Ray.h"
#include <iostream>

using namespace std;

Ray::Ray(double x0, double y0, double z0, double x1, double y1, double z1) {

	this->x0 = x0;
	this->y0 = y0;
	this->z0 = z0;

	this->xd = x1-x0;
	this->yd = y1-y0;
	this->zd = z1-z0;

	this->Normalize();
}

void Ray::Normalize(void){
	double magn = sqrt(xd*xd + yd*yd + zd*zd);

	this->xd = xd/magn;
	this->yd = yd/magn;
	this->zd = zd/magn;
}

void Ray::printRay(void){
	cout<<"Ray (x0= "<<x0<<", y0= "<<y0<<", z0= "<<z0<<", xd= "<<xd<<", yd= "<<yd<<", zd= "<<zd<<" )"<<endl;
}

double Ray::getX0() const
{
    return x0;
}

double Ray::getXd() const
{
    return xd;
}

double Ray::getY0() const
{
    return y0;
}

double Ray::getYd() const
{
    return yd;
}

double Ray::getZ0() const
{
    return z0;
}

double Ray::getZd() const
{
    return zd;
}

void Ray::setX0(double x0)
{
    this->x0 = x0;
}

void Ray::setXd(double xd)
{
    this->xd = xd;
}

void Ray::setY0(double y0)
{
    this->y0 = y0;
}

void Ray::setYd(double yd)
{
    this->yd = yd;
}

void Ray::setZ0(double z0)
{
    this->z0 = z0;
}

void Ray::setZd(double zd)
{
    this->zd = zd;
}

Ray::~Ray() {
	// TODO Auto-generated destructor stub
}
