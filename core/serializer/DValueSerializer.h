#pragma once

#include <algorithm>
#include <iostream>
#include <string_view>

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
            
            void Serialize(std::ostream&, std::shared_ptr<DValue>);

            bool Deserialize(std::istream&, std::shared_ptr<DValue>);

        private:
            void RecursiveDeserialize(std::string_view, std::shared_ptr<DValue>);

            std::string GetCurrentName(std::string_view);

            std::vector<std::string_view> GetChildren(std::string_view);

            std::string GetValidStr(std::string&&);

            void RecursiveSerialize(std::ostream&, std::shared_ptr<DValue>, size_t);
        };

    }
}