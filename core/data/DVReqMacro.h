#pragma once

#include "DVGlobalRequirements.h"

#define __SRC_DV_REQ2(name, type, pattern) \
    void __bm##name(std::shared_ptr<qtproject::data::DValue>); \
    qtproject::data::require::Requirement* name = new qtproject::data::require::Requirement(type, __bm##name); \
    void __bm##name(std::shared_ptr<qtproject::data::DValue> pattern) 

#define DV_REQUIREMENT(name, type) __SRC_DV_REQ2(name, type, pattern)
#define DV_REQUIREMENT_P(name, type, pattern__) __SRC_DV_REQ2(name, type, pattern__)


