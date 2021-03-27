/* File name: persp.cpp
 *
 * Intro:
 * C++ implementation of the perspective custom library.
 */

#include "persp.hpp"

glm::mat4 Persp::projMat() {
    // clang-format off
    glm::mat4 projMat = glm::perspective(
        glm::radians(_fov), _aspect, _near, _far
    );
    // clang-format on
    return projMat;
}

Persp::Persp(int width, int height, float near, float far, float fov) {
    _aspect = (float)width / (float)height;
    _near = near;
    _far = far;
    _fov = fov;
}

float Persp::aspect() {
    return _aspect;
}

float Persp::aspect(int width, int height) {
    float old = _aspect;
    _aspect = (float)width / (float)height;
    return old;
}

float Persp::near() {
    return _near;
}

float Persp::near(float near) {
    float old = _near;
    _near = near;
    return old;
}

float Persp::far() {
    return _far;
}

float Persp::far(float far) {
    float old = _far;
    _far = far;
    return old;
}

float Persp::fov() {
    return _fov;
}

float Persp::fov(float fov) {
    float old = _fov;
    _fov = fov;
    return old;
}

glm::mat4 Persp::proj() {
    glm::mat4 projMat = this->projMat();

    // clang-format off
    // Create a view matrix that looks forward at +Z direction and looks upward
    // at +Y direction
    glm::mat4 viewMat = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    // clang-format on

    // Apply the view on the perspective
    return projMat * viewMat;
}

glm::mat4 Persp::of(Trans &trans) {
    glm::mat4 result = this->proj() * trans.world();
    return result;
}

glm::mat4 Persp::of(Cam &cam, Trans &trans) {
    glm::mat4 result = this->projMat() * cam.viewOf(trans);
    return result;
}
