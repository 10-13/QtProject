#include <catch2/catch_all.hpp>
#include <fstream>

#include "core/includes/Includes.h"
#include "core/serializer/DValueSerializer.h"
#include "core/data/DValue.h"

using namespace qtproject::data;

TEST_CASE("DValueSerializer::GetCurrentName test") {
    DValueSerializer serializer;
    {
    std::string_view view = "[name]";
    REQUIRE(serializer.GetCurrentName(view) == "name");
    }
    {
    std::string_view view = "[main[child[child1]][child2]]";
    REQUIRE(serializer.GetCurrentName(view) == "main");
    }
    {
    std::string_view view = "[main[child0][child1][child2][child3]]";
    REQUIRE(serializer.GetCurrentName(view) == "main");
    }
}

template<typename ViewVec>
void Check(ViewVec& vec, std::vector<std::string_view> expected) {
    REQUIRE(vec.size() == expected.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        REQUIRE(vec[i] == expected[i]);
    }
}

TEST_CASE("DValueSerializer::GetChildren test") {
    DValueSerializer serializer;
    {
    std::string_view view = "[name[child1[child1_1][child1_2]][child2]]";
    std::vector<std::string_view> expected = {
        "[child1[child1_1][child1_2]]",
        "[child1_2]]"
    };
    auto current = serializer.GetChildren(view);
    Check(current, expected);
    }
    {
    std::string_view view = "[name[child1[child1_1][child1_2]][child2[child2_1][child2_2]]]";
    std::vector<std::string_view> expected = {
        "[child1[child1_1][child1_2]]",
        "[child2[child2_1][child2_2]]"
    };
    auto current = serializer.GetChildren(view);
    Check(current, expected);
    }
}

/*
TEST_CASE("std::ifstream and std::ofstream test") {
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

    serializer.Deserialize(in, dvalue);
    serializer.Serialize(out, dvalue);

    out.close();
    std::ifstream in2("output.txt");

    std::string buf1, buf2;
    while (std::getline(in, buf1) && std::getline(in2, buf2)) {
        REQUIRE(buf1 == buf2);
    }

    in.close();
    in2.close();
}
*/