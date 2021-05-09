/* File name: ctrl.hpp
 * 
 * Intro:
 * C++ implementation of the cam (Camera) libraries' ctrl (Control) module. */

#include "ctrl.hpp"
#include "../cam.hpp"

namespace camLib {

Ctrl::Ctrl() {
    _enabled = false;
    _subject = nullptr;
    _moveStep = 1.0f;
}

bool Ctrl::enabled() {
    return _enabled;
}

bool Ctrl::enabled(bool newVal) {
    bool oldVal = _enabled;
    _enabled = newVal;
    return oldVal;
}

Cam *Ctrl::subject() {
    return _subject;
}

Cam *Ctrl::subject(Cam *newVal) {
    Cam *oldVal = _subject;
    _subject = newVal;
    return oldVal;
}

float Ctrl::moveStep() {
    return _moveStep;
}

float Ctrl::moveStep(float newVal) {
    float oldVal = _moveStep;
    _moveStep = newVal;
    return oldVal;
}

bool Ctrl::onKey(int key) {
    bool result;

    if (!_enabled or _subject == nullptr) {
        result = false;
        return result;
    }

    switch (key) {
        case GLUT_KEY_UP:
            _moveOn();
            result = true;
            break;
        case GLUT_KEY_DOWN:
            _moveBack();
            result = true;
            break;
        case GLUT_KEY_LEFT:
            _moveLeft();
            result = true;
            break;
        case GLUT_KEY_RIGHT:
            _moveRight();
            result = true;
            break;
        default:
            result = false;
            break;
    }

    return result;
}

// Implement action helper functions

void Ctrl::_moveOn() {
    glm::vec3 unitAim = glm::normalize(_subject->aim());
    glm::vec3 newPos = _subject->pos() + unitAim * _moveStep;
    _subject->pos(newPos);
}

void Ctrl::_moveBack() {
    glm::vec3 unitAim = glm::normalize(_subject->aim());
    glm::vec3 newPos = _subject->pos() - unitAim * _moveStep;
    _subject->pos(newPos);
}

void Ctrl::_moveLeft() {
    glm::vec3 left = glm::cross(_subject->up(), _subject->aim());
    glm::vec3 unitLeft = glm::normalize(left);
    glm::vec3 newPos = _subject->pos() + unitLeft * _moveStep;
    _subject->pos(newPos);
}

void Ctrl::_moveRight() {
    glm::vec3 right = glm::cross(_subject->aim(), _subject->up());
    glm::vec3 unitRight = glm::normalize(right);
    glm::vec3 newPos = _subject->pos() + unitRight * _moveStep;
    _subject->pos(newPos);
}

}  // namespace camLib
