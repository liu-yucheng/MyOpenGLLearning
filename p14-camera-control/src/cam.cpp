/* File name: cam.cpp
 *
 * Intro:
 * C++ implementation of the camera custom library. */

/* Copyright 2022 Yucheng Liu. GNU GPL3 license.
 * GNU GPL3 license copy: https://www.gnu.org/licenses/gpl-3.0.txt */

#include "cam.hpp"
#include "cam/ctrl.hpp"

Cam::Cam() {
    _pos = glm::vec3(0.0f, 0.0f, 0.0f);
    _aim = glm::vec3(0.0f, 0.0f, 1.0f);
    _up = glm::vec3(0.0f, 1.0f, 0.0f);
    _ctrl = nullptr;
}

Cam::~Cam() {
    // Delete the control
    if (_ctrl != nullptr) {
        delete _ctrl;
    }
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

glm::vec3 Cam::pos(glm::vec3 newVal) {
    glm::vec3 oldVal = _pos;
    _pos = newVal;
    return oldVal;
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

glm::vec3 Cam::aim(glm::vec3 newVal) {
    glm::vec3 oldVal = _aim;
    _aim = newVal;
    return oldVal;
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

glm::vec3 Cam::up(glm::vec3 newVal) {
    glm::vec3 oldVal = _up;
    _up = newVal;
    return oldVal;
}

camLib::Ctrl &Cam::ctrl() {
    if (_ctrl == nullptr) {
        _ctrl = new camLib::Ctrl();
        _ctrl->subject(this);
    }
    return *_ctrl;
}

glm::mat4 Cam::view() {
    /* Note:
     * The center parameter (2nd parameter) of the lookAt call is the sum of
     * the position and the aim because the aim is defined to be relative to
     * the position. */
    glm::mat4 viewMat = glm::lookAt(_pos, _pos + _aim, _up);
    return viewMat;
}
