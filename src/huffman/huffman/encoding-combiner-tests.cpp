#ifdef TEST_BUILD

#include "catch.hpp"
#include "io/memory-buffer.h"
#include "encoding/eof-encoding.h"
#include "encoding/bit-grouper.h"
#include "encoding/encoding-combiner.h"
#include "encoding/bit-grouper.h"

TEST_CASE("Test encode and decode combiner with size 16 and 17") {
	io::MemoryBuffer<17> inputStream;
	io::MemoryBuffer<18> outputStream;

	for (int i = 0; i < 17; i++)
	{
		inputStream.data()->push_back(i);
	}

	auto eof1 = encoding::eof_encoding<17>();
	auto eof2 = encoding::eof_encoding<18>();

	auto combiner = eof1 | eof2;

	auto input = inputStream.source()->create_input_stream();
	auto output = outputStream.destination()->create_output_stream();

	combiner->encode(*input, *output);

	io::MemoryBuffer<17> inputStreamDestination;

	auto inputDecode = outputStream.source()->create_input_stream();
	auto outputDecode = inputStreamDestination.destination()->create_output_stream();

	combiner->decode(*inputDecode, *outputDecode);

	for (int i = 0; i < 17; i++)
	{
		REQUIRE(std::find(inputStreamDestination.data()->begin(), inputStreamDestination.data()->end(), i) != inputStreamDestination.data()->end());
	}

	// Check if eof encoding is gone
	REQUIRE(std::find(inputStreamDestination.data()->begin(), inputStreamDestination.data()->end(), 17) == inputStreamDestination.data()->end());
	REQUIRE(std::find(inputStreamDestination.data()->begin(), inputStreamDestination.data()->end(), 18) == inputStreamDestination.data()->end());

	// Check if input and output are the same
	REQUIRE(*inputStream.data() == *inputStreamDestination.data());

}

#endif // TEST_BUILD
