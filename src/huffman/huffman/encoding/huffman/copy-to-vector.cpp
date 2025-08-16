#include "copy-to-vector.h"

std::unique_ptr<std::vector<Datum>> copy_to_vector(io::InputStream& input)
{
	auto copy = std::make_unique<std::vector<Datum>>();
	while (!input.end_reached()) 
	{
		copy->push_back(input.read());
	}

	return std::move(copy);
}