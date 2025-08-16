#ifndef BINARY_IO_H
#define BINARY_IO_H

#include <cstdint>
#include "memory-buffer.h"

namespace io
{
	typedef uint64_t u64;

	u64 read_bits(unsigned nbits, InputStream& input);

	void write_bits(u64 value, unsigned nbits, OutputStream& output);
}

#endif
