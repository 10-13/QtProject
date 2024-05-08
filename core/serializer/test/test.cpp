#include <catch2/catch_all.hpp>
#include <sstream>

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
        "[child2]"
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


TEST_CASE("Serialize test") {
    {
        DValueSerializer serializer;
        std::shared_ptr<DValue> dvalue = DValue::Create("main");
        dvalue->Add("child1");
        dvalue->Add("child2");
        dvalue->Add("child3");
        std::ostringstream out;
        serializer.Serialize(out, dvalue);
        REQUIRE(out.str() == "[main[child1][child2][child3]]");
    }
    {
        DValueSerializer serializer;
        std::shared_ptr<DValue> dvalue = DValue::Create("main");
        dvalue->Add("child1");
        dvalue->Add("child2");
        dvalue->Add("child3");
        dvalue->At(0)->Add("child1_1");
        dvalue->At(0)->Add("child1_2");
        dvalue->At(1)->Add("child2_1");
        dvalue->At(1)->Add("child2_2");
        dvalue->At(1)->At(0)->Add("child2_1_1");
        std::ostringstream out;
        serializer.Serialize(out, dvalue);
        REQUIRE(out.str() == "[main[child1[child1_1][child1_2]][child2[child2_1[child2_1_1]][child2_2]][child3]]");
    }
}

TEST_CASE("Deserialize test") {
    {
        std::stringstream ss("[main[child1][child2][child3]]");
        DValueSerializer serializer;
        std::shared_ptr<DValue> dvalue = DValue::Create("");
        serializer.Deserialize(ss, dvalue);
        
        ss.str("");
        serializer.Serialize(ss, dvalue);
        REQUIRE(ss.str() == "[main[child1][child2][child3]]");
    }
}