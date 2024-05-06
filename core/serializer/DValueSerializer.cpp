#include "core/serializer/DValueSerializer.h"

namespace qtproject {
    namespace data {
        bool DValueSerializer::Serialize(const std::istream& in, std::shared_ptr<DValue>& dvalues) {
            return false;
        }

        bool DValueSerializer::Deserialize(std::ostream& out, std::shared_ptr<DValue>& dvalues) {
            return false;
        }
    }
}