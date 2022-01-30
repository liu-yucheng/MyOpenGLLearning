/* File name: pipeline.cpp
 *
 * Intro:
 * C++ implementation of the rendering pipeline custom library.
 */

/* Copyright 2022 Yucheng Liu. GNU GPL3 license.
 * GNU GPL3 license copy: https://www.gnu.org/licenses/gpl-3.0.txt */

#include "pipeline.hpp"

Pipeline::Pipeline(Trans *trans) {
    _trans = trans;
}

Pipeline::Pipeline(Trans *trans, Persp *persp) {
    _trans = trans;
    _persp = persp;
}

glm::mat4 Pipeline::mapping() {
    glm::mat4 result(1.0f);

    if (_trans != nullptr) {
        result = _trans->world() * result;
    }
    if (_persp != nullptr) {
        result = _persp->projView() * result;
    }

    return result;
}
