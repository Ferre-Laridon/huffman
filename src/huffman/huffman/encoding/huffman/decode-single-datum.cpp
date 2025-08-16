#include "encoding/huffman/decode-single-datum.h"

Datum decode_single_datum(io::InputStream& inputStream, const data::Node<Datum>& tree)
{
	const data::Branch<Datum>* branch = dynamic_cast<const data::Branch<Datum>*>(&tree);

	if (branch != nullptr)
	{
		if (inputStream.end_reached())
		{
			return Datum(0);
		}

		const Datum bit = inputStream.read();

		if (bit == 0)
		{
			return decode_single_datum(inputStream, branch->get_left_child());
		}

		return decode_single_datum(inputStream, branch->get_right_child());
	}

	const data::Leaf<Datum>& leaf = static_cast<const data::Leaf<Datum>&>(tree);
	return leaf.get_value();
}
