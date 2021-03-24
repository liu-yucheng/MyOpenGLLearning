/* File name: main.cpp
 * 
 * Intro:
 * C++ implementation of the program defined in main.hpp.
 */

#include "main.hpp"

int main(int argc, char **argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(winTitle);

    loadGLUTFuncs();

    // Initialize GLEW after GLUT
    initGLEW();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    loadVertexBuffer();
    loadIndexBuffer();
    loadShaderProgram();

    // Draw
    glutMainLoop();

    return 0;
}

static void loadGLUTFuncs() {
    glutDisplayFunc(display);
    glutIdleFunc(display);
}

static void display() {
    static float const rotateSpeed = 0.1f;
    static int transCount = 0;
    static Trans trans;
    static Persp persp(winWidth, winHeight, 1.0f, 100.0f, 30.0f);
    static glm::mat4 worldVal(1.0f);

    transCount += 1;

    trans.rot(0.0f, rotateSpeed * transCount, 0.0f);
    trans.pos(0.0f, 0.0f, 5.0f);
    worldVal = persp.of(trans);

    glClear(GL_COLOR_BUFFER_BIT);

    glUniformMatrix4fv(world, 1, GL_FALSE, glm::value_ptr(worldVal));

    // Draw based on the vertices and indices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}

static void initGLEW() {
    char const funcName[] = "initGLEW";

    GLenum result = glewInit();
    if (result != GLEW_OK) {
        errShowLine(funcName, "error: initializing GLEW");
        errShowLine(funcName, "error string: %s", glewGetErrorString(result));
        exit(1);
    }
}

static void loadVertexBuffer() {
    int const vertexCount = 4;
    glm::vec3 vertices[vertexCount];
    {
        glm::vec3 *v = vertices;
        v[0] = glm::vec3(-1.0f, -1.0f, 0.5773f);
        v[1] = glm::vec3(0.0f, -1.0f, -1.1548f);
        v[2] = glm::vec3(1.0f, -1.0f, 0.5773f);
        v[3] = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    // Put vertices into buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // clang-format off
    glBufferData(
        GL_ARRAY_BUFFER,
        vertexCount * sizeof(glm::vec3),
        vertices,
        GL_STATIC_DRAW
    );
    // clang-format on
}

static void loadIndexBuffer() {
    int const indexCount = 12;
    // clang-format off
    unsigned int indices[indexCount] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 2, 1
    };
    // clang-format on

    // Put indices into buffer
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    // clang-format off
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indexCount * sizeof(int),
        indices,
        GL_STATIC_DRAW
    );
    // clang-format on
}

static void loadShaderProgram() {
    char const funcName[] = "loadShaderProgram";

    GLuint program = glCreateProgram();
    if (program == 0) {
        errShowLine(funcName, "error: creating shader program");
        exit(1);
    }

    // Load shader texts
    readShaderFile(vsFileName, vsText);
    readShaderFile(fsFileName, fsText);
    addShaderTextToProgram(program, GL_VERTEX_SHADER, vsText.c_str());
    addShaderTextToProgram(program, GL_FRAGMENT_SHADER, fsText.c_str());

    // Link and validate
    GLint result = 0;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == 0) {
        errShowLine(funcName, "error: linking shader program");
        errShowProgramLog(funcName, program);
        exit(1);
    }
    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
    if (result == 0) {
        errShowLine(funcName, "error: validating shader program");
        errShowProgramLog(funcName, program);
        exit(1);
    }

    glUseProgram(program);

    // Bind shader variable "world"
    world = glGetUniformLocation(program, "world");
    if (world == 0xFFFFFFFF) {
        errShowLine(funcName, "error: binding shader variable \"world\"");
        exit(1);
    }
}

static void readShaderFile(char const *name, std::string &content) {
    char const funcName[] = "readShaderFile";

    std::fstream file;
    file.open(name, std::ios::in);
    if (!file.is_open()) {
        errShowLine(funcName, "error: reading file: %s", name);
        exit(1);
    }

    std::string line;
    content = "";
    while (getline(file, line)) {
        line += "\n";
        content += line;
    }
}

// clang-format off
static void addShaderTextToProgram(
    GLuint program, GLenum type, char const *text
) {
    // clang-format on
    char const funcName[] = "addShaderTextToProgram";

    GLuint shader = glCreateShader(type);
    if (shader == 0) {
        errShowLine(funcName, "error: creating shader");
        exit(1);
    }

    // Bind shader text
    int const textCount = 1;
    GLchar const *glTexts[textCount];
    glTexts[0] = text;
    GLint textLengths[textCount];
    textLengths[0] = strlen(text);
    glShaderSource(shader, textCount, glTexts, textLengths);

    // Compile
    glCompileShader(shader);
    GLint compilationResult = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationResult);
    if (compilationResult == 0) {
        errShowLine(funcName, "error: compiling shader");
        errShowLine(funcName, "shader type: %d", type);
        errShowShaderLog(funcName, shader);
        exit(1);
    }

    glAttachShader(program, shader);
}

static void errShowLine(char const *funcName, char const *format, ...) {
    va_list args;
    va_start(args, format);

    fprintf(stderr, "%s: ", funcName);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    fflush(stderr);

    va_end(args);
}

static void errShowProgramLog(char const *funcName, GLuint program) {
    int const logLength = 1023;
    GLchar log[logLength + 1] = {0};
    glGetProgramInfoLog(program, logLength, NULL, log);
    errShowLine(funcName, "info log: %s", log);
}

static void errShowShaderLog(char const *funcName, GLuint shader) {
    int const logLength = 1023;
    GLchar log[logLength + 1] = {0};
    glGetShaderInfoLog(shader, logLength, NULL, log);
    errShowLine(funcName, "info log: %s", log);
}
