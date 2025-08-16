#ifdef TEST_BUILD

#include "catch.hpp"
#include "encoding/encoding.h"
#include "encoding/eof-encoding.h"
#include "io/memory-buffer.h"

TEST_CASE("EOF Encoding with domain size 17 and 18")
{
    // Create 2 MemoryBuffers with domain sizes 17 and 18
    io::MemoryBuffer<17> inputBuffer;
    io::MemoryBuffer<18> outputBuffer;

    // Populate the input buffer
    for (int i = 0; i < 17; i++)
    {
        inputBuffer.data()->push_back(i);
    }

    // Apply EOF encoding on the input buffer and store the result in the output buffer
    encoding::encode<17, 18>(inputBuffer.source(), encoding::eof_encoding<17>(), outputBuffer.destination());

    // Check that the output buffer has one more element, which is the EOF symbol
    REQUIRE(std::find(outputBuffer.data()->begin(), outputBuffer.data()->end(), 17) != outputBuffer.data()->end());
}

TEST_CASE("EOF Decoding with domain size 17 and 18")
{
    // Create 2 MemoryBuffers with domain sizes 18 and 17
    io::MemoryBuffer<18> encodedBuffer;
    io::MemoryBuffer<17> decodedBuffer;

    // Populate the encodedBuffer
    for (int i = 0; i < 18; i++)
    {
        encodedBuffer.data()->push_back(i);
    }

    // Apply EOF decoding on the encoded buffer and store the result in the decoded buffer
    encoding::decode<18, 17>(encodedBuffer.source(), encoding::eof_encoding<17>(), decodedBuffer.destination());

    // Check that the encoded buffer has one more element, which is the EOF symbol
    REQUIRE(std::find(decodedBuffer.data()->begin(), decodedBuffer.data()->end(), 16) != decodedBuffer.data()->end());
}


#endif