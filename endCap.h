#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

typedef float point[3];

class EndCap {
  point topLeft;
  float height, width, depth;

public:
  EndCap(float x, float y, float z);
  void draw();
};

EndCap::EndCap(float x, float y, float z) {
  topLeft[0] = x;
  topLeft[1] = y;
  topLeft[2] = z;
  sideHeight = 7.0;
  roofHeight = 7.0;
  width = 12.0;
  depth = 0;
}

void EndCap::draw() {
  glPushAttrib(GL_CURRENT_BIT);
  glPushAttrib(GL_POLYGON_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(0.04, 0.37, 0.37);
  glBegin(GL_QUADS);
    glVertex3f(topLeft[0], topLeft[1], topLeft[2]);
    glVertex3f(topLeft[0], topLeft[1] - height, topLeft[2]);
    glVertex3f(topLeft[0] + width, topLeft[1] - height, topLeft[2]);
    glVertex3f(topLeft[0] + width, topLeft[1], topLeft[2]);
  glEnd();
  glPopAttrib();
}
