/* File name: trans.hpp
 *
 * Intro:
 * C++ header of the transformation custom library.
 * 
 * Dependencies:
 * 1. GLM library (libglm-dev)
 */

#ifndef TRANS_HPP
#define TRANS_HPP

#include <glm/glm.hpp>
#include <glm/ext.hpp>

/* Transformation. */
class Trans {
   private:
    /* Scale. */
    glm::vec3 _scale;
    /* Rotation (unit: degrees). */
    glm::vec3 _rot;
    /* Position. */
    glm::vec3 _pos;

   public:
    /* Initializes the object to scale 1, rotation 0 degrees, and position 0.*/
    Trans();
    /* Reads the scale. */
    glm::vec3 scale();
    /* Reads and updates the scale. */
    glm::vec3 scale(float x, float y, float z);
    /* Reads the rotation (unit: degrees). */
    glm::vec3 rot();
    /* Reads and updates the rotation (unit: degrees). */
    glm::vec3 rot(float x, float y, float z);
    /* Reads the position. */
    glm::vec3 pos();
    /* Reads and updates the position. */
    glm::vec3 pos(float x, float y, float z);
    /* Finds the world matrix. */
    glm::mat4 world();
};

/* TRANS_HPP */
#endif
