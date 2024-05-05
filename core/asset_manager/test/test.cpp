#include <fstream>

#include "core/asset_manager/AssetManager.h"
#include "core/data/DValue.h"


int main() {
    std::ifstream input_json("test_input.json");
    std::ofstream output_json("test_output.json");
    qtproject::data::AssetManager::Init(&input_json, &output_json);
    auto data = qtproject::data::AssetManager::Read();
    qtproject::data::AssetManager::Write(data);

    return 0;
}