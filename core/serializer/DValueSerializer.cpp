#include "core/serializer/DValueSerializer.h"

namespace qtproject {
    namespace data {
        bool DValueSerializer::Deserialize(std::istream& in, std::shared_ptr<DValue> dvalue) {
            std::string str_buf;
            char symb_buf;
            in >> symb_buf;
            
            if (symb_buf != Open) {
                return false;
            }

            while (std::getline(in, str_buf, Close)) { // Read until ']'
                std::getline(in, str_buf, Open); // Read until '['
                dvalue = DValue::Create(str_buf);

                in >> symb_buf;
                if (symb_buf == Close) {
                    continue;
                }
                while (std::getline(in, str_buf, Close)) { // Read until ']'
                    std::getline(in, str_buf, Open); // Read until '['
                    dvalue->Add(str_buf);
                    Deserialize(in, dvalue->At(str_buf));
                }
            }
            
            return true;
        }

        bool DValueSerializer::Serialize(std::ostream& out, std::shared_ptr<DValue> dvalues) {
            out << '[' << dvalues->Name();
            for (size_t i = 0; i < dvalues->Size(); i++) {
                Serialize(out, dvalues->At(i));
            }
            out << ']';
            
            return true;
        }
    }
}