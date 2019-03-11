// Name:
// Quarter, Year:
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <vector>
#include <cstdio>
#include <math.h>
#include "vec.h"
#include <iostream>

using namespace std;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

std::vector<float> control_pointsX;
std::vector<float> control_pointsY;

float factorial (int n)
{
	if (n <= 1 ) return 1;
	else return n * factorial(n - 1);
}

float combination (int n,int k)
{
	return ((factorial(n)) / (factorial(k) * factorial(n - k)));
}

float binomaial (int n, int k, float t)
{
	float result = 0;
	
	if (k == 0)
	{
		for (int i = 0; i < n; i++)
		{
			result += combination(n,i) * pow(t,i) * pow((1-t),(n-i)) * control_pointsX[i];
		}
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			result += combination(n,i) * pow(t,i) * pow((1-t),(n-i)) * control_pointsY[i];
		}
	}

	
	return result;
}

void GL_render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();

    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);
    // just for example, remove if desired
	if (control_pointsX.size() != 0)
	{
		//glVertex2f(-.5f,-.5f);
		//glVertex2f(.5f,-.5f);
		float Bx = 0, By = 0;
		vec2 F;
		F[0] = 0;
		F[1] = 0;
		for(float i = 0 ; i <= 1 ; i += 0.00001)
		{
			Bx = binomaial(control_pointsX.size(),0,i);
			By = binomaial(control_pointsY.size(),1,i);
			for (int j = 0; j < control_pointsX.size(); j++)
			{
				F[0] += Bx * control_pointsX[j];
				F[1] += By * control_pointsY[j]; 
			}
			glVertex2f(Bx, By);
		}
	}
    //glVertex2f(.5f,.5f);
    //glVertex2f(-.5f,.5f);
    glEnd();
    glFlush();
}

void GL_mouse(int button,int state,int x,int y)
{
    y=WINDOW_HEIGHT-y;
    GLdouble mv_mat[16];
    GLdouble proj_mat[16];
    GLint vp_mat[4];
    glGetDoublev(GL_MODELVIEW_MATRIX,mv_mat);
    glGetDoublev(GL_PROJECTION_MATRIX,proj_mat);
    glGetIntegerv(GL_VIEWPORT,vp_mat);

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        double px,py,dummy_z; // we don't care about the z-value but need something to pass in
        gluUnProject(x,y,0,mv_mat,proj_mat,vp_mat,&px,&py,&dummy_z);
        glutPostRedisplay();
		
		control_pointsX.push_back(px);
		control_pointsY.push_back(py);
	}
	
	
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
    glutInit(argc, argv);
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //glMatrixMode(GL_PROJECTION_MATRIX);
    //glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glutCreateWindow("CS 130 - <Benjamin West>");
    glutDisplayFunc(GL_render);
    glutMouseFunc(GL_mouse);
}

int main(int argc, char** argv)
{
    GLInit(&argc, argv);
    glutMainLoop();
    return 0;
}
