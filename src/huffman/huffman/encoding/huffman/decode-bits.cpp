#include "encoding/huffman/decode-bits.h"


void decode_bits(io::InputStream& inputStream, const data::Node<Datum>& tree, io::OutputStream& outputStream)
{
	while (!inputStream.end_reached())
	{
		outputStream.write(decode_single_datum(inputStream, tree));
	}
}
