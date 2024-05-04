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

            size_t Size() {
                return Subvalues_.size();
            }

            bool IsValue() {
                return Subvalues_.size() == 0;
            }

            std::string Content(size_t index = 0) {
                if(Subvalues_.size() == 0)
                    return "";
                return Subvalues_[index]->Name_;
            }

            std::shared_ptr<DValue> At(std::string Name) {
                for(auto i : Subvalues_)
                    if(i->Name_ == Name)
                        return i;
                return {};
            }

            std::shared_ptr<DValue> At(size_t index) {
                return Subvalues_[index];
            }

            std::string operator*() {
                return Content();
            }

            std::shared_ptr<DValue> operator[](std::string Name) {
                return At(Name);
            }

            std::string operator[](size_t index) {
                return Content(index);
            }

            static std::shared_ptr<DValue> Create(std::string Name) {
                return std::make_shared<DValue>(Name);
            }
        };
    }
}