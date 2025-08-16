#ifndef DECODE_SINGLE_DATUM_H
#define DECODE_SINGLE_DATUM_H

#include "util.h"
#include "io/streams.h"
#include "data/binary-tree.h"

Datum decode_single_datum(io::InputStream& inputStream, const data::Node<Datum>& tree);

#endif // !DECODE_SINGLE_DATUM_H
