#include "encoding/huffman/tree-encoding.h"

namespace encoding
{
	namespace huffman
	{
        void encode_tree(const data::Node<Datum>& root, unsigned bits_per_datum, io::OutputStream& outputStream)
        {
            const data::Leaf<Datum>* leaf = dynamic_cast<const data::Leaf<Datum>*>(&root);

            if (leaf != nullptr) {
                io::write_bits(0b0, 1, outputStream);
                io::write_bits(leaf->get_value(), bits_per_datum, outputStream);
            }
            else 
            {
                const data::Branch<Datum>& branch = static_cast<const data::Branch<Datum>&>(root);
                io::write_bits(0b1, 1, outputStream);
                encode_tree(branch.get_left_child(), bits_per_datum, outputStream);
                encode_tree(branch.get_right_child(), bits_per_datum, outputStream);
            }
        }

        std::unique_ptr<data::Node<Datum>> decode_tree(unsigned bits_per_datum, io::InputStream& inputStream)
        {
            Datum firstBit = inputStream.read();

            if (firstBit == 0) 
            {
                std::unique_ptr<data::Leaf<Datum>> value = std::make_unique<data::Leaf<Datum>>(io::read_bits(bits_per_datum, inputStream));
                return value;
            }
            else 
            {
                std::unique_ptr<data::Node<Datum>> left_child = decode_tree(bits_per_datum, inputStream);
                std::unique_ptr<data::Node<Datum>> right_child = decode_tree(bits_per_datum, inputStream);
                return std::make_unique<data::Branch<Datum>>(std::move(left_child), std::move(right_child));
            }
        }

	}
}