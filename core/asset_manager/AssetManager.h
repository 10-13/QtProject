#pragma once

#include <iostream>
#include <nlohmann/json.hpp>

#include "core/includes/Includes.h"

namespace qtproject
{
    namespace data
    {
        class AssetManager {
            private:
            inline static AssetManager* manager_{nullptr};
            std::ostream* os_{nullptr};
            std::istream* is_{nullptr};

            AssetManager(std::ostream* os, std::istream* is) : os_(os), is_(is) {
            }

            AssetManager(std::istream* is) : is_(is) {
            }

            public:
            static AssetManager& Init(std::ostream* os, std::istream* is = nullptr) {
                if (manager_ != nullptr)
                    delete manager_;
                manager_ = new AssetManager(os, is);
                return *manager_;
            }

            static AssetManager& Init(std::istream* is) {
                if (manager_ != nullptr)
                    delete manager_;
                manager_ = new AssetManager(is);
                return *manager_;
            }


            static bool InitedToWrite() {
                return manager_ != nullptr && manager_->os_ != nullptr;
            }

            static bool InitedToRead() {
                return manager_ != nullptr && manager_->is_ != nullptr;
            }

            static void Close() {
                delete manager_;
                manager_ = nullptr;
            }

        };
    }
}