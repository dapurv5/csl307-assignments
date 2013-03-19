/*
 * interpolator.h
 *
 *  Created on: 01-Nov-2011
 *      Author: apurv
 */
#include "Vector4.h"
#include "geometryKernel.h"

#ifndef INTERPOLATOR_H_
#define INTERPOLATOR_H_

double interpolateShininess(double x, double y, double z, Triangle& triangle);

Vector4* interpolateKd(double x, double y, double z, Triangle& triangle);
Vector4* interpolateKs(double x, double y, double z, Triangle& triangle);

Vector4* interpolateVectors(double xS, double yS, double zS, Triangle& triangle, Vector4& N1,
		Vector4& N2, Vector4& N3);


double interpolateScalar(double xS, double yS, double zS, Triangle& triangle, double N1, double N2,
						double N3);

#endif /* INTERPOLATOR_H_ */
