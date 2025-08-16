#ifdef TEST_BUILD


#include "catch.hpp"
#include "io/binary-io.h"
#include "io/memory-buffer.h"

void check(u64 n, unsigned nbits)
{
    io::MemoryBuffer<2> buffer;
    auto input = buffer.source()->create_input_stream();
    auto output = buffer.destination()->create_output_stream();
    io::write_bits(n, nbits, *output);
    auto result = io::read_bits(nbits, *input);

    REQUIRE(n == result);
}

TEST_CASE("write_bits and read_bits functions work correctly") 
{
    check(0, 1);
    check(3, 2);
    check(4, 3);
    check(10, 4);
    check(53, 8);
    check(128, 8);
    check(255, 8);
    check(256, 9);
    check(512, 10);
    check(1024, 11);
    check(2681, 12);
    check(25170, 15);
    check(135697, 18);
    check(797542119, 30);
    check(2147483640, 31);
    check(1125899906842623, 50);
    check(1152921504606846975, 60);
    check(18446744073709551610, 64);
}

#endif // TEST_BUILD
