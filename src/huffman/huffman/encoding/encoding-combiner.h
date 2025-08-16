#ifndef ENCODING_COMBINER_H
#define ENCODING_COMBINER_H

#include "encoding/encoding.h"
#include "io/streams.h"
#include "io/memory-buffer.h"

namespace encoding
{
	template<u64 N1, u64 N2, u64 N3>
	class EncodingCombinerImplementation : public EncodingImplementation
	{
		Encoding<N1, N2> e1;
		Encoding<N2, N3> e2;
		
	public:
		EncodingCombinerImplementation(Encoding<N1, N2> e1, Encoding<N2, N3> e2) : e1(e1), e2(e2) 
		{
					
		}

		void encode(io::InputStream& in, io::OutputStream& out)
		{
			io::MemoryBuffer<N2> temp;

			e1->encode(in, *(temp.destination()->create_output_stream()));
			e2->encode(*(temp.source()->create_input_stream()), out);
		}

		void decode(io::InputStream& in, io::OutputStream& out) {
			io::MemoryBuffer<N2> temp;

			e2->decode(in, *(temp.destination()->create_output_stream()));
			e1->decode(*(temp.source()->create_input_stream()), out);
		}
	};

	template<u64 N1, u64 N2, u64 N3>
	Encoding<N1, N3> operator | (encoding::Encoding<N1, N2>e1, encoding::Encoding<N2, N3>e2) {
		return Encoding<N1, N3>(std::make_shared<EncodingCombinerImplementation<N1, N2, N3>>(e1, e2));
	}
}

#endif