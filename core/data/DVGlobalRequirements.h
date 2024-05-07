#pragma once

#include "DVRequire.h"
#include <map>
#include <iostream>

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
                Requirement(std::string Name, BuildMethod builder) : Name(Name) {
                    Checker.Pattern = std::make_shared<DValue>(Name);
                    builder(Checker.Pattern);
                    PushToGlob_();
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
                static bool Contains(std::string Name) {
                    return Templates_.find(Name) != Templates_.end();
                }
                static void AddRequirement(Requirement* req) {
                    if(!Contains(req->Name)) {  
                        Templates_.emplace(req->Name, StructureChecker{});  
                        Templates_[req->Name].Pattern = DValue::Create(req->Name);
                    }
                    req->Checker.RestorePathes(Templates_[req->Name].Pattern, StructureChecker::TreatPatternValuesAsPath);
                }
            };

            std::map<std::string, StructureChecker> GlobalTemplates::Templates_{};

            void Requirement::PushToGlob_() {
                GlobalTemplates::AddRequirement(this);
            }
        }
    }
}