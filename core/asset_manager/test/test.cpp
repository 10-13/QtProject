#include <fstream>

#include "core/asset_manager/AssetManager.h"
#include "core/data/DValue.h"


int main() {
    std::ifstream input_json("input.json", std::ios::binary);
    std::ofstream output_json("output.json", std::ios::binary);

    if (!input_json){
        std::cerr << "Error opening input.json\n";
        return 1;
    }

    if (input_json.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "input.json is empty\n";
        return 1;
    }

    if (!output_json){
        std::cerr << "Error opening output.json\n";
        return 1;
    }

    qtproject::data::AssetManager::Init(&input_json, &output_json);
    auto data = qtproject::data::AssetManager::Read();
    qtproject::data::AssetManager::Write(data);

    return 0;
}