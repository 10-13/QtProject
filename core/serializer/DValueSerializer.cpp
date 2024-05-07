#include "core/serializer/DValueSerializer.h"

namespace qtproject {
    namespace data {
        bool DValueSerializer::Serialize(std::istream& in, std::shared_ptr<DValue> dvalue) {
            std::string str_buf;
            char symb_buf;
            in >> symb_buf;
            
            if (symb_buf != brackets_[0]) {
                return false;
            }

            while (std::getline(in, str_buf, brackets_[1])) { // Read until ']'
                std::getline(in, str_buf, brackets_[0]); // Read until '['
                dvalue = DValue::Create(str_buf);

                in >> symb_buf;
                if (symb_buf == brackets_[1]) {
                    continue;
                }
                while (std::getline(in, str_buf, brackets_[1])) { // Read until ']'
                    std::getline(in, str_buf, brackets_[0]); // Read until '['
                    dvalue->Add(str_buf);
                    Serialize(in, dvalue->At(str_buf));
                }
            }
            
            return true;
        }

        bool DValueSerializer::Deserialize(std::ostream& out, std::shared_ptr<DValue> dvalues) {
            out << '[' << dvalues->Name();
            for (size_t i = 0; i < dvalues->Size(); i++) {
                Deserialize(out, dvalues->At(i));
            }
            out << ']';
            
            return true;
        }
    }
}