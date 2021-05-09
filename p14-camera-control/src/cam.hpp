/* File name: cam.hpp
 *
 * Intro:
 * C++ header of the camera custom library.
 * 
 * Dependencies:
 * 1. GLUT library (freeglut3-dev)
 * 2. GLM library (libglm-dev)
 * 3. All modules of the cam library (cam/*.hpp) */

#ifndef CAM_HPP
#define CAM_HPP

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// Forward declare camLib::Ctrl (from cam/ctrl.hpp)
namespace camLib {
    class Ctrl;
}
// Include cam/ctrl.hpp in cam.cpp to complete the declarations above

/* Camera. */
class Cam {
   private:
    /* Position. */
    glm::vec3 _pos;
    /* Aim (relative to the position). */
    glm::vec3 _aim;
    /* Up direction of the camera space. */
    glm::vec3 _up;
    /* Camera control */
    camLib::Ctrl *_ctrl;

   public:
    /* Initializes a default camera.
     * Position: 0; Aiming at: 0, 0, 1; Up direction: 0, 1, 0;
     * Control: nullptr (initialized later, before first usage). */
    Cam();
    /* Destructs a camera. */
    ~Cam();
    /* Reads the position. */
    glm::vec3 pos();
    /* Reads and updates the position. */
    glm::vec3 pos(float x, float y, float z);
    /* Reads and updates the position. */
    glm::vec3 pos(glm::vec3 newVal);
    /* Reads the aim. */
    glm::vec3 aim();
    /* Reads and updates the aim. */
    glm::vec3 aim(float x, float y, float z);
    /* Reads and updates the aim. */
    glm::vec3 aim(glm::vec3 newVal);
    /* Reads the up direction. */
    glm::vec3 up();
    /* Reads and updates the up direction. */
    glm::vec3 up(float x, float y, float z);
    /* Reads and updates the up direction. */
    glm::vec3 up(glm::vec3 newVal);
    /* Reads the control's reference. */
    camLib::Ctrl &ctrl();
    /* Finds the camera view matrix. */
    glm::mat4 view();
};

// CAM_HPP
#endif
