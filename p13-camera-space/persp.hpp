/* File name: persp.hpp
 *
 * Intro:
 * C++ header of the perspective custom library.
 * 
 * Dependencies:
 * 1. GLM library (libglm-dev)
 * 2. The transformation custom library.
 * 3. The camera custom library.
 */

#ifndef PERSP_HPP
#define PERSP_HPP

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "trans.hpp"
#include "cam.hpp"

/* Perspective. */
class Persp {
   private:
    /* Aspect ratio. */
    float _aspect;
    /* Near plane's Z position. */
    float _near;
    /* Far plane's Z position. */
    float _far;
    /* Field of view (unit: degrees). */
    float _fov;
    /* Finds the perspective projection matrix.
     * Note:
     * The projection matrix is looking forward at +Y direction and up at +Z
     * direction. */
    glm::mat4 projMat();

   public:
    /* Initializes the object with the specified parameters. */
    Persp(int width, int height, float near, float far, float fov);
    /* Reads the aspect ratio. */
    float aspect();
    /* Reads and updates the aspect ratio. */
    float aspect(int width, int height);
    /* Reads the near plane's Z position. */
    float near();
    /* Reads and updates the near plane's Z position. */
    float near(float near);
    /* Reads the far plane's Z position. */
    float far();
    /* Reads and updates the far plane's Z location. */
    float far(float far);
    /* Reads the field of view (unit: degrees). */
    float fov();
    /* Reads and updates the field of view (unit: degrees). */
    float fov(float fov);
    /* Finds the perspective projection matrix.
     * Note: 
     * The projection matrix has a view that looks forward at +Z direction and
     * looks upward at +Y direction. */
    glm::mat4 proj();
    /* Finds the matrix of this perspective of a specified transformation. */
    glm::mat4 of(Trans &trans);
    /* Finds the matrix of this perspective of a camera on a transformation. */
    glm::mat4 of(Cam &cam, Trans &trans);
};

// PERSP_HPP
#endif
