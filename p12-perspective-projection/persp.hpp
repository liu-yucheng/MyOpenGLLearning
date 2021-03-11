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

/* Perspective information. */
class Persp {
   private:
    /* Aspect ratio of the Persp. */
    float _aspect;
    /* Near plane's Z position of the Persp. */
    float _near;
    /* Far plane's Z position of the Persp. */
    float _far;
    /* Field of view (unit: degrees) of the Persp. */
    float _fov;

   public:
    /* Initializes a Persp. */
    Persp(int width, int height, float near, float far, float fov);
    /* Returns the aspect ratio. */
    float aspect();
    /* Updates the aspect ratio.
     * Returns the old aspect ratio. */
    float aspect(int width, int height);
    /* Returns the near plane's Z position. */
    float near();
    /* Updates the near plane's Z location.
     * Returns the old near plane's Z location. */
    float near(float near);
    /* Returns the far plane's Z position. */
    float far();
    /* Updates the far plane's Z location.
     * Returns the old far plane's Z location. */
    float far(float far);
    /* Returns the field of view (unit: degrees). */
    float fov();
    /* Updates the field of view (unit: degrees).
     * Returns the field of view. */
    float fov(float fov);
    /* Finds the perspective projection matrix.
     * Returns the perspective projection matrix.
     * 
     * Note: 
     * The projection matrix has a view that looks forward at +Z direction and
     * looks up at +Y direction. */
    glm::mat4 proj();
};

// PERSP_HPP
#endif
