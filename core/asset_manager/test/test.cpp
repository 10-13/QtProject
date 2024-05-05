#include <fstream>

#include "core/asset_manager/AssetManager.h"
#include "core/data/DValue.h"


int main() {
    using  qtproject::data::AssetManager;

    std::ifstream input_json("input.json");
    std::ofstream output_json("output.json");

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

    AssetManager::Init(&input_json, &output_json);
    auto data = qtproject::data::AssetManager::Read();
    AssetManager::Write(data);

    return 0;
}