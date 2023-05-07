#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// window dimentions
int WIDTH = 512;
int HEIGHT = 512;

enum DisplayType {
    Isometric,
    Cavalier,
    Cabinet
};

// default display
DisplayType display = Isometric;

// initialize cube
void drawUnitCube() {
  glColor3f(0.0f,0.0f,0.0f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 1.0f);
  glVertex3f(1.0f, 0.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f(1.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 0.0f, 1.0f);
  glVertex3f(1.0f, 0.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 0.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f(1.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f(1.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 0.0f);
  glEnd();
}

// initialize axes
void drawCoordinateAxisZ() {	// draw z axis
  glLineWidth(2);
  glBegin(GL_LINES);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 2.0f);
  glEnd();
  glLineWidth(1);

  // z-axis tip
  glBegin(GL_TRIANGLES);
  glVertex3f(0.0f, 0.0f, 2.0f);
  glVertex3f(-0.05f, 0.05f, 1.9f);
  glVertex3f(0.05f, 0.05f, 1.9f);
  glVertex3f(0.0f, 0.0f, 2.0f);
  glVertex3f(0.05f, -0.05f, 1.9f);
  glVertex3f(-0.05f, -0.05f, 1.9f);
  glVertex3f(0.0f, 0.0f, 2.0f);
  glVertex3f(0.05f, 0.05f, 1.9f);
  glVertex3f(0.05f, -0.05f, 1.9f);
  glVertex3f(0.0f, 0.0f, 2.0f);
  glVertex3f(-0.05f, -0.05f, 1.9f);
  glVertex3f(-0.05f,  0.05f, 1.9f);
  glEnd();
  glBegin(GL_POLYGON);
  glVertex3f(0.05f, -0.05f, 1.9f);
  glVertex3f(0.05f,  0.05f, 1.9f);
  glVertex3f(-0.05f,  0.05f, 1.9f);
  glVertex3f(-0.05f, -0.05f, 1.9f);
  glEnd();
}

void drawCoordinateAxisX() {	// draw x axis
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    drawCoordinateAxisZ();
    glPopMatrix();
}

void drawCoordinateAxisY() {	// draw y axis
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    drawCoordinateAxisZ();
    glPopMatrix();
}

/* render event */
void handleRender() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float m[16];	// identity matrix
    glGetFloatv(GL_MODELVIEW_MATRIX, m);

	// calculate projection angles
    switch(display) {
        case Isometric: {
            float angleA = (M_PI / 180.0f) * (45.0f);
            float angleB = (M_PI / 180.0f) * (35.264);
            m[0] = sin(angleA);
            m[1] = cos(angleB)/2;
            m[2] = -sin(angleB);

            m[5] = cos(angleB);
            m[6] = sin(angleB);

            m[8] = sin(angleA);
            m[9] = -cos(angleB)/2;
            m[10] = sin(angleB);

            break;
        }
        case Cavalier: {
            float angle = (M_PI / 180.0f) * (-45.0f);
            m[8] = -cos(angle);
            m[9] = sin(angle);

            break;
        }
        case Cabinet: {
            float angle = (M_PI / 180.0f) * (-45.0f);
            m[8] = -cos(angle)/2.0f;
            m[9] = sin(angle)/2.0;

            break;
        }
    }

    glLoadMatrixf(m);

	// draw axes
    glColor3f(0.0f, 0.0f, 1.0f);
    drawCoordinateAxisZ();
    glColor3f(0.0f, 1.0f, 0.0f);
    drawCoordinateAxisY();
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCoordinateAxisX();

    drawUnitCube();

    // do the buffer swap
    glutSwapBuffers();
    glutReportErrors();
}

/* reshape event */
void handleReshape(int w, int h) {
    float aspect = (float) w / (float) h;

	// resize projection
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4.0*aspect, 4.0*aspect, -4.0, 4.0, -10.0, 10.0);
}

/* key press event */
void handleKeydown(unsigned char key, int x, int y) {
    if (key=='1') {
        display = Isometric;
        glutSetWindowTitle("* 1: Isometric, 2: Cavalier, 3: Cabinet");
    }
    if (key=='2') {
       display = Cavalier;
       glutSetWindowTitle("1: Isometric, * 2: Cavalier, 3: Cabinet");
    }
    if (key=='3') {
        display = Cabinet;
        glutSetWindowTitle("1: Isometric, 2: Cavalier, * 3: Cabinet");
     }

    handleRender();
}

/* main */
int main(int argc, char* argv[]) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("* 1: Isometric, 2: Cavalier, 3: Cabinet");
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);    // white background

    glutDisplayFunc(handleRender);
    glutReshapeFunc(handleReshape);
    glutKeyboardFunc(handleKeydown);

    glutMainLoop();

    return 0;
}
