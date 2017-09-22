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
#include "colors.h"
#include "window.h"
#include "smallWindow.h"
#include "door.h"
#include "dormer.h"
#include "smallDormer.h"

void drawBase(GLenum mode);
void drawRoof(GLenum mode);
void drawSlice();
void drawEndCap(bool onRightSide, GLenum mode);
void drawGuides();
void drawGrass();

/* Globals */
float baseHeight = 7.0;
float baseWidth = 10.0;
float baseDepth = 12.0;
float baseXOffset, baseZOffset = 0;
float baseYOffset = -3.5;

float roofHeight = 4.0;
float roofWidth = 10.0;
float roofDepth = 12.0;
float roofZOffset = 0.0;

void myDisplay() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  drawGuides();
  drawGrass();

  drawSlice();
  glTranslatef(10.0, 0.0, 0.0);
  drawSlice();
  glTranslatef(-20.0, 0.0, 0.0);
  drawSlice();
  glTranslatef(-10.0, 0.0, 0.0);
  drawSlice();
  glTranslatef(30.0, 0.0, 0.0);
  drawEndCap(1, GL_FILL);
  glTranslatef(-30.0, 0.0, 0.0);
  drawEndCap(0, GL_FILL);

  glRotatef(90, 0, 5, 0);
  glTranslatef(-5.0, 0.0, 7.0);
  drawSlice();
  glTranslatef(-10.0, 0.0, 0.0);
  drawSlice();
  glTranslatef(-10.0, 0.0, 0.0);
  drawSlice();
  glTranslatef(-10.0, 0.0, 0.0);
  drawEndCap(1, GL_FILL);
  glTranslatef(45.0, 0.0, 0.0);
  drawEndCap(0, GL_FILL);


  glFlush();
}

void drawSlice() {

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0, 1.0);

  drawBase(GL_FILL);
  // drawBase(GL_LINE);

  glDisable(GL_POLYGON_OFFSET_FILL);

  Window window1(-4.0, 2.5, 0);
  Window window2(-2.75, 2.5, 0);
  Window window3(-4.0, -.25, 0);
  Window window4(-2.75, -.25, 0);
  Window window5(1.75, 2.5, 0);
  Window window6(3.0, 2.5, 0);
  Window window7(1.75, -.25, 0);
  Window window8(3.0, -.25, 0);
  window1.draw(GL_FILL);
  window2.draw(GL_FILL);
  window3.draw(GL_FILL);
  window4.draw(GL_FILL);
  window5.draw(GL_FILL);
  window6.draw(GL_FILL);
  window7.draw(GL_FILL);
  window8.draw(GL_FILL);
  window1.draw(GL_LINE);
  window2.draw(GL_LINE);
  window3.draw(GL_LINE);
  window4.draw(GL_LINE);
  window5.draw(GL_LINE);
  window6.draw(GL_LINE);
  window7.draw(GL_LINE);
  window8.draw(GL_LINE);

  SmallWindow smallWindow1(-1.0, 2.5, 0);
  SmallWindow smallWindow2(-0.25, 2.5, 0);
  SmallWindow smallWindow3(0.5, 2.5, 0);
  SmallWindow smallWindow4(-1.0, 1.0, 0);
  SmallWindow smallWindow5(-0.25, 1.0, 0);
  SmallWindow smallWindow6(0.5, 1.0, 0);
  smallWindow1.draw(GL_FILL);
  smallWindow1.draw(GL_LINE);
  smallWindow2.draw(GL_FILL);
  smallWindow2.draw(GL_LINE);
  smallWindow3.draw(GL_FILL);
  smallWindow3.draw(GL_LINE);
  smallWindow4.draw(GL_FILL);
  smallWindow4.draw(GL_LINE);
  smallWindow5.draw(GL_FILL);
  smallWindow5.draw(GL_LINE);
  smallWindow6.draw(GL_FILL);
  smallWindow6.draw(GL_LINE);

  Door door(-0.625, -1.0, 0);
  door.draw();

  Dormer dormer_left(-1 * ((baseWidth / 2) + baseXOffset - 2), baseHeight + baseYOffset, 0 + baseZOffset);
  Dormer dormer_right(((baseWidth / 2) + baseXOffset - 2), baseHeight + baseYOffset, 0 + baseZOffset);
  dormer_left.draw(GL_FILL);
  dormer_left.draw(GL_LINE);
  dormer_right.draw(GL_FILL);
  dormer_right.draw(GL_LINE);

  SmallDormer smallDormer_center(baseXOffset, baseHeight + baseYOffset + 0.5, 0 + baseZOffset);
  smallDormer_center.draw(GL_FILL);
  smallDormer_center.draw(GL_LINE);

  drawRoof(GL_FILL);
  // drawRoof(GL_LINE);
}

