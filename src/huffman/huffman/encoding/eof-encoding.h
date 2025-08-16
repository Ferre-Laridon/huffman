#ifndef EOF_ENCODING_H
#define EOF_ENCODING_H

#include "encoding/encoding.h"
#include "io/data-endpoints.h"
#include "io/streams.h"

typedef uint64_t u64;

namespace encoding
{
	std::shared_ptr<EncodingImplementation> create_eof_implementation(u64 domain_size);

	template<u64 N>
	Encoding<N, N + 1> eof_encoding()
	{
		return Encoding<N, N + 1>(create_eof_implementation(N));
	}
}

#endif