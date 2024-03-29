/* File name: main.hpp
 * 
 * Intro:
 * C++ header of a program that shows a tetrahedron with various colors (red,
 * green, blue, black) rotating around the Y axis.
 * 
 * References:
 * 1. ogldev.org/www/tutorial12/tutorial12.html
 * 2. glm.g-truc.net/0.9.9/api/modules.html
 */

/* Copyright 2022 Yucheng Liu. GNU GPL3 license.
 * GNU GPL3 license copy: https://www.gnu.org/licenses/gpl-3.0.txt */

// Include C++ libraries
#include <iostream>
#include <fstream>
#include <string>
// Include C libraries
#include <cstdio>
#include <cstring>
#include <cmath>
// Include GLEW before other GL libraries
#include <GL/glew.h>
// Include other GL/GL-related libraries
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
// Include custom libraries
#include "trans.hpp"
#include "persp.hpp"
#include "pipeline.hpp"

// Define variables
static char const winTitle[] = "Perspective Projection";
static int const winWidth = 1024;
static int const winHeight = 768;
static GLuint vertexBuffer;
static GLuint indexBuffer;
static char const vsFileName[] = "./shader.vs";
static std::string vsText;
static char const fsFileName[] = "./shader.fs";
static std::string fsText;
static GLuint mapping;

// Define functions
/* Loads the GLUT function callbacks. */
static void loadGLUTFuncs();
/* Displays the objects to be rendered. */
static void display();
/* Initializes GLEW. */
static void initGLEW();
/* Loads the vertex buffer. */
static void loadVertexBuffer();
/* Loads the index buffer */
static void loadIndexBuffer();
/* Loads the shader program. */
static void loadShaderProgram();
/* Reads from the specified shader file to a specified string. */
static void readShaderFile(char const *, std::string &);
/* Adds a shader text to a shader program */
static void addShaderTextToProgram(GLuint, GLenum, char const *);
/* Shows an error information line in stderr. */
static void errShowLine(char const *, char const *, ...);
/* Gets and shows the GL shader program info log in stderr. */
static void errShowProgramLog(char const *, GLuint);
/* Gets and shows the GL shader info log in stderr. */
static void errShowShaderLog(char const *, GLuint);
