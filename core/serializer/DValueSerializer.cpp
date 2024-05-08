#include "core/serializer/DValueSerializer.h"

namespace qtproject {
    namespace data {
        std::string DValueSerializer::GetValidStr(std::string&& name) {
            auto begin_pos = name.find_first_not_of("\n\t ");
            auto end_pos = name.find_last_not_of("\n\t ");
            return name.substr(begin_pos, end_pos - begin_pos + 1);
        }

        void DValueSerializer::RecursiveDeserialize(std::string_view view, std::shared_ptr<DValue> dvalue) { 
            dvalue->Name() = GetValidStr(GetCurrentName(view));
            for (auto child_view : GetChildren(view)) {
                RecursiveDeserialize(child_view, dvalue->Add(""));
            }
        }

        std::string DValueSerializer::GetCurrentName(std::string_view view) {
            size_t end_pos = 0;
            for (size_t i = 1; i != view.size(); ++i) { // skip first open bracket
                if (view[i] == Open || view[i] == Close) {
                    end_pos = i;
                    break;
                }
            }
            return std::string(view.substr(1, end_pos - 1));
        }

        std::vector<std::string_view> DValueSerializer::GetChildren(std::string_view view) {
            std::vector<std::string_view> children;
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

        bool DValueSerializer::Deserialize(std::istream& in, std::shared_ptr<DValue> dvalue) {
            [[maybe_unused]] char symb_buf;
            in >> symb_buf;

            if (in.eof()) {
                return false;
            }
            in.seekg(-1, std::ios::cur);

            // Read block
            std::string buffer;
            size_t bracket_count = 0;
            do{
                in >> symb_buf;
                if(symb_buf == Open) {
                    ++bracket_count;
                } else if(symb_buf == Close) {
                    --bracket_count;
                }
                buffer.push_back(symb_buf);
            } while(bracket_count != 0);

            // Clear from garbage
            auto begin_pos = buffer.find_first_of(Open);
            buffer.erase(0, begin_pos);

            std::string_view view(buffer);
            RecursiveDeserialize(view, dvalue);
            return true;
        }

        void DValueSerializer::RecursiveSerialize(std::ostream& out, 
                                    std::shared_ptr<DValue> dvalues, size_t depth) {
            if (Indent) {
                out << (depth > 0 ? "\n" : "") << std::string(depth, '\t');
            }
            out << Open << dvalues->Name();
            for (auto dvalue : dvalues->Subvalues()) {
                RecursiveSerialize(out, dvalue, depth + 1);
            }
            out << (Indent ? "\n" + std::string(depth, '\t') : "");
            out << Close;
        }

        void DValueSerializer::Serialize(std::ostream& out, std::shared_ptr<DValue> dvalues) {
            RecursiveSerialize(out, dvalues, 0);
        }
    }
}