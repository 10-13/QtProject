#include "DVRequire.h"
#include <map>

namespace qtproject {
    namespace data {
        namespace require
        {
            struct Requirement {
                std::string Name;
                StructureChecker Checker;
            };

            class GlobalTemplates {
            private:
                std::map<std::string, Requirement*> Templates_;

            public:
                StructureChecker& GetByRequirementName(std::string Name) {
                    return Templates_[Name]->Checker;
                }
                void AddRequirement(Requirement* req) {
                    Templates_[req->Name] = req;
                }
            };
        }
    }
}