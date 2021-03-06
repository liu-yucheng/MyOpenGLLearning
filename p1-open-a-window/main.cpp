/* File name: main.cpp
 *
 * Reference:
 * http://ogldev.org/www/tutorial01/tutorial01.html
 * 
 * Intro:
 * A C++ program that initializes the OpenGL context and displays a blank
 * window on the screen.
 */

#include <GL/freeglut.h>

static char const windowTitle[] = "Open a Window";
static void display();

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(windowTitle);
    glutDisplayFunc(display);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutMainLoop();

    return 0;
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}
