#include "encoding/huffman/tree-encoding.h"
#include "encoding/huffman/copy-to-vector.h"
#include "frequency-table.h"
#include "util.h"
#include "encoding/huffman/build-tree.h"
#include "encoding/huffman/build-codes.h"
#include "encoding/encoding.h"
#include <utility>
#include "encoding/huffman/decode-bits.h"
#include "huffman-encoding.h"

namespace
{
	class HuffmanEncodingImplementation : public encoding::EncodingImplementation
	{
		const u64 domain_size;

	public:
		HuffmanEncodingImplementation(const u64 domain_size) : domain_size(domain_size)
		{

		}

		void encode(io::InputStream& inputStream, io::OutputStream& outputStream)
		{
			auto copy = copy_to_vector(inputStream);
			auto frequency = data::count_frequencies<Datum>(*copy);
			auto tree = build_tree(frequency);
			auto codes = build_codes(*tree, domain_size);

			std::function<Datum(std::pair<Datum, unsigned long>)> function = [](std::pair<Datum, unsigned long> pair) { return pair.first; };
			auto map = data::map<std::pair<Datum, unsigned long>, Datum>(*tree, function);

			encoding::huffman::encode_tree(*map, bits_needed(domain_size), outputStream);

			for (Datum data : *copy)
			{
				for (unsigned i = 0; i < codes->at(data).size(); ++i)
				{
					io::write_bits(codes->at(data).at(i), 1, outputStream);
				}
			}
		}

		void decode(io::InputStream& inputStream, io::OutputStream& outputStream)
		{
			auto tree = encoding::huffman::decode_tree(bits_needed(domain_size), inputStream);
			decode_bits(inputStream, *tree, outputStream);
		}
	};
}

std::shared_ptr<encoding::EncodingImplementation> create_huffman_implementation(unsigned domain_size)
{
	return std::make_unique<HuffmanEncodingImplementation>(domain_size);
}
