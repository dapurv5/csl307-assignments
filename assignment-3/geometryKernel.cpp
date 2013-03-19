/*
 * geometryKernel.cpp
 *
 *  Created on: 26-Oct-2011
 *      Author: apurv
 */
#include "geometryKernel.h"
#include "Vector4.h"

#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <cassert>
#include <auto_ptr.h>

using namespace std;


extern Triangle triangles[MAX_TRIANGLES];
extern Sphere spheres[MAX_SPHERES];
extern Light lights[MAX_LIGHTS];
extern int iType;
extern int num_triangles;
extern int num_spheres;
extern int num_lights;
extern int index_sphere;
extern int index_triangle;

extern int eX;
extern int eY;
extern int eZ;


/**
 * Returns the 't' corresponding to the intersecting point.
 * @param r
 * @return
 */
double findIntersect(Ray& r){

	int i = 0;

	iType = NONE;
	double t = NO_INTERSECTION;
	double t_min = 100000;

	for(i = 0; i < num_spheres; i++){
		Sphere s = spheres[i];
		t = findIntersectionWithSphere(r,s);

		if(t!=NO_INTERSECTION && t < t_min){
			t_min = t;
			iType = SPHERE;
			index_sphere = i;

		}
	}

	for(i=0; i < num_triangles; i++){

		Triangle triangle = triangles[i];
		t = findIntersectionWithTriangle(r, triangle);
		if(t!=NO_INTERSECTION && t < t_min && t>0.05){
			t_min = t;
			iType = TRIANGLE;
			index_triangle = i;
		}

	}

	//If the value of t_min = 10000 then t_min never got updated, hence NO_INTERSECTION.
	if(t_min == 100000 || t_min==NO_INTERSECTION){
		iType = NONE;
		index_sphere = -1;
		index_triangle = -1;
		return NO_INTERSECTION;

	}else{
		return t_min;
	}
}

double findIntersectionWithSphere(Ray& r, Sphere& s){

	double t_min = NO_INTERSECTION;

	//Coordinates of the centre of the sphere.
	double x_c = s.position[0];
	double y_c = s.position[1];
	double z_c = s.position[2];

	//radius of the sphere.
	double S_r = s.radius;

	//Direction of the ray
	double x_d = r.getXd();
	double y_d = r.getYd();
	double z_d = r.getZd();

	//Start coordinates of the ray.
	double x_0 = r.getX0();
	double y_0 = r.getY0();
	double z_0 = r.getZ0();

	double A = x_d*x_d + y_d*y_d + z_d*z_d;
	double B = 2*(x_d*(x_0-x_c) + y_d*(y_0-y_c) + z_d*(z_0-z_c));
	double C = (x_0-x_c)*(x_0-x_c) + (y_0-y_c)*(y_0-y_c) + (z_0-z_c)*(z_0-z_c) - (S_r*S_r);

	double discr = B*B - 4*A*C ;

	if(discr < 0){
		t_min = NO_INTERSECTION;
		return t_min;

	}else{
		double t_0 = (-1*B - sqrt(discr))/(2*A);
		double t_1 = (-1*B + sqrt(discr))/(2*A);
		if(t_0 < t_1){
			t_min = t_0;

		}else{
			t_min = t_1;
		}
	}

	//TODO: Still to verify this.
	if(t_min < 0){
		t_min = NO_INTERSECTION;
	}

	return t_min;
}


