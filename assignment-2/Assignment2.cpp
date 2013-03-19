//============================================================================
// Name        : Assignment2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Vector4.h"
#include "Matrix4.h"

#include "test.h"
#include "render.h"
#include "transformWorld.h"
#include "transformCamera.h"
#include "transformObject.h"

#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glui.h"

#include <iostream>

using namespace std;

#define SIZE 500
#define TRANSLATE_QUANTA 0.05
#define ROTATE_QUANTA 0.03
#define SCALE_QUANTA 1.2

/*Global data structure that contains all the triangles to be drawn.*/
IFS_DATA* data;

/*Global matrix for model transformation*/
Matrix4 modelMatrix;

/*Global matrix for view transformation*/
Matrix4 viewMatrix;

/*Global u,v and w vector associated with the camera*/
Vector4 uVector;
Vector4 vVector;
Vector4 wVector;

bool ortho;

int window_id;

GLUI_Spinner *lookAtEyeX;
GLUI_Spinner *lookAtEyeY;
GLUI_Spinner *lookAtEyeZ;
GLUI_Spinner *lookAtCenterX;
GLUI_Spinner *lookAtCenterY;
GLUI_Spinner *lookAtCenterZ;
GLUI_Spinner *lookAtUpX;
GLUI_Spinner *lookAtUpY;
GLUI_Spinner *lookAtUpZ;

GLUI_Spinner *rotateX1;
GLUI_Spinner *rotateY1;
GLUI_Spinner *rotateZ1;
GLUI_Spinner *rotateX2;
GLUI_Spinner *rotateY2;
GLUI_Spinner *rotateZ2;


//forward declaration
void doLighting();

void doResize(int a, int b);

void _init_(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);   //Specify the clear color to black.
    glClear(GL_COLOR_BUFFER_BIT);       //Clear the color buffer.
    glColor3b(1.0, 1.0, 1.0);           //Specify the color of the brush.(openGL is a state machine
                                        //so it remembers this color until it is changed.

    modelMatrix.SetMatrix4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    viewMatrix.SetMatrix4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);

    uVector.SetVector4(1,0,0,1);
    vVector.SetVector4(0,1,0,1);
    wVector.SetVector4(0,0,1,1);

    gluLookAt(0,0,10, 0,0,-1, 0,1,0);

    doLighting();

    ortho = true;
}

void doLighting(){
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = {2, 2, 1, -3};
    GLfloat ambient_light[]={1,1,1,1};
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MATERIAL_SIDE_HINT_PGI);
}


void drawWindow(void)
{
    glutInitWindowSize (SIZE, SIZE);
    glutInitWindowPosition (50, 100);
    window_id = glutCreateWindow ("Teapot");
    glEnable(GL_DEPTH_TEST);
}


void display(void){
	// Clear Screen
    glClear(GL_COLOR_BUFFER_BIT);
    renderMesh();
    glutSwapBuffers();
}