void drawBase(GLenum mode) {

  glPolygonMode(GL_FRONT_AND_BACK, mode);
  if (mode == GL_LINE) {
    glColor3f(0.0, 0.0, 0.0);
  } else {
    glColor3f(brickColor[0], brickColor[1], brickColor[2]);
  }
  glBegin(GL_QUADS);
    // rectangle 1
    glVertex3f(-1 * (baseWidth / 2), 0 + baseYOffset, 0);
    glVertex3f((baseWidth / 2), 0 + baseYOffset, 0);
    glVertex3f((baseWidth / 2), baseHeight + baseYOffset, 0);
    glVertex3f(-1 * (baseWidth / 2), baseHeight + baseYOffset, 0);

    // glColor3f(0.0, 1.0, 0.0);
    // rectangle 2
    glVertex3f(baseWidth / 2, 0 + baseYOffset, 0);
    glVertex3f(baseWidth / 2, 0 + baseYOffset, -1 * baseDepth);
    glVertex3f(baseWidth / 2, baseHeight + baseYOffset, -1 * baseDepth);
    glVertex3f(baseWidth / 2, baseHeight + baseYOffset, 0);

    // glColor3f(0.0, 0.0, 1.0);
    // rectangle 3
    glVertex3f(-1 * (baseWidth / 2), 0 + baseYOffset, -1 * baseDepth);
    glVertex3f((baseWidth / 2), 0 + baseYOffset, -1 * baseDepth);
    glVertex3f((baseWidth / 2), baseHeight + baseYOffset, -1 * baseDepth);
    glVertex3f(-1 * (baseWidth / 2), baseHeight + baseYOffset, -1 * baseDepth);

    // glColor3f(0.0, 0.0, 0.0);
    // rectangle 4
    glVertex3f(-1 * (baseWidth / 2), 0 + baseYOffset, 0);
    glVertex3f(-1 * (baseWidth / 2), 0 + baseYOffset, -1 * baseDepth);
    glVertex3f(-1 * (baseWidth / 2), baseHeight + baseYOffset, -1 * baseDepth);
    glVertex3f(-1 * (baseWidth / 2), baseHeight + baseYOffset, 0);
  glEnd();

  // glPointSize(5.0);
  // glBegin(GL_POINTS);
  //   glVertex3f(-1 * (baseWidth / 2), 0 + baseYOffset, 0);
  //   glVertex3f((baseWidth / 2), 0 + baseYOffset, 0);
  //   glVertex3f((baseWidth / 2), baseHeight + baseYOffset, 0);
  //   glVertex3f(-1 * (baseWidth / 2), baseHeight + baseYOffset, 0);
  //   glVertex3f(baseWidth / 2, 0 + baseYOffset, 0);
  //   glVertex3f(baseWidth / 2, 0 + baseYOffset, -1 * baseDepth);
  //   glVertex3f(baseWidth / 2, baseHeight + baseYOffset, -1 * baseDepth);
  //   glVertex3f(baseWidth / 2, baseHeight + baseYOffset, 0);
  // glEnd();
  glFlush();
}

void drawRoof(GLenum mode) {

  glPolygonMode(GL_FRONT_AND_BACK, mode);
  if (mode == GL_LINE) {
    glColor3f(0.0, 0.0, 0.0);
  } else {
    glColor3f(roofColor[0],roofColor[1],roofColor[2]);
  }

  glBegin(GL_QUADS);
    glVertex3f(-1 * (baseWidth / 2), (baseHeight + baseYOffset), 0 + roofZOffset);
    glVertex3f(baseWidth / 2, (baseHeight + baseYOffset), 0 + roofZOffset);
    glVertex3f(baseWidth / 2, (baseHeight + baseYOffset) + roofHeight, (-1 * (roofDepth / 2)) + roofZOffset);
    glVertex3f(-1 * (baseWidth / 2), (baseHeight + baseYOffset) + roofHeight, (-1 * (roofDepth / 2)) + roofZOffset);

    glVertex3f(-1 * (baseWidth / 2), (baseHeight + baseYOffset), (-1 * roofDepth) + roofZOffset);
    glVertex3f(baseWidth / 2, (baseHeight + baseYOffset), (-1 * roofDepth) + roofZOffset);
    glVertex3f(baseWidth / 2, (baseHeight + baseYOffset) + roofHeight, (-1 * (roofDepth / 2)) + roofZOffset);
    glVertex3f(-1 * (baseWidth / 2), (baseHeight + baseYOffset) + roofHeight, (-1 * (roofDepth / 2)) + roofZOffset);

  glEnd();
}

