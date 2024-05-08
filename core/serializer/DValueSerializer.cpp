#include "core/serializer/DValueSerializer.h"

namespace qtproject {
    namespace data {
        void DValueSerializer::RecursiveDeserialize(std::string_view view, std::shared_ptr<DValue> dvalue) { 
            dvalue = DValue::Create(std::string(GetCurrentName(view)));
            for (auto child_view : GetChildren(view)) {
                RecursiveDeserialize(child_view, dvalue->Add(""));
            }
        }

        std::string_view DValueSerializer::GetCurrentName(std::string_view view) {
            size_t end_pos = 0;
            for (size_t i = 1; i != view.size(); ++i) { // skip first open bracket
                if (view[i] == Open || view[i] == Close) {
                    end_pos = i;
                    break;
                }
            }
            return view.substr(1, end_pos - 1);
        }

        std::vector<std::string_view> DValueSerializer::GetChildren(std::string_view view) {
            std::vector<std::string_view> children;
            std::cerr << view << std::endl;
            size_t start_pos = 1;
            size_t end_pos = 1;
            size_t bracket_count = 0;
            for (size_t i = 1; i != view.size(); ++i) { // skip first open bracket
                if (view[i] == Open) {
                    ++bracket_count;
                    if (bracket_count == 1) {
                        start_pos = i;
                    }
                } else if (view[i] == Close) {
                    --bracket_count;
                    if (bracket_count == 0) {
                        end_pos = i;
                        auto substring = view.substr(start_pos, end_pos - start_pos + 1);
                        children.push_back(substring);
                    }
                }
            }
            return children;
        }

        // TODO: Add reading by one dvalue-tree
        bool DValueSerializer::Deserialize(std::istream& in, std::shared_ptr<DValue> dvalue) {
            std::string buffer(std::istreambuf_iterator<char>(in), {});
            if (buffer.empty()) {
                return false;
            }

            std::string_view view(buffer);
            RecursiveDeserialize(view, dvalue);
            return true;
        }

        bool DValueSerializer::Serialize(std::ostream& out, std::shared_ptr<DValue> dvalues) {
            out << Open << dvalues->Name();
            for (size_t i = 0; i < dvalues->Size(); i++) {
                Serialize(out, dvalues->At(i));
            }
            out << Close;
            
            return true;
        }
    }
}