void keyboard( unsigned char key, int x, int y )
{
	switch(key){
	case 27:
		_init_();
		break;
	case 'x':
		translateX(TRANSLATE_QUANTA);
		break;
	case 'X':
		translateX(-TRANSLATE_QUANTA);
		break;
	case 'y':
		translateY(TRANSLATE_QUANTA);
		break;
	case 'Y':
			translateY(-TRANSLATE_QUANTA);
			break;
	case 'z':
		translateZ(TRANSLATE_QUANTA);
		break;
	case 'Z':
			translateZ(-TRANSLATE_QUANTA);
			break;
	case 'l':
		rotateX(ROTATE_QUANTA);
		break;
	case 'L':
		rotateX(-ROTATE_QUANTA);
		break;
	case 'm':
		rotateY(ROTATE_QUANTA);
		break;
	case 'M':
		rotateY(-ROTATE_QUANTA);
		break;
	case 'n':
		rotateZ(ROTATE_QUANTA);
		break;
	case 'N':
		rotateZ(-ROTATE_QUANTA);
		break;
	case '1':
		scaleX(SCALE_QUANTA);
		break;
	case '!':
		scaleX(1.0/SCALE_QUANTA);
		break;
	case '2':
		scaleY(SCALE_QUANTA);
		break;
	case '@':
		scaleY(1.0/SCALE_QUANTA);
		break;
	case '3':
		scaleZ(SCALE_QUANTA);
		break;
	case '#':
		scaleZ(1.0/SCALE_QUANTA);
		break;
	case '4':
		scaleX(SCALE_QUANTA);
		scaleY(SCALE_QUANTA);
		scaleZ(SCALE_QUANTA);
		break;
	case '5':
		scaleX(1.0/SCALE_QUANTA);
		scaleY(1.0/SCALE_QUANTA);
		scaleZ(1.0/SCALE_QUANTA);
		break;
	case 'k':
		rotateK(ROTATE_QUANTA);
		break;
	case 'K':
		rotateK(-ROTATE_QUANTA);
		break;
	case 'j':
		rotateJ(ROTATE_QUANTA);
		break;
	case 'J':
		rotateJ(-ROTATE_QUANTA);
		break;
	case 'i':
		rotateI(ROTATE_QUANTA);
		break;
	case 'I':
		rotateI(-ROTATE_QUANTA);
		break;
	case '+':
		scaleIJK(SCALE_QUANTA);
		break;
	case '-':
		scaleIJK(1.0/SCALE_QUANTA);
		break;
	case 'u':
		rotateU(ROTATE_QUANTA);
		break;
	case 'U':
		rotateU(-ROTATE_QUANTA);
		break;
	case 'v':
		rotateV(ROTATE_QUANTA);
		break;
	case 'V':
		rotateV(-ROTATE_QUANTA);
		break;
	case 'w':
		rotateW(ROTATE_QUANTA);
		break;
	case 'W':
		rotateW(-ROTATE_QUANTA);
		break;

	case 'd':
	{
		float eX = lookAtEyeX->get_float_val();
		float eY = lookAtEyeY->get_float_val();
		float eZ = lookAtEyeZ->get_float_val();

		float cX = lookAtCenterX->get_float_val();
		float cY = lookAtCenterY->get_float_val();
		float cZ = lookAtCenterZ->get_float_val();

		float uX = lookAtUpX->get_float_val();
		float uY = lookAtUpY->get_float_val();
		float uZ = lookAtUpZ->get_float_val();

		myGluLookAt(eX,eY,eZ, cX,cY,cZ, uX,uY,uZ);
		//gluLookAt(0.05,0,0, 0,0,-1, 0,1,0);
		//myGluLookAt(0.05,0,0, 0,0,-1, 0,1,0);
		break;
	}
	case 'o':
	{
		float x1 = rotateX1->get_float_val();
		float y1 = rotateY1->get_float_val();
		float z1 = rotateZ1->get_float_val();

		float x2 = rotateX2->get_float_val();
		float y2 = rotateY2->get_float_val();
		float z2 = rotateZ2->get_float_val();

		rotateAboutAxis(x1,y1,z1, x2,y2,z2, ROTATE_QUANTA);
		//rotateAboutAxis(0,0,0, 0,1,0, 0.2);
		break;
	}
	case 'O':
	{
		float x1 = rotateX1->get_float_val();
		float y1 = rotateY1->get_float_val();
		float z1 = rotateZ1->get_float_val();

		float x2 = rotateX2->get_float_val();
		float y2 = rotateY2->get_float_val();
		float z2 = rotateZ2->get_float_val();

		rotateAboutAxis(x1,y1,z1, x2,y2,z2, -ROTATE_QUANTA);
		//rotateAboutAxis(0,0,0, 0,1,0, 0.2);
		break;
	}
	case 't':
		if(ortho){
			ortho = false;
			doResize(SIZE, SIZE);
		}
		else{
			ortho = true;
			doResize(SIZE, SIZE);
		}
	default:
		break;
	}
    glutPostRedisplay();        //This tells that there is a need to redisplay so call the display() asap.
}


void doResize(int newWidth, int newHeight){

  GLfloat aspectRatio = (GLfloat)newWidth / (GLfloat)newHeight;
  glViewport(0, 0, newWidth, newHeight);

  glMatrixMode(GL_PROJECTION_MATRIX);
  glLoadIdentity();

  if(ortho){
	  glOrtho(-1*aspectRatio,1*aspectRatio, -1,1, -1,1);

  }else{
	  gluPerspective(60.0, aspectRatio, 0,5);

  }

  renderMesh();
  doLighting();
  glutPostRedisplay();

  /* WARNING: matrix mode left as projection! */
}


