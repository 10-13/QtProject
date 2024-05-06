#include "DVGlobalRequirements.h"

#define __MERGE(a,b) a##b
#define __MERGE2(a,b) __MERGE(a, b)

#define __DV_BUILD_NAME() __MERGE2(__dv_req,__COUNTER__)

#define __SRC_DV_REQ(nameArg, PID) \
    void __bm##PID(std::shared_ptr<qtproject::data::DValue>); \
    qtproject::data::require::Requirement* req = new qtproject::data::require::Requirement(nameArg, __bm##PID); \
    void __bm##PID(std::shared_ptr<qtproject::data::DValue> pattern) 

#define __SRC_DV_REQ2(nameArg, PID) __SRC_DV_REQ(nameArg, PID)

#define DV_REQUIREMENT(name) __SRC_DV_REQ2(name, __DV_BUILD_NAME())



DV_REQUIREMENT("block") {
    pattern->Add("Type");
    pattern->Add("Firm");
}