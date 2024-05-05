#pragma once

#include <iostream>
#include <nlohmann/json.hpp>

#include "core/includes/Includes.h"
#include "core/data/DValue.h"

namespace qtproject
{
    namespace data
    {
        class AssetManager {
            private:
            using json = nlohmann::json;

            inline static AssetManager* manager_{nullptr};
            std::istream* is_{nullptr};
            std::ostream* os_{nullptr};

            AssetManager(std::istream* is, std::ostream* os) : is_(is), os_(os) {
            }

            AssetManager(std::ostream* os) : os_(os) {
            }

            void ReadJson(const json& j, std::shared_ptr<DValue> dvalue) {
                for(size_t i = 0; i < j["Subvalues_"].size(); ++i) {
                    auto& item = j["Subvalues_"][i];
                    dvalue->Add(item["Name_"].template get<std::string>());
                    if (!item["Subvalues_"].empty()) {
                        ReadJson(item, dvalue->At(item["Name_"].template get<std::string>()));
                    }
                }
            }

            void WriteJson(json& j, const std::shared_ptr<DValue>& dvalue) {
                j["Name_"] = dvalue->Name();
                j["Subvalues_"] = std::vector<json>(dvalue->Size());

                if (dvalue->Size() > 0) {
                    for(size_t i = 0; i < dvalue->Size(); ++i){
                        WriteJson(j["Subvalues_"][i], dvalue->Subvalues()[i]);
                    }
                }
            }

            public:
            static AssetManager& Init(std::istream* is, std::ostream* os = nullptr) {
                if (manager_ != nullptr)
                    delete manager_;
                manager_ = new AssetManager(is, os);
                return *manager_;
            }

            static AssetManager& Init(std::ostream* os) {
                if (manager_ != nullptr)
                    delete manager_;
                manager_ = new AssetManager(os);
                return *manager_;
            }


            static bool InitedToWrite() {
                return manager_ != nullptr && manager_->os_ != nullptr;
            }

            static bool InitedToRead() {
                return manager_ != nullptr && manager_->is_ != nullptr;
            }

            static std::vector<std::shared_ptr<DValue>> Read() {
                if (!InitedToRead()) {
                    return {};
                }

                json j;
                *manager_->is_ >> j["Data"];

                std::vector<std::shared_ptr<DValue>> result;
                for(auto& item : j["Data"]) {
                    result.push_back(DValue::Create(item["Name_"].template get<std::string>()));
                    if (!item["Subvalues_"].empty()) {
                        manager_->ReadJson(item, result.back());
                    } else {
                        result.back()->Add(item["Name_"].template get<std::string>());
                    }
                }
                return result;
            }

            static void Write(const std::vector<std::shared_ptr<DValue>>& data) {
                if (!InitedToWrite())
                    return;

                json j;
                j["Data"] = std::vector<json>(data.size());
                j = j["Data"];

                for(size_t i = 0; i < data.size(); ++i) {
                    manager_->WriteJson(j[i], data[i]);
                }
                *manager_->os_ << j.dump(4);
            }

            static void Close() {
                delete manager_;
                manager_ = nullptr;
            }

        };
    }
}