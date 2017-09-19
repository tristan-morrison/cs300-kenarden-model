#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

typedef float point[3];

class Window {
  point topLeft;
  float height, width, depth;

public:
  Window(float x, float y, float z);
  void draw();
};

Window::Window(float x, float y, float z) {
  topLeft[0] = x;
  topLeft[1] = y;
  topLeft[2] = z;
  height = 2.0;
  width = 1.0;
  depth = 0;
}

void Window::draw() {
  glPushAttrib(GL_CURRENT_BIT);
  glPushAttrib(GL_POLYGON_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_QUADS);
    glVertex3f(topLeft[0], topLeft[1], topLeft[2]);
    glVertex3f(topLeft[0], topLeft[1] - height, topLeft[2]);
    glVertex3f(topLeft[0] + width, topLeft[1] - height, topLeft[2]);
    glVertex3f(topLeft[0] + width, topLeft[1], topLeft[2]);
  glEnd();
  glPopAttrib();
}
