//============================================================================
// Name        : Assignment3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
Author: Frank Pfenning
*/
#include "Ray.h"
#include "geometryKernel.h"
#include "colorKernel.h"
#include "rayTracer.h"
#include "Color.h"

#include "tests/test.h";

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <auto_ptr.h>


#include "pic.h"

using namespace std;


char *filename=0;

//different display modes
#define MODE_DISPLAY 1
#define MODE_JPEG 2
int mode=MODE_DISPLAY;

//you may want to make these smaller for debugging purposes
//#define WIDTH 640
//#define HEIGHT 480

#define WIDTH 320
#define HEIGHT 240

unsigned char buffer[HEIGHT][WIDTH][3];

/**************************************More Parameters*****************************************/

//the field of view of the camera
#define fov 60.0
#define PI 3.1459265

const double z = -1.0;							//The position of our viewing plane.
const double a = WIDTH/HEIGHT;					//The aspect ratio.
const double theta = fov/2.0;
const double width = 2*a*tan((theta*PI)/180.0);	//The height of our viewing window.
const double height = 2*tan((theta*PI)/180.0);	//The height of the viewing window.

int eX = 0;
int eY = 0;
int eZ = 1;

//Intersection type.
int iType = NONE;

//Intersection index
int index_sphere = -1;							//The sphere with which the current ray intersected.
int index_triangle = -1;						//The triangle with which the current ray intersected.

/***************************************More Parameters*****************************************/


Triangle triangles[MAX_TRIANGLES];
Sphere spheres[MAX_SPHERES];
Light lights[MAX_LIGHTS];
double ambient_light[3];

int num_triangles=0;
int num_spheres=0;
int num_lights=0;

void plot_pixel_display(int x,int y,unsigned char r,unsigned char g,unsigned char b);
void plot_pixel_jpeg(int x,int y,unsigned char r,unsigned char g,unsigned char b);
void plot_pixel(int x,int y,unsigned char r,unsigned char g,unsigned char b);

//MODIFY THIS FUNCTION
void draw_scene()
{
  int x,y;

  //simple output
  for(x=-WIDTH/2;x < WIDTH/2;x++)
  {
    glBegin(GL_POINTS);
    for(y=-HEIGHT/2;y < HEIGHT/2;y++)
    {

//    	auto_ptr<Ray> ray(new Ray(x/32.0,y/32.0,zNear, x/32.0, y/32.0, -400));
    	auto_ptr<Ray> ray(new Ray(eX,eY,eZ, x*width/WIDTH, y*height/HEIGHT, 0));

    	auto_ptr<Color> color(traceRay(*ray, 1));
    	int red = color->getRed();
    	int green = color->getGreen();
    	int blue = color->getBlue();
		plot_pixel(x,y, red, green, blue);

    }
    glEnd();
    glFlush();
  }
  printf("Done!\n"); fflush(stdout);
}


void plot_pixel_display(int x,int y,unsigned char r,unsigned char g,unsigned char b)
{
  glColor3f((r)/256.f,(g)/256.f,(b)/256.f);
  glVertex2i(x,y);
}

void plot_pixel_jpeg(int x,int y,unsigned char r,unsigned char g,unsigned char b)
{
  buffer[HEIGHT-y-1][x][0]=r;
  buffer[HEIGHT-y-1][x][1]=g;
  buffer[HEIGHT-y-1][x][2]=b;
}

void plot_pixel(int x,int y,unsigned char r,unsigned char g, unsigned char b)
{
  plot_pixel_display(x,y,r,g,b);
  if(mode == MODE_JPEG)
      plot_pixel_jpeg(x,y,r,g,b);
}

void save_jpg()
{
  Pic *in = NULL;

//  in = pic_alloc(640, 480, 3, NULL);
//  printf("Saving JPEG file: %s\n", filename);
//
//  memcpy(in->pix,buffer,3*WIDTH*HEIGHT);
//  if (jpeg_write(filename, in))
//    printf("File saved Successfully\n");
//  else
//    printf("Error in Saving\n");
//
//  pic_free(in);

}

void parse_check(char *expected,char *found)
{
  if(strcasecmp(expected,found))
    {
      char error[100];
      printf("Expected '%s ' found '%s '\n",expected,found);
      printf("Parse error, abnormal abortion\n");
      exit(0);
    }

}

