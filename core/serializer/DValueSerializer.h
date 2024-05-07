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
            DValueSerializer() = default;

            DValueSerializer(std::string brackets, int indent = 0)
             : brackets_(brackets)
             , indent_(indent) {
            }

            DValueSerializer(int indent) : indent_(indent) {
            }
            
            bool Serialize(std::istream& in, std::shared_ptr<DValue> dvalue);

            bool Deserialize(std::ostream& out, std::shared_ptr<DValue> dvalue);
        };

    }
}