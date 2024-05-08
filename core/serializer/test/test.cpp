#include <catch2/catch_all.hpp>
#include <sstream>
#include <iostream>

#include "core/includes/Includes.h"
#include "core/serializer/DValueSerializer.h"
#include "core/data/DValue.h"

using namespace qtproject::data;

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
        serializer.Indent = false;
        serializer.Serialize(ss, dvalue);
        REQUIRE(ss.str() == "[main[child1][child2][child3]]");
    }
}