#ifndef HUFFMAN_ENCODING_H
#define HUFFMAN_ENCODING_H

#include "util.h"
#include "encoding/encoding.h"

std::shared_ptr<encoding::EncodingImplementation> create_huffman_implementation(unsigned domain_size);

template<unsigned DOMAIN_SIZE>
encoding::Encoding<DOMAIN_SIZE, 2>huffman()
{
	return encoding::Encoding<DOMAIN_SIZE, 2>(create_huffman_implementation(DOMAIN_SIZE));
}

#endif // !HUFFMAN_ENCODING_H
