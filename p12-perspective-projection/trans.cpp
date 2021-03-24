/* File name: trans.cpp
 *
 * Intro:
 * C++ implementation of the transformation custom library.
 */

#include "trans.hpp"

Trans::Trans() {
    _scale = glm::vec3(1.0f, 1.0f, 1.0f);
    _rot = glm::vec3(0.0f, 0.0f, 0.0f);
    _pos = glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 Trans::scale() {
    return _scale;
}

glm::vec3 Trans::scale(float x, float y, float z) {
    glm::vec3 old = _scale;
    _scale[0] = x;
    _scale[1] = y;
    _scale[2] = z;
    return old;
}

glm::vec3 Trans::rot() {
    return _rot;
}

glm::vec3 Trans::rot(float x, float y, float z) {
    glm::vec3 old = _rot;
    _rot[0] = x;
    _rot[1] = y;
    _rot[2] = z;
    return old;
}

glm::vec3 Trans::pos() {
    return _pos;
}

glm::vec3 Trans::pos(float x, float y, float z) {
    glm::vec3 old = _pos;
    _pos[0] = x;
    _pos[1] = y;
    _pos[2] = z;
    return old;
}

glm::mat4 Trans::world() {
    // Find the scale, rotation, and position matrices.
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), _scale);
    glm::mat4 rotMat(1.0f);
    {
        glm::vec3 xAxis(1.0f, 0.0f, 0.0f);
        glm::vec3 yAxis(0.0f, 1.0f, 0.0f);
        glm::vec3 zAxis(0.0f, 0.0f, 1.0f);
        // Rotate around x, y, and z axes
        rotMat = glm::rotate(rotMat, glm::radians(_rot[0]), xAxis);
        rotMat = glm::rotate(rotMat, glm::radians(_rot[1]), yAxis);
        rotMat = glm::rotate(rotMat, glm::radians(_rot[2]), zAxis);
    }
    glm::mat4 posMat = glm::translate(glm::mat4(1.0f), _pos);
    // Scale, rotate, and position in order
    // (In matrix left-multiplication, the order is from right to left.)
    glm::mat4 world = posMat * rotMat * scaleMat;
    return world;
}
