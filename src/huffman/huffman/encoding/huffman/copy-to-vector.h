#ifndef COPY_TO_VECTOR_H
#define COPY_TO_VECTOR_H

#include "io/streams.h"
#include <vector>
#include "util.h"
#include <memory>

std::unique_ptr<std::vector<Datum>> copy_to_vector(io::InputStream& input);

#endif // !COPY_TO_VECTOR_H
