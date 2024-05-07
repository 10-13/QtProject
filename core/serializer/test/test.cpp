#include <catch2/catch_all.hpp>
#include <fstream>

#include "core/includes/Includes.h"
#include "core/serializer/DValueSerializer.h"
#include "core/data/DValue.h"

using namespace qtproject::data;

TEST_CASE("Simple") {
    DValueSerializer serializer;
    std::shared_ptr<DValue> dvalue;

    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    if(!in) {
        FAIL("Cannot open input file.");
        std::exit(1);
    }

    if (in.peek() == std::ifstream::traits_type::eof()) {
        FAIL("Input file is empty.");
        std::exit(1);
    }

    if(!out) {
        FAIL("Cannot open output file.");
        std::exit(1);
    }

    serializer.Serialize(in, dvalue);
    serializer.Deserialize(out, dvalue);

    out.close();
    std::ifstream in2("output.txt");

    std::string buf1, buf2;
    while (std::getline(in, buf1) && std::getline(in2, buf2)) {
        REQUIRE(buf1 == buf2);
    }

    in.close();
    in2.close();
}