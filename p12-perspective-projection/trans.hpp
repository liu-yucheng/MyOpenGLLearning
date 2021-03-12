/* File name: trans.hpp
 *
 * Intro:
 * C++ header of the transformation custom library.
 * 
 * Dependencies:
 * 1. GLM library (libglm-dev)
 * 2. Perspective library (persp.hpp)
 */

#ifndef TRANS_HPP
#define TRANS_HPP

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "persp.hpp"

/* Transformation of a 3 dimensional object. */
class Trans {
   private:
    /* Scale of the object. */
    glm::vec3 _scale;
    /* Rotation of the object (unit: degrees). */
    glm::vec3 _rot;
    /* Position of the object. */
    glm::vec3 _pos;

   public:
    /* Initializes a Trans object.
     * Initializes the object's scale to 1, rotation to 0 degrees, and position
     * to 0. */
    Trans();
    /* Returns the scale of the object. */
    glm::vec3 scale();
    /* Scales the object.
     * Returns the old scale. */
    glm::vec3 scale(float x, float y, float z);
    /* Returns the rotation of the object (unit: degrees). */
    glm::vec3 rot();
    /* Rotates the object (unit: degrees).
     * Returns the old rotation. */
    glm::vec3 rot(float x, float y, float z);
    /* Returns the position of the object. */
    glm::vec3 pos();
    /* Positions the object.
     * Returns the old position. */
    glm::vec3 pos(float x, float y, float z);
    /* Finds the world matrix of the object.
     * Returns the world matrix. */
    glm::mat4 world();
    /* Finds the specified perspective projection of the object.
     * Returns the perspective projection matrix.
     * Note:
     * The perspective projection matrix has a view that looks forward at +Z
     * and upward at +Y directions. */
    glm::mat4 persp(Persp persp);
};

/* trans.hpp */
#endif