void prepareGUI(){
	GLUI_Master.set_glutIdleFunc(NULL);
	GLUI* glui = GLUI_Master.create_glui("Parameters Window");

	//Panel for taking parameters for gluLookAt().

	GLUI_Panel* lookAtPanel = glui->add_rollout("Look At", false, GLUI_PANEL_EMBOSSED);

	lookAtCenterX = glui->add_spinner_to_panel(lookAtPanel,"centerX",GLUI_SPINNER_FLOAT);
	lookAtCenterX->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	lookAtCenterX->set_speed(1);

	lookAtCenterY = glui->add_spinner_to_panel(lookAtPanel,"centerY",GLUI_SPINNER_FLOAT);
	lookAtCenterY->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	lookAtCenterY->set_speed(1);

	lookAtCenterZ = glui->add_spinner_to_panel(lookAtPanel,"centerZ",GLUI_SPINNER_FLOAT);
	lookAtCenterZ->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	lookAtCenterZ->set_speed(1);

	lookAtEyeX = glui->add_spinner_to_panel(lookAtPanel,"EyeX",GLUI_SPINNER_FLOAT);
	lookAtEyeX->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	lookAtEyeX->set_speed(1);

	lookAtEyeY = glui->add_spinner_to_panel(lookAtPanel,"EyeY",GLUI_SPINNER_FLOAT);
	lookAtEyeY->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	lookAtEyeY->set_speed(1);

	lookAtEyeZ = glui->add_spinner_to_panel(lookAtPanel,"EyeZ",GLUI_SPINNER_FLOAT);
	lookAtEyeZ->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	lookAtEyeZ->set_speed(1);

	lookAtUpX = glui->add_spinner_to_panel(lookAtPanel,"UpX",GLUI_SPINNER_FLOAT);
	lookAtUpX->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	lookAtUpX->set_speed(1);

	lookAtUpY = glui->add_spinner_to_panel(lookAtPanel,"UpY",GLUI_SPINNER_FLOAT);
	lookAtUpY->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	lookAtUpY->set_speed(1);

	lookAtUpZ = glui->add_spinner_to_panel(lookAtPanel,"UpZ",GLUI_SPINNER_FLOAT);
	lookAtUpZ->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	lookAtUpZ->set_speed(1);

	glui->add_column(true);

	//Panel for taking parameters for rotation about arbitrary axis.

	GLUI_Panel* rotateAboutPanel = glui->add_rollout("Rotate About Axis", false, GLUI_PANEL_EMBOSSED);

	rotateX1 = glui->add_spinner_to_panel(rotateAboutPanel,"X1",GLUI_SPINNER_FLOAT);
	rotateX1->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	rotateX1->set_speed(1);

	rotateY1 = glui->add_spinner_to_panel(rotateAboutPanel,"Y1",GLUI_SPINNER_FLOAT);
	rotateY1->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	rotateY1->set_speed(1);

	rotateZ1 = glui->add_spinner_to_panel(rotateAboutPanel,"Z1",GLUI_SPINNER_FLOAT);
	rotateZ1->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	rotateZ1->set_speed(1);

	rotateX2 = glui->add_spinner_to_panel(rotateAboutPanel,"X2",GLUI_SPINNER_FLOAT);
	rotateX2->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	rotateX2->set_speed(1);

	rotateY2 = glui->add_spinner_to_panel(rotateAboutPanel,"Y2",GLUI_SPINNER_FLOAT);
	rotateY2->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	rotateY2->set_speed(1);

	rotateZ2 = glui->add_spinner_to_panel(rotateAboutPanel,"Z2",GLUI_SPINNER_FLOAT);
	rotateZ2->set_float_limits(-2,2,GLUI_LIMIT_CLAMP);
	rotateZ2->set_speed(1);

}


int main(int argc, char** argv) {

//	Test();

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE);

	drawWindow();

	prepareGUI();

	//char* filename = "../Assignment2/resources/teapot.ifs";
	char* filename = "teapot.ifs";
	data = load_ifs_file(filename);

	//Register the GLUT callbacks
	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );
	glutReshapeFunc(doResize);

	_init_();
	glutMainLoop();

	cout << "main ends \n";

	return EXIT_SUCCESS;
}