double findIntersectionWithTriangle(Ray& r, Triangle& t){

	double x0 = t.v[0].position[0];
	double y0 = t.v[0].position[1];
	double z0 = t.v[0].position[2];

	double x1 = t.v[1].position[0];
	double y1 = t.v[1].position[1];
	double z1 = t.v[1].position[2];

	double x2 = t.v[2].position[0];
	double y2 = t.v[2].position[1];
	double z2 = t.v[2].position[2];

	auto_ptr<Vector4> edge1(new Vector4());
	auto_ptr<Vector4> edge2(new Vector4());

	edge1->SetVector4(x1-x0, y1-y0, z1-z0, 1);
	edge2->SetVector4(x2-x0, y2-y0, z2-z0, 1);

	//Normal to the triangle namely the values of A,B and C.
	auto_ptr<Vector4> n(edge1->CrossProduct(*edge1, *edge2));
	n->ConvertToUnit();

	float A = n->getX();
	float B = n->getY();
	float C = n->getZ();

	//Get the parameters of the ray.
	double x0_ray = r.getX0();
	double y0_ray = r.getY0();
	double z0_ray = r.getZ0();

	double xd = r.getXd();
	double yd = r.getYd();
	double zd = r.getZd();

	float D = 0.0;
	auto_ptr<Vector4> R(new Vector4());
	R->SetVector4(x0,y0,z0,1);

	D = -1.0*R->DotProduct(*n, *R);

	double num = A*x0_ray + B*y0_ray + C*z0_ray + D;
	double den = A*xd + B*yd + C*zd;

//TODO: Should it be done
//	if(den>0){
//		den = -1.0*den;
//	}

	double t_min = -1.0*(num/den);

//Equivalent to checking if denominator = 0;
//Ray is parallel to the plane, no intersection.
//	if(den == 0.0){
//		t_min = NO_INTERSECTION;
//		return t_min;
//	}


//TODO:TODO:TODO
	if(t_min<0){
		return NO_INTERSECTION;
	}

	//Coordinates of the point of intersection.
	double P_x = getXIntersect(r, t_min);
	double P_y = getYIntersect(r, t_min);
	double P_z = getZIntersect(r, t_min);


	auto_ptr<Vector4> P0(new Vector4());
	P0->SetVector4(x0,y0,z0,1.0f);
	auto_ptr<Vector4> P1(new Vector4());
	P1->SetVector4(x1,y1,z1,1.0f);
	auto_ptr<Vector4> P2(new Vector4());
	P2->SetVector4(x2,y2,z2,1.0f);
	auto_ptr<Vector4> P(new Vector4());
	P->SetVector4(P_x,P_y,P_z,1.0f);

	if(isInsideTheTriangle(*P0, *P1, *P2, *P, *n)){
		return t_min;
	}else{
		return NO_INTERSECTION;
	}

	return t_min;
}

/**
 *
 * @param P0
 * @param P1
 * @param P2
 * @param P
 * @param n
 * @return
 *
 * @see http://www.cs.cornell.edu/courses/cs465/2003fa/homeworks/raytri.pdf
 */
bool isInsideTheTriangle(Vector4& P0, Vector4& P1, Vector4& P2, Vector4& P, Vector4& n){

	//Vector from one vertex to other vertex.
	auto_ptr<Vector4> Edge01(P0.Subtract(P1, P0));
	auto_ptr<Vector4> Edge12(P1.Subtract(P2, P1));
	auto_ptr<Vector4> Edge20(P2.Subtract(P0, P2));

	//Vector from one vertex to the point of intersection.
	auto_ptr<Vector4> X0(P.Subtract(P,P0));
	auto_ptr<Vector4> X1(P.Subtract(P,P1));
	auto_ptr<Vector4> X2(P.Subtract(P,P2));

	//Cross Products of the above two.
	auto_ptr<Vector4> Product1(Edge01->CrossProduct(*Edge01, *X0));
	auto_ptr<Vector4> Product2(Edge12->CrossProduct(*Edge12, *X1));
	auto_ptr<Vector4> Product3(Edge20->CrossProduct(*Edge20, *X2));

	//Dot product with normals.
	double d1 = Product1->DotProduct(*Product1, n);
	double d2 = Product2->DotProduct(*Product2, n);
	double d3 = Product3->DotProduct(*Product3, n);

	if((d1>=0 and d2>=0 and d3>=0) or (d1<=0 and d2<=0 and d3<=0)){
		return true;

	}else{
		return false;
	}
}



/**
 * Finds the x coordinate of the intersection point on this ray with parameter t.
 * @param r
 * @param t
 * @return
 */
