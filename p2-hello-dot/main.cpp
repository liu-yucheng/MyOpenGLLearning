/* File name: main.cpp
 *
 * References:
 * 1.   ogldev.org/www/tutorial02/tutorial02.html
 * 2.   glm.g-truc.net/0.9.9/api/modules.html
 * 
 * Intro:
 * A C++ program that displays a white "Hello Dot" in the center of the window.
 * 
 * Note:
 * This program uses the GLEW library.
 * To use GLEW, do the following:
 * 1.   Install the GLEW dev package.
 *      (On Ubuntu: sudo apt install libglew-dev)
 * 2.   Include <GL/glew.h> in the source code.
 *      (See the #include statements below.)
 * 3.   Add the -lGLEW option in the compilation command.
 *      (See the Makefile of this program.)
 * 
 * Note 2:
 * The ogldev tutorial this program follows uses a custom library called
 * math_3d.h
 * The header file, math_3d.h, along with its implementation, math_3d.cpp, is
 * available in the GitHub repo at the following URLs:
 * GitHub Repo: github.com/triplepointfive/ogldev
 * math_3d.h:   github.com/triplepointfive/ogldev/blob/master/tutorial40/
 *              math_3d.h
 * math_3d.cpp: github.com/triplepointfive/ogldev/blob/master/tutorial40/
 *              math_3d.cpp
 * 
 * Note 3:
 * This program and the succeeding programs in this repository will use the GLM
 * library instead of the math_3d.h custom library.
 * To use GLM, do the following:
 * 1.   Install the GLM dev package.
 *      (On Ubuntu: sudo apt install libglm-dev)
 * 2.   Include <glm/glm.hpp> header file in the source code.
 *      (See the #include statements below.)
 * 3.   Optionally, include the extensions, <glm/ext.hpp>, in the source code.
 * 4.   Since GLM is a header-only library, no extra linking option is needed
 *      in the compilation command.
 * 
 * Note 4:
 * The Hello Dot's size on screen is 1 by 1 pixel.
 * That means the dot is very tiny in actual size.
 * Please watch out.
 */

// Include C libraries
#include <cstdio>
// Include GLEW before other GL libraries
#include <GL/glew.h>
// Include other GL libraries
#include <GL/freeglut.h>
#include <glm/glm.hpp>

static char const windowTitle[] = "Hello Dot";
static GLuint vertexBuffer;
static void display();
static void initGLEW();
static void loadVertexBuffer();

int main(int argc, char **argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(windowTitle);
    glutDisplayFunc(display);
    // Initialize GLEW
    initGLEW();
    // Set up the background of the window
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // Prepare the objects to be drawn
    loadVertexBuffer();
    // Draw the objects onto the window
    glutMainLoop();

    return 0;
}

/* Displays objects to be rendered. */
static void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(0);
    // Bind the buffer that has the contents to be drawn
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // Specify the data structure of a vertex to OpenGL
    // attribute index:                 0 (default)
    // attribute element count:         3
    // attribute data type:             float
    // make attribute normalized:       false
    // size of vertex data structure:   0 (default)
    // attribute position in vertex:    0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    // Draw the verteices
    // draw as:             points
    // draw from index:     0
    // count to be drawn:   1
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableVertexAttribArray(0);
    glutSwapBuffers();
}

/* Initializes GLEW. */
static void initGLEW() {
    GLenum result = glewInit();
    if (result != GLEW_OK) {
        fprintf(stderr, "initGLEW: error occured in GLEW initialization\n");
        // clang-format off
        fprintf(
            stderr,
            "initGLEW: error string: %s\n",
            glewGetErrorString(result)
        );
        // clang-format on
        fflush(stderr);
        exit(1);
    }
}

/* Initializes the vertex buffer. */
static void loadVertexBuffer() {
    // Create array of vertices
    int const verticesCount = 1;
    glm::vec3 vertices[verticesCount];
    // Fill the array with the info of the point
    vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f);
    // Generate 1 vertex buffer
    glGenBuffers(1, &vertexBuffer);
    // Make the vertex buffer an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // Fill the buffer with the array of vertices
    // clang-format off
    glBufferData(
        GL_ARRAY_BUFFER,
        verticesCount * sizeof(glm::vec3),
        vertices,
        GL_STATIC_DRAW
    );
    // clang-format on
}