void drawEndCap(bool onRightSide, GLenum mode) {
  int sideMultiplier;
  if (onRightSide) {
    sideMultiplier = 1;
  } else {
    sideMultiplier = -1;
  }

  if (mode == GL_LINE) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.0, 0.0, 0.0);
  } else {
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0);
    glDisable(GL_POLYGON_OFFSET_FILL);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(brickColor[0], brickColor[1], brickColor[2]);
  }

  glBegin(GL_QUADS);
    glVertex3f(sideMultiplier * (baseWidth / 2), 0 + baseYOffset, 0);
    glVertex3f(sideMultiplier * (baseWidth / 2), 0 + baseYOffset, -1 * baseDepth);
    glVertex3f(sideMultiplier * (baseWidth / 2), baseYOffset + baseHeight + 1.0, -1 * baseDepth);
    glVertex3f(sideMultiplier * (baseWidth / 2), baseYOffset + baseHeight + 1.0, 0);
  glEnd();

  glBegin(GL_TRIANGLES);
    glVertex3f(sideMultiplier * (baseWidth / 2), baseYOffset + baseHeight + 1.0, 0);
    glVertex3f(sideMultiplier * (baseWidth / 2), baseYOffset + baseHeight + 1.0, -1 * baseDepth);
    glVertex3f(sideMultiplier * (baseWidth / 2), baseYOffset + baseHeight + roofHeight + 1.0, -1 * (baseDepth / 2));
  glEnd();
}

void drawGuides() {
  glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50, 0, 0);
    glVertex3f(50, 0, 0);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, -50, 0);
    glVertex3f(0, 50, 0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, -50);
    glVertex3f(0, 0, 50);


  glEnd();
}

void drawGrass() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_QUADS);
  glColor3f(0.41, 0.74, 0.18);
    glVertex3f(-14.0, baseYOffset, 0.0);
    glVertex3f(50.0, baseYOffset, 0.0);
    glVertex3f(50.0, baseYOffset, 5.0);
    glVertex3f(-14.0, baseYOffset, 5.0);

  glColor3f(0.49, 0.76, 0.18);
    glVertex3f(-14.0, baseYOffset, 5.0);
    glVertex3f(50.0, baseYOffset, 5.0);
    glVertex3f(50.0, baseYOffset, 10.0);
    glVertex3f(-14.0, baseYOffset, 10.0);

  glColor3f(0.41, 0.74, 0.18);
    glVertex3f(-14.0, baseYOffset, 10.0);
    glVertex3f(50.0, baseYOffset, 10.0);
    glVertex3f(50.0, baseYOffset, 15.0);
    glVertex3f(-14.0, baseYOffset, 15.0);

  glColor3f(0.49, 0.76, 0.18);
    glVertex3f(-14.0, baseYOffset, 15.0);
    glVertex3f(50.0, baseYOffset, 15.0);
    glVertex3f(50.0, baseYOffset, 20.0);
    glVertex3f(-14.0, baseYOffset, 20.0);

  glColor3f(0.41, 0.74, 0.18);
    glVertex3f(-14.0, baseYOffset, 20.0);
    glVertex3f(50.0, baseYOffset, 20.0);
    glVertex3f(50.0, baseYOffset, 25.0);
    glVertex3f(-14.0, baseYOffset, 25.0);

  glColor3f(0.49, 0.76, 0.18);
    glVertex3f(-14.0, baseYOffset, 25.0);
    glVertex3f(50.0, baseYOffset, 25.0);
    glVertex3f(50.0, baseYOffset, 30.0);
    glVertex3f(-14.0, baseYOffset, 30.0);

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0, 1.0);
  glColor3f(0.36, 0.4, 0.4);
    // glVertex3f(-10, baseYOffset + 0.5, 0);
    // glVertex3f(, baseYOffset + 0.5, 0);
    // glVertex3f(10, baseYOffset + 0.5, 30);
    // glVertex3f(20, baseYOffset + 0.5, 40);
  glDisable(GL_POLYGON_OFFSET_FILL);
  glEnd();
}

void myinit() {
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  glOrtho(-40.0, 40.0, -40.0, 40.0, 1.0, 40.0);
  glMatrixMode(GL_MODELVIEW);
  // glClearColor (1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0,0.0,0.0);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glDepthRange(0.0f, 1.0f);

  // default
  // gluLookAt(0, 0, 1, 0, 0, 0, 0, 1., 0.);
  // front, right side view
  // gluLookAt(5.0,1,10,0.,0.,0.,0.,1.,0.);
  // gluLookAt(10.0,1,10,0.,0.,0.,0.,1.,0.);
  // left, right side view
  // gluLookAt(-5.0,1,5,0.,0.,0.,0.,1.,0.);
  // side view
  // gluLookAt(9.0,0,-0,0.,0.,0.,0.,1.,0.);
  // top side
  // gluLookAt(0, 5, 15, -15, 0, 0, 0, 1., 0.);
  // top more to the side
  gluLookAt(10, 7, 25, -30, 0, 0, 0, 1., 0.);
  // gluLookAt(-5, 5, 0, -5, 0, 0, 1,


}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Knard");
  glutDisplayFunc(myDisplay);
  myinit();
  glutMainLoop();
}
