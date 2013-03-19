/*
 * render.h
 *
 *  Created on: 24-Sep-2011
 *      Author: apurv
 */
#include "ifs.h"
#include "Vector4.h"

#ifndef RENDER_H_
#define RENDER_H_


void renderMesh();
void getViewTransformedPoint(Vector4 &p);
void getModelTransformedPoint(Vector4 &p);



#endif /* RENDER_H_ */
