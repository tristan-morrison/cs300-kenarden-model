//
// Authors: Blaire Bosely, Tristan Lopus
// For: CS300 - Computer Graphics
//
//

/* -----------------------------------
A model of one part, replicable of Kenarden Lodge. Intended for use in constructing a larger model of the entire building.

------------------------------------*/

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "window.h"
#include "smallWindow.h"
#include "door.h"

void drawBase();

void myDisplay() {
  glClear(GL_COLOR_BUFFER_BIT);

  drawBase();

  Window window1(-4.0, 2.5, 0);
  Window window2(-2.75, 2.5, 0);
  Window window3(-4.0, -.25, 0);
  Window window4(-2.75, -.25, 0);
  Window window5(1.75, 2.5, 0);
  Window window6(3.0, 2.5, 0);
  Window window7(1.75, -.25, 0);
  Window window8(3.0, -.25, 0);
  window1.draw();
  window2.draw();
  window3.draw();
  window4.draw();
  window5.draw();
  window6.draw();
  window7.draw();
  window8.draw();

  SmallWindow smallWindow1(-1.0, 2.5, 0);
  SmallWindow smallWindow2(-0.25, 2.5, 0);
  SmallWindow smallWindow3(0.5, 2.5, 0);
  SmallWindow smallWindow4(-1.0, 1.0, 0);
  SmallWindow smallWindow5(-0.25, 1.0, 0);
  SmallWindow smallWindow6(0.5, 1.0, 0);
  smallWindow1.draw();
  smallWindow2.draw();
  smallWindow3.draw();
  smallWindow4.draw();
  smallWindow5.draw();
  smallWindow6.draw();

  Door door(-0.625, -1.0, 0);
  door.draw();

  glFlush();
}

void drawBase() {
  float height = 7.0;
  float width = 10.0;
  float depth = 12.0;

  float xOffset, yOffset, zOffset;
  yOffset = -3.5;

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    // rectangle 1
    glVertex3f(-1 * (width / 2), 0 + yOffset, 0);
    glVertex3f((width / 2), 0 + yOffset, 0);
    glVertex3f((width / 2), height + yOffset, 0);
    glVertex3f(-1 * (width / 2), height + yOffset, 0);

    glColor3f(0.0, 1.0, 0.0);
    // rectangle 2
    glVertex3f(width / 2, 0 + yOffset, 0);
    glVertex3f(width / 2, 0 + yOffset, -1 * depth);
    glVertex3f(width / 2, height + yOffset, -1 * depth);
    glVertex3f(width / 2, height + yOffset, 0);

    glColor3f(0.0, 0.0, 1.0);
    // rectangle 3
    glVertex3f(-1 * (width / 2), 0 + yOffset, -1 * depth);
    glVertex3f((width / 2), 0 + yOffset, -1 * depth);
    glVertex3f((width / 2), height + yOffset, -1 * depth);
    glVertex3f(-1 * (width / 2), height + yOffset, -1 * depth);

    glColor3f(0.0, 0.0, 0.0);
    // rectangle 4
    glVertex3f(-1 * (width / 2), 0 + yOffset, 0);
    glVertex3f(-1 * (width / 2), 0 + yOffset, -1 * depth);
    glVertex3f(-1 * (width / 2), height + yOffset, -1 * depth);
    glVertex3f(-1 * (width / 2), height + yOffset, 0);
  glEnd();

  glPointSize(5.0);
  glBegin(GL_POINTS);
    glVertex3f(-1 * (width / 2), 0 + yOffset, 0);
    glVertex3f((width / 2), 0 + yOffset, 0);
    glVertex3f((width / 2), height + yOffset, 0);
    glVertex3f(-1 * (width / 2), height + yOffset, 0);
    glVertex3f(width / 2, 0 + yOffset, 0);
    glVertex3f(width / 2, 0 + yOffset, -1 * depth);
    glVertex3f(width / 2, height + yOffset, -1 * depth);
    glVertex3f(width / 2, height + yOffset, 0);
  glEnd();

}

void drawRoof() {

  glBegin(GL_QUADS);

  glEnd();
}

void myinit() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-20.0, 20.0, -20.0, 20.0, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glClearColor (1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0,0.0,0.0);

  // default
  // gluLookAt(0, 0, 1, 0, 0, 0, 0, 1., 0.);
  // side view
  gluLookAt(5.0,1,5,0.,0.,0.,0.,1.,0.);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize(500, 500);
  glutCreateWindow("Knard");
  glutDisplayFunc(myDisplay);
  myinit();
  glutMainLoop();
}
