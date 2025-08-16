#ifdef TEST_BUILD

#include <iostream>
#include <string>
#include "data/binary-tree.h"
#include "catch.hpp"

// Test Leaf class
TEST_CASE("Leaf class")
{
    SECTION("Get value")
    {
        int value = 5;
        data::Leaf<int> leaf(value);
        REQUIRE(leaf.get_value() == value);
    }
}

#endif // TEST_BUILD
