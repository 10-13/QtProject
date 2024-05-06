#include "DVRequire.h"
#include <map>

namespace qtproject {
    namespace data {
        namespace require
        {
            struct Requirement {
            private:
                using BuildMethod = void(*)(std::shared_ptr<qtproject::data::DValue> req);
            public:
                std::string Name;
                StructureChecker Checker;
                Requirement(std::string Name, BuildMethod builder) {
                    builder(Checker.Pattern);
                }
            };

            class GlobalTemplates {
            private:
                std::map<std::string, StructureChecker> Templates_;

            public:
                StructureChecker& GetByRequirementName(std::string Name) {
                    return Templates_[Name];
                }
                void AddRequirement(Requirement* req) {
                    if(Templates_.find(req->Name) == Templates_.end())
                        Templates_[req->Name] = StructureChecker{};
                    req->Checker.RestorePathes(Templates_[req->Name].Pattern);
                }
            };
        }
    }
}