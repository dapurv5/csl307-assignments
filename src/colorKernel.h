/*
 * colorKernel.h
 *
 *  Created on: 27-Oct-2011
 *      Author: apurv
 */
#include "Color.h"
#include "geometryKernel.h"

#ifndef COLORKERNEL_H_
#define COLORKERNEL_H_

int getRed(double I,double ka_red, double kd_red, double ks_red, double LN, double RV, double shininess);
int getGreen(double I,double ka_green, double kd_green, double ks_green, double LN, double RV, double shininess);
int getBlue(double I,double ka_blue, double kd_blue, double ks_blue, double LN, double RV, double shininess);

double getAmbientRed(double ka_red);
double getAmbientGreen(double ka_green);
double getAmbientBlue(double ka_blue);

double getDiffuseRed(double I, double kd_red, double LN);
double getDiffuseGreen(double I, double kd_green, double LN);
double getDiffuseBlue(double I, double kd_blue, double LN);

double getSpecularRed(double I, double ks_red, double LN, double RV, double shininess);
double getSpecularGreen(double I, double ks_green, double LN, double RV, double shininess);
double getSpecularBlue(double I, double ks_blue, double LN, double RV, double shininess);

Color* getColor(double x, double y, double z, double t, int depth);
bool isShadowed(double x, double y, double z, Light& currentLight);

double distance(double x1, double y1, double z1, double x2, double y2, double z2);

#endif /* COLORKERNEL_H_ */
