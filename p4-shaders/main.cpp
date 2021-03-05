/* File name: main.cpp
 *
 * References:
 * 1.   ogldev.org/www/tutorial04/tutorial04.html
 * 2.   glm.g-truc.net/0.9.9/api/modules.html
 * 
 * Intro:
 * A C++ (with GLSL) program that draws a medium-size red triangle in the
 * center of the window.
 * 
 * Note:
 * The tutorial that this program follows uses OpenGL 3.3 with GLSL 3.30.
 * However, this program is developed in a runtime environment that does not
 * support OpenGL 3.3 and GLSL 3.30.
 * This program is developed in Ubuntu 20.04 LTS on VirtualBox 6, with OpenGL
 * 3.1 and GLSL 1.40 / 3.30 ES supports.
 * GLSL 3.30 ES is for embedded systems; it runs in the above development
 * environment, but it requires some slight changes in the shader texts; Thus,
 * it is not chosen for this program.
 * As such, this program choose to use GLSL 1.40 with extensions.
 * See the 2 shader texts below.
 * 
 * Note 2:
 * This program uses C++ raw strings to store shader texts.
 * C++ raw string is a language feature that is supported in C++ 11 and above.
 */

// Include C libraries
#include <cstdio>
#include <cstring>
// Include C++ libraries
#include <iostream>
// Include GLEW before other GL libraries
#include <GL/glew.h>
// Include other GL libraries
#include <GL/freeglut.h>
#include <glm/glm.hpp>

static GLuint vertexBuffer;
static char const vertexShaderText[] = R"(
#version 140
#extension GL_ARB_explicit_attrib_location: require
#extension GL_ARB_explicit_uniform_location: require

layout (location = 0) in vec3 position;

void main() {
    gl_Position = vec4(
        0.5 * position.x,
        0.5 * position.y,
        position.z,
        1.0
    );
}
)";
static char const fragShaderText[] = R"(
#version 140
#extension GL_ARB_explicit_attrib_location: require
#extension GL_ARB_explicit_uniform_location: require

out vec4 fragColor;

void main() {
    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
)";
static void display();
static void initGLEW();
static void loadVertexBuffer();
static void loadShaderProgram();
static void addShaderTextToProgram(GLuint, GLenum, char const *);
static void errShowLine(char const *, char const *, ...);
static void errShowProgramLog(char const *, GLuint);
static void errShowShaderLog(char const *, GLuint);

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
    // Prepare the shaders
    loadShaderProgram();
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
    char const funcName[] = "initGLEW";

    GLenum result = glewInit();
    if (result != GLEW_OK) {
        errShowLine(funcName, "error occured when initializing GLEW");
        errShowLine(funcName, "error string: %s", glewGetErrorString(result));
        exit(1);
    }
}

/*
 * Initializes the vertex buffer.
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

/* Prepares the shader program. */
static void loadShaderProgram() {
    // Create a shader program
    char const funcName[] = "loadShaderProgram";

    GLuint shaderProgram = glCreateProgram();
    if (shaderProgram == 0) {
        errShowLine(funcName, "error occured when creating shader program");
        exit(1);
    }

    // Attach the vertex and fragment shaders to the program
    // clang-format off
    addShaderTextToProgram(
        shaderProgram,
        GL_VERTEX_SHADER,
        vertexShaderText
    );
    addShaderTextToProgram(
        shaderProgram,
        GL_FRAGMENT_SHADER,
        fragShaderText
    );
    // clang-format on

    GLint result = 0;
    // Link the shader program
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
    if (result == 0) {
        errShowLine(funcName, "error occured when linking shader program");
        errShowProgramLog(funcName, shaderProgram);
        exit(1);
    }

    // Validate the shader program
    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &result);
    if (result == 0) {
        errShowLine(funcName, "error occured when validating shader program");
        errShowProgramLog(funcName, shaderProgram);
        exit(1);
    }

    // Use the shader program
    glUseProgram(shaderProgram);
}

/* Attaches a shader text to a shader program */
// clang-format off
static void addShaderTextToProgram(
    GLuint shaderProgram,
    GLenum shaderType,
    char const *shaderText
) {
    // clang-format on
    char const funcName[] = "addShaderTextToProgram";

    // Create a shader
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0) {
        errShowLine(funcName, "error occured when creating shader");
        exit(1);
    }

    // Feed the shader text to the shader
    int const shaderTextsCount = 1;
    GLchar const *glShaderTexts[shaderTextsCount];
    glShaderTexts[0] = shaderText;
    GLint shaderTextLengths[shaderTextsCount];
    shaderTextLengths[0] = strlen(shaderText);
    glShaderSource(shader, shaderTextsCount, glShaderTexts, shaderTextLengths);

    // Compile the shader
    glCompileShader(shader);
    GLint compilationResult = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationResult);
    if (compilationResult == 0) {
        errShowLine(funcName, "error occured when compiling shader");
        errShowLine(funcName, "shader type: %d", shaderType);
        errShowShaderLog(funcName, shader);
        exit(1);
    }

    // Attach the shader to the shader program
    glAttachShader(shaderProgram, shader);
}

/*
 * Show an error information line in stderr.
 */
static void errShowLine(char const *funcName, char const *format, ...) {
    va_list args;
    va_start(args, format);
    // Print "<funcName>: "
    fprintf(stderr, "%s: ", funcName);
    // Print the error information line
    vfprintf(stderr, format, args);
    // Print a new line character
    fprintf(stderr, "\n");
    // Flush the stderr file onto the terminal
    fflush(stderr);
    va_end(args);
}

/*
 * Get and show the GL shader program info log in stderr.
 */
static void errShowProgramLog(char const *funcName, GLuint program) {
    int const logLength = 1023;
    GLchar log[logLength + 1] = {0};
    glGetProgramInfoLog(program, logLength, NULL, log);
    errShowLine(funcName, "info log: %s", log);
}

/*
 * Get and show the GL shader info log in stderr.
 */
static void errShowShaderLog(char const *funcName, GLuint shader) {
    int const logLength = 1023;
    GLchar log[logLength + 1] = {0};
    glGetShaderInfoLog(shader, logLength, NULL, log);
    errShowLine(funcName, "info log: %s", log);
}
