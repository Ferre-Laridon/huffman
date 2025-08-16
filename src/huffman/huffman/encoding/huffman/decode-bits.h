#ifndef DECODE_BITS_H
#define DECODE_BITS_H

#include "io/streams.h"
#include "data/binary-tree.h"
#include "encoding/huffman/decode-single-datum.h"

void decode_bits(io::InputStream& inputStream, const data::Node<Datum>& tree, io::OutputStream& outputStream);

#endif // !DECODE_BITS_H
