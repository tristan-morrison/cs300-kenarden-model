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
#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "window.h"
#include "smallWindow.h"
#include "door.h"
#include "dormer.h"
#include "smallDormer.h"

/* Declarations */
void drawBase(GLenum mode);
void drawRoof(GLenum mode);
void drawSlice();
void drawEndCap(bool onRightSide, GLenum mode);
void drawGuides();
void drawGrass();

/* Globals */
// base dimensions
float baseHeight = 7.0;
float baseWidth = 10.0;
float baseDepth = 12.0;
float baseXOffset, baseZOffset = 0;
float baseYOffset = -3.5;
// roof dimensions
float roofHeight = 4.0;
float roofWidth = 10.0;
float roofDepth = 12.0;
float roofZOffset = 0.0;
// rotation variables
static int moving = 0, startx = 0, starty = 0;
static GLfloat angle = 0;
static GLfloat angle2 = 0;

/*
 * myDisplay
 * Callback for GLUT display. Draws, grass, slices of building, and end caps of building
 */
void myDisplay() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glRotatef(angle, 0.0, 1.0, 0.0);
  glRotatef(angle2, 5.0, 0.0, 5.0);

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

  glFlush();
  glPopMatrix();
}

/*
 * drawSlice
 * Draws one part — or "slice" — of the building. These slices are pieced together to create the entire building.
 */
void drawSlice() {

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0, 1.0);

  // draw the four polygons that form the sides of the building
  drawBase(GL_FILL);

  // disable polygon offsetting, so that windows drawn in the same plane as the walls will display properly
  glDisable(GL_POLYGON_OFFSET_FILL);

  // define all windows
  Window window1(-4.0, 2.5, 0);
  Window window2(-2.75, 2.5, 0);
  Window window3(-4.0, -.25, 0);
  Window window4(-2.75, -.25, 0);
  Window window5(1.75, 2.5, 0);
  Window window6(3.0, 2.5, 0);
  Window window7(1.75, -.25, 0);
  Window window8(3.0, -.25, 0);

  // calls each window's draw() function twice, once with GL_FILL, and once with GL_LINE to outline each window
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

  // define all SmallWindows
  SmallWindow smallWindow1(-1.0, 2.5, 0);
  SmallWindow smallWindow2(-0.25, 2.5, 0);
  SmallWindow smallWindow3(0.5, 2.5, 0);
  SmallWindow smallWindow4(-1.0, 1.0, 0);
  SmallWindow smallWindow5(-0.25, 1.0, 0);
  SmallWindow smallWindow6(0.5, 1.0, 0);

  // call each SmallWindow's draw() function twice, once with GL_FILL and once with GL_LINE
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


  // define and draw the Door.
  // In hindsight, since there's only one door, we didn't really have to create a separate class for doors...
  Door door(-0.625, -1.0, 0);
  door.draw();

  // Define two Dormers
  Dormer dormer_left(-1 * ((baseWidth / 2) + baseXOffset - 2), baseHeight + baseYOffset, 0 + baseZOffset);
  Dormer dormer_right(((baseWidth / 2) + baseXOffset - 2), baseHeight + baseYOffset, 0 + baseZOffset);

  // draw each dormer twice, once with GL_FILL and once with GL_LINE
  dormer_left.draw(GL_FILL);
  dormer_left.draw(GL_LINE);
  dormer_right.draw(GL_FILL);
  dormer_right.draw(GL_LINE);

  // draw the SmallDormer, and draw with both GL_FILL and GL_LINE
  SmallDormer smallDormer_center(baseXOffset, baseHeight + baseYOffset + 0.5, 0 + baseZOffset);
  smallDormer_center.draw(GL_FILL);
  smallDormer_center.draw(GL_LINE);

  drawRoof(GL_FILL);
}

/*
 * drawBase
 * draws the four quadrilaterals that form the base of the building
 */
