#pragma once

#include <iostream>

#include "core/includes/Includes.h"
#include "core/data/DValue.h"

namespace qtproject {
    namespace data {
        class DValueSerializer {
           private:
            std::string brackets_{"[]"};
            int indent_{0};
        
           public:
            bool Serialize(const std::istream& in, std::shared_ptr<DValue>& dvalues);
            bool Deserialize(std::ostream& out,const <std::shared_ptr<DValue>& dvalues);
        };

    }
}