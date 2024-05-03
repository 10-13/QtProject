#include "core/includes/Includes.h"

namespace qtproject
{
    namespace data
    {
        class DValue {
            private:
            std::vector<std::shared_ptr<DValue>> Subvalues_;
            std::string Name_{"ERROR"};

            public:
            DValue() = default;
            DValue(std::string Name) : Name_(Name) {}

            std::vector<std::shared_ptr<DValue>>& Subvalues() {
                return Subvalues_;
            }

            std::shared_ptr<DValue> Add(std::string Name) {
                auto r = std::make_shared<DValue>(Name);
                Subvalues_.push_back(r);
                return r;
            }

            std::string Name() {
                return Name_;
            }

            std::string Content() {
                if(Subvalues_.size() == 0)
                    return "";
                return Subvalues_[0]->Name_;
            }

            std::shared_ptr<DValue> At(std::string Name) {
                for(auto i : Subvalues_)
                    if(i->Name_ == Name)
                        return i;
                return {};
            }

            std::string operator*() {
                return Content();
            }

            std::shared_ptr<DValue> operator[](std::string Name) {
                return At(Name);
            }
        };
    }
}