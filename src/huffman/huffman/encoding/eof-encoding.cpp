#include "encoding.h"
#include "eof-encoding.h"

namespace
{
	class EofEncodingImplementation : public encoding::EncodingImplementation
	{
	private:
		const u64 domain_size;

	public:
		EofEncodingImplementation(const u64 domain_size) : domain_size(domain_size)
		{

		}

		void encode(io::InputStream& inputStream, io::OutputStream& outputStream)
		{
			// Copy inputStream to outputStream
			while (!inputStream.end_reached())
			{
				outputStream.write(inputStream.read());
			}

			// Add new EOF symbol to outputStream.
			// This EOF symbol has to be a new symbol.
			// If the domain size is 256 you know that all existing symbols will range from 0 to 255.
			// The first new available symbol would be 256 ( = domain_size).
			outputStream.write(domain_size);
		}

		void decode(io::InputStream& inputStream, io::OutputStream& outputStream)
		{
			// Read first to avoid reading twice (in while loop and in check)
			auto input = inputStream.read();

			// Write inputStream to outputStream
			// Stop when it encounters EOF symbol (exclude EOF symbol from outputStream)
			while (!inputStream.end_reached() && input != domain_size)
			{
				outputStream.write(input);
				input = inputStream.read();
			}
		}
	};
}

std::shared_ptr<encoding::EncodingImplementation> encoding::create_eof_implementation(const u64 domain_size)
{
	return std::make_shared<EofEncodingImplementation>(domain_size);
}