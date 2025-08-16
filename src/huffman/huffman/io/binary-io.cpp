#include <cstdint>
#include "memory-buffer.h"
#include "binary-io.h"

namespace io
{
	u64 read_bits(unsigned nbits, InputStream& input)
	{
        u64 result = 0;

        for (int i = 0; i < nbits; i++)
        {
            u64 bit = input.end_reached() ? 0 : input.read();

            result = (result << 1) | bit;
        }

        return result;
	}

	void write_bits(u64 value, unsigned nbits, OutputStream& output)
	{
        for (int i = nbits; i >= 1; i--) {
            output.write((value >> (i - 1)) & 1);
        }
	}
}