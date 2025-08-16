#ifdef TEST_BUILD

#include "catch.hpp"
#include "encoding/bit-grouper.h"
#include "io/memory-buffer.h"
#include "io/binary-io.h"
#include "encoding/encoding.h"

TEST_CASE("Encode with buffer size of 16")
{
    io::MemoryBuffer<2> bits;
    io::MemoryBuffer<16> output;

    auto outputStream = bits.destination()->create_output_stream();

    io::write_bits(0b0000, 4, *outputStream);
    io::write_bits(0b0001, 4, *outputStream);
    io::write_bits(0b1000, 4, *outputStream);
    io::write_bits(0b1111, 4, *outputStream);

    encoding::encode(bits.source(), encoding::bit_grouper<4>(), output.destination());

    auto reader = output.source()->create_input_stream();

    REQUIRE(reader->read() == 0b0000);
    REQUIRE(reader->read() == 0b0001);
    REQUIRE(reader->read() == 0b1000);
    REQUIRE(reader->read() == 0b1111);
}

TEST_CASE("Encode with buffer size of 256")
{
    io::MemoryBuffer<2> bits;
    io::MemoryBuffer<256> output;

    auto outputStream = bits.destination()->create_output_stream();

    io::write_bits(0b00000000, 8, *outputStream);
    io::write_bits(0b00000001, 8, *outputStream);
    io::write_bits(0b10000000, 8, *outputStream);
    io::write_bits(0b11111111, 8, *outputStream);

    encoding::encode(bits.source(), encoding::bit_grouper<8>(), output.destination());

    auto reader = output.source()->create_input_stream();

    REQUIRE(reader->read() == 0b00000000);
    REQUIRE(reader->read() == 0b00000001);
    REQUIRE(reader->read() == 0b10000000);
    REQUIRE(reader->read() == 0b11111111);
}

TEST_CASE("Decode with buffer size of 16") {
    io::MemoryBuffer<16> input;
    io::MemoryBuffer<2> bits;

    input.data()->push_back(0b0000);
    input.data()->push_back(0b0001);
    input.data()->push_back(0b1000);
    input.data()->push_back(0b1111);

    encoding::decode(input.source(), encoding::bit_grouper<4>(), bits.destination());

    auto reader = bits.source()->create_input_stream();

    REQUIRE(io::read_bits(4, *reader) == 0b0000);
    REQUIRE(io::read_bits(4, *reader) == 0b0001);
    REQUIRE(io::read_bits(4, *reader) == 0b1000);
    REQUIRE(io::read_bits(4, *reader) == 0b1111);
}

TEST_CASE("Decode with buffer size of 256") {
    io::MemoryBuffer<256> input;
    io::MemoryBuffer<2> bits;

    input.data()->push_back(0b00000000);
    input.data()->push_back(0b00000001);
    input.data()->push_back(0b10000000);
    input.data()->push_back(0b11111111);

    encoding::decode(input.source(), encoding::bit_grouper<8>(), bits.destination());

    auto reader = bits.source()->create_input_stream();

    REQUIRE(io::read_bits(8, *reader) == 0b00000000);
    REQUIRE(io::read_bits(8, *reader) == 0b00000001);
    REQUIRE(io::read_bits(8, *reader) == 0b10000000);
    REQUIRE(io::read_bits(8, *reader) == 0b11111111);
}

#endif // BUILD_TEST