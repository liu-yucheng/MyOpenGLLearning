/* File name: persp.hpp
 *
 * Intro:
 * C++ header of the perspective custom library.
 * 
 * Dependencies:
 * 1. GLM library (libglm-dev)
 */

#ifndef PERSP_HPP
#define PERSP_HPP

#include <glm/glm.hpp>
#include <glm/ext.hpp>

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
     * The matrix sees +Y as forward and -Z as upward.
     */
    glm::mat4 proj();
    /* Finds the perspective projection view matrix.
     * Note: 
     * The matrix has a view that looks forward at +Z direction and looks
     * upward at +Y direction. */
    glm::mat4 projView();
};

// PERSP_HPP
#endif