void drawBase(GLenum mode) {

  glPolygonMode(GL_FRONT_AND_BACK, mode);
  // if outlining, set color to black; else set to brick color
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

    // rectangle 2
    glVertex3f(baseWidth / 2, 0 + baseYOffset, 0);
    glVertex3f(baseWidth / 2, 0 + baseYOffset, -1 * baseDepth);
    glVertex3f(baseWidth / 2, baseHeight + baseYOffset, -1 * baseDepth);
    glVertex3f(baseWidth / 2, baseHeight + baseYOffset, 0);

    // rectangle 3
    glVertex3f(-1 * (baseWidth / 2), 0 + baseYOffset, -1 * baseDepth);
    glVertex3f((baseWidth / 2), 0 + baseYOffset, -1 * baseDepth);
    glVertex3f((baseWidth / 2), baseHeight + baseYOffset, -1 * baseDepth);
    glVertex3f(-1 * (baseWidth / 2), baseHeight + baseYOffset, -1 * baseDepth);

    // rectangle 4
    glVertex3f(-1 * (baseWidth / 2), 0 + baseYOffset, 0);
    glVertex3f(-1 * (baseWidth / 2), 0 + baseYOffset, -1 * baseDepth);
    glVertex3f(-1 * (baseWidth / 2), baseHeight + baseYOffset, -1 * baseDepth);
    glVertex3f(-1 * (baseWidth / 2), baseHeight + baseYOffset, 0);
  glEnd();

  glFlush();
}

/*
 * drawRoof
 * draws the roof of the building
 */
void drawRoof(GLenum mode) {

  glPolygonMode(GL_FRONT_AND_BACK, mode);
  // if drawing outline, set color to black; else set color to brick color
  if (mode == GL_LINE) {
    glColor3f(0.0, 0.0, 0.0);
  } else {
    glColor3f(roofColor[0],roofColor[1],roofColor[2]);
  }

  glBegin(GL_QUADS);
    // front side
    glVertex3f(-1 * (baseWidth / 2), (baseHeight + baseYOffset), 0 + roofZOffset);
    glVertex3f(baseWidth / 2, (baseHeight + baseYOffset), 0 + roofZOffset);
    glVertex3f(baseWidth / 2, (baseHeight + baseYOffset) + roofHeight, (-1 * (roofDepth / 2)) + roofZOffset);
    glVertex3f(-1 * (baseWidth / 2), (baseHeight + baseYOffset) + roofHeight, (-1 * (roofDepth / 2)) + roofZOffset);

    // back side
    glVertex3f(-1 * (baseWidth / 2), (baseHeight + baseYOffset), (-1 * roofDepth) + roofZOffset);
    glVertex3f(baseWidth / 2, (baseHeight + baseYOffset), (-1 * roofDepth) + roofZOffset);
    glVertex3f(baseWidth / 2, (baseHeight + baseYOffset) + roofHeight, (-1 * (roofDepth / 2)) + roofZOffset);
    glVertex3f(-1 * (baseWidth / 2), (baseHeight + baseYOffset) + roofHeight, (-1 * (roofDepth / 2)) + roofZOffset);

  glEnd();
}

/*
 * drawEndCap
 * Draws the ends of the two segments of the building
 */
void drawEndCap(bool onRightSide, GLenum mode) {
  int sideMultiplier;
  // if drawing the left side of the building, the x coordinates will be multiplied by sideMultiplier=-1 to make them negative
  if (onRightSide) {
    sideMultiplier = 1;
  } else {
    sideMultiplier = -1;
  }

  if (mode == GL_LINE) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.0, 0.0, 0.0);
  } else {
    // glEnable(GL_POLYGON_OFFSET_FILL);
    // glPolygonOffset(1.0, 1.0);

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

/*
 * drawGrass
 * Draws grass in front of building. Alternates between two shades of green to mimic lines of a mowed lawn
 */
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
  glEnd();
}

void myinit() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-35.0, 35.0, -35.0, 35.0, 1.0, 50.0);
  glMatrixMode(GL_MODELVIEW);
	glColor3f(0.0,0.0,0.0);
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glDepthRange(0.0f, 1.0f);
  gluLookAt(10, 7, 25, -30, 0, 0, 0, 1., 0.);
}

//Quits the program using q key
void Keyboard (unsigned char key, int x, int y){

  #pragma unsued (x,y);

  switch (key){
      case 'q':
      exit (0);
      break;
  }
}

//Rotating with Left Button on Mouse
static void mouse (int button, int state, int x, int y)
{
if (button == GLUT_LEFT_BUTTON){
  if (state == GLUT_DOWN){
    moving = 1;
    startx = x;
    starty = y;
    }
    if (state == GLUT_UP){
      moving = 0;
    }
}
}

static void motion (int x, int y)
{
  if(moving){
    angle = (angle + (( x - startx) / 2));
    if (angle > 360) {
      angle = angle - 360;
    }
    angle2 = (angle2 + ((y - starty) / 2));
    if (angle2 > 360) {
      angle2 = angle2 - 360;
    }
    startx = x;
    starty = y;
    glutPostRedisplay();
   }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Kenarden Lodge");
  glutDisplayFunc(myDisplay);
  glutKeyboardFunc(Keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  myinit();
  glutMainLoop();
}
