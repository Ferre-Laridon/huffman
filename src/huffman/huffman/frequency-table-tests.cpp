#ifdef TEST_BUILD

#include "catch.hpp"
#include "frequency-table.h"


TEST_CASE("Frequency Table")
{
    data::FrequencyTable<char> freqtable;

    // add key and associate value 0 with it
    REQUIRE(freqtable['a'] == 0);

    // increment the key with 1, check if value becomes 1
    freqtable.increment('a');
    REQUIRE(freqtable['a'] == 1);

    // increment again, check if value becomes 2
    freqtable.increment('a');
    REQUIRE(freqtable['a'] == 2);

    // add and increment at the same time
    freqtable.increment('b');
    REQUIRE(freqtable['b'] == 1);
}

TEST_CASE("count_frequencies")
{
    std::vector<char> values = { 'a', 'b', 'c', 'd', 'a', 'a', 'b' };
    data::count_frequencies(values);

    REQUIRE(data::count_frequencies(values)['a'] == 3);
    REQUIRE(data::count_frequencies(values)['b'] == 2);
    REQUIRE(data::count_frequencies(values)['c'] == 1);
    REQUIRE(data::count_frequencies(values)['d'] == 1);
}

#endif