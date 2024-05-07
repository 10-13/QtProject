#pragma once

#include <iostream>

#include "core/includes/Includes.h"
#include "core/data/DValue.h"

namespace qtproject {
    namespace data {
        class DValueSerializer {        
        public:
            char Open{'['};
            char Close{']'};

            bool Indent{false};

            DValueSerializer() = default;
            
            bool Serialize(std::ostream& in, std::shared_ptr<DValue> dvalue);

            bool Deserialize(std::istream& out, std::shared_ptr<DValue> dvalue);
        };

    }
}