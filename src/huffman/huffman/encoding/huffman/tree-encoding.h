#ifndef TREE_ENCODING_H
#define TREE_ENCODING_H

#include "io/binary-io.h"
#include "data/binary-tree.h"

namespace encoding
{
	namespace huffman
	{
		void encode_tree(const data::Node<Datum>& root, unsigned bits_per_datum, io::OutputStream& outputStream);
		std::unique_ptr<data::Node<Datum>> decode_tree(unsigned bits_per_datum, io::InputStream& inputStream);
	}
}

#endif // !TREE_ENCODING_H
