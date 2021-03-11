/* File name: main.cpp
 *
 * References:
 * 1.   ogldev.org/www/tutorial12/tutorial12.html
 * 2.   glm.g-truc.net/0.9.9/api/modules.html
 * 
 * Intro:
 * A C++ (with OpenGL) program that shows a tetrahedron with various colors 
 * (red, green, blue, black) rotating around the Y axis.
 */

// Include C libraries
#include <cstdio>
#include <cstring>
#include <cmath>
// Include GLEW before other GL libraries
#include <GL/glew.h>
// Include other GL libraries
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
// Include custom libraries
#include "trans.hpp"
#include "persp.hpp"

static char const windowTitle[] = "Perspective Projection";
static int const windowWidth = 1024;
static int const windowHeight = 768;
static GLuint vertexBuffer;
static GLuint indexBuffer;
/* Reference of the uniform variable "world" in shader program. */
static GLuint world;
static char const vertexShaderText[] = R"(
#version 140
#extension GL_ARB_explicit_attrib_location: require
#extension GL_ARB_explicit_uniform_location: require

layout (location = 0) in vec3 position;
uniform mat4 world;
out vec4 color;

void main() {
    gl_Position = world * vec4(position, 1.0);
    color = vec4(clamp(position, 0.0, 1.0), 1.0);
}
)";
static char const fragShaderText[] = R"(
#version 140
#extension GL_ARB_explicit_attrib_location: require
#extension GL_ARB_explicit_uniform_location: require

in vec4 color;
out vec4 fragColor;

void main() {
    fragColor = color;
}
)";
static void display();
static void loadGLUTFuncs();
static void initGLEW();
static void loadVertexBuffer();
static void loadIndexBuffer();
static void loadShaderProgram();
static void addShaderTextToProgram(GLuint, GLenum, char const *);
static void errShowLine(char const *, char const *, ...);
static void errShowProgramLog(char const *, GLuint);
static void errShowShaderLog(char const *, GLuint);

int main(int argc, char **argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(windowTitle);
    // Register GLUT function callbacks
    loadGLUTFuncs();
    // Initialize GLEW
    initGLEW();
    // Set up the background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // Prepare the buffers
    loadVertexBuffer();
    loadIndexBuffer();
    // Prepare the shaders
    loadShaderProgram();
    // Draw the objects
    glutMainLoop();

    return 0;
}

/* Displays the objects to be rendered. */
static void display() {
    /* Speeds of transformation actions. */
    static float const rotateSpeed = 0.1f;
    /* Count of transformation actions. */
    static int transCount = 0;
    /* Transformation of the object to be rendered. */
    static Trans trans;
    /* Perspective that is used to see the object. */
    static Persp persp(windowWidth, windowHeight, 1.0f, 100.0f, 30.0f);
    /* Value of the variable "world" in the shader text. */
    static glm::mat4 worldVal(1.0f);

    transCount += 1;
    // Update the object's transformation
    trans.rot(0.0f, rotateSpeed * transCount, 0.0f);
    trans.pos(0.0f, 0.0f, 5.0f);
    // Find the perspective from which the object is seen
    worldVal = trans.persp(persp);

    glClear(GL_COLOR_BUFFER_BIT);

    // Update the "world" varible in the shader program
    glUniformMatrix4fv(world, 1, GL_FALSE, glm::value_ptr(worldVal));

    glEnableVertexAttribArray(0);
    // Bind the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // Specify the data structure of a vertex to OpenGL
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    // Bind the index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    // Do indexed draws
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glutSwapBuffers();
}

/* Loads the GLUT function callbacks. */
static void loadGLUTFuncs() {
    glutDisplayFunc(display);
    glutIdleFunc(display);
}

/* Initializes GLEW. */
static void initGLEW() {
    char const funcName[] = "initGLEW";

    GLenum result = glewInit();
    if (result != GLEW_OK) {
        errShowLine(funcName, "error: initializing GLEW");
        errShowLine(funcName, "error string: %s", glewGetErrorString(result));
        exit(1);
    }
}

/* Loads the vertex buffer. */
static void loadVertexBuffer() {
    // Create array of vertices
    int const verticesCount = 4;
    glm::vec3 vertices[verticesCount];
    {
        // Fill the array with the vertices info
        glm::vec3 *v = vertices;
        v[0] = glm::vec3(-1.0f, -1.0f, 0.5773f);
        v[1] = glm::vec3(0.0f, -1.0f, -1.1548f);
        v[2] = glm::vec3(1.0f, -1.0f, 0.5773f);
        v[3] = glm::vec3(0.0f, 1.0f, 0.0f);
    }
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

/* Initializes the index buffer */
static void loadIndexBuffer() {
    // Create indices
    int const indicesCount = 12;
    // clang-format off
    unsigned int indices[indicesCount] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 2, 1
    };
    // clang-format on
    // Create, set up, and fill index buffer
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    // clang-format off
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indicesCount * sizeof(int),
        indices,
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
        errShowLine(funcName, "error: creating shader program");
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
        errShowLine(funcName, "error: linking shader program");
        errShowProgramLog(funcName, shaderProgram);
        exit(1);
    }

    // Validate the shader program
    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &result);
    if (result == 0) {
        errShowLine(funcName, "error: validating shader program");
        errShowProgramLog(funcName, shaderProgram);
        exit(1);
    }

    // Use the shader program
    glUseProgram(shaderProgram);

    // Locate the uniform variable "world" in the shader program
    world = glGetUniformLocation(shaderProgram, "world");
    if (world == 0xFFFFFFFF) {
        errShowLine(funcName, "error: locating uniform variable \"world\"");
        exit(1);
    }
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
        errShowLine(funcName, "error: creating shader");
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
        errShowLine(funcName, "error: compiling shader");
        errShowLine(funcName, "shader type: %d", shaderType);
        errShowShaderLog(funcName, shader);
        exit(1);
    }

    // Attach the shader to the shader program
    glAttachShader(shaderProgram, shader);
}

/* Shows an error information line in stderr. */
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

/* Gets and shows the GL shader program info log in stderr. */
static void errShowProgramLog(char const *funcName, GLuint program) {
    int const logLength = 1023;
    GLchar log[logLength + 1] = {0};
    glGetProgramInfoLog(program, logLength, NULL, log);
    errShowLine(funcName, "info log: %s", log);
}

/* Gets and shows the GL shader info log in stderr. */
static void errShowShaderLog(char const *funcName, GLuint shader) {
    int const logLength = 1023;
    GLchar log[logLength + 1] = {0};
    glGetShaderInfoLog(shader, logLength, NULL, log);
    errShowLine(funcName, "info log: %s", log);
}
