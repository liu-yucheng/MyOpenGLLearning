/* File name: cam.cpp
 *
 * Intro:
 * C++ implementation of the camera custom library.
 */

#include "cam.hpp"

/* Note:
 * For key reaction helper functions, see below the definition of the onKey
 * function. */

Cam::Cam() {
    _pos = glm::vec3(0.0f, 0.0f, 0.0f);
    _aim = glm::vec3(0.0f, 0.0f, 1.0f);
    _up = glm::vec3(0.0f, 1.0f, 0.0f);
    _step = 1.0f;

    controlled = false;
}

glm::vec3 Cam::pos() {
    return _pos;
}

glm::vec3 Cam::pos(float x, float y, float z) {
    glm::vec3 old = _pos;
    _pos[0] = x;
    _pos[1] = y;
    _pos[2] = z;
    return old;
}

glm::vec3 Cam::aim() {
    return _aim;
}

glm::vec3 Cam::aim(float x, float y, float z) {
    glm::vec3 old = _aim;
    _aim[0] = x;
    _aim[1] = y;
    _aim[2] = z;
    return old;
}

glm::vec3 Cam::up() {
    return _up;
}

glm::vec3 Cam::up(float x, float y, float z) {
    glm::vec3 old = _up;
    _up[0] = x;
    _up[1] = y;
    _up[2] = z;
    return old;
}

glm::mat4 Cam::view() {
    /* Note:
     * The center parameter (2nd parameter) of the lookAt call is the sum of
     * the position and the aim because the aim is defined to be relative to
     * the position. */
    glm::mat4 viewMat = glm::lookAt(_pos, _pos + _aim, _up);
    return viewMat;
}

bool Cam::onKey(int key) {
    bool result;

    if (!controlled) {
        result = false;
        return result;
    }

    switch (key) {
        case GLUT_KEY_UP:
            onKeyUp();
            result = true;
            break;
        case GLUT_KEY_DOWN:
            onKeyDown();
            result = true;
            break;
        case GLUT_KEY_LEFT:
            onKeyLeft();
            result = true;
            break;
        case GLUT_KEY_RIGHT:
            onKeyRight();
            result = true;
            break;
        default:
            result = false;
            break;
    }

    return result;
}

// Implement the key reaction helper functions
void Cam::onKeyUp() {
    glm::vec3 unitAim = glm::normalize(_aim);
    _pos += unitAim * _step;
}

void Cam::onKeyDown() {
    glm::vec3 unitAim = glm::normalize(_aim);
    _pos -= unitAim * _step;
}

void Cam::onKeyLeft() {
    glm::vec3 left = glm::cross(_up, _aim);
    glm::vec3 unitLeft = glm::normalize(left);
    _pos += unitLeft * _step;
}

void Cam::onKeyRight() {
    glm::vec3 right = glm::cross(_aim, _up);
    glm::vec3 unitRight = glm::normalize(right);
    _pos += unitRight * _step;
}
