#include <catch2/catch_all.hpp>

#include "core/includes/Includes.h"
#include "core/serializer/DValueSerializer.h"
#include "core/data/DValue.h"

using namespace qtproject::data;

TEST_CASE("Simple") {
    REQUIRE(1 == 1);
}