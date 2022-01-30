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

/* Copyright 2022 Yucheng Liu. GNU GPL3 license.
 * GNU GPL3 license copy: https://www.gnu.org/licenses/gpl-3.0.txt */

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
