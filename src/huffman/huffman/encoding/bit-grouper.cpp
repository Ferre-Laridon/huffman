#include "encoding/bit-grouper.h"
#include "io/streams.h"
#include "io/binary-io.h"

namespace
{
	class BitGrouperImplementation : public encoding::EncodingImplementation
	{
		unsigned group_size;

	public:
		BitGrouperImplementation(unsigned group_size) : group_size(group_size) {}

		void encode(io::InputStream& inputStream, io::OutputStream& outputStream) {
			while (!inputStream.end_reached()) {
				u64 grouped_bits = io::read_bits(group_size, inputStream);
				outputStream.write(grouped_bits);
			}
		}

		void decode(io::InputStream& inputStream, io::OutputStream& outputStream) {
			while (!inputStream.end_reached()) {
				u64 split_bits = inputStream.read();
				io::write_bits(split_bits, group_size, outputStream);
			}
		}
	};
}

std::shared_ptr<encoding::EncodingImplementation> encoding::create_bit_grouper_implementation(unsigned group_size)
{
	return std::make_shared<BitGrouperImplementation>(group_size);
}