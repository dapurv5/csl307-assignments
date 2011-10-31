/*
 * interpolator.cpp
 *
 *  Created on: 01-Nov-2011
 *      Author: apurv
 */

#include "interpolator.h"

#include <auto_ptr.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>


using namespace std;


double interpolateShininess(double x, double y, double z, Triangle& triangle){
	double N1 = triangle.v[0].shininess;
	double N2 = triangle.v[1].shininess;
	double N3 = triangle.v[2].shininess;

	return interpolateScalar(x,y,z, triangle, N1, N2, N3);
}

Vector4* interpolateKd(double x, double y, double z, Triangle& triangle){

	Vector4* kd_P0 = new Vector4();
	Vector4* kd_P1 = new Vector4();
	Vector4* kd_P2 = new Vector4();

	kd_P0->SetVector4(triangle.v[0].color_diffuse[0], triangle.v[0].color_diffuse[1],triangle.v[0].color_diffuse[2], 1.0);

	kd_P1->SetVector4(triangle.v[1].color_diffuse[0], triangle.v[1].color_diffuse[1],triangle.v[0].color_diffuse[2], 1.0);

	kd_P2->SetVector4(triangle.v[2].color_diffuse[0], triangle.v[2].color_diffuse[1],triangle.v[2].color_diffuse[2], 1.0);

	return interpolateVectors(x,y,z, triangle, *kd_P0, *kd_P1, *kd_P2);
}


Vector4* interpolateKs(double x, double y, double z, Triangle& triangle){

	Vector4* ks_P0 = new Vector4();
	Vector4* ks_P1 = new Vector4();
	Vector4* ks_P2 = new Vector4();

	ks_P0->SetVector4(triangle.v[0].color_specular[0], triangle.v[0].color_specular[1],triangle.v[0].color_specular[2], 1.0);

	ks_P1->SetVector4(triangle.v[1].color_specular[0], triangle.v[1].color_specular[1],triangle.v[0].color_specular[2], 1.0);

	ks_P2->SetVector4(triangle.v[2].color_specular[0], triangle.v[2].color_specular[1],triangle.v[2].color_specular[2], 1.0);

	return interpolateVectors(x,y,z, triangle, *ks_P0, *ks_P1, *ks_P2);
}







Vector4* interpolateVectors(double xS, double yS, double zS, Triangle& triangle, Vector4& N0,
		Vector4& N1, Vector4& N2){

	double x0 = triangle.v[0].position[0];
	double y0 = triangle.v[0].position[1];
	double z0 = triangle.v[0].position[2];

	double x1 = triangle.v[1].position[0];
	double y1 = triangle.v[1].position[1];
	double z1 = triangle.v[1].position[2];

	double x2 = triangle.v[2].position[0];
	double y2 = triangle.v[2].position[1];
	double z2 = triangle.v[2].position[2];

	//Calculate the vertices of the triangle.
	auto_ptr<Vector4> P0(new Vector4());
	P0->SetVector4(x0,y0,z0,1.0f);
	auto_ptr<Vector4> P1(new Vector4());
	P1->SetVector4((float)x1,(float)y1,(float)z1,1.0f);
	auto_ptr<Vector4> P2(new Vector4());
	P2->SetVector4((float)x2,(float)y2,(float)z2,1.0f);
	auto_ptr<Vector4> P(new Vector4());
	P->SetVector4((float)xS,(float)yS,(float)zS,1.0f);


	//Vector from one vertex to other vertex.
	auto_ptr<Vector4> Edge01(P0->Subtract(*P1, *P0));
	auto_ptr<Vector4> Edge12(P1->Subtract(*P2, *P1));
	auto_ptr<Vector4> Edge20(P2->Subtract(*P0, *P2));

	//Area of the complete triangle.
	double area_P0P1P2 =   0.5*Edge01->CrossProduct(*Edge01, *Edge20)->GetMagnitude()  ;
	area_P0P1P2 = (area_P0P1P2);

	assert(area_P0P1P2 > 0);

	//Area of PP0P2
	auto_ptr<Vector4> EdgePP2(new Vector4());
	EdgePP2->SetVector4(xS-x2, yS-y2, zS-z2,1);
	double area_PP0P2 = (0.5*Edge20->CrossProduct(*Edge20, *EdgePP2)->GetMagnitude());
	assert(area_PP0P2 >= 0.0);

	//Area of PP1P2
	double area_PP1P2 = (0.5 * EdgePP2->CrossProduct(*EdgePP2, *Edge12)->GetMagnitude());
	assert(area_PP1P2 >= 0);

	//Area of PP0P1
	auto_ptr<Vector4> EdgePP0(new Vector4());
	EdgePP0->SetVector4(xS-x0, yS-y0, zS-z0,1);
	double area_PP0P1 = (0.5*Edge01->CrossProduct(*Edge01, *EdgePP0)->GetMagnitude());
	assert(area_PP0P1 >= 0);

	double alpha = area_PP1P2/area_P0P1P2;
	double beta = area_PP0P2/area_P0P1P2;
	double gamma = area_PP0P1/area_P0P1P2;

	N0.Elongate(alpha);
	N1.Elongate(beta);
	N2.Elongate(gamma);

	Vector4* normalTemp = N0.Add(N0, N1);
	Vector4* normal = N0.Add(*normalTemp, N2);

	delete normalTemp;
	//NOTE: This error took a lot of time.A result of copy pasting code.
	//TODO: Do not copy paste code.
	//normal->ConvertToUnit();
	return normal;
}





double interpolateScalar(double xS, double yS, double zS, Triangle& triangle, double N1, double N2,
						double N3){
	double x0 = triangle.v[0].position[0];
	double y0 = triangle.v[0].position[1];
	double z0 = triangle.v[0].position[2];

	double x1 = triangle.v[1].position[0];
	double y1 = triangle.v[1].position[1];
	double z1 = triangle.v[1].position[2];

	double x2 = triangle.v[2].position[0];
	double y2 = triangle.v[2].position[1];
	double z2 = triangle.v[2].position[2];

	//Calculate the vertices of the triangle.
	auto_ptr<Vector4> P0(new Vector4());
	P0->SetVector4(x0,y0,z0,1.0f);
	auto_ptr<Vector4> P1(new Vector4());
	P1->SetVector4((float)x1,(float)y1,(float)z1,1.0f);
	auto_ptr<Vector4> P2(new Vector4());
	P2->SetVector4((float)x2,(float)y2,(float)z2,1.0f);
	auto_ptr<Vector4> P(new Vector4());
	P->SetVector4((float)xS,(float)yS,(float)zS,1.0f);


	//Vector from one vertex to other vertex.
	auto_ptr<Vector4> Edge01(P0->Subtract(*P1, *P0));
	auto_ptr<Vector4> Edge12(P1->Subtract(*P2, *P1));
	auto_ptr<Vector4> Edge20(P2->Subtract(*P0, *P2));

	//Area of the complete triangle.
	double area_P0P1P2 =   0.5*Edge01->CrossProduct(*Edge01, *Edge20)->GetMagnitude()  ;
	area_P0P1P2 = (area_P0P1P2);

	assert(area_P0P1P2 > 0);

	//Area of PP0P2
	auto_ptr<Vector4> EdgePP2(new Vector4());
	EdgePP2->SetVector4(xS-x2, yS-y2, zS-z2,1);
	double area_PP0P2 = (0.5*Edge20->CrossProduct(*Edge20, *EdgePP2)->GetMagnitude());
	assert(area_PP0P2 >= 0.0);

	//Area of PP1P2
	double area_PP1P2 = (0.5 * EdgePP2->CrossProduct(*EdgePP2, *Edge12)->GetMagnitude());
	assert(area_PP1P2 >= 0);

	//Area of PP0P1
	auto_ptr<Vector4> EdgePP0(new Vector4());
	EdgePP0->SetVector4(xS-x0, yS-y0, zS-z0,1);
	double area_PP0P1 = (0.5*Edge01->CrossProduct(*Edge01, *EdgePP0)->GetMagnitude());
	assert(area_PP0P1 >= 0);

	double alpha = area_PP1P2/area_P0P1P2;
	double beta = area_PP0P2/area_P0P1P2;
	double gamma = area_PP0P1/area_P0P1P2;

	double result = alpha*N1 + beta*N2 + gamma*N3;
	return result;
}