void parse_doubles(FILE*file, char *check, double p[3])
{
  char str[100];
  fscanf(file,"%s",str);
  parse_check(check,str);
  fscanf(file,"%lf %lf %lf",&p[0],&p[1],&p[2]);
  printf("%s %lf %lf %lf\n",check,p[0],p[1],p[2]);
}

void parse_rad(FILE*file,double *r)
{
  char str[100];
  fscanf(file,"%s",str);
  parse_check("rad:",str);
  fscanf(file,"%lf",r);
  printf("rad: %f\n",*r);
}

void parse_shi(FILE*file,double *shi)
{
  char s[100];
  fscanf(file,"%s",s);
  parse_check("shi:",s);
  fscanf(file,"%lf",shi);
  printf("shi: %f\n",*shi);
}

int loadScene(char *argv)
{
  FILE *file = fopen(argv,"r");
  int number_of_objects;
  char type[50];
  int i;
  Triangle t;
  Sphere s;
  Light l;
  fscanf(file,"%i",&number_of_objects);

  printf("number of objects: %i\n",number_of_objects);
  char str[200];

  parse_doubles(file,"amb:",ambient_light);

  for(i=0;i < number_of_objects;i++)
    {
      fscanf(file,"%s\n",type);
      printf("%s\n",type);
      if(strcasecmp(type,"triangle")==0)
	{

	  printf("found triangle\n");
	  int j;

	  for(j=0;j < 3;j++)
	    {
	      parse_doubles(file,"pos:",t.v[j].position);
	      parse_doubles(file,"nor:",t.v[j].normal);
	      parse_doubles(file,"dif:",t.v[j].color_diffuse);
	      parse_doubles(file,"spe:",t.v[j].color_specular);
	      parse_shi(file,&t.v[j].shininess);
	    }

	  if(num_triangles == MAX_TRIANGLES)
	    {
	      printf("too many triangles, you should increase MAX_TRIANGLES!\n");
	      exit(0);
	    }
	  triangles[num_triangles++] = t;
	}
      else if(strcasecmp(type,"sphere")==0)
	{
	  printf("found sphere\n");

	  parse_doubles(file,"pos:",s.position);
	  parse_rad(file,&s.radius);
	  parse_doubles(file,"dif:",s.color_diffuse);
	  parse_doubles(file,"spe:",s.color_specular);
	  parse_shi(file,&s.shininess);

	  if(num_spheres == MAX_SPHERES)
	    {
	      printf("too many spheres, you should increase MAX_SPHERES!\n");
	      exit(0);
	    }
	  spheres[num_spheres++] = s;
	}
      else if(strcasecmp(type,"light")==0)
	{
	  printf("found light\n");
	  parse_doubles(file,"pos:",l.position);
	  parse_doubles(file,"col:",l.color);

	  if(num_lights == MAX_LIGHTS)
	    {
	      printf("too many lights, you should increase MAX_LIGHTS!\n");
	      exit(0);
	    }
	  lights[num_lights++] = l;
	}
      else
	{
	  printf("unknown type in scene description:\n%s\n",type);
	  exit(0);
	}
    }
  return 0;
}

void display()
{

}

void init()
{
  glMatrixMode(GL_PROJECTION);
  //glOrtho(0,WIDTH,0,HEIGHT,1,-1);
  glOrtho(-WIDTH/2,WIDTH/2,-HEIGHT/2,HEIGHT/2,1,-1);//TODO:Check if this is correct.
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
}

void idle()
{
  //hack to make it only draw once
  static int once=0;
  if(!once)
  {
      draw_scene();
      if(mode == MODE_JPEG)
    	  save_jpg();
  }
  once=1;
}

int main (int argc, char ** argv)
{

//  if (argc<2 || argc > 3)
//  {
//    printf ("usage: %s <scenefile> [jpegname]\n", argv[0]);
//    exit(0);
//  }
//  if(argc == 3)
//    {
//      mode = MODE_JPEG;
//      filename = argv[2];
//    }
//  else if(argc == 2)
//    mode = MODE_DISPLAY;


	mode = MODE_DISPLAY;
//	char* scene_file = "../Assignment3/resources/test2.scene";
//	char* scene_file = "../Assignment3/resources/spheres.scene";
	char* scene_file = "../Assignment3/resources/table.scene";
//	char* scene_file = "../Assignment3/resources/SIGGRAPH.scene";



	glutInit(&argc,argv);
	//  loadScene(argv[1]);
	loadScene(scene_file);

	Test();

	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	int window = glutCreateWindow("Ray Tracer");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
}
