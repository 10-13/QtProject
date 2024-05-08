#include <fstream>
#include <iostream>

#include "core/includes/Includes.h"
#include "core/serializer/DValueSerializer.h"
#include "core/data/DValue.h"

using namespace qtproject::data;

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    if (!in){
        std::cerr << "Error opening input.txt\n";
        return 1;
    }

    if (in.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "input.txt is empty\n";
        return 1;
    }

    if (!out){
        std::cerr << "Error opening output.txt\n";
        return 1;
    }

    DValueSerializer serializer;
    serializer.Indent = true;
    auto dvalue = DValue::Create("");
    serializer.Deserialize(in, dvalue);
    serializer.Serialize(out, dvalue);

    in.close();
    out.close();
    return 0;
}