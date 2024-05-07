#pragma once

#include "DVRequire.h"
#include <map>

namespace qtproject {
    namespace data {
        namespace require
        {
            struct Requirement {
            private:
                using BuildMethod = void(*)(std::shared_ptr<qtproject::data::DValue> req);
                std::string Name;
                StructureChecker Checker;

                void PushToGlob_();
            public:
                Requirement(std::string Name, BuildMethod builder) {
                    Checker.Pattern = std::make_shared<DValue>(Name);
                    builder(Checker.Pattern);
                }

                const StructureChecker& GetChecker() {
                    return Checker;
                }

                friend class GlobalTemplates;
            };

            class GlobalTemplates {
            private:
                static std::map<std::string, StructureChecker> Templates_;

            public:
                static const StructureChecker& GetByRequirementName(std::string Name) {
                    return Templates_[Name];
                }
                static void AddRequirement(Requirement* req) {
                    if(Templates_.find(req->Name) == Templates_.end())
                        Templates_[req->Name] = StructureChecker{};
                    req->Checker.RestorePathes(Templates_[req->Name].Pattern);
                }
            };

            void Requirement::PushToGlob_() {
                GlobalTemplates::AddRequirement(this);
            }
        }
    }
}