#pragma once

#include "DVGlobalRequirements.h"

#define __SRC_DV_REQ2(name, pattern) \
    void __bm##name(std::shared_ptr<qtproject::data::DValue>); \
    qtproject::data::require::Requirement* name = new qtproject::data::require::Requirement(#name, __bm##name); \
    void __bm##name(std::shared_ptr<qtproject::data::DValue> pattern) 

#define DV_REQUIREMENT(name) __SRC_DV_REQ2(name, pattern)
#define DV_REQUIREMENT_P(name, pattern__) __SRC_DV_REQ2(name, pattern__)

namespace {
    DV_REQUIREMENT(block) {
        pattern->Add("Type")->Add("!v body hands head legs");
        pattern->Add("Firm")->Add("!u");
    }
}

class MyClass {
    void SomeMethodWithData(std::shared_ptr<qtproject::data::DValue> data) {
        if(!block->GetChecker().CheckValue(data))
            throw std::exception();
    }
};



