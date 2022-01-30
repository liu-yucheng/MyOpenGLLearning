/* File name: ctrl.hpp
 * 
 * Intro:
 * C++ header of the cam (Camera) libraries' ctrl (Control) module.
 * 
 * Dependencies:
 * 1. GLUT library (freeglut3-dev)
 * 2. GLM library (libglm-dev)
 * 3. The cam libraries' main module (../cam.hpp) */

/* Copyright 2022 Yucheng Liu. GNU GPL3 license.
 * GNU GPL3 license copy: https://www.gnu.org/licenses/gpl-3.0.txt */

#ifndef CAM__CTRL_HPP
#define CAM__CTRL_HPP

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// Forward declare Cam (from ../cam.hpp)
class Cam;
// Include ../cam.hpp in cam/ctrl.cpp to complete the declarations above

/* Camera library */
namespace camLib {

/* (Camera) control. */
class Ctrl {
   private:
    bool _enabled;
    /* The camera that is being controlled. */
    Cam *_subject;
    /* Step size of the subject's movement. */
    float _moveStep;

    // Action helper functions

    void _moveOn();
    void _moveBack();
    void _moveLeft();
    void _moveRight();

   public:
    /* Constructs a default control.
     * enabled: false; subject: nullptr; moveStep: 1.*/
    Ctrl();
    /* Reads the enabled status. */
    bool enabled();
    /* Reads and updates the enabled status. */
    bool enabled(bool newVal);
    /* Reads the subject's identity. */
    Cam *subject();
    /* Reads and rgisters a new subject. */
    Cam *subject(Cam *newVal);
    /* Reads the movement step. */
    float moveStep();
    /* Reads and updates the movement step. */
    float moveStep(float newVal);
    /* Triggers an action based on the keyboard input. */
    bool onKey(int key);
};

}  // namespace camLib

// CAM__CTRL_HPP
#endif
