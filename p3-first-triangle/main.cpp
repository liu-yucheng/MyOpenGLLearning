/* File name: main.cpp
 *
 * References:
 * 1.   ogldev.org/www/tutorial03/tutorial03.html
 * 2.   glm.g-truc.net/0.9.9/api/modules.html
 * 
 * Intro:
 * A C++ program that draws a large white triangle on the window.
 * 
 * Note:
 * This program is only slightly different from the one in part 2.
 */

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

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
    glutCreateWindow("Open a Window");
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

/*
 * Displays contents in the window.
 */
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
    // draw as:             triangles
    // draw from index:     0
    // count to be drawn:   3
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
    glutSwapBuffers();
}

/*
 * Initializes GLEW.
 */
static void initGLEW() {
    GLenum result = glewInit();
    if (result != GLEW_OK) {
        std::cerr << "initGLEW: error occured in GLEW initialization\n"
                  << "initGLEW: error string: " << glewGetErrorString(result)
                  << std::endl;
        exit(1);
    }
}

/*
 * Loads the vertex buffer.
 */
static void loadVertexBuffer() {
    // Create array of vertices
    int const verticesCount = 3;
    glm::vec3 vertices[verticesCount];
    // Fill the array with the vertices info of the triangle
    vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
    vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
    vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);
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
