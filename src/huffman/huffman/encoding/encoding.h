#ifndef ENCODING_H
#define ENCODING_H

#include "io/streams.h"
#include "io/data-endpoints.h"

namespace encoding
{
	class EncodingImplementation
	{
	public:
		// virtual destructor
		virtual ~EncodingImplementation() {}

		virtual void encode(io::InputStream& inputStream, io::OutputStream& outputStream) = 0;
		virtual void decode(io::InputStream& inputStream, io::OutputStream& outputStream) = 0;
	};

	template<u64 IN, u64 OUT>
	class Encoding
	{
		std::shared_ptr<EncodingImplementation> encodingImplementation;

	public:
		Encoding(std::shared_ptr<EncodingImplementation> encodingImplementation) : encodingImplementation(encodingImplementation) {}

		EncodingImplementation* operator -> ()
		{
			return encodingImplementation.get();
		}

		const EncodingImplementation* operator -> () const
		{
			return encodingImplementation.get();
		}
	};

	template<u64 IN, u64 OUT>
	void encode(io::DataSource<IN> source, Encoding<IN, OUT> huffman, io::DataDestination<OUT> destination)
	{
		// Ask data source for input stream
		auto inputStream = source->create_input_stream();
		// Ask data destination for output stream
		auto outputStream = destination->create_output_stream();
		// Call encode method
		huffman->encode(*inputStream, *outputStream);
	}

	template<u64 IN, u64 OUT>
	void decode(io::DataSource<IN> source, Encoding<OUT, IN> huffman, io::DataDestination<OUT> destination)
	{
		// Ask data source for input stream
		auto inputStream = source->create_input_stream();
		// Ask data destination for output stream
		auto outputStream = destination->create_output_stream();
		// Call decode method
		huffman->decode(*inputStream, *outputStream);
	}
}

#endif