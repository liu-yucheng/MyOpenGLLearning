/* File name: cam.hpp
 *
 * Intro:
 * C++ header of the camera custom library.
 * 
 * Dependencies:
 * 1. GLUT library (freeglut3-dev)
 * 2. GLM library (libglm-dev)
 * 3. The transformation custom library.
 */

#ifndef CAM_HPP
#define CAM_HPP

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "trans.hpp"

#include <cstdio>

class Cam {
   private:
    /* Position. */
    glm::vec3 _pos;
    /* Aim (relative to the position). */
    glm::vec3 _aim;
    /* Up direction of the camera space. */
    glm::vec3 _up;
    /* Step size of camera control. */
    float _step;

    // Define key reaction helper functions
    void onKeyUp();
    void onKeyDown();
    void onKeyLeft();
    void onKeyRight();

   public:
    /* Camera control switch. */
    bool controlled;
    /* Initializes a default camera.
     * Position: 0; Aiming at: 0, 0, 1; Up direction: 0, 1, 0.
     * Camera control: Step: 1; Controlled: false.
     */
    Cam();
    /* Reads the position. */
    glm::vec3 pos();
    /* Reads and updates the position. */
    glm::vec3 pos(float x, float y, float z);
    /* Reads the aim. */
    glm::vec3 aim();
    /* Reads and updates the aim. */
    glm::vec3 aim(float x, float y, float z);
    /* Reads the up direction. */
    glm::vec3 up();
    /* Reads and updates the up direction. */
    glm::vec3 up(float x, float y, float z);
    /* Finds the camera view matrix. */
    glm::mat4 view();
    /* Finds the view matrix of this camera on a specified object. */
    glm::mat4 viewOf(Trans &trans);
    /* Changes the camera's state on keyboard input. */
    bool onKey(int key);
};

// CAM_HPP
#endif