double getXIntersect(Ray& r, double t){
	double x_0 = r.getX0();
	double x_d = r.getXd();
	double x_boom = x_0 + t*x_d;
	return x_boom;
}

/**
 * Finds the y coordinate of the intersection point on this ray with parameter t.
 * @param r
 * @param t
 * @return
 */
double getYIntersect(Ray& r, double t){
	double y_0 = r.getY0();
	double y_d = r.getYd();
	double y_boom = y_0 + t*y_d;
	return y_boom;
}


/**
 * Finds the z coordinate of the intersection point on this ray with parameter t.
 * @param r
 * @param t
 * @return
 */
double getZIntersect(Ray& r, double t){
	double z_0 = r.getZ0();
	double z_d = r.getZd();
	double z_boom = z_0 + t*z_d;
	return z_boom;
}


/**
 * Calculates the direction of the light source.
 * @param xS
 * @param yS
 * @param zS
 * @return
 */
Vector4* findLightDirection(double xS, double yS, double zS, Light& light){
	double xL = light.position[0];
	double yL = light.position[1];
	double zL = light.position[2];

	Vector4* L = new Vector4();
	L->SetVector4(xL-xS, yL-yS, zL-zS,1.0);

	return L;
}

Vector4* findViewDirection(double xS, double yS, double zS){

	Vector4* V = new Vector4();
	V->SetVector4(eX-xS, eY-yS, eZ-zS,1.0);
	V->ConvertToUnit();
	return V;
}


Vector4* findReflectedRayDirection(Vector4 &N, Vector4& L){

	Vector4* R;
	Vector4* Rtemp = new Vector4();
	Rtemp->SetVector4(0,0,0,1);
	Rtemp->GetCopyOf(N);
	double N_dot_L = N.DotProduct(N,L);
	Rtemp->Elongate(2*N_dot_L);
	R = Rtemp->Subtract(*Rtemp,L);
	delete Rtemp;
	return R;
}


Vector4* findNormalToTriangle(double xS, double yS, double zS, Triangle& triangle){

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
	double area_P0P1P2 = (0.5*Edge01->CrossProduct(*Edge01, *Edge20)->GetMagnitude());
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

	assert(area_PP0P1 >= 0);//I am here

	double alpha = area_PP1P2/area_P0P1P2;
	double beta = area_PP0P2/area_P0P1P2;
	double gamma = area_PP0P1/area_P0P1P2;


	double n0_x = triangle.v[0].normal[0];
	double n0_y = triangle.v[0].normal[1];
	double n0_z = triangle.v[0].normal[2];
	auto_ptr<Vector4> N0(new Vector4());
	N0->SetVector4(n0_x, n0_y, n0_z, 1);

	double n1_x = triangle.v[1].normal[0];
	double n1_y = triangle.v[1].normal[1];
	double n1_z = triangle.v[1].normal[2];
	auto_ptr<Vector4> N1(new Vector4());
	N1->SetVector4(n1_x, n1_y, n1_z, 1);

	double n2_x = triangle.v[2].normal[0];
	double n2_y = triangle.v[2].normal[1];
	double n2_z = triangle.v[2].normal[2];
	auto_ptr<Vector4> N2(new Vector4());
	N2->SetVector4(n2_x, n2_y, n2_z, 1);

	N0->Elongate(alpha);
	N1->Elongate(beta);
	N2->Elongate(gamma);

	Vector4* normalTemp = N0->Add(*N0, *N1);
	Vector4* normal = N0->Add(*normalTemp, *N2);

	delete normalTemp;
	normal->ConvertToUnit();
	return normal;
}




Vector4* findNormalToSphere(double xS, double yS, double zS, Sphere& sphere){

	//Coordinates of the centre of the sphere.
	double x_c = sphere.position[0];
	double y_c = sphere.position[1];
	double z_c = sphere.position[2];

	//radius of the sphere.
	double S_r = sphere.radius;

	Vector4* normal = new Vector4();
	normal->SetVector4(xS-x_c, yS-y_c, zS-z_c, 1.0);
	normal->ConvertToUnit();
	return normal;

}
