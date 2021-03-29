/* File name: pipeline.hpp
 *
 * Intro:
 * C++ header of the rendering pipeline custom library.
 * 
 * Dependencies:
 * 1. GLM library. (libglm-dev)
 * 2. The transformation custom library.
 * 3. The perspective custom library.
 */

#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "trans.hpp"
#include "persp.hpp"

/* Rendering pipeline. */
class Pipeline {
   private:
    Trans *_trans = nullptr;
    Persp *_persp = nullptr;

   public:
    Pipeline(Trans *trans);
    Pipeline(Trans *trans, Persp *persp);
    /* Finds the composite mapping matrix. */
    glm::mat4 mapping();
};

// PIPELINE_HPP
#endif